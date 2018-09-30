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
	MEMORY mem1("MEMORY1.txt");
	DISPLAY disp1("DISPLAY1.txt","c++ c tro bi1");
	PROGRAMME prg;
	prg.load("PROG.txt");
	prg.printProg();

	// Filling up memories
	for (int i=0;i<300;i++){ //Simulation of 300 cycles
		mem1.data_in=(i+1)/3;
		mem1.simulate();
	}
	// Waiting for display to be ready to get values from memory
	DATA_VALUE mem_data=mem1.read();
	disp1.data_in=mem_data;
	while (!disp1.get_state()){
		disp1.simulate();
	}
	while (disp1.get_state()){
		disp1.data_in=mem_data; // Link between components
		disp1.simulate(); // We store the value
		mem_data=mem1.read(); // Read in the memory
	}
}
