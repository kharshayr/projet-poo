#include "headers.hpp"

MEM_POINT::MEM_POINT(){
	AGE_RANK=0;
	VALUE=0;
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

DATA_VALUE::DATA_VALUE(double value, bool valid){
	VALUE=value;
	VALID=valid;
}

void DATA_VALUE::print_data(){
	if (VALID){
		cout << "VALUE: " << VALUE << endl;
	}
	else{
		cout << "INVALID DATA" << endl;
	}
}
