#include <list>
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

BUS::BUS(string file) {
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

PROGRAMME::PROGRAMME(string file){
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for VECT_INST" << endl;
	}
	else {
		while (getline(inFile,x)){
			INSTRUCTION inst(x);
			VECT_INST.push_back(inst);

		}
	}
}

void INSTRUCTION::printInst() {
	if (OPERATION=="NOP" || OPERATION=="") {
		cout << OPERATION << endl;
	}
	else
	{
		cout << OPERATION << " " << OPERANDE1 << " "<< OPERANDE2<< endl;
	}
}

void PROGRAMME::printProg() {
	for( vector<INSTRUCTION>::iterator i = VECT_INST.begin(); i!= VECT_INST.end(); i++) {
		(*i).printInst();
	}
}

CPU_Register::CPU_Register(){
	EMPTY = true;
}

void CPU_Register::appendValue(double value) {
	FIFO.push(value);
	EMPTY = FIFO.empty();
}

double CPU_Register::readValue() {
	double x = FIFO.front();
	FIFO.pop();
	EMPTY = FIFO.empty();
	return x;
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
	int min=SIZE;
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
	int min=SIZE;
	for (int i=0;i<SIZE;i++){
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
	}
	else {
		COUNTER=1;
		MEM_POINT temp;
		int add=search_write();
		temp.AGE_RANK=search_max_rank()+1;
		/*temp.VALUE= ???; Comment lier les composants ? */
		MEM_CONTENT[add]=temp;
		if (MEM_CONTENT[add].AGE_RANK==SIZE+1){
			rank_downgrade();
		}
	}
}

DATA_VALUE::DATA_VALUE(){
	VALID=false;
	VALUE=0;
}

DATA_VALUE MEMORY::read(){
	DATA_VALUE value;
	int oldest_index=search_read();
	if (oldest_index!=SIZE){
		value.VALID=true;
		value.VALUE=MEM_CONTENT[oldest_index].VALUE;
		MEM_POINT MEM_CONTENT[oldest_index];
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
