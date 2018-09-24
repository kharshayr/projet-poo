#include <list>
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

    class BUS : public component {
    public:
      int WIDTH;
      string SOURCE;
      BUS(string);
      ~BUS(){};};

      class MEMORY : public component {
      public:
        int SIZE;
        int ACCESS;
        string SOURCE;
        MEMORY(string file);
        ~MEMORY(){};};

        class DISPLAY : public component {
        public:
          int RR;
          string SOURCE;
          DISPLAY(string,string);
          ~DISPLAY(){};};

          class INSTRUCTION {
          public:
            string OPERATION;
            double OPERANDE1;
            double OPERANDE2;
            ~INSTRUCTION(){};
          };

          class PROGRAMME {
          public:
            std::list<INSTRUCTION> LIST_INST;
            PROGRAMME(string);
            ~PROGRAMME(){};};

            class DATA_VALUE {
            	public:
            		double VALUE;
            		bool VALID;};

            class CPU_Register {
            	public:
            		std::list<int> VALUE;
            		bool EMPTY;};
