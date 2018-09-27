#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "headers.hpp"

using namespace std;


int main() {
	CPU cpu1("CPU1.txt");
	BUS bus1("BUS1.txt");
	MEMORY mem1("MEMORY1.txt");
	DISPLAY disp1("DISPLAY1.txt","c++ c tro bi1");
	PROGRAMME prg("PROG.txt");
	prg.printProg();
}
