#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tdl.h"

extern int yylex(void);
extern FILE* yyin;
extern int yylineno;
void LD(void);
void LDP(void);
void P( void);
void D(void);
void LV(void);
void LVP(void);
void LS(void);
void LSP(void);
void S(void);
void LP(void);
void LPP(void);
void PAR(void);
int get_yylex( void);
void unget_yylex( void);

int symbol = 0;
int symbol_devuelto = FALSE; 
char file_name[10];

int main(
   int argc,
   char** argv
)
{
   int yyvalue= 0;

   strcpy(file_name, argv[ 0]);

   if( argc != 2)
   {
      fprintf( stdout, "Use: exp <in_file_name: char*>.\n");
      return EXIT_FAILURE;
   }

   yyin= fopen( argv[ 1], "r");

   if( yyin == NULL)
   {
      fprintf( stdout, "File \"%s\" could not be opened\n", argv[ 1]);
      fprintf( stdout, "Check if the name is correct ");
      fprintf( stdout, "or if the file is damaged\n");
      exit( EXIT_FAILURE);
   }
   P();
   fprintf( stdout, "EOF.\n%d lines analysed.\n", yylineno - 1);

   return EXIT_SUCCESS;
}

void P(void)
{ 
    symbol= get_yylex();
    if(symbol == PROGRAM)
    {
        LD();
        LS();
        symbol= get_yylex();
        if(symbol == END)
            return;
        else
        {
            fprintf(stderr, "file \"%s\" : END missing.\n", file_name);
            exit(EXIT_FAILURE);
        }
     }
        else
        {
            fprintf(stderr, "file \"%s\" : expected PROGRAM\n", file_name);
            exit(EXIT_FAILURE);
        }
}

void LD(void)
{  

    D();
    LDP();
}

void LDP(void)
{

    symbol= get_yylex();
    if(symbol == INT || symbol == REAL)   
    {
        unget_yylex();
        D();
        LDP();
    }
    else
        unget_yylex();
}

void D(void)
{
    symbol= get_yylex();
    if(symbol == INT || symbol == REAL)  
    {
        LV();
        symbol= get_yylex();
        if(symbol == ';')
            return;
        else
        {
            fprintf(stderr, "file \"%s\" : expected ';' ,\n", file_name);

            exit(EXIT_FAILURE);
        }
    }
    else
    {
       fprintf(stderr, "file \"%s\" : expected INT or REAL\n", file_name);
       exit(EXIT_FAILURE);
    }
}

void LV(void)
{

   symbol = get_yylex();
   if(symbol==ID)
   {
      symbol = get_yylex();
      if(symbol== ','){
         unget_yylex();
         LVP();
      }
      else
      {
       
       fprintf(stderr, "file \"%s\" : expected ID\n", file_name);
       exit(EXIT_FAILURE);
      }
   } 
   else
   {
      fprintf(stderr, "file \"%s\" : expected ID\n", file_name);
       exit(EXIT_FAILURE);
   }
}

void LVP(void)
{

   symbol = get_yylex();
   if(symbol== ',')
   {
      symbol =get_yylex();
      if(symbol == ID){
      	LVP();
      }
       
   } 
   else 
      unget_yylex();
}

void LS(void)
{ 

   S();
   LSP();
}

void LSP(void)
{


   symbol = get_yylex();
   if(symbol==READ || symbol == WRITE || symbol==WRITELN)
   {  
      unget_yylex();
      S();
      LSP();
   } 
   else 
      unget_yylex();
}

void S(void)
{
   symbol = get_yylex();
   if(symbol==READ)
   {
      symbol= get_yylex();
      if( symbol==ID)
      {
         symbol= get_yylex();
         if(symbol==';')
            return;
         else{ 
             fprintf(stderr, "file \"%s\" : expected ';'\n", file_name);
             exit(EXIT_FAILURE);
         }
      }
      else {
         fprintf(stderr, "file \"%s\" : expected ID\n", file_name);
         exit(EXIT_FAILURE);
         }
   }

   else if(symbol==WRITE)
   {
      LP();
      symbol= get_yylex();
      if(symbol==';')
         return;
      else {
         fprintf(stderr, "file \"%s\" : expected ';'\n", file_name);
         exit(EXIT_FAILURE);
      }
   }

   else if(symbol==WRITELN)
   {
      symbol= get_yylex();
      if(symbol==';')
         return;
      else {
      fprintf(stderr, "file \"%s\" : expected ';'\n", file_name);
         exit(EXIT_FAILURE);
      }
   }
   else {
         fprintf(stderr, "file \"%s\" : expected ';'\n", file_name);
         exit(EXIT_FAILURE);
      }
}

void LP (void)
{
   PAR();  
   LPP();
}

void LPP (void)
{ 

   symbol = get_yylex();
   if(symbol== ',')
   {
      
      PAR();
      LPP();
   } 
   else 
      unget_yylex();
}

void PAR(void)
{

   symbol = get_yylex();
   if(symbol== CONST_CHAR || symbol== ID || symbol== CONST_INT || symbol==CONST_REAL)
      return;
   else
     {
         fprintf(stderr, "file \"%s\" : expected CONST_CHAR, ID,CONST_INT or CONST_REAL\n", file_name);
         exit(EXIT_FAILURE);
}
}

int get_yylex( void)
{
    if( symbol_devuelto == FALSE)
    {
      symbol = yylex();
      return symbol;
    }
    symbol_devuelto = FALSE;
    return symbol;
}

void unget_yylex( void)
{
  symbol_devuelto = TRUE;
}
