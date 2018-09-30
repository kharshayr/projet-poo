#include <list>
#include <iostream>
#include <fstream>

using namespace std;

class DATA_VALUE {
public:
  double VALUE;
  bool VALID;
  DATA_VALUE(double value, bool valid);
  ~DATA_VALUE(){};
};

class component {
public:
  string TYPE;
  string LABEL;
//  virtual void simulate();
  virtual DATA_VALUE read(){return DATA_VALUE(0,true);};
};

class INSTRUCTION {
private:
  string OPERATION;
  double OPERANDE1;
  double OPERANDE2;
public:
  INSTRUCTION(string);
  ~INSTRUCTION(){};
  double computeInst();
  void printInst();
};

class PROGRAMME {
private:
  std::vector<INSTRUCTION> LIST_INST;
  int POINTER;
public:
  void printProg();
  INSTRUCTION compute();
  void reset();
  bool isDone();
  void load(string file);
//  PROGRAMME();
//  ~PROGRAMME(){};
};

class CPU_Register {
private:
  std::queue<double> FIFO;
public:
  void appendValue(double value);
  double readValue();
  bool isEmpty();
//  CPU_Register();
//  ~CPU_Register(){};
};

class CPU : public component {
private:
  int CORES;
  int ACTIVE_CORE;
  int FREQUENCY;
  string PROGRAM;
  PROGRAMME prg;
  CPU_Register REG;
public:
  void simulate();
  DATA_VALUE read();
  CPU(string);
  ~CPU(){};
};

class BUS : public component {
private:
  int WIDTH;
  string SOURCE;
  component* pSOURCE;
  queue<DATA_VALUE> pending;
  queue<DATA_VALUE> ready;
  int readNumber;
public:
  string sourceLabel();
  void readyValues();
  void simulate();
  DATA_VALUE read();
  BUS(string,component*);
  ~BUS(){};
};

class MEMORY : public component {
  int SIZE;
  int ACCESS;
  string SOURCE;
public:
  DATA_VALUE read(){return DATA_VALUE(0,true);};
  MEMORY(string file);
  ~MEMORY(){};
};

class DISPLAY : public component {
private:
  int RR;
  string SOURCE;
public:
  DATA_VALUE read(){return DATA_VALUE(0,true);};
  DISPLAY(string,string);
  ~DISPLAY(){};
};
