all:
	g++ -std=c++17 -O2 src/pigeon-lisp.cpp -o bin/pigeon-lisp

debug:
	g++ -std=c++17 -O0 -ggdb src/pigeon-lisp.cpp -o bin/pigeon-lisp