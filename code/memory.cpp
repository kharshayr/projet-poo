#include "headers.hpp"

MEMORY::MEMORY(string file, component* source) {
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
	pSOURCE = source;
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
	MEM_CONTENT[add].VALUE= (*pSOURCE).read().VALUE;
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

void MEM_POINT::print_mem_point(){
	cout << "[value: " << VALUE << ",rank: " << AGE_RANK << "]" << endl;
}

void MEMORY::print_mem_content(){
	for (int i=0;i<SIZE;i++){
		MEM_CONTENT[i].print_mem_point();
	}
}

string MEMORY::sourceLabel() {
	return (*pSOURCE).LABEL;
}

string MEMORY::get_source(){
	return SOURCE;
}
