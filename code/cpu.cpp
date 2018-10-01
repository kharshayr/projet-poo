#include "headers.hpp"

CPU::CPU(string file) {
	ifstream inFile(file,ios::out);
	string x;
	ACTIVE_CORE=0;
	if (!inFile) {
		cerr << "Unable to open file for CPU" << endl;
		return;
	}
	else {
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;
			}
			else if ("LABEL:"==x) {
				inFile >> x;
				LABEL=x;
			}
			else if ("CORES:"==x) {
				inFile >> x;
				CORES=stoi(x);
			}
			else if ("FREQUENCY:"==x) {
				inFile >> x;
				FREQUENCY=stoi(x);
			}
			else if ("PROGRAM:"==x) {
				inFile >> x;
				PROGRAM=x;
			}

			else{
				cout << "Etiquette " << x << " non reconnue pour CPU"<< endl;
			}
		}
	}
}

void CPU_Register::appendValue(double value) {
	FIFO.push(value);
}

double CPU_Register::readValue() {
		double x = FIFO.front();
		FIFO.pop();
		return x;
}

bool CPU_Register::isEmpty() {
	return FIFO.empty();
}

void CPU::simulate() {
	prg.load("PROG.txt");
	printCPU();
	while(ACTIVE_CORE!=CORES) {
		while(!prg.isDone()) {
			INSTRUCTION inst = prg.compute();
			inst.printInst();
			cout << "Result : " << inst.computeInst();
			for(int i = 0; i<FREQUENCY; i++) {
				REG.appendValue(inst.computeInst());
			}
		}
		prg.reset();
		ACTIVE_CORE++;
	}
	ACTIVE_CORE = 0;
}

void CPU::printCPU() {
 cout << "CPU Label : " << LABEL << endl;
 cout << "Total number of cores : " << CORES << endl;
 cout << "Active core : " << (ACTIVE_CORE + 1) << endl;
 cout << "Frequency : " << FREQUENCY << endl;
}

DATA_VALUE CPU::read() {
	bool v = REG.isEmpty() ? false : true;
	return DATA_VALUE(REG.readValue(),v);
}
