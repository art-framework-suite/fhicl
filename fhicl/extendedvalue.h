// extendedvalue.h
// class for fhiclcpp_antlr paramset.h
// 
//
#include <map>
#include <string>
#include <vector>
#include <any>

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

class extendedvalue{
public:
  // constructors
  extendedvalue(){
    _type = value_tag::UNKNOWN;
    _protection = protection_tag::None;
  }

  extendedvalue( const extendedvalue& other ){
    
    _value	= other._value;
    _type	= other._type;
    _is_prolog  = other._is_prolog;
    _protection = other._protection;
    _location	= other._location;
    _comment	= other._comment;
   
  }


  // Modifiers
  void set_val(std::any val, std::string loc){
    if( prot_checkpoint(loc) ) _value = val;
  }

  void set_type(value_tag typ, std::string loc){
    if(prot_checkpoint(loc)) _type = typ;
  }

  void set_protection(protection_tag prot,std::string loc){
    if(prot_checkpoint(loc)) _protection = prot;
  }

  void add_info(std::string loc){
    if(prot_checkpoint(loc)) _location = loc;
  }

  void clear(std::string loc){
    if(prot_checkpoint(loc)){
      _value = 0;
      _type  = value_tag::UNKNOWN;
      _is_prolog = false;
      _location  = "";
      _comment   = "";
    }
  }

  void set_prolog(bool isprolog, std::string loc){
    if(prot_checkpoint(loc))  _is_prolog = isprolog;
  }

  void addcomment(std::string comment, std::string loc){
    if(prot_checkpoint(loc)) _comment = comment;
  }

private:
  // Checks protections and errors if trying to overwrite a protected entity
  bool prot_checkpoint(std::string loc){
    switch(_protection){
      case None: return true;
      case Protect_Ignore: return false;
      case Protect_Error: {
	std::cerr << "Tried to overwrite protected value located @ " << _location << " with entry at " << loc << std::endl; 
	exit(EXIT_FAILURE);
      }
      default: return false;
    }
  }


  //------ member vars ------
  std::any _value;
  value_tag _type;
  bool _is_prolog;
  protection_tag _protection;
  std::string _location;  // String representing origin information
  std::string _comment;  // Just in case someone needs comments
};
