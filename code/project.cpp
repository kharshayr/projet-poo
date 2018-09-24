#include<list>
#include <iostream>
#include <fstream>

using namespace std;

class component {
	public:
		virtual void load(string file);
		virtual void simulate();
		virtual void read();
	};

class CPU : public component {
	public:
		string TYPE;
		string LABEL;
		int CORES;
		int FREQUENCY;
		string PROGRAM;
		void load(string file);};

void CPU:: load(string file) {
	ifstream inFile;
	inFile.open(file,ios::out);
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
		string TYPE;
		string LABEL;
		int WIDTH;
		string SOURCE;
		BUS(string);};

BUS::BUS(string file) {
	ifstream inFile;
	inFile.open(file,ios::out);
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
		string TYPE;
		string LABEL;
		int SIZE;
		int ACCESS;
		string SOURCE;};

class DISPLAY : public component {
	public:
		string TYPE;
		int RR;
		string SOURCE;};

class DATA_VALUE {
	public:
		double VALUE;
		bool VALID;};

class CPU_Register {
	public:
		std::list<int> VALUE;
		bool EMPTY;};

int main() {
	CPU cpu1;
	cpu1.load("CPU1.txt");
}
