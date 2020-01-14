#ifndef calculator_h
#define calculator_h

#include <string>
#include <map>
 
using namespace std;


class Calculator {
 public:

   map<string, double>variables;
   map<string, double>::iterator it;
   Calculator();

   double eval(string expr);
   void store(double val);
   double recall();
   void addVariable(string name, double val);
   double hasVar(string name);
   //bool isVariable(string str);

 private:
   double memory;
};

extern Calculator* calc;

#endif

