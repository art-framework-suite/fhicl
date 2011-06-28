
%{
 int yyparse();
#include "bnf.tab.h"
#include <string>
#include <iostream>

using namespace std;

#define YY_BREAK
/* #define yylval fhicl_lval */

#define RETURN_TOKEN(token) { printf(#token"\n"); return token; }
#define RETURN_STR_TOKEN(token) { printf(#token": %s\n", yytext); yylval.str = stringDup(yytext); return token; }
#define RETURN_BOOL_TOK(value) { printf(#value"\n"); yylval._bool = value; return BOOL_TOK; }

char* stringDup(const char* s);
char* stringDupQuoted(const char* s,char quotetype);
char* handlePound(const char* s);
void readFile(string & content);
void preProcessor(char* argv[]);

/* NOTE: underscore not handled properly! */

/* target              {alpha_start_string}((\.{alpha_start_string})|(\[[ ]*[[:digit:]]*[ ]*\]))+ */
/* squoted             ([']).*?(?<!\\)(\\\\)*\1 */
/* dquoted             (["]).*?(?<!\\)(\\\\)*\1 */

%}


infinity            [\+\-]?infinity
unsigned            [[:digit:]]+
alpha_start_string  [[:alpha:]_][[:alnum:]_]*
num_start_string    [[:digit:]][[:alnum:]_]+
dotindex            \.{alpha_start_string}
bracketindex        \[[[:digit:]]+\]
index               {dotindex}|{bracketindex}
target              {alpha_start_string}{index}+
real                [-+]?((([[:digit:]]+\.?)|([[:digit:]]*\.[[:digit:]]+))([eE][-+]?[[:digit:]]+)?)
ref                 @(local|db)::({target}|{alpha_start_string})
include		    ^(#include[ \t]\"[.*]\")$
comment		    (\/\/.*$)|(#.*$)
%x DQ
%x SQ
%x CMNT

%%
:                     RETURN_TOKEN(COLON);
,                     RETURN_TOKEN(COMMA);
\(                    { printf("LPAREN\n"); return LPAREN; }
\)                    { printf("RPAREN\n"); return RPAREN; }
\[                    { printf("LBRACKET\n"); return LBRACKET; }
\]                    { printf("RBRACKET\n"); return RBRACKET; }
\{                    { printf("LBRACE\n"); return LBRACE; }
\}                    { printf("RBRACE\n"); return RBRACE; }
"ENDPROLOG"           { return ENDPROLOG; }
"PROLOG"              { return BEGINPROLOG; }
"nil"                 { printf("NIL\n"); return NIL; }
"true"                RETURN_BOOL_TOK(true)
"false"               RETURN_BOOL_TOK(false)
{infinity}            { yylval.str = stringDup(yytext); return INFINITY; }
{unsigned}            { printf("UNSIGNED: %s\n", yytext); yylval.str = stringDup(yytext); return UNSIGNED; }
{real}                { printf("REAL: %s\n", yytext); yylval.str = stringDup(yytext); return REAL; }
{alpha_start_string}  { printf("ASS: %s\n", yytext); yylval.str = stringDup(yytext); return ALPHA_START_STRING; }
{ref}                 { printf("REF: %s\n", yytext); yylval.str = stringDup(yytext); return REF; }
{target}              { printf("TARGET: %s\n", yytext); yylval.str = stringDup(yytext); return TARGET; }
{num_start_string}    { printf("NSS: %s\n", yytext); yylval.str = stringDup(yytext); return NUM_START_STRING; }
^#.*$		      { printf(handlePound(yytext), yytext); yylval.str = stringDup(yytext); break; }
#.*$		      { printf("COMMENT: %s\n", yytext); yylval.str = stringDup(yytext); break; }
\/\/.*$               { printf("COMMENT: %s\n", yytext); yylval.str = stringDup(yytext); break; }
\'                    { BEGIN SQ; break; }
\"                    { BEGIN DQ; break; }
\"\"                  { yylval.str = stringDupQuoted("",'"'); return DQUOTED; }
\'\'                  { yylval.str = stringDupQuoted("",'\''); return SQUOTED; }
[ \n\t]+              { break; }
.                     { printf("Unrecognized characters: %s\n", yytext); break; }

<DQ>((\\\")*[^\"\n]*(\\\")*)+ { printf("DQ: %s\n", yytext); yylval.str = stringDupQuoted(yytext,'"'); return DQUOTED; }
<DQ>\"                        { BEGIN 0; break; }
<DQ>\n                        { BEGIN 0; return ERROR; }

<SQ>((\\\')*[^\'\n]*(\\\')*)+ { printf("SQ: %s\n", yytext); yylval.str = stringDupQuoted(yytext,'\''); return SQUOTED; }
<SQ>\'                        { BEGIN 0; break; }
<SQ>\n                        { BEGIN 0; return ERROR;}

%%
#include <string>
#include <fstream>

int yywrap() { return 1; }

char* stringDup(const char* s)
{
  char* buffer = static_cast<char*>(malloc(strlen(s)+1));
  strcpy(buffer, s);
  return buffer;
}

char* stringDupQuoted(const char* s,char quotetype)
{
  int len = strlen(s);
  char* buffer = static_cast<char*>(malloc(len+1+2));
  strcpy(buffer+1, s);
  buffer[0]=quotetype;
  buffer[len+1]=quotetype;
  buffer[len+2]='\0';
  return buffer;
}

char* handlePound(const char* s)
{
  std::string str(s);
  int i = str.find("#include \"", 0);
  if (i != std::string::npos)
  {
     return (char*) "INCLUDE: %s\n";
  }
  return (char*) "COMMENT: %s\n";
}

int main(int argc, char* argv[])
{
  return yyparse();
}

