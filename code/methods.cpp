#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "headers.hpp"

using namespace std;

CPU:: CPU(string file) {
	ifstream inFile(file,ios::out);
	string x;
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

BUS::BUS(string file, component* source) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for BUS" << endl;
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
			else if ("WIDTH:"==x) {
				inFile >> x;
				WIDTH=stoi(x);
			}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;
			}
			else{
				cout << "Etiquette " << x << " non reconnue pour BUS"<< endl;
			}
		}
		readNumber = 0;
		pSOURCE = source;
	}
}



MEMORY::MEMORY(string file) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for MEMORY" << endl;
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
			else if ("SIZE:"==x) {
				inFile >> x;
				SIZE=stoi(x);
			}
			else if ("ACCESS:"==x) {
				inFile >> x;
				ACCESS=stoi(x);
			}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;
			}
			else{
				cout << "Etiquette " << x << " non reconnue pour MEMORY"<< endl;
			}
		}
	}
}



DISPLAY::DISPLAY(string file,string label) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for DISPLAY" << endl;
	}
	else {
		LABEL=label;
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;
			}
			else if ("REFRESH:"==x) {
				inFile >> x;
				RR=stoi(x);
			}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;
			}
			else{
				cout << "Etiquette " << x << " non reconnue pour DISPLAY"<< endl;
			}
		}
	}
}


INSTRUCTION::INSTRUCTION(string line){
	istringstream iss(line);
	string x;
	iss >> x;
	if ("NOP"==x) {
		OPERATION=x;
	}
	else{
		OPERATION=x;
		if (iss >> x)
		OPERANDE1=stod(x);
		if (iss >> x)
		OPERANDE2=stod(x);
	}
}

/*PROGRAMME::PROGRAMME(string file){
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for LIST_INST" << endl;
	}
	else {
		while (getline(inFile,x)){
			INSTRUCTION inst(x);
			LIST_INST.push_back(inst);

		}
	}
}*/

void PROGRAMME::load(string file){
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for LIST_INST" << endl;
	}
	else {
		while (getline(inFile,x)){
			INSTRUCTION inst(x);
			LIST_INST.push_back(inst);

		}
	}
}

void PROGRAMME::printProg() {
	for( vector<INSTRUCTION>::iterator i = LIST_INST.begin(); i!= LIST_INST.end(); i++) {
		(*i).printInst();
	}
}

INSTRUCTION PROGRAMME::compute() {
	if (POINTER != (int)LIST_INST.size()) {
		INSTRUCTION inst = LIST_INST[POINTER];
		POINTER++;
		return inst;
	}
	else {
		return INSTRUCTION("NOP");
	}
}

void PROGRAMME::reset(){
	POINTER = 0;
}

bool PROGRAMME::isDone() {
	return (POINTER != (int)LIST_INST.size()) ? false : true;
}

void INSTRUCTION::printInst() {
	if (OPERATION=="NOP") {
		cout << OPERATION << endl;
	}
	else {
		cout << OPERATION << " " << OPERANDE1 << " "<< OPERANDE2<< endl;
	}
}

double INSTRUCTION::computeInst() {
	if (OPERATION=="NOP") return 0;
	else if (OPERATION=="ADD") return OPERANDE1 + OPERANDE2;
	else if (OPERATION=="DIV") return OPERANDE1/OPERANDE2;
	else if (OPERATION=="MUL") return OPERANDE1*OPERANDE2;
	else return 0;
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
	while(ACTIVE_CORE!=CORES) {
		while(!prg.isDone()) {
			INSTRUCTION inst = prg.compute();
			for(int i = 0; i<FREQUENCY; i++) {
				REG.appendValue(inst.computeInst());
			}
		}
		prg.reset();
		ACTIVE_CORE++;
	}
	ACTIVE_CORE = 0;
}

DATA_VALUE::DATA_VALUE(double value, bool valid){
	VALUE=value;
	VALID=valid;
}

DATA_VALUE CPU::read() {
	bool v = REG.isEmpty() ? false : true;
	return DATA_VALUE(REG.readValue(),v);
}

string BUS::sourceLabel() {
	return (*pSOURCE).LABEL;
}

void BUS::readyValues() {
	while (!pending.empty()) {
		ready.push(pending.front());
		pending.pop();
	}
}

void BUS::simulate(){
	readyValues();
	for(int i = 0; i < WIDTH; i++){
		DATA_VALUE dv = pSOURCE->read();
		if(dv.VALID == false) return;
		else pending.push(dv);
	}
}

DATA_VALUE BUS::read() {
	if (!ready.empty()) {
		DATA_VALUE dv1 = ready.front();
		ready.pop();
		return dv1;
	}
	else {
		DATA_VALUE dv2(0,false);
		return dv2;
	}
	readNumber++;
}
