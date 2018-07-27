
// Generated from /home/mikhails/scratch/mrb-art/build_slf7.x86_64/antlrtest/fhiclcpp_antlr/grammar/fhicl.g4 by ANTLR 4.7.1

#pragma once

#ifndef debug_visitor
#define debug_visitor 1
#endif


#include "antlr4-runtime.h"
#include "fhiclVisitor.h"
#include "paramset.h"

namespace fhiclcppantlr {

/**
 * This class provides an empty implementation of fhiclVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  fhiclTestVisitor : public fhiclVisitor {
public:

  virtual antlrcpp::Any visitParamset(fhiclParser::ParamsetContext *ctx) override {
    if(debug_visitor) std::cout << "Entering Paramset" << std::endl;
    curr_file = "";
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProlog(fhiclParser::PrologContext *ctx) override {
    is_prolog = true;
    if(debug_visitor) std::cout << "Entering Prolog" << std::endl;
    antlrcpp::Any to_return = visitChildren(ctx);
    is_prolog = false;
    if(debug_visitor) std::cout << "Exiting Prolog, returning to normal mode" << std::endl;
    return to_return;
  }

  virtual antlrcpp::Any visitTable(fhiclParser::TableContext *ctx) override {
    curr_type = TABLE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRegularEntry(fhiclParser::RegularEntryContext *ctx) override {
    //~curr_entry;
    extendedvalue curr_entry;

    curr_type = UNKNOWN;
    curr_prot = None;
    if(ctx->PRO_ERR()) curr_prot = Protect_Error;
    if(ctx->PRO_IGN()) curr_prot = Protect_Ignore;
    
    std::string linenum = std::to_string(ctx->ID()->getSymbol()->getLine());
    curr_loc = curr_file + ":" + linenum;
    

    antlrcpp::Any to_return = visitChildren(ctx);
    
    if(debug_visitor){
      std::cout << "-------------------------------" << std::endl;
      std::cout << ctx->ID()->getText()  << std::endl;
      std::cout << ctx->val()->getText() << std::endl;
      if(ctx->PRO_ERR() || ctx->PRO_IGN()) std::cout << "PROTECTED" << std::endl;
      if(ctx->COMM())std::cout << ctx->COMM()->getText() << std::endl;
      std::cout << ctx->ID()->getSymbol()->getLine() << std::endl;
      std::cout << ctx->ID()->getSymbol()->getCharPositionInLine() << std::endl;
      //if(ctx->getToken()) std::cout << ctx->getToken()->getLine() << std::endl;
      std::cout << ctx->getText() << std::endl;
      std::cout << curr_type << std::endl;
    }

    // Setup the entry for the config, as if it had no protection
    curr_entry.set_protection(None, curr_loc);
    curr_entry.set_val(curr_value, curr_loc);
    curr_entry.set_type(curr_type, curr_loc);
    curr_entry.add_info(curr_loc);
    curr_entry.set_prolog(is_prolog, curr_loc);
    if(ctx->COMM()) curr_entry.addcomment(ctx->COMM()->getText(), curr_loc);

    // Now that everything is set, set protection
    curr_entry.set_protection(curr_prot, curr_loc);

    //config.add(ctx->ID()->getText(), curr_entry);

    return to_return;
  }

  virtual antlrcpp::Any visitEntryFusion(fhiclParser::EntryFusionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueAtom(fhiclParser::ValueAtomContext *ctx) override {
    return visitChildren(ctx); //ignore, will go to others
  }

  virtual antlrcpp::Any visitValueSeqence(fhiclParser::ValueSeqenceContext *ctx) override {
    curr_type = SEQUENCE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueTable(fhiclParser::ValueTableContext *ctx) override {
    curr_type = TABLE;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueReferenced(fhiclParser::ValueReferencedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueErased(fhiclParser::ValueErasedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValref(fhiclParser::ValrefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSeq(fhiclParser::SeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntegerAtom(fhiclParser::IntegerAtomContext *ctx) override {
    curr_type = INT;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHexAtom(fhiclParser::HexAtomContext *ctx) override {
    curr_type = HEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinAtom(fhiclParser::BinAtomContext *ctx) override {
    curr_type = BIN;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloatingAtom(fhiclParser::FloatingAtomContext *ctx) override {
    curr_type = FLOAT;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComplexAtom(fhiclParser::ComplexAtomContext *ctx) override {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBoolAtom(fhiclParser::BoolAtomContext *ctx) override {
    curr_type = BOOL;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringAtom(fhiclParser::StringAtomContext *ctx) override {
    curr_type = STRING;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdAtom(fhiclParser::IdAtomContext *ctx) override {
    curr_type = STRING;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSpecialValue(fhiclParser::SpecialValueContext *ctx) override {
    if(ctx->SPVAL()->getText() == "@nil"){ 
      curr_type  = NIL;
      curr_value = "nil";
    }
    if(ctx->SPVAL()->getText() == "@infinity"){
      curr_type  = INF;
      curr_value = "infinity";
    }
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInfinityAtom(fhiclParser::InfinityAtomContext *ctx) override {
    curr_type = INF;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNegInfinityAtom(fhiclParser::NegInfinityAtomContext *ctx) override {
    curr_type = NegINF;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComp(fhiclParser::CompContext *ctx) override {
    curr_type = COMPLEX;
    return visitChildren(ctx);
  }

  private:
    bool is_prolog = false;
    paramset config;
    value_tag curr_type;
    protection_tag curr_prot;
    std::any  curr_value;
    std::string curr_loc;
    std::string curr_file;
    extendedvalue curr_entry;
    std::stack<paramset> scoping;

};

}  // namespace fhiclcppantlr
