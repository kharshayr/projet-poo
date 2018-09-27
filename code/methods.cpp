#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include "headers.hpp"

using namespace std;

CPU:: CPU(string file) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for CPU" << endl;
		return;}
	else {
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;}
			else if ("LABEL:"==x) {
				inFile >> x;
				LABEL=x;}
			else if ("CORES:"==x) {
				inFile >> x;
				CORES=stoi(x);}
			else if ("FREQUENCY:"==x) {
				inFile >> x;
				FREQUENCY=stoi(x);}
			else if ("PROGRAM:"==x) {
				inFile >> x;
				PROGRAM=x;}
			else{
				cout << "Etiquette " << x << " non reconnue pour CPU"<< endl;}}}}

BUS::BUS(string file) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for BUS" << endl;}
	else {
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;}
			else if ("LABEL:"==x) {
				inFile >> x;
				LABEL=x;}
			else if ("WIDTH:"==x) {
				inFile >> x;
				WIDTH=stoi(x);}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;}
			else{
				cout << "Etiquette " << x << " non reconnue pour BUS"<< endl;}}}}



MEMORY::MEMORY(string file) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for MEMORY" << endl;}
	else {
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;}
			else if ("LABEL:"==x) {
				inFile >> x;
				LABEL=x;}
			else if ("SIZE:"==x) {
				inFile >> x;
				SIZE=stoi(x);}
			else if ("ACCESS:"==x) {
				inFile >> x;
				ACCESS=stoi(x);}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;}
			else{
				cout << "Etiquette " << x << " non reconnue pour MEMORY"<< endl;}}}}



DISPLAY::DISPLAY(string file,string label) {
	ifstream inFile(file,ios::out);
	string x;
	if (!inFile) {
		cerr << "Unable to open file for DISPLAY" << endl;}
	else {
		LABEL=label;
		while (inFile >> x){
			if ("TYPE:"==x) {
				inFile >> x;
				TYPE=x;}
			else if ("REFRESH:"==x) {
				inFile >> x;
				RR=stoi(x);}
			else if ("SOURCE:"==x) {
				inFile >> x;
				SOURCE=x;}
			else{
				cout << "Etiquette " << x << " non reconnue pour DISPLAY"<< endl;}}}}


/*PROGRAMME::PROGRAMME(string file) {
	ifstream inFile(file,ios::out);
	string x;
	INSTRUCTION I;
	if (!inFile) {
		cerr << "Unable to open file for LIST_INST" << endl;}
	else {
		while (inFile >> x){
			if ("NOP"==x) {
				I.OPERATION=stod(x);}
			else{
				I.OPERATION=x;
				inFile >> x;
				I.OPERANDE1=stod(x);
				inFile >> x;
				I.OPERANDE2=stod(x);}
			LIST_INST.push_back(I);}}}*/


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
