#include <string.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string eval(string in_str) {
  return in_str;
}

/**
 * A prints pigeon-lisp's arguments
 */
void print_help() {
  cout << "USAGE: " << endl;
  cout << "\t-i <filename> : Executes file specified" << endl;
}

int main(int argc, char* argv[]) {
  // Every argument to pigeon-lisp follows "-flag <value>". As such, there will
  // always be an odd number of arguments to the program
  if (argc % 2 != 1) {
    print_help();
    return 1;
  }

  // The stream to get data from. Can either be std::cin or a std::ifstream
  istream* stream = &cin;

  // Argument parsing
  for (int i = 1; i < argc; i += 2) {
    if (strcmp(argv[i], "-i") == 0 && stream == &cin) {
      stream = new ifstream(argv[i + 1]);
    }
  }

  // Main loop
  while(true) {
    if (stream == &cin) cout << "pigeon-lisp> ";

    // Read
    string line;
    if (!getline(*stream, line)) break;

    // Eval
    auto e = eval(line);
    
    // Print
    cout << e << endl;
  }

  return 0;
}