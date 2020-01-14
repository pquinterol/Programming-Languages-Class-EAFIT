#ifndef scanner_h
#define scanner_h

#include <iostream>
#include "token.h"

class Scanner {
public:
  Scanner(istream* in);
  ~Scanner();

  Token* getToken();
  void putBackToken();
  int contDots;
 
private:
  Scanner();

  istream* inStream;
  int lineCount;
  int colCount;

  bool needToken;
  bool has_paren;
  Token* lastToken;
};

#endif
  
  

