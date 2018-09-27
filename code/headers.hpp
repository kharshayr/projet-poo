#include <list>
#include <iostream>
#include <fstream>

using namespace std;

class component {
public:
  string TYPE;
  string LABEL;
  /*virtual void simulate();
  virtual void read();*/
};

class INSTRUCTION {
private:
  string OPERATION;
  double OPERANDE1;
  double OPERANDE2;
public:
  INSTRUCTION(string);
  ~INSTRUCTION(){};
  void computeInst();
  void printInst();
};

class PROGRAMME {
private:
  std::list<INSTRUCTION> LIST_INST;
public:
  void printProg();
  PROGRAMME(string);
  ~PROGRAMME(){};
};

class CPU_Register {
private:
  std::queue<double> FIFO;
  bool EMPTY;
public:
  CPU_Register();
  ~CPU_Register(){};
  void appendValue(double value);
  double readValue();
  bool isEmpty();
};

class CPU : public component {
private:
  int CORES;
  int ACTIVE_CORES;
  int FREQUENCY;
  string PROGRAM;
//  PROGRAMME PROG;
//  CPU_Register REG;
public:
  CPU(string);
  ~CPU(){};
};

class BUS : public component {
private:
  int WIDTH;
  string SOURCE;
public:
  BUS(string);
  ~BUS(){};
};

class MEMORY : public component {
  int SIZE;
  int ACCESS;
  string SOURCE;
public:
  MEMORY(string file);
  ~MEMORY(){};
};

class DISPLAY : public component {
private:
  int RR;
  string SOURCE;
public:
  DISPLAY(string,string);
  ~DISPLAY(){};
};

class DATA_VALUE {
private:
  double VALUE;
  bool VALID;
};
