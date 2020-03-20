%{
/*
 *   exp.flex: lexical analyzer for arithmetic expressions
 */
#include "tdl.h"
#include <string.h>
int get_symbol(char* yytext);
%}

blank    [ \t]
letter   [a-zA-Z]
digit    [0-9]
digits   {digit}+
fraction (\.{digits})
exponent (E(\+|\-)?{digits}) 

%%

{blank}+                          ;
\n                                yylineno++;
({letter}|_)({letter}|{digit}|_)* return get_symbol( yytext);
{digits}                          return CONST_INT;
{digits}{fraction}                return CONST_REAL;
{digits}{exponent}                return CONST_REAL;
{digits}{fraction}{exponent}      return CONST_REAL;
\"[^\n\"]*\"                      return CONST_CHAR;
.                                 return yytext[ 0];

%%

#include <string.h>
int get_symbol(char* yytext)
{
	if(strcmp(yytext,"program") == 0)
		return PROGRAM;
	else if(strcmp(yytext,"end") == 0)
		return END;
	else if(strcmp(yytext,"int") == 0)
		return INT;
	else if(strcmp(yytext,"real") == 0)
		return REAL;
	else if(strcmp(yytext,"write") == 0)
		return WRITE;
	else if(strcmp(yytext,"writeln") == 0)
		return WRITELN;
	else if(strcmp(yytext,"if") == 0)
		return IF;
	else if(strcmp(yytext,"then") == 0)
		return THEN;
	else if(strcmp(yytext,"else") == 0)
		return ELSE;
	else if(strcmp(yytext,"endif") == 0)
		return ENDIF;
	else if(strcmp(yytext,"false") == 0)
		return FALSE;
	else if(strcmp(yytext,"true") == 0)
		return TRUE;
	else if(strcmp(yytext,"for") == 0)
		return FOR;
	else if(strcmp(yytext,"endfor") == 0)
		return ENDFOR;
	else if(strcmp(yytext,"stop") == 0)
		return STOP;
	else if(strcmp(yytext,"break") == 0)
		return BREAK;
	else if(strcmp(yytext,"continue") == 0)
		return CONTINUE;
        else 
		return ID;
}
