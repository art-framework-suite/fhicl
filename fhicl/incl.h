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

#ifndef INCL_DEBUG
#define INCL_DEBUG 0
#endif
#ifndef LEXER_INCL
#define LEXER_INCL 0 
// LEXER_INCL is 1 for lexer, 0 for visitor includes
#endif
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <tuple>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#include "antlr4cpp/include/antlr4-runtime/antlr4-runtime.h"
#pragma GCC diagnostic pop

std::stack<std::pair<antlr4::CharStream*, int>> filestack;

void setInputCharStream(antlr4::CharStream *input){
  reset();
  _input = input;
}

inline
void checkincl(antlr4::RuleContext* context){
  if(LEXER_INCL){
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
    //antlr4::CharStream *curr_stream = _input;
 
    filestack.push(std::make_pair(_input, pos));
  
    //setInputCharStream(&new_file);
    //errors.clear();
    this->reset();
    if(INCL_DEBUG) std::cout << context << std::endl;
    if(INCL_DEBUG) std::cout << "Is this causing the fault?" << std::endl;
    _input = dynamic_cast<antlr4::CharStream*>(&new_source);
    reset();
  
    if(INCL_DEBUG) std::cout << _input << std::endl;   
  }
}
inline
void changeline(antlr4::RuleContext* context){
  if(context) {}
  std::string lineinfo = getText();
  size_t ind = lineinfo.find(' ') + 1;
  lineinfo = lineinfo.substr(ind, lineinfo.size()-(ind+1));
  ind = lineinfo.find(' ');
  if(ind == std::string::npos){ 
    //this->getInputStream()->name = lineinfo;
    return ;
  } else {
    while(lineinfo[0] == ' '){lineinfo.erase(0,1);}
    if(lineinfo.find(" ")!= std::string::npos){
      
    }  
  }
  std::cout << lineinfo << std::endl;
}

inline
void checkstack(){
  if(!filestack.empty()){
    
  }
  std::cout<< "At end of file in file: " <<  _input->getSourceName() << std::endl;
}
//incl_h
#endif
