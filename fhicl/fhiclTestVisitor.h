// Generated from /home/mikhails/scratch/mrb-art/build_slf7.x86_64/antlrtest/fhiclcpp_antlr/grammar/fhicl.g4 by ANTLR 4.7.1

#pragma once

#ifndef debug_visitor
#define debug_visitor 1
#endif

#include "antlr4-runtime.h"
#include "fhiclVisitor.h"

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/make_ParameterSet.h"
#include "fhiclcpp/intermediate_table.h"
#include "fhiclcpp/detail/encode_extended_value.h"


#include <stdlib.h>
#include <any>

namespace fhiclcppantlr {

enum value_tag {
  UNKNOWN,  // 0
  TABLE,    // 1
  SEQUENCE, // 2
  STRING,   // 3
  COMPLEX,  // 4
  FLOAT,    // 5
  INT,	    // 6
  HEX,	    // 7
  BIN,	    // 8
  BOOL,	    // 9
  NIL,	    // 10
  NegINF,   // 11
  INF,	    // 12
  SP	    // 13
};

enum protection_tag {
  None,
  Protect_Ignore,
  Protect_Error
};


/**
 * This class provides an empty implementation of fhiclVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  fhiclTestVisitor : public fhiclVisitor {
public:

  virtual antlrcpp::Any visitIntermTable(fhiclParser::IntermTableContext *ctx) {
    if(debug_visitor) std::cout << "Entering Paramset" << std::endl;
    if(ctx->COMM(0)){
      curr_file = ctx->COMM(0)->getSymbol()->getTokenSource()->getSourceName();
    }
    offset = 0;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProlog(fhiclParser::PrologContext *ctx)  {
    if(debug_visitor) std::cout << "Entering Prolog" << std::endl;

    is_prolog = true;
    antlrcpp::Any to_return = visitChildren(ctx);
    is_prolog = false;
    
    if(debug_visitor) std::cout << "Exiting Prolog, returning to normal mode" << std::endl;
    return to_return;
  }

  virtual antlrcpp::Any visitTable(fhiclParser::TableContext *ctx) {
    curr_type = TABLE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRegularEntry(fhiclParser::RegularEntryContext *ctx){
    //~curr_entry;
    //extendedvalue curr_entry;

    curr_type = UNKNOWN;
    curr_prot = None;
    if(ctx->PRO_ERR()) curr_prot = Protect_Error;
    if(ctx->PRO_IGN()) curr_prot = Protect_Ignore;
    
    curr_line= (ctx->ID()->getSymbol()->getLine()+offset);
    curr_loc = curr_file + ":" + std::to_string(curr_line);
    

    antlrcpp::Any to_return = visitChildren(ctx);
    
    if(debug_visitor){
      std::cout << "-------------------------------" << std::endl;
      std::cout <<"ID      |"<< ctx->ID()->getText()  << std::endl;
      std::cout <<"VAL TEXT|"<< ctx->val()->getText() << std::endl;
      if(ctx->PRO_ERR() || ctx->PRO_IGN()) std::cout << "PROTECTED" << std::endl;
      if(ctx->COMM())std::cout <<"COMMENT |"<< ctx->COMM()->getText() << std::endl;
      std::cout <<"LINE    |"<< curr_line << std::endl;
      std::cout <<"POSITION|"<< ctx->ID()->getSymbol()->getCharPositionInLine() << std::endl;
      //if(ctx->getToken()) std::cout << ctx->getToken()->getLine() << std::endl;
      std::cout <<"FULLLINE|"<< ctx->getText() << std::endl;
      std::cout <<"TYPE    |"<< curr_type << std::endl;
      std::cout <<"SOURCE  |"<< curr_file <<std::endl;
      //std::cout << to_return << std::endl;
    }

    // Setup the entry for the config, as if it had no protection
    //curr_entry.set_protection(None, curr_loc);
    //curr_entry.set_val(curr_value, curr_loc);
    //curr_entry.set_type(curr_type, curr_loc);
    //curr_entry.add_info(curr_loc);
    //curr_entry.set_prolog(is_prolog, curr_loc);
    //if(ctx->COMM()) curr_entry.addcomment(ctx->COMM()->getText(), curr_loc);
    config.put(ctx->ID()->getText(), ctx->val()->getText(), is_prolog);
    
    // Now that everything is set, set protection
    //curr_entry.set_protection(curr_prot, curr_loc);

    //config.add(ctx->ID()->getText(), curr_entry);

    return to_return;
  }

  virtual antlrcpp::Any visitEntryFusion(fhiclParser::EntryFusionContext *ctx) {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueAtom(fhiclParser::ValueAtomContext *ctx) {
    return visitChildren(ctx); //ignore, will go to others
  }

  virtual antlrcpp::Any visitValueSequence(fhiclParser::ValueSequenceContext *ctx) {
    curr_type = SEQUENCE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueTable(fhiclParser::ValueTableContext *ctx) {
    curr_type = TABLE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueErased(fhiclParser::ValueErasedContext *ctx) {
    return visitChildren(ctx);
  }
  
  virtual antlrcpp::Any visitValueExternal(fhiclParser::ValueExternalContext *ctx) {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSeq(fhiclParser::SeqContext *ctx) {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntegerAtom(fhiclParser::IntegerAtomContext *ctx) {
    curr_type = INT;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHexAtom(fhiclParser::HexAtomContext *ctx) {
    curr_type = HEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinAtom(fhiclParser::BinAtomContext *ctx) {
    curr_type = BIN;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloatingAtom(fhiclParser::FloatingAtomContext *ctx) {
    curr_type = FLOAT;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComplexAtom(fhiclParser::ComplexAtomContext *ctx) {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolAtom(fhiclParser::BoolAtomContext *ctx) {
    curr_type = BOOL;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringAtom(fhiclParser::StringAtomContext *ctx) {
    curr_type = STRING;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdAtom(fhiclParser::IdAtomContext *ctx) {
    curr_type = STRING;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfinityAtom(fhiclParser::InfinityAtomContext *ctx) {
    curr_type = INF;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNegInfinityAtom(fhiclParser::NegInfinityAtomContext *ctx) {
    curr_type = NegINF;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp(fhiclParser::CompContext *ctx) {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReal(fhiclParser::RealContext *ctx) {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImaginary(fhiclParser::ImaginaryContext *ctx) {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIncl(fhiclParser::InclContext *ctx) {
    #ifndef LEXER_INCL
    #define LEXER_INCL 0
    #endif

    antlrcpp::Any to_return;
    std::string holdfile=curr_file;
    int holdline=offset;
    if(!LEXER_INCL){
      std::string file = ctx->INCL()->getText();
      if(debug_visitor) std::cout << "found an include " << file << std::endl;   
      file = file.substr(10, file.length());
      file = file.substr(0, file.find("\""));
      curr_file = file;
      offset = 0;
      std::ifstream inclsource(file);
    
      if(inclsource.is_open()){
	antlr4::ANTLRInputStream input(inclsource);
	input.name = file;
	fhiclcppantlr::fhiclLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	tokens.fill();
	if(debug_visitor){
	  for (auto token : tokens.getTokens()){
	    std::cout <<token->getTokenSource()->getSourceName() << token->toString() << std::endl;
	  }
	}
      
	fhiclcppantlr::fhiclParser parser(&tokens);
	fhiclcppantlr::fhiclParser::IntermTableContext* tree = parser.intermTable();
	if(debug_visitor) std::cout << tree->toStringTree(&parser) << std::endl;
	ctx->addChild(tree);
      
	to_return = visitChildren(tree);
	if(debug_visitor) std::cout << "ok?" <<std::endl;
	//if(debug_visitor) std::cout << tree->getParent() << std::endl;
	inclsource.close();

      } else {
	std::cout << "ERROR opening file " << file << std::endl;
      }
    
      if(debug_visitor) std::cout << "No segfault yet..." << std::endl;
    } else {
      to_return = 0; 
    }
    curr_file = holdfile;
    offset = holdline;
    return to_return;
  }
  virtual antlrcpp::Any visitLine(fhiclParser::LineContext *ctx) {
    std::string test = ctx->getText();
    test = test.substr(5);
    offset = stol(test) - ctx->LINE()->getSymbol()->getLine();
    if(debug_visitor)std::cout << offset << " " << stol(test) << std::endl;
    return 0;
  }
  
  virtual antlrcpp::Any visitFile(fhiclParser::FileContext *ctx) {
    if(debug_visitor)std::cout << curr_file << " becomes ";
    curr_file = ctx->getText();
    curr_file = curr_file.substr(6, curr_file.length()-7);
    if(debug_visitor)std::cout << curr_file << std::endl;
    return 0;
  }

  virtual antlrcpp::Any visitValueDB(fhiclParser::ValueDBContext *ctx) {
    if(ctx){}
    
    return 0;
  }

  virtual antlrcpp::Any visitValueLocal(fhiclParser::ValueLocalContext *ctx) {
    if(ctx){}
    
    return 0;
  }


private:
    bool is_prolog = false;
    //intermTable config;
    fhicl::intermediate_table config;
    value_tag curr_type;
    protection_tag curr_prot;
    std::any  curr_value;
    int curr_line;
    int offset;
    int curr_char_in_line;
    std::string curr_loc;
    std::string curr_file;
    fhicl::extended_value curr_entry;
    //std::stack<intermTable> scoping;

};

}  // namespace fhiclcppantlr
