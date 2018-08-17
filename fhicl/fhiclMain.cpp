//Defining debug flags
#define debug 1
#define debug_visitor 1
#define debug_paramset 1
#define debug_extendedval 1
#define INCL_debug 1
#define LEXER_INCL 0 
// 1 for lexer include, 0 for visitor include

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#pragma GCC diagnostic ignored "-Wattributes"
#include "antlr4cpp/include/antlr4-runtime/antlr4-common.h"
#include "antlr4cpp/include/antlr4-runtime/antlr4-runtime.h"
#include "fhicl/fhiclcppantlr/fhiclLexer.h"
#include "fhicl/fhiclcppantlr/fhiclParser.h"
#include "fhicl/fhiclcppantlr/fhiclVisitor.h"
#include "fhiclTestVisitor.h"
#include "fhiclcpp/intermediate_table.h"
#pragma GCC diagnostic pop
//#include "intermTable.h"

using namespace antlr4;
using namespace fhiclcppantlr;


int main(int argc, char *argv[]){
  if(argc < 2){
    std::cout << "USAGE: " << argv[0] << " <filename> (--inject-\"FHiCL parameter\")*" << std::endl;
    return 1;
  }
  
  std::ifstream fhiclSource(argv[1]);
  
  if( !fhiclSource.is_open() ){
    std::cout << "Can't open " << argv[1] << std::endl;
    return 1;
  }

  
  std::string buff;
  ANTLRInputStream input(fhiclSource);
  if(argc >2){
    buff = input.toString();
    buff.append("#file injected\n");
    buff.append("#line 0\n");
    std::string injection;
    for(int i = 2; i<argc ; i++){
      injection = argv[i];
      injection = injection.substr(9,injection.length());
      injection = injection.substr(0, injection.find('\"'));
      buff.append(injection);
      buff.append("\n");
    }
    if(debug) std::cout << buff << std::endl;
    input = ANTLRInputStream(buff);
  }

  input.name = argv[1];
  fhiclLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  tokens.fill();
  
  if(debug){
    for(auto token : tokens.getTokens()){
      std::cout << token->getTokenSource()->getSourceName() << token->toString() << std::endl;
    }
  }

  fhiclParser parser(&tokens);
  fhiclParser::IntermTableContext* tree = parser.intermTable();

  if(debug) std::cout << tree->toStringTree(&parser) << std::endl;
  if(debug) std::cout << sizeof(*tree) <<std::endl;
  fhiclTestVisitor visitor;
  visitor.visitIntermTable(tree);

 // if(debug) std::cout << tree->toStringTree(parser) << std::endl;
  fhiclSource.close();
  return 0;
}
