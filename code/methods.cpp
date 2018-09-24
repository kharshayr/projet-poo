#include <list>
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
