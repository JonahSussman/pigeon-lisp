#include <string.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


namespace reader {
struct Reader {
  vector<string> tokens;
  int pos;

  Reader(vector<string> tokens) : tokens(tokens), pos(0) { }
  bool end() { return pos >= tokens.size(); }
  string peak() { return tokens[pos]; }
  string next() { return tokens[pos++]; }
};

vector<string> tokenize(string s) {
  regex e(R"((~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"?|;.*|[^\s\[\]{}('"`,;)]*))");
  regex_token_iterator<string::iterator> rend, iter(s.begin(), s.end(), e);

  vector<string> result;
  while(iter != rend) {
    string r = *iter;
    if (r.length()) result.push_back(r);
    *iter++;
  }

  return result;
}

PType read_form(Reader reader);

PType read_list(Reader reader) {
  PList list;
  while ()
}

PType read_form(Reader reader) {
  auto token = reader.next();
  return (token == "(") ? read_list() : read_atom();
}

void read_str() {
  auto reader = Reader(tokenize(str));
  read_form(reader);
}
}

string read(string str) {
  return str;
}

string eval(string str) {
  return str;
}

string print(string str) {
  return str;
}

// This could all be in one line, but expanded for clarity
string rep(string line) {
  auto read_result  = read(line);
  auto eval_result  = eval(read_result);
  auto print_result = print(eval_result);

  return print_result;
}

/**
 * A prints pigeon-lisp's arguments
 */
void print_help() {
  cout << "USAGE: " << endl;
  cout << "\t-i <filename> : Executes file specified" << endl;
}

int main(int argc, char* argv[]) {
  // Every argument to pigeon-lisp follows "-<flag> <value>". As such, there
  // will always be an odd number of arguments to the program
  if (argc % 2 != 1) {
    print_help();
    return 1;
  }

  // The stream to get data from. Can either be std::cin or a std::ifstream
  istream* in_stream  = &cin;
  ostream* out_stream = &cout;

  // Argument parsing
  for (int i = 1; i < argc; i += 2) {
    if (strcmp(argv[i], "-i") == 0 && in_stream  == &cin)
      in_stream = new ifstream(argv[i + 1]);

    if (strcmp(argv[i], "-o") == 0 && out_stream == &cout)
      out_stream = new ofstream(argv[i + 1]);
  }

  // Main loop
  while(true) {
    if (in_stream == &cin) cout << "pigeon-lisp> ";

    // Read
    string line;
    if (!getline(*in_stream, line)) {
      if (!in_stream->eof()) {
        cout << "Input stream failure" << endl;
      }

      break;
    }

    cout << rep(line) << endl;
  }

  return 0;
}