#ifndef parser_h
#define parser_h

#include "ast.h"
#include "scanner.h"
#include <map>

class Parser {
 public:
   Parser(istream* in,map<string,double>& varMap);
   ~Parser();

   AST* parse();

 private:
   map<string,double>* vM;
   AST* prog();
   AST* expr();
   AST* restExpr(AST* e);
   AST* term();
   AST* restTerm(AST* e);
   AST* memOperation(AST* e);
   AST* storable();
   AST* factor();

   Scanner* scan;
};

#endif   
