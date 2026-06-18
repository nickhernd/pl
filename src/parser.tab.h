/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 117 "src/parser.y"

  #include "ASTNodes.h"
  #include "comun.h"

#line 54 "src/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    id = 258,                      /* id  */
    nentero = 259,                 /* nentero  */
    nreal = 260,                   /* nreal  */
    relop = 261,                   /* relop  */
    addop = 262,                   /* addop  */
    mulop = 263,                   /* mulop  */
    ctebool = 264,                 /* ctebool  */
    asig = 265,                    /* asig  */
    cori = 266,                    /* cori  */
    cord = 267,                    /* cord  */
    and_token = 268,               /* and_token  */
    or_token = 269,                /* or_token  */
    not_token = 270,               /* not_token  */
    if_token = 271,                /* if_token  */
    while_token = 272,             /* while_token  */
    system_token = 273,            /* system_token  */
    return_token = 274,            /* return_token  */
    final_token = 275,             /* final_token  */
    class_token = 276,             /* class_token  */
    public_token = 277,            /* public_token  */
    static_token = 278,            /* static_token  */
    void_token = 279,              /* void_token  */
    main_token = 280,              /* main_token  */
    boolean = 281,                 /* boolean  */
    int_type = 282,                /* int_type  */
    double_type = 283,             /* double_type  */
    out_token = 284,               /* out_token  */
    in_token = 285,                /* in_token  */
    print_token = 286,             /* print_token  */
    println_token = 287,           /* println_token  */
    string_token = 288,            /* string_token  */
    import_token = 289,            /* import_token  */
    new_token = 290,               /* new_token  */
    scanner_token = 291,           /* scanner_token  */
    nextint = 292,                 /* nextint  */
    nextdouble = 293,              /* nextdouble  */
    else_token = 294,              /* else_token  */
    coma = 295,                    /* coma  */
    pyc = 296,                     /* pyc  */
    punto = 297,                   /* punto  */
    pari = 298,                    /* pari  */
    pard = 299,                    /* pard  */
    llavei = 300,                  /* llavei  */
    llaved = 301                   /* llaved  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 122 "src/parser.y"

    char *lexema;
    Atributos *attr;
    Node *node;
    StmtNode *stmt;
    ExprNode *expr;
    BlockNode *block;

#line 126 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
