grammar fhicl;

@lexer::members{ 
  #include "fhicl/incl.h"

}


paramset: ((COMM|INCL) (NL|WS)* )* prolog? (NL|WS)* ((entry|COMM|INCL) (NL|WS)* )* ;

prolog	: 'BEGIN_PROLOG' (NL|WS)* ((entry|COMM) (NL|WS)* )* 'END_PROLOG' ; 

table 	: '{' (NL|WS)* ((entry|COMM) (NL|WS)* )* '}' ;

entry 	: ID WS* (PRO_ERR | PRO_IGN)? WS* ':' WS* val WS* (COMM)? #RegularEntry
      	| TAB ID				      #EntryFusion
      	;

val     : atom	  #ValueAtom
	| seq	  #ValueSeqence
	| table	  #ValueTable
	| valref  #ValueReferenced
	| ERASE	  #ValueErased
	;

valref	: (TAB | REF | EXTERN) ID ;

seq	: '[' (NL|WS)* val  (',' (NL|WS)* val)* (NL|WS)* ']' 
	| '[' (NL|WS)* ']'
	;

atom  	: INT		#IntegerAtom
	| HEX		#HexAtom
	| BIN		#BinAtom
	| FLOAT		#FloatingAtom
	| comp		#ComplexAtom
	| BOOL		#BoolAtom
	| STRNG		#StringAtom
	| ID		#IdAtom	      //because antlr (It's actually a string)
	| SPVAL		#SpecialValue
	| INFTY		#InfinityAtom
	| NINFTY	#NegInfinityAtom
	;

comp 	: '(' WS* (INT | FLOAT ) WS* ',' WS* (INT | FLOAT) WS* ')' ;

//Tags
TAB	: '@table::' ;
SEQ	: '@sequence::' ; 
REF	: '@local::' | '@db::' ;
EXTERN	: '@id::' ;
SPVAL	: '@nil'   | '@infinity' ;
PRO_IGN	: '@'[Pp]'rotect_'[Ii]'gnore' ;
PRO_ERR	: '@'[Pp]'rotect_'[Ee]'rror' ;
ERASE	: '@erase' ;

INCL	: '#include "'  .*? '"' NL {checkincl(context); /*execute include code from incl.h*/} ;
//hopefully this doesnt catch includes...
COMM	: ('//' | '#') .*? NL 
	| '/*' .*? '*/'
	;

//Basic atoms
BOOL 	: '"' [Tt]'rue' '"' 
	| [Tt]'rue' 
	| '"'[Ff]'alse' '"' 
	| [Ff]'alse' 
	;

ID	: ALPH (ALPH|DIGIT)* ('.'ID)* ;

STRNG  	: '\'' ( '\\\'' | . )*? '\''	
     	| '"' ( '\\"' | . )*? '"' 
     	| ALPH ~[:@{}()[\] \n]+
	;

FLOAT 	: INT '.' INT (('e'|'E') INT)? 
	| INT ('e'|'E') INT
 	;

HEX  	: ('0x' | '0X') [0-9a-fA-F]+ ;
BIN  	: ('0b' | '0B') ('0' | '1')+ ;

INT  	: SIGN? DIGIT+ ;

INFTY	: '+'? ('i' | 'I' ) 'nfinity' ;
NINFTY 	: '-' ('i' | 'I' ) 'nfinity' ;

//Lexer tools
fragment
ALPH 	: [a-zA-Z_] ;
fragment
DIGIT	: [0-9] ;
fragment
SIGN	: ('+' | '-') ;

fragment
RESERVED: [:@{}()] ;
fragment
RB	: ']' ;
fragment
LB	: '[' ;

NL   	: '\r'? '\n' ;
WS   	: [ \t] ;

FIN	: EOF {checkstack(); } ;
