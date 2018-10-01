#include <list>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

class DATA_VALUE {
public:
  double VALUE;
  bool VALID;
  DATA_VALUE(double value, bool valid);
  ~DATA_VALUE(){};
  void print_data();

};

class component {
public:
  string TYPE;
  string LABEL;
  virtual void simulate() =0;
  virtual DATA_VALUE read() =0;
  //component();
  virtual ~component(){};
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
  ~PROGRAMME(){};
};

class CPU_Register {
private:
  std::queue<double> FIFO;
public:
  void appendValue(double value);
  double readValue();
  bool isEmpty();
//  CPU_Register();
  ~CPU_Register(){};
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

class MEM_POINT {
private:
  friend class MEMORY;
  int AGE_RANK;
  double VALUE;
public:
  void print_mem_point();
  MEM_POINT();
  ~MEM_POINT(){};
};

class MEMORY : public component {
private:
  int SIZE;
  int ACCESS;
  int COUNTER;
  int ADD_WR;
  std::vector<MEM_POINT> MEM_CONTENT;
  string SOURCE;
  component* pSOURCE;
  int search_max_rank();
  void rank_downgrade();
  int search_write();
  int search_read();
public:
  DATA_VALUE read();
  string sourceLabel();
  void print_mem_content();
  void simulate();
  MEMORY(string file, component* source);
  ~MEMORY(){};
};

class DISPLAY : public component {
private:
  int RR;
  int COUNTER;
  bool reading;
  string SOURCE;
  string DISP;
  component* pSOURCE;
public:
  DATA_VALUE read(){return DATA_VALUE(0,true);};
  bool get_state();
  string sourceLabel();
  void simulate();
  DISPLAY(string file, component* source);
  ~DISPLAY(){};
};
