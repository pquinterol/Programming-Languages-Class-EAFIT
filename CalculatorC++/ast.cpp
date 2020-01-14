#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <sstream>
#include <math.h>
#include "calc.h"
// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   



AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}




UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}




AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

TimNode::TimNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

DivNode::DivNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

ModNode::ModNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

PowNode::PowNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

StNode::StNode(AST* ar):
   AST(),
   subTree(ar)
{}

ReNode::ReNode():
   AST()
{}

PlusNode::PlusNode(AST* _sub):
  AST(),
  sub(_sub)
{}

MinusNode::MinusNode(AST* _sub):
  AST(),
  sub(_sub)
{}


NumNode::NumNode(double n) :
   AST(),
   val(n)
{}

VarNode::VarNode(std::string _var,AST* _value):
  AST(),
  var(_var),
  subtree(_value)
{
  calc->variables[var]=subtree->evaluate();
}

LetterNode::LetterNode(std::string _var):
   var(_var)
{
   value = calc->variables[var];
}



double AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

double SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

double TimNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

double DivNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

double ModNode::evaluate(){
  
  double l,r;
  l = getLeftSubTree()->evaluate();
  r = getRightSubTree()->evaluate();

  if(r>l)return 0.0;
  else{
    double div = l/r;
    int d = div;
    return l-d*r;
  }
}

double PowNode::evaluate(){

  return pow(getLeftSubTree()->evaluate(),getRightSubTree()->evaluate());

}

double StNode::evaluate() {
  double i = subTree->evaluate();
  calc->store(i);
  return i;
}

double ReNode::evaluate() {
  double i = calc->recall();
  return i;
}

double PlusNode::evaluate() {
  double i = sub->evaluate() + calc->recall();
  calc->store(i);
  return i;
}

double MinusNode::evaluate() {
  double i = calc->recall() - sub->evaluate();
  calc->store(i);
  return i;
}

double NumNode::evaluate() {
   return val;
}

double VarNode::evaluate() {
  return calc->variables[var];
}

double LetterNode::evaluate()  {
  return value;
}
