/***************************************
 * incl.h 
 *
 * This file contains everything needed
 * for the include functionality of 
 * FHiCL.
 *
 **************************************/
#ifndef incl_h
#define incl_h
#define INCL_DEBUG 1


#include <iostream>
#include <fstream>
#include <stack>
#include <tuple>
#include "locals/antlr4cpp/include/antlr4-runtime/antlr4-runtime.h"

std::stack<std::pair<antlr4::CharStream*, int>> filestack;

void setInputCharStream(antlr4::CharStream *input){
  reset();
  _input = input;
}

inline
void checkincl(antlr4::RuleContext *context){
  std::string filename = getText();
  filename = filename.substr(10, filename.size()-12); // get only the stuff inside the ""
  std::cout << "Found include statement: " << filename << std::endl;
  std::cout << _input->index() << " in file" << _input->getSourceName() <<std::endl;
  
  std::ifstream new_file;
  new_file.open(filename);
  if(!new_file){  
    std::cerr << "Failed to open file " << filename <<std::endl;
    exit(1);
  }
  antlr4::ANTLRInputStream new_source(new_file);
  int pos = _input->index();
  antlr4::CharStream *curr_stream = _input;
 
  filestack.push(std::make_pair(_input, pos));
  
  //setInputCharStream(&new_file);
  reset();
  
  if(INCL_DEBUG) std::cout << "Is this causing the fault?" << std::endl;
  _input = dynamic_cast<antlr4::CharStream*>(&new_source);

   if(INCL_DEBUG) std::cout << _input << std::endl;   
}

void checkstack(){
  if(!filestack.empty()){
    
  }
  std::cout<< "At end of file in file: " <<  _input->getSourceName() << std::endl;
}
//incl_h
#endif
