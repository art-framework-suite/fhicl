grammar fhicl;

@lexer::members{ 
  #include "fhicl/incl.h"
}

intermTable: ((COMM|dir) (NL|WS)* )* prolog? (NL|WS)*  ((entry|COMM|dir) (NL|WS)* )* ;

prolog	: 'BEGIN_PROLOG' (NL|WS)* ((entry|COMM) (NL|WS)* )* 'END_PROLOG' ; 

table 	: '{' (NL|WS)* ((entry|COMM) (NL|WS)* )* '}' ;

entry 	: ID WS* (PRO_ERR | PRO_IGN)? WS* ':' WS* val WS* (COMM)? #RegularEntry
      	| TAB ID				      #EntryFusion
      	;

dir	: INCL	#incl
	| LINE	#line
	| FILE  #file
	;

val     : atom	    #ValueAtom
	| seq	    #ValueSequence
	| table	    #ValueTable
 	| EXTERN    #ValueExternal
	| ERASE	    #ValueErased
	| REF STRNG #ValueDB
	| LOCAL ID  #ValueLocal
	;

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
	| ID		#IdAtom	      //It's actually a string
	| INFTY		#InfinityAtom
	| NINFTY	#NegInfinityAtom
	;

comp 	: '(' WS* real WS* ',' WS* imaginary WS* ')' ;
real	 : (INT|FLOAT) ;
imaginary: (INT|FLOAT) ;

//Tags
TAB	: '@table::' ;
SEQ	: '@sequence::' ; 
LOCAL	: '@local::' ;
REF	: '@db::' ;
EXTERN	: '@id::' [0-9a-zA-Z]+ ;
NIL	: '@nil'  ;
PRO_IGN	: '@protect_ignore' ;
PRO_ERR	: '@protect_error' ;
ERASE	: '@erase' ;
LINE	: '#line ' .*? WS* NL ;
FILE	: '#file ' .*? WS* NL ;
INCL	: '#include "' .*? '"' WS* NL {if(LEXER_INCL){checkincl(context);}} ;

COMM	: '//' .*? NL
	| '#' .*? NL
	| '/*' .*? '*/'
	;

//Basic atoms
BOOL 	: '"' [Tt]'rue' '"' 
	| [Tt]'rue' 
	| '"'[Ff]'alse' '"' 
	| [Ff]'alse' 
	;

FLOAT 	: INT '.' INT (('e'|'E') INT)? 
	| INT ('e'|'E') INT
 	;

HEX  	: ('0x' | '0X') [0-9a-fA-F]+ ;
BIN  	: ('0b' | '0B') ('0' | '1')+ ;

INT  	: SIGN? DIGIT+ ;

INFTY	: '+'? ('i' | 'I' ) 'nfinity' ;
NINFTY 	: '-' ('i' | 'I' ) 'nfinity' ;

ID	: ALPH (ALPH|DIGIT)* ('.'ID)* ;

STRNG  	: '\'' ( '\\\'' | . )*? '\''	
     	| '"'  ( '\\"'  | . )*? '"' 
     	| ALPH ~[:@{}()[\] \r\n]+
	;

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

FIN	: EOF {if(context){}; if(LEXER_INCL) checkstack(); } ;
