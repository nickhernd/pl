D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]

%{
#include <string.h> 
#include <string>
#include <iostream>

using namespace std;

#include "comun.h"
#include "plp4.tab.h"

int ncol = 1,
    nlin = 1;

int findefichero = 0;

int ret(int token);
void msgError(int nerror, int nlin, int ncol, const char *s);

%}

%x COMENTARIO

%%
" "                {ncol++;}
[\t]               {ncol++;}
[\n]               {nlin++;ncol=1;}
"//"(.)*           {; /* comentarios de una linea */}
"/*"               {ncol += strlen(yytext); BEGIN(COMENTARIO);}
<COMENTARIO>[^/*\n]+ {ncol += strlen(yytext);}
<COMENTARIO>\n     {nlin++; ncol=1;}
<COMENTARIO><<EOF>> {msgError(ERRLEXEOF,-1,-1,"");}
<COMENTARIO>"*/"   {ncol += strlen(yytext); BEGIN(INITIAL);}
<COMENTARIO>[*/]   {ncol += strlen(yytext);}

"class"            {return ret(CLASS);}
"fun"              {return ret(FUN);}
"int"              {return ret(INT);}
"float"            {return ret(FLOAT);}
"print"            {return ret(PRINT);}
"if"               {return ret(IF);}
"else"             {return ret(ELSE);}
"fi"               {return ret(FI);}

{L}({LD})*         {return ret(ID);}
{D}+               {return ret(NUMENTERO);}
{D}+(\.){D}+       {return ret(NUMREAL);}

"+"                {return ret(AS);}
"-"                {return ret(AS);}
"*"                {return ret(MD);}
"/"                {return ret(MD);}

"<="               {return ret(REL);}
">="               {return ret(REL);}
"<"                {return ret(REL);}
">"                {return ret(REL);}
"=="               {return ret(REL);}
"!="               {return ret(REL);}

"="                {return ret(ASIGN);}
":"                {return ret(DOSPTOS);}
"{"                {return ret(LLAVEI);}
"}"                {return ret(LLAVED);}
"("                {return ret(PARI);}
")"                {return ret(PARD);}
";"                {return ret(PYC);}
","                {return ret(COMA);}

.                  {msgError(ERRLEXICO, nlin, ncol, yytext);}

%%

int yywrap(void) {findefichero=1; return 1;}

int ret(int token)
{
   yylval.lexema = yytext;
   yylval.nlin = nlin;
   yylval.ncol = ncol;
   ncol += strlen(yytext);
   return(token);
}
