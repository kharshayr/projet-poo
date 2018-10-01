#include "headers.hpp"

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

void BUS::printBus(){
	cout << "-----------------------------------------------------------" << endl;
	cout << "BUS Label : " << LABEL << endl;
	cout << "Nmber of accesses : " << readNumber << endl;
}

void BUS::simulate(){
	readyValues();
	for(int i = 0; i < WIDTH; i++){
		DATA_VALUE dv = pSOURCE->read();
		if(dv.VALID == false) return;
		else pending.push(dv);
	}
	printBus();
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

string BUS::get_source(){
	return SOURCE;
}
