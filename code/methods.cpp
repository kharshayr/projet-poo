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

PROGRAMME::PROGRAMME(){
	POINTER=0;
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

PLATFORM::PLATFORM(){
	platform=1;
}

void PLATFORM::load(string file){
	ifstream inFile(file,ios::out);
	string comp_path;
	string x;
	std::vector<string> paths;
	if (!inFile) {
		cerr << "Unable to open file " << file << endl;
		return;
	}
	while (inFile >> x){
		paths.push_back(x);
	}
	while (!paths.empty()){
		comp_path=paths.front();
		ifstream inFile(comp_path,ios::out);
		inFile >> x;
		component* temp=NULL;
		if (x=="TYPE:"){
			inFile >> x;
			if (x=="CPU"){
				CPU* cpu=new CPU(comp_path);
				component_map[cpu->LABEL]=cpu;
				list_labels.push_back(cpu->LABEL);
			}
			else if (x=="MEMORY"){
				MEMORY* mem_temp=new MEMORY(comp_path,temp);
				MEMORY* mem=new MEMORY(comp_path,component_map[mem_temp->get_source()]);
				component_map[mem->LABEL]=mem;
				list_labels.push_back(mem->LABEL);
			}
			else if (x=="DISPLAY"){
				DISPLAY* display_temp=new DISPLAY(comp_path,temp);
				DISPLAY* display=new DISPLAY(comp_path,component_map[display_temp->get_source()]);
				component_map[display->LABEL]=display;
				list_labels.push_back(display->LABEL);
			}
			else if (x=="BUS"){
				BUS* bus_temp=new BUS(comp_path,temp);
				BUS* bus=new BUS(comp_path,component_map[bus_temp->get_source()]);
				component_map[bus->LABEL]=bus;
				list_labels.push_back(bus->LABEL);
			}
			else {
				cout << "Component type not valid for " << x << endl;
			}
		}
		else{
			cout << "File path invalid for " << comp_path << endl;
		}
		paths.erase(paths.begin());
	}
}

void PLATFORM::simulate(){
	std::vector<string> labels=list_labels;
	while (!labels.empty()){
		component_map[labels.front()]->simulate();
		labels.erase(labels.begin());
	}
}
