#include "headers.hpp"

DISPLAY::DISPLAY(string file, component* source) {
	ifstream inFile(file,ios::out);
	DISP="";
	reading=false;
	string x;
	COUNTER=1;
	if (!inFile) {
		cerr << "Unable to open file for DISPLAY" << endl;
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
	pSOURCE = source;
}

string DISPLAY::sourceLabel() {
	return (*pSOURCE).LABEL;
}

void DISPLAY::simulate(){
	DATA_VALUE dv = (*pSOURCE).read();
	if (COUNTER!=RR){
		COUNTER+=1;
		reading=false;
		return;
	}
	else if (reading==false && COUNTER==RR){
		reading=true;
	}
	else if (reading==true && dv.VALID){
		DISP=DISP+" "+to_string(dv.VALUE);}
	else if (reading==true && !dv.VALID){
		cout << "Ceci est une ligne de " << LABEL << " : " << DISP << endl;
		DISP.clear();
		COUNTER=1;
		reading=false;
	}
}

bool DISPLAY::get_state(){
	return reading;
}
