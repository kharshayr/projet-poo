#include <list>
#include <iostream>
#include <fstream>
#include "headers.hpp"

using namespace std;

int main() {
	CPU cpu1("CPU1.txt");
	BUS bus1("BUS1.txt");
	MEMORY mem1("MEMORY1.txt");
	DISPLAY disp1("DISPLAY1.txt","c++ c tro bi1");
	cout << cpu1.LABEL << endl << bus1.LABEL << endl << mem1.LABEL << endl << disp1.LABEL <<endl;}
