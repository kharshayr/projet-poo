#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "headers.hpp"

using namespace std;


int main() {
	CPU cpu1("CPU1.txt");
	BUS bus1("BUS1.txt",&cpu1);
	MEMORY mem1("MEMORY1.txt",&bus1);
	DISPLAY disp1("DISPLAY1.txt",&mem1);
	PROGRAMME prg;
	prg.load("PROG.txt");
	
}
