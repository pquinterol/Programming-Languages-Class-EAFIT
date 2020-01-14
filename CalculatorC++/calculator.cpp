#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>


Calculator::Calculator():
   memory(0)
{}

double Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr),variables);
   
   AST* tree = parser->parse();
   
   //cout << "arbol: " << tree->mostrar() << endl; 

   double result = tree -> evaluate();

   store(result); // DONE BY ME
   
   delete tree;
   delete parser;
   return result;
}

/*bool Calculator::isVariable(string str){

  size_t ind = str.find("let ");
  if(ind!=std::string::npos && ind==1){
    string n = str.substr(ind+2);
    size_t equal = str.find("=");
    if(equal!=std::string::npos){

    }
  }

}
*/

void Calculator::store(double val) {
   memory = val;
}

double Calculator::recall() {
   return memory;
}

void Calculator::addVariable(string name, double val){
  variables[name]=val;
}

double Calculator::hasVar(string name){
  return variables.count(name);
}
