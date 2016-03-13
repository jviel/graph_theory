main: main.cpp graphtheory.h makefile
	g++ -std=c++11 -g -lgsl -lgslcblas -lm main.cpp -o main

