#include "scanner.h"
#include "calcex.h"
#include <iostream>
#include <string>

using namespace std;

const int numberOfKeywords = 5;

const string keywd[numberOfKeywords] = {
  string("S"), string("R"),string("P"),string("M"),string("C")
};

int isLetter(char c) {
   return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int isDigit(char c, int& contDots) {

  if(contDots<=1){
    if (c >= '0' && c <= '9')
     return 1;
    else if (c == '.'){
      contDots++;
      return 1;
    }else{
      return 0;
    }
  }else{
    throw UnrecognizedToken;
  }

  return 0;
}

int isWhiteSpace(char c) {
  return (c == ' ' || c == '\t' || c == '\n');
}

Scanner::Scanner(istream* in):
  inStream(in),
  lineCount(1),
  colCount(-1),
  needToken(true),
  lastToken(0),
  contDots(0),
  has_paren(false)
{}

Scanner::~Scanner() {
   try {
      delete inStream;
   } catch (...) {}
}

void Scanner::putBackToken() {
   needToken = false;
}

Token* Scanner::getToken() {
   
   if (!needToken) {
      needToken=true;
      return lastToken;
   }

   Token* t;
   int state=0;
   bool foundOne=false;
   char c;
   string lex;
   TokenType type;
   int k;
   int column, line;

   c = inStream->get();
   

   while (!foundOne) {
      colCount++;
      int hasLet = 0;
      int car = c;
      /*cout << "caracter " << car << endl;
      cout << "estado " << state << endl;
      cout << "foundOne " << foundOne << endl;
      */
      switch (state) {
         case 0 : 
            lex = "";
            column=colCount;
            line = lineCount;
            if (isLetter(c)) state=1;
            else if (isDigit(c,contDots)||(c=='-' && (has_paren==true ||column==0))) state=2;
            else if (c=='+') state=3;
            else if (c=='-') state=4;
            else if (c=='*') state=5;
            else if (c=='/') state=6;
            else if (c=='(') state=7;
            else if (c==')') state=8;
            else if (c=='%') state=9;
            else if (c=='^') state=10;
            else if (c=='=') state=11;
            else if (c=='\n') {
               colCount=-1;
               lineCount++;
            }
            else if (isWhiteSpace(c));
            else if (inStream->eof() || c == -1) {
               foundOne=true;
               type=eof;
            }
            else {
               cout << "Unrecognized Token found at line " << line <<
                  " and column " << column << endl;
               throw UnrecognizedToken;
            }
            break;
         case 1 :
            if (isLetter(c) || isDigit(c,contDots)){ state=1;
            has_paren=false;
            break;

            }else {

               for (k=0;k<numberOfKeywords;k++){

                  if (lex == keywd[k]) {
                    foundOne = true;
                    type = keyword;
                    }

                  }
               }
               if (!foundOne) {
                  type = identifier;
                  foundOne = true;
               }
               has_paren=false;
            
            break;
         case 2 :
            if (isDigit(c,contDots)) state=2;
            else {
               type = number;
               foundOne=true;
            }
            has_paren=false;
            break;
         case 3 :
            type = add;
            has_paren=false;
            foundOne = true;
            break;
         case 4 :
            type = sub;
            has_paren=false;
            foundOne = true;
            break;
         case 5 :
            type = times;
            has_paren=false;
            foundOne=true;
            break;
         case 6 :
            type = divide;
            has_paren=false;
            foundOne=true;
            break;
         case 7 :
            type = lparen;
            has_paren=true;
            foundOne=true;
            break;
         case 8 :
            type = rparen;
            has_paren=false;
            foundOne=true;
            break;

         case 9:
           type = module;
           has_paren=false;
           foundOne = true;
           break;

         case 10:
           type = Pow;
           has_paren=false;
           foundOne = true;
           break;

         case 11:
           type = equals;
           //Usamos el booleano has_paren para que a las variable se le pueda asignar numeros negativos
           has_paren = true;
           foundOne = true;
           break;
      }
      
      if (!foundOne) {
        
        /*if(c=='.' && lex==""){
          lex = lex + '0' + c;
        }else{
          lex = lex + c;
        }*/

        if(!isWhiteSpace(c)){
          lex = lex + c;
        }

        if(lex.compare("let")==0 && column == 0){

          type = keyword;
          foundOne = true;

        }

         c = inStream->get();
      }
   }

   contDots = 0;
   

   inStream->putback(c);
   colCount--;
   if (type == number || type == identifier || type == keyword) {
      
      LexicalToken* te = new LexicalToken(type,new string(lex), line, column);
      t = te;
      
   }
   else {
      
      t = new Token(type,line,column);
   }
   
   lastToken = t;
   return t;
}

