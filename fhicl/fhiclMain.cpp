//Defining debug flags
#define debug 1
#define debug_visitor 1
#define debug_paramset 1
#define debug_extendedval 1
#define INCL_debug 1


#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

#include "locals/antlr4cpp/include/antlr4-runtime/antlr4-runtime.h"
#include "fhicl/fhiclcppantlr/fhiclLexer.h"
#include "fhicl/fhiclcppantlr/fhiclParser.h"
#include "fhiclTestVisitor.h"

//#include "paramset.h"

using namespace antlr4;
using namespace fhiclcppantlr;


int main(int argc, char *argv[]){
  if(argc != 2){
    std::cout << "USAGE: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  
  std::ifstream fhiclSource(argv[1]);
  
  if( !fhiclSource.is_open() ){
    std::cout << "Can't open " << argv[1] << std::endl;
    return 1;
  }
  ANTLRInputStream input(fhiclSource);
  fhiclLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  
  tokens.fill();
  
  if(debug){
    for(auto token : tokens.getTokens()){
      std::cout << token->toString() << std::endl;
    }
  }

  fhiclParser parser(&tokens);
  fhiclParser::ParamsetContext* tree = parser.paramset();

  if(debug) std::cout << tree->toStringTree(&parser) << std::endl;
  /*
  tree::ParseTree *to_walk = parser.paramset();
  fhiclListenerTest listener;
  std::cout << "Listening to the tree" << std::endl;
  //tree::ParseTreeWalker::DEFAULT.walk(&listener, to_walk);
  tree::ParseTreeWalker walker; //= new tree::ParseTreeWalker();
  walker.walk(&listener, to_walk);
  */
  fhiclTestVisitor visitor;
  visitor.visitParamset(tree);


  fhiclSource.close();
  return 0;
}
