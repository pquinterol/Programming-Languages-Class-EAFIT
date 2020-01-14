#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>
#include "calc.h"

Parser::Parser(istream* in,map<string,double>& varMap ) {
   scan = new Scanner(in);
   vM = &varMap;
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return prog();
}

AST* Parser::prog() {
   AST* result = expr();
   Token* t = scan->getToken();//por tercera vez

   if (t->getType() != eof) {
      cout << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;
      throw ParseError;
   }
   

   return result;
}

AST* Parser::expr() {
   return restExpr(term());
}

AST* Parser::restExpr(AST* e) {
   Token* t = scan->getToken();//segundo llamado para la operacion


   if (t->getType() == add) 
      return restExpr(new AddNode(e,term()));

   if (t->getType() == sub)
      return restExpr(new SubNode(e,term()));
    
   
   scan->putBackToken();

   return e;
}




AST* Parser::term() {
   
   return restTerm(storable()); 
}




AST* Parser::restTerm(AST* e) {

  Token* t = scan->getToken();
   
   if (t->getType() == times)
      return restTerm(new TimNode(e,term()));
    
   if (t->getType() == divide)
      return restTerm(new DivNode(e,term()));

   if (t->getType() == module)
      return restTerm(new ModNode(e,term()));

   if (t->getType() == Pow)
      return restTerm(new PowNode(e,term()));
  
   scan->putBackToken();
   return e;
}

AST* Parser::storable() {

   return memOperation(factor());
}

AST* Parser::memOperation(AST* e){

  Token* t = scan->getToken();

  if(t->getType()==keyword){
    if(t->getLex()=="S"){
      return new StNode(e);
    }else if(t->getLex()=="P"){
      return new PlusNode(e);
    }else if(t->getLex()=="M"){
      return new MinusNode(e);
    }else{
      cout<<"Not found \"S\", either \"P\" or \"M\""<<endl;
      throw ParseError;
    }
  }

  scan->putBackToken();
  return e;

}

AST* Parser::factor() {

  Token* t = scan->getToken();

   if (t->getType() == number) {
      istringstream in(t->getLex());
      double val;
      in >> val;
      return new NumNode(val);
   }
   
   if (t->getType() == keyword){

     if(t->getLex() == "R"){

      return new ReNode();

     }else if(t->getLex()=="C"){

       return new StNode(new NumNode(0));

     }else if(t->getLex()=="let"){

       t = scan->getToken();
       string var = t->getLex();
       t = scan->getToken();

       if(t->getType()!=equals){
         cout<<"Missing  \" = \""<<endl;
         throw ParseError;
       }
       return new VarNode(var,expr());
     }
     
   }

   if(t->getType()==identifier){

     map<string,double>::iterator it;

     it=(*vM).find(t->getLex());

     if(it!=(*vM).end()){
        return new LetterNode(t->getLex());
     }else{
       cout<<"Variable no existente"<<endl;
       throw ParseError;
     }
   }

   if(t->getType()==lparen){
     AST* result = expr();
     t= scan->getToken();
     if(t->getType()==rparen){
       return result;
     }else{
       cout<<"Missing \")\""<<endl;
       throw ParseError;
     }
   }

   throw ParseError; 
}
   
