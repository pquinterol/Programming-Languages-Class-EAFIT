
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>
#include "calcex.h"
#include "calculator.h"

using namespace std;

Calculator* calc;

void getCommand(int i, char* command[]);
void getVariable(char **env);
void setVariable(string str);

void getCommand(int i,char* command[]){

string com,var;
bool has_e =false;

  for(int j = 0; j < i ;j++){

    com = command[j];

    if(com.compare("-v")==0 && has_e){
       var=command[j];
       setVariable(var);
    }else if(com.compare("-e")) {
       has_e=true;
    }

  }
}

void setVariable(string str){
  
  string var;
  double num;
  size_t equ = str.find("=");

  var = str.substr(0,equ);
  num = atof(str.substr(equ+1).c_str());

  if(calc->hasVar(var)!=0){
    calc->addVariable(var, num);
  }
}

void getVariable(char **env){

  for(int i = 0; env[i]; i++){
    if(strncmp(env[i],"CALCVAR",7)==0){
      string exp = env[i];
      size_t equ = exp.find("=");
      string var = exp.substr(7,equ-7);
      double val = atof(exp.substr(equ+1).c_str());

      calc->addVariable(var,val);
    }
  }

}

void fileMode(string path){

  ifstream file;
  string data;

    file.open(path,ios::in);

    while(file.fail()){

       std::cout<<"Ubicacion o archivo invalido. Digite de nuevo"<<endl;
       getline(cin,path);
       file.open(path,ios::in);

    }

    //calc = new Calculator();

    //cin.clear();
    //cin.ignore();
    getline(file,data);

    while(!file.eof()){
       try {
            getline(file, data);

            if(data.compare("")!=0 && data.compare("\n")!=0){
              double result = calc->eval(data);

              cout << "= " << result << endl;
            }
       }
       catch(Exception ex) {
          cout << "* " << endl;
       }
    }

    file.close();
    
    delete calc;

}

void interactiveMode(){

  string line;
 
    //calc = new Calculator();

    while(1){
       try {
            cout << "> ";
            getline(cin, line);

            double result = calc->eval(line);

            cout << "= " << result << endl;
       }
       catch(Exception ex) {
          cout << "* " << endl;
       }
    }
    
    delete calc;

}

int main(int argc, char* argv[], char **env) {

  calc = new Calculator();

  getVariable(env);
  getCommand(argc, argv);

  string decision;

  cout<<"Digite el tipo de modo en el que quiere usar la calculadora:     interactive  o  file."<<endl;

  cin>>decision;

  while(decision.compare("file")!=0 && decision.compare("interactive")!=0){

    cout<<"Digite un modo valido. Vuelva a ingresar el modo:     ";
    cin.clear();
    cin>>decision;

  }

  if(decision.compare("file")==0){
    system("cls");
    cout<<"NOTA:\nSi desea elevar, multiplicar, dividir o modulo por un numero negativo debe meterlo dentro de ()"<<endl;
    cout<<"\n\n          Modo de Lectura de Archivo\n\n"
    <<"Ingrese la direccion del archivo   ";
    cin.clear();
    cin>>decision;

    fileMode(decision);

  }else if(decision.compare("interactive")==0){
    cin.clear();
    cin.ignore();
    system("cls");
    cout<<"NOTA:\nSi desea elevar, multiplicar, dividir o modulo por un numero negativo debe meterlo dentro de parentesis \"()\""<<endl;

    cout<<"\n\n          Modo Interactivo"<<endl;
    interactiveMode();

  }else{
    cout<<"HPTA"<<endl;
  }

  system("pause");
}
   
   