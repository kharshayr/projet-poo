#include<list>
#include <iostream>
#include <fstream>

using namespace std;

class component {
	public:
		string TYPE;
		string LABEL;
		/*virtual void simulate();
		virtual void read();*/};

class CPU : public component {
	public:
		int CORES;
		int FREQUENCY;
		string PROGRAM;
	CPU(string);
	~CPU(){};};

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


class BUS : public component {
	public:
		int WIDTH;
		string SOURCE;
	BUS(string);
	~BUS(){};};

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

class MEMORY : public component {
	public:
		int SIZE;
		int ACCESS;
		string SOURCE;
	MEMORY(string file);
	~MEMORY(){};};

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

class DISPLAY : public component {
	public:
		int RR;
		string SOURCE;
	DISPLAY(string,string);
	~DISPLAY(){};};

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

/*
class INSTRUCTION {
	public:
		string OPERATION;
		string OPERANDE1;
		string OPERANDE2;
	INSTRUCTION(string s
}
*/

class DATA_VALUE {
	public:
		double VALUE;
		bool VALID;};

class CPU_Register {
	public:
		std::list<int> VALUE;
		bool EMPTY;};

int main() {
	CPU cpu1("CPU1.txt");
	BUS bus1("BUS1.txt");
	MEMORY mem1("MEMORY1.txt");
	DISPLAY disp1("DISPLAY1.txt","c++ c tro bi1");
	cout << cpu1.LABEL << endl << bus1.LABEL << endl << mem1.LABEL << endl << disp1.LABEL <<endl;}
