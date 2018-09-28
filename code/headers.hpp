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
  std::vector<INSTRUCTION> VECT_INST;
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

class DATA_VALUE {
private:
  friend class MEMORY;
  double VALUE;
  bool VALID;
public:
  void print_data();
  DATA_VALUE();
  ~DATA_VALUE(){};
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
  int search_max_rank();
  void rank_downgrade();
  int search_add();
  int search_read();
public:
  MEMORY(string file);
  ~MEMORY(){};
  void print_mem_content();
  void simulate();
  DATA_VALUE read();
};

class DISPLAY : public component {
private:
  int RR;
  string SOURCE;
public:
  DISPLAY(string,string);
  ~DISPLAY(){};
};
