#ifndef ast_h
#define ast_h

#include <string>
// using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual double evaluate() = 0;
   //virtual std::string mostrar() = 0;
};



class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};



class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;

 private:
   AST* subTree;
};



class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);
   
   double evaluate();
   //std::string mostrar();

};



class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   double evaluate();
   //std::string mostrar();
};




class TimNode : public BinaryNode {
 public:
   TimNode(AST* left, AST* right);

   double evaluate();
   //std::string mostrar();
};



class DivNode : public BinaryNode {
 public:
   DivNode(AST* left, AST* right);

   double evaluate();
   //std::string mostrar();
};

class ModNode : public BinaryNode {
  public:
  ModNode(AST* left, AST* right);

  double evaluate();
  //std::string mostrar();

};

class PowNode : public BinaryNode {

  public:
    PowNode(AST* left,AST* right);
    double evaluate();
    //std::string mostrar();

};

class VarNode : public AST {

  public:
    VarNode(std::string _var, AST* _value);

    //std::string mostrar();
    double evaluate();

  private:
  std::string var;
  AST* subtree;

};


class StNode : public AST {
 public:
   StNode(AST* sub);

   double evaluate();
   //std::string mostrar();

 private:
   AST* subTree;
};


class ReNode : public AST {
 public:
   ReNode();

   double evaluate();
   //std::string mostrar();

 private:
  double val;
};

class PlusNode : public AST {

  public:
  PlusNode(AST* _sub);
  double evaluate();
  //std::string mostrar();

  private:
  AST* sub;

};

class MinusNode : public AST {

  public:
  MinusNode(AST* _sub);
  double evaluate();
  //std::string mostrar();

  private:
  AST* sub;

};

class LetterNode : public AST {

  public:
    LetterNode(std::string _var);

    double evaluate();
    //std::string mostrar();
  
  private:
    std::string var;
    double value;

};

class NumNode : public AST {
 public:
   NumNode(double n);

   double evaluate();
   //std::string mostrar();

 private:
   double val;
};




#endif

