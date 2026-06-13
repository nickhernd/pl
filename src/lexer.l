%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "parser.tab.h"

int nlin = 1;
int ncol = 1;
int findefichero = 0;

void count(void) {
    int i;
    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            nlin++;
            ncol = 1;
        } else if (yytext[i] == '\t') {
            ncol += 1; // Assuming tab is 1 space as per Note 1
        } else {
            ncol++;
        }
    }
}

#define RET(token) { count(); return token; }
#define RET_ATTR(token) { \
    count(); \
    yylval.attr = new Atributos(); \
    yylval.attr->lexema = yytext; \
    yylval.attr->nlin = nlin; \
    yylval.attr->ncol = ncol - strlen(yytext); \
    return token; \
}

%}

%option noyywrap

%%

"boolean"           { RET(boolean); }
"int"               { RET(int_type); }
"double"            { RET(double_type); }
"main"              { RET(main_token); }
"System"            { RET(system_token); }
"out"               { RET(out_token); }
"in"                { RET(in_token); }
"print"             { RET(print_token); }
"println"           { RET(println_token); }
"String"            { RET(string_token); }
"class"             { RET(class_token); }
"import"            { RET(import_token); }
"new"               { RET(new_token); }
"public"            { RET(public_token); }
"static"            { RET(static_token); }
"void"              { RET(void_token); }
"Scanner"           { RET(scanner_token); }
"nextInt"           { RET(nextint); }
"nextDouble"        { RET(nextdouble); }
"if"                { RET_ATTR(if_token); }
"else"              { RET(else_token); }
"while"             { RET_ATTR(while_token); }
"true"              { RET_ATTR(ctebool); }
"false"             { RET_ATTR(ctebool); }

[a-zA-Z][a-zA-Z0-9]* { RET_ATTR(id); }

[0-9]+ { RET_ATTR(nentero); }

[0-9]+"."[0-9]+ { RET_ATTR(nreal); }

","                 { RET(coma); }
";"                 { RET(pyc); }
"."                 { RET(punto); }
"("                 { RET(pari); }
")"                 { RET(pard); }
"=="                { RET_ATTR(relop); }
"!="                { RET_ATTR(relop); }
"<"                 { RET_ATTR(relop); }
"<="                { RET_ATTR(relop); }
">"                 { RET_ATTR(relop); }
">="                { RET_ATTR(relop); }
"+"                 { RET_ATTR(addop); }
"-"                 { RET_ATTR(addop); }
"*"                 { RET_ATTR(mulop); }
"/"                 { RET_ATTR(mulop); }
"="                 { RET_ATTR(asig); }
"["                 { RET_ATTR(cori); }
"]"                 { RET_ATTR(cord); }
"{"                 { RET(llavei); }
"}"                 { RET(llaved); }
"&&"                { RET_ATTR(and_token); }
"||"                { RET_ATTR(or_token); }
"!"                 { RET_ATTR(not_token); }

"//".*              { count(); /* ignore comments */ }
[ \t\n\r]+          { count(); /* ignore whitespace */ }

.                   { msgError(ERRLEXICO, nlin, ncol, yytext); }

<<EOF>>             { findefichero = 1; yyterminate(); }

%%
