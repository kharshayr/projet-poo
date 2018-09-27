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
	PROGRAMME prg("PROG.txt");
	list<INSTRUCTION>::iterator i;
	for( i = prg.LIST_INST.begin(); i!= prg.LIST_INST.end(); ++i)
		if (i->OPERATION=="NOP")
			cout << i->OPERATION << endl;
		else
			cout << i->OPERATION << " " << i->OPERANDE1 << " "<< i->OPERANDE2<< endl;
}
