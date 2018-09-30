#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include "headers.hpp"

using namespace std;

CPU::CPU(string file) {
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

MEM_POINT::MEM_POINT(){
	AGE_RANK=0;
	VALUE=0;
}

MEMORY::MEMORY(string file) {
	COUNTER=1;
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
	for (int i=0;i<SIZE;i++){
		MEM_CONTENT.emplace_back();
	}
}

DISPLAY::DISPLAY(string file,string label) {
	ifstream inFile(file,ios::out);
	DISP="";
	reading=false;
	string x;
	COUNTER=1;
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

int MEMORY::search_max_rank(){
	int max_rank=0;
	for (int i=0;i<SIZE;i++){
		if (MEM_CONTENT[i].AGE_RANK>=max_rank){
			max_rank=MEM_CONTENT[i].AGE_RANK;
		}
	}
	return max_rank;
}

int MEMORY::search_write(){
	int min=0;
	for (int i=0;i<SIZE;i++){
		if (MEM_CONTENT[i].AGE_RANK==0){
			return i;
		}
		if (MEM_CONTENT[i].AGE_RANK<=MEM_CONTENT[min].AGE_RANK){
			min=i;
		}
	}
return min;
}

int MEMORY::search_read(){
	int min=0;
	int i=0;
	while (MEM_CONTENT[min].AGE_RANK==0 && i!=SIZE){ // min initialisation
		min=i;
		i++;
	}
	for (i=0;i<SIZE;i++){
		if (MEM_CONTENT[i].AGE_RANK<=MEM_CONTENT[min].AGE_RANK && MEM_CONTENT[i].AGE_RANK!=0){
			min=i;
		}
	}
	return min;
}

void MEMORY::rank_downgrade(){
	for (int i=0;i<SIZE;i++){
		if (MEM_CONTENT[i].AGE_RANK!=0){
			MEM_CONTENT[i].AGE_RANK-=1;
		}
	}
}

void MEMORY::simulate(){
	if (COUNTER!=ACCESS){
		COUNTER+=1;
		return;
	}
	COUNTER=1;
	int add=search_write();
	MEM_CONTENT[add].AGE_RANK=search_max_rank()+1;
	MEM_CONTENT[add].VALUE=data_in;
	if (MEM_CONTENT[add].AGE_RANK==SIZE+1){
		rank_downgrade();
	}
}

DATA_VALUE MEMORY::read(){
	DATA_VALUE value(0,false);
	int oldest_index=search_read();
	if (MEM_CONTENT[oldest_index].AGE_RANK!=0){
		value.VALID=true;
		value.VALUE=MEM_CONTENT[oldest_index].VALUE;
		MEM_CONTENT[oldest_index].AGE_RANK=0;
		rank_downgrade();
	}
	return value;
}

void DATA_VALUE::print_data(){
	if (VALID){
		cout << "VALUE: " << VALUE << endl;
	}
	else{
		cout << "INVALID DATA" << endl;
	}
}

void MEM_POINT::print_mem_point(){
	cout << "[value: " << VALUE << ",rank: " << AGE_RANK << "]" << endl;
}

void MEMORY::print_mem_content(){
	for (int i=0;i<SIZE;i++){
		MEM_CONTENT[i].print_mem_point();
	}
}

void MEMORY::print_label(){
	cout << SOURCE << endl;
}

void DISPLAY::print_label(){
	cout << SOURCE << endl;
}

void DISPLAY::simulate(){
	if (COUNTER!=RR){
		COUNTER+=1;
		reading=false;
		return;
	}
	else if (reading==false && COUNTER==RR){
		reading=true;
	}
	else if (reading==true && data_in.VALID){
		DISP=DISP+" "+to_string(data_in.VALUE);}
	else if (reading==true && !data_in.VALID){
		cout << "Ceci est une ligne de " << LABEL << " : " << DISP << endl;
		DISP.clear();
		COUNTER=1;
		reading=false;
	}
}

bool DISPLAY::get_state(){
	return reading;
}
