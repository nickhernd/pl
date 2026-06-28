/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "TablaSimbolos.h"
#include "TablaTipos.h"
#include "ASTNodes.h"

using namespace std;

extern int yylex();
extern int nlin, ncol;
extern char *yytext;
extern int findefichero;
extern FILE *yyin;

Node* rootAST = nullptr;

void msgError(int nerror, int nlin, int ncol, const char *s) {
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
         default:
            fprintf(stderr,"Error semantico (%d,%d): ", nlin,ncol);
            switch(nerror) {
             case ERR_YADECL: fprintf(stderr,"simbolo '%s' ya declarado\n",s);
               break;
             case ERR_NODECL: fprintf(stderr,"identificador '%s' no declarado\n",s);
               break;
             case ERR_NOSC: fprintf(stderr,"identificador '%s' no es un Scanner\n",s);
               break;
             case ERR_SCVAR: fprintf(stderr,"identificador '%s' es de tipo Scanner\n",s);
               break;
             case ERR_TIPOSDECLARRAY: fprintf(stderr,"los tipos deben ser iguales en la declaracion del array '%s'\n",s);
               break;
             case ERR_DIMSDECLARRAY: fprintf(stderr,"las dimensiones deben ser iguales en la declaracion del array '%s'\n",s);
               break;
             case ERR_TIPOSASIG: fprintf(stderr,"tipos incompatibles en asignacion\n");
               break;
             case ERR_TIPOS: fprintf(stderr,"tipos incompatibles en '%s'\n",s);
               break;
             case ERR_TIPOSIFW: fprintf(stderr,"la expresion de if/while debe ser booleana\n");
               break;
             case ERR_OPNOBOOL: fprintf(stderr,"los operandos deben ser booleanos\n");
               break;
             case ERR_NUM: fprintf(stderr,"los operandos deben ser numericos\n");
               break;
             case ERR_DIM: fprintf(stderr,"la dimension debe ser mayor que cero\n");
               break;
             case ERR_FALTAN: fprintf(stderr,"faltan indices\n");
               break;
             case ERR_SOBRAN: fprintf(stderr,"sobran indices\n");
               break;
             case ERR_INDICE_ENTERO: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n");
               break;
             case ERR_NOCABE:fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
               break;
             case ERR_MAXTMP:fprintf(stderr,"no hay espacio para variables temporales\n");
               break;
            }
        }
     exit(1);
}

int yyerror(const char *s) {
    if (findefichero) {
       msgError(ERREOF, -1, -1, "");
    } else {  
       msgError(ERRSINT, nlin, ncol-strlen(yytext), yytext);
    }
    return 0;
}

TablaSimbolos *ts = new TablaSimbolos(NULL);
TablaTipos tt;

// [VER-1] Variables globales para acumular anotaciones antes de un método
ExprNode* g_pre  = nullptr;
ExprNode* g_post = nullptr;

unsigned next_dir = 0;
unsigned next_tmp = 16000;
unsigned next_label = 1;
int current_type;
bool is_constant = false;

string newLabel() {
    return "L" + to_string(next_label++);
}

unsigned getTemp() {
    if (next_tmp >= 16384) {
        msgError(ERR_MAXTMP, nlin, ncol, "");
    }
    return next_tmp++;
}

void releaseTemp(int n = 1) {
    next_tmp -= n;
}

unsigned getSafeTmp(int above) {
    if (above >= 0 && (int)next_tmp <= above) {
        next_tmp = (unsigned)(above + 1);
    }
    return getTemp();
}


#line 191 "src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_id = 3,                         /* id  */
  YYSYMBOL_nentero = 4,                    /* nentero  */
  YYSYMBOL_nreal = 5,                      /* nreal  */
  YYSYMBOL_relop = 6,                      /* relop  */
  YYSYMBOL_addop = 7,                      /* addop  */
  YYSYMBOL_mulop = 8,                      /* mulop  */
  YYSYMBOL_ctebool = 9,                    /* ctebool  */
  YYSYMBOL_asig = 10,                      /* asig  */
  YYSYMBOL_cori = 11,                      /* cori  */
  YYSYMBOL_cord = 12,                      /* cord  */
  YYSYMBOL_and_token = 13,                 /* and_token  */
  YYSYMBOL_or_token = 14,                  /* or_token  */
  YYSYMBOL_not_token = 15,                 /* not_token  */
  YYSYMBOL_if_token = 16,                  /* if_token  */
  YYSYMBOL_while_token = 17,               /* while_token  */
  YYSYMBOL_system_token = 18,              /* system_token  */
  YYSYMBOL_return_token = 19,              /* return_token  */
  YYSYMBOL_final_token = 20,               /* final_token  */
  YYSYMBOL_class_token = 21,               /* class_token  */
  YYSYMBOL_public_token = 22,              /* public_token  */
  YYSYMBOL_static_token = 23,              /* static_token  */
  YYSYMBOL_void_token = 24,                /* void_token  */
  YYSYMBOL_main_token = 25,                /* main_token  */
  YYSYMBOL_pre_token = 26,                 /* pre_token  */
  YYSYMBOL_post_token = 27,                /* post_token  */
  YYSYMBOL_invariant_token = 28,           /* invariant_token  */
  YYSYMBOL_variant_token = 29,             /* variant_token  */
  YYSYMBOL_implies_token = 30,             /* implies_token  */
  YYSYMBOL_result_token = 31,              /* result_token  */
  YYSYMBOL_boolean = 32,                   /* boolean  */
  YYSYMBOL_int_type = 33,                  /* int_type  */
  YYSYMBOL_double_type = 34,               /* double_type  */
  YYSYMBOL_out_token = 35,                 /* out_token  */
  YYSYMBOL_in_token = 36,                  /* in_token  */
  YYSYMBOL_print_token = 37,               /* print_token  */
  YYSYMBOL_println_token = 38,             /* println_token  */
  YYSYMBOL_string_token = 39,              /* string_token  */
  YYSYMBOL_import_token = 40,              /* import_token  */
  YYSYMBOL_new_token = 41,                 /* new_token  */
  YYSYMBOL_scanner_token = 42,             /* scanner_token  */
  YYSYMBOL_nextint = 43,                   /* nextint  */
  YYSYMBOL_nextdouble = 44,                /* nextdouble  */
  YYSYMBOL_else_token = 45,                /* else_token  */
  YYSYMBOL_coma = 46,                      /* coma  */
  YYSYMBOL_pyc = 47,                       /* pyc  */
  YYSYMBOL_punto = 48,                     /* punto  */
  YYSYMBOL_pari = 49,                      /* pari  */
  YYSYMBOL_pard = 50,                      /* pard  */
  YYSYMBOL_llavei = 51,                    /* llavei  */
  YYSYMBOL_llaved = 52,                    /* llaved  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_S = 54,                         /* S  */
  YYSYMBOL_Import = 55,                    /* Import  */
  YYSYMBOL_SecImp = 56,                    /* SecImp  */
  YYSYMBOL_Class = 57,                     /* Class  */
  YYSYMBOL_Members = 58,                   /* Members  */
  YYSYMBOL_Member = 59,                    /* Member  */
  YYSYMBOL_Main = 60,                      /* Main  */
  YYSYMBOL_Method = 61,                    /* Method  */
  YYSYMBOL_Tipo = 62,                      /* Tipo  */
  YYSYMBOL_Bloque = 63,                    /* Bloque  */
  YYSYMBOL_64_1 = 64,                      /* $@1  */
  YYSYMBOL_BDecl = 65,                     /* BDecl  */
  YYSYMBOL_DVar = 66,                      /* DVar  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_DimSN = 69,                     /* DimSN  */
  YYSYMBOL_Dimensiones = 70,               /* Dimensiones  */
  YYSYMBOL_LIdent = 71,                    /* LIdent  */
  YYSYMBOL_Variable = 72,                  /* Variable  */
  YYSYMBOL_SeqInstr = 73,                  /* SeqInstr  */
  YYSYMBOL_Instr = 74,                     /* Instr  */
  YYSYMBOL_Expr = 75,                      /* Expr  */
  YYSYMBOL_EConj = 76,                     /* EConj  */
  YYSYMBOL_ERel = 77,                      /* ERel  */
  YYSYMBOL_Esimple = 78,                   /* Esimple  */
  YYSYMBOL_Term = 79,                      /* Term  */
  YYSYMBOL_Factor = 80,                    /* Factor  */
  YYSYMBOL_Ref = 81,                       /* Ref  */
  YYSYMBOL_IfGuard = 82,                   /* IfGuard  */
  YYSYMBOL_WhileGuard = 83,                /* WhileGuard  */
  YYSYMBOL_PredExpr = 84,                  /* PredExpr  */
  YYSYMBOL_OptPre = 85,                    /* OptPre  */
  YYSYMBOL_OptPost = 86,                   /* OptPost  */
  YYSYMBOL_OptInvariant = 87,              /* OptInvariant  */
  YYSYMBOL_OptVariant = 88                 /* OptVariant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  185

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   152,   155,   159,   160,   161,   163,   167,
     171,   176,   181,   185,   186,   187,   189,   197,   210,   224,
     225,   226,   228,   228,   236,   239,   243,   243,   246,   246,
     249,   259,   268,   269,   271,   272,   274,   275,   277,   288,
     292,   296,   297,   298,   303,   306,   309,   312,   315,   321,
     324,   328,   331,   333,   336,   338,   341,   343,   346,   348,
     351,   353,   356,   359,   362,   365,   368,   371,   374,   377,
     380,   383,   386,   390,   393,   397,   401,   406,   409,   412,
     413,   415,   416,   419,   420,   422,   423
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "id", "nentero",
  "nreal", "relop", "addop", "mulop", "ctebool", "asig", "cori", "cord",
  "and_token", "or_token", "not_token", "if_token", "while_token",
  "system_token", "return_token", "final_token", "class_token",
  "public_token", "static_token", "void_token", "main_token", "pre_token",
  "post_token", "invariant_token", "variant_token", "implies_token",
  "result_token", "boolean", "int_type", "double_type", "out_token",
  "in_token", "print_token", "println_token", "string_token",
  "import_token", "new_token", "scanner_token", "nextint", "nextdouble",
  "else_token", "coma", "pyc", "punto", "pari", "pard", "llavei", "llaved",
  "$accept", "S", "Import", "SecImp", "Class", "Members", "Member", "Main",
  "Method", "Tipo", "Bloque", "$@1", "BDecl", "DVar", "$@2", "$@3",
  "DimSN", "Dimensiones", "LIdent", "Variable", "SeqInstr", "Instr",
  "Expr", "EConj", "ERel", "Esimple", "Term", "Factor", "Ref", "IfGuard",
  "WhileGuard", "PredExpr", "OptPre", "OptPost", "OptInvariant",
  "OptVariant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-74)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -86,    66,    27,   -86,   -13,     7,   -86,    75,   -86,    61,
     -26,   -86,    -1,   -86,   -86,   -86,    54,    85,    45,     8,
       8,   -86,   -86,   -86,    80,   -86,   -86,   -86,   -86,    89,
     -86,   -86,   -86,   -86,    71,    -4,   -86,   -86,     8,   -86,
       8,   -86,     8,    39,   107,   -86,   108,    94,   -86,   120,
     -86,   -86,   122,   121,   131,    53,   131,    48,   132,    78,
      86,   -86,   -86,   -10,     8,     8,     8,     8,     8,     8,
       8,    99,   -86,   -86,    79,   -86,   133,   129,    81,    93,
      95,    96,    98,   100,   -86,   -86,   107,   134,   -86,   143,
      94,   -86,    77,   109,   131,   -86,   111,   -86,   -86,   103,
     115,   105,   106,   110,   -86,   112,   -86,    85,   114,   146,
     114,   -86,   -86,   140,   148,   -86,   -86,   150,   -86,   116,
     159,   119,   -86,   164,   135,   156,   -86,    65,   123,   124,
     148,   -86,     3,   114,   125,   -86,   -86,   126,   127,   130,
      28,   -86,   -86,   -86,   -86,   113,    11,   141,   -86,   -86,
       8,     8,   142,   -86,    -9,     8,   136,     8,   151,     2,
      10,   137,   -86,    -5,    11,   -86,     8,    11,   -86,   -86,
      92,   -86,   -86,   -86,   -86,   138,   139,     8,     8,    20,
      22,   144,   145,   -86,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,     0,     7,     0,
       0,     3,     0,    12,     5,     6,     0,     0,     0,     0,
       0,    21,    19,    20,     0,     8,     9,    13,    14,    26,
      15,    10,    11,    28,     0,    62,    63,    64,     0,    65,
       0,    70,     0,    78,    52,    54,    56,    58,    60,    66,
      79,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    38,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    69,    61,    51,    77,    53,    55,
      57,    59,     0,     0,     0,    27,     0,    32,    29,     0,
       0,     0,     0,     0,    74,     0,    36,     0,     0,     0,
       0,    71,    72,     0,     0,    22,    18,     0,    17,     0,
       0,     0,    25,     0,     0,     0,    30,    40,     0,     0,
      35,    24,     0,     0,     0,    34,    73,     0,     0,     0,
       0,    41,    23,    42,    39,     0,     0,    84,    16,    31,
       0,     0,     0,    50,     0,     0,    46,     0,    86,     0,
       0,     0,    49,     0,     0,    83,     0,     0,    75,    76,
       0,    43,    47,    85,    48,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -16,
     -62,   -86,   -86,    43,   -86,   -86,   -86,    49,   128,    88,
     -86,   -54,   -39,   147,   117,    23,   118,    25,   -85,   -86,
     -86,   -20,   -86,   -86,   -86,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     9,     6,    16,    26,    27,    28,    29,
     143,   122,   127,    30,    54,    56,    55,   121,    74,    75,
     132,   144,    43,    44,    45,    46,    47,    48,    49,   146,
     147,    50,    31,    32,   158,   167
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    33,    14,    63,    64,    64,   136,   -73,     7,    64,
       8,    35,    36,    37,   136,    38,    64,    39,    58,   137,
     138,   139,   140,    40,    64,    13,    87,   137,   138,   139,
     140,    35,    36,    37,    64,    38,    64,    39,   162,    41,
      85,    15,   171,    40,    59,    60,   116,   145,   118,     4,
     141,    79,   168,    64,   115,   142,    76,    42,   141,    41,
     169,   145,   115,    61,    77,    62,     3,     5,    34,    65,
     181,   148,   182,    80,    17,   153,    18,    42,    10,   145,
      19,    20,   145,    52,    68,    17,    21,    22,    23,   104,
      89,   114,   156,    92,    91,    57,    24,    21,    22,    23,
      53,   154,    69,    21,    22,    23,    25,    24,    11,    12,
     172,   159,   160,   174,    67,    68,   163,    21,    22,    23,
      66,    82,    83,   155,    70,    94,    95,    94,    98,   175,
     176,    70,    71,    72,    73,    81,    84,   165,   179,   180,
      93,    97,    99,    96,   100,   101,   173,   102,    64,   103,
      68,   105,   107,   108,   109,   110,   111,   117,   119,   120,
     112,   113,   123,   125,   124,   115,   126,   128,   130,   157,
     131,   129,   149,   133,   134,   150,   151,   161,   152,   135,
     166,   164,   106,    88,    78,   170,    90,   177,   178,     0,
       0,   183,   184,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86
};

static const yytype_int16 yycheck[] =
{
      20,    17,     3,    42,    14,    14,     3,    11,    21,    14,
       3,     3,     4,     5,     3,     7,    14,     9,    34,    16,
      17,    18,    19,    15,    14,    51,    65,    16,    17,    18,
      19,     3,     4,     5,    14,     7,    14,     9,    47,    31,
      50,    42,    47,    15,    48,    49,   108,   132,   110,    22,
      47,     3,    50,    14,    51,    52,     3,    49,    47,    31,
      50,   146,    51,    38,    11,    40,     0,    40,    23,    30,
      50,   133,    50,    25,    20,    47,    22,    49,     3,   164,
      26,    27,   167,     3,     7,    20,    32,    33,    34,    12,
      67,   107,   146,    70,    69,    24,    42,    32,    33,    34,
      11,   140,     8,    32,    33,    34,    52,    42,    47,    48,
     164,   150,   151,   167,     6,     7,   155,    32,    33,    34,
      13,    43,    44,    10,    11,    46,    47,    46,    47,    37,
      38,    11,    10,    12,     3,     3,    50,   157,   177,   178,
      41,    12,    49,    10,    49,    49,   166,    49,    14,    49,
       7,    42,    41,    50,    39,    50,    50,    11,    18,    11,
      50,    49,    12,     4,    48,    51,    47,     3,    12,    28,
     127,    36,    47,    50,    50,    49,    49,    35,    48,   130,
      29,    45,    94,    66,    56,    48,    68,    49,    49,    -1,
      -1,    47,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,     0,    22,    40,    57,    21,     3,    56,
       3,    47,    48,    51,     3,    42,    58,    20,    22,    26,
      27,    32,    33,    34,    42,    52,    59,    60,    61,    62,
      66,    85,    86,    62,    23,     3,     4,     5,     7,     9,
      15,    31,    49,    75,    76,    77,    78,    79,    80,    81,
      84,    84,     3,    11,    67,    69,    68,    24,    62,    48,
      49,    80,    80,    75,    14,    30,    13,     6,     7,     8,
      11,    10,    12,     3,    71,    72,     3,    11,    71,     3,
      25,     3,    43,    44,    50,    50,    76,    75,    77,    78,
      79,    80,    78,    41,    46,    47,    10,    12,    47,    49,
      49,    49,    49,    49,    12,    42,    72,    41,    50,    39,
      50,    50,    50,    49,    62,    51,    63,    11,    63,    18,
      11,    70,    64,    12,    48,     4,    47,    65,     3,    36,
      12,    66,    73,    50,    50,    70,     3,    16,    17,    18,
      19,    47,    52,    63,    74,    81,    82,    83,    63,    47,
      49,    49,    48,    47,    75,    10,    74,    28,    87,    75,
      75,    35,    47,    75,    45,    84,    29,    88,    50,    50,
      48,    47,    74,    84,    74,    37,    38,    49,    49,    75,
      75,    50,    50,    47,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    58,
      58,    58,    58,    59,    59,    59,    60,    61,    61,    62,
      62,    62,    64,    63,    65,    65,    67,    66,    68,    66,
      66,    66,    69,    69,    70,    70,    71,    71,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    82,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     3,     1,     6,     2,
       2,     2,     0,     1,     1,     1,    11,     7,     7,     1,
       1,     1,     0,     5,     2,     0,     0,     4,     0,     5,
       8,    11,     3,     2,     4,     3,     3,     1,     1,     2,
       0,     1,     1,     4,     9,     9,     2,     4,     4,     3,
       2,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     2,     2,     3,
       1,     5,     5,     1,     4,     4,     4,     3,     1,     2,
       0,     2,     0,     2,     0,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: Import Class  */
#line 148 "src/parser.y"
                 {
    rootAST = (yyvsp[0].node);
}
#line 1399 "src/parser.tab.c"
    break;

  case 3: /* Import: Import import_token SecImp pyc  */
#line 152 "src/parser.y"
                                        {
    (yyval.attr) = (yyvsp[-3].attr);
}
#line 1407 "src/parser.tab.c"
    break;

  case 4: /* Import: %empty  */
#line 155 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1415 "src/parser.tab.c"
    break;

  case 5: /* SecImp: SecImp punto id  */
#line 159 "src/parser.y"
                         { (yyval.attr) = (yyvsp[-2].attr); }
#line 1421 "src/parser.tab.c"
    break;

  case 6: /* SecImp: SecImp punto scanner_token  */
#line 160 "src/parser.y"
                             { (yyval.attr) = (yyvsp[-2].attr); }
#line 1427 "src/parser.tab.c"
    break;

  case 7: /* SecImp: id  */
#line 161 "src/parser.y"
     { (yyval.attr) = new Atributos(); }
#line 1433 "src/parser.tab.c"
    break;

  case 8: /* Class: public_token class_token id llavei Members llaved  */
#line 163 "src/parser.y"
                                                          {
    (yyval.node) = new ProgramNode((yyvsp[-1].block));
}
#line 1441 "src/parser.tab.c"
    break;

  case 9: /* Members: Members Member  */
#line 167 "src/parser.y"
                         {
    if ((yyvsp[0].stmt)) (yyvsp[-1].block)->add((yyvsp[0].stmt));
    (yyval.block) = (yyvsp[-1].block);
}
#line 1450 "src/parser.tab.c"
    break;

  case 10: /* Members: Members OptPre  */
#line 171 "src/parser.y"
                 {
    // [VER-1] Anotación @pre acumulada para el siguiente método
    delete g_pre; g_pre = (yyvsp[0].expr);
    (yyval.block) = (yyvsp[-1].block);
}
#line 1460 "src/parser.tab.c"
    break;

  case 11: /* Members: Members OptPost  */
#line 176 "src/parser.y"
                  {
    // [VER-1] Anotación @post acumulada para el siguiente método
    delete g_post; g_post = (yyvsp[0].expr);
    (yyval.block) = (yyvsp[-1].block);
}
#line 1470 "src/parser.tab.c"
    break;

  case 12: /* Members: %empty  */
#line 181 "src/parser.y"
  {
    (yyval.block) = new BlockNode(nlin, ncol);
}
#line 1478 "src/parser.tab.c"
    break;

  case 13: /* Member: Main  */
#line 185 "src/parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1484 "src/parser.tab.c"
    break;

  case 14: /* Member: Method  */
#line 186 "src/parser.y"
         { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1490 "src/parser.tab.c"
    break;

  case 15: /* Member: DVar  */
#line 187 "src/parser.y"
       { (yyval.stmt) = nullptr; }
#line 1496 "src/parser.tab.c"
    break;

  case 16: /* Main: public_token static_token void_token main_token pari string_token cori cord id pard Bloque  */
#line 189 "src/parser.y"
                                                                                                  {
    MethodNode* m = new MethodNode("main", -1, (yyvsp[0].block), (yyvsp[-10].attr)->nlin, (yyvsp[-10].attr)->ncol);
    m->precondition.reset(g_pre);
    m->postcondition.reset(g_post);
    g_pre = g_post = nullptr;
    (yyval.stmt) = m;
}
#line 1508 "src/parser.tab.c"
    break;

  case 17: /* Method: public_token static_token Tipo id pari pard Bloque  */
#line 197 "src/parser.y"
                                                            {
    Simbolo s;
    s.nombre = (yyvsp[-3].attr)->lexema;
    s.tipo = (yyvsp[-4].attr)->tipo;
    s.isFunction = true;
    s.returnType = (yyvsp[-4].attr)->tipo;
    ts->set(s);
    MethodNode* m = new MethodNode((yyvsp[-3].attr)->lexema, (yyvsp[-4].attr)->tipo, (yyvsp[0].block), (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol);
    m->precondition.reset(g_pre);
    m->postcondition.reset(g_post);
    g_pre = g_post = nullptr;
    (yyval.stmt) = m;
}
#line 1526 "src/parser.tab.c"
    break;

  case 18: /* Method: public_token static_token void_token id pari pard Bloque  */
#line 210 "src/parser.y"
                                                           {
    Simbolo s;
    s.nombre = (yyvsp[-3].attr)->lexema;
    s.tipo = -1;
    s.isFunction = true;
    s.returnType = -1;
    ts->set(s);
    MethodNode* m = new MethodNode((yyvsp[-3].attr)->lexema, -1, (yyvsp[0].block), (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol);
    m->precondition.reset(g_pre);
    m->postcondition.reset(g_post);
    g_pre = g_post = nullptr;
    (yyval.stmt) = m;
}
#line 1544 "src/parser.tab.c"
    break;

  case 19: /* Tipo: int_type  */
#line 224 "src/parser.y"
                { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = ENTERO; (yyval.attr)->tam = 1; }
#line 1550 "src/parser.tab.c"
    break;

  case 20: /* Tipo: double_type  */
#line 225 "src/parser.y"
              { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = REAL; (yyval.attr)->tam = 1; }
#line 1556 "src/parser.tab.c"
    break;

  case 21: /* Tipo: boolean  */
#line 226 "src/parser.y"
          { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = LOGICO; (yyval.attr)->tam = 1; }
#line 1562 "src/parser.tab.c"
    break;

  case 22: /* $@1: %empty  */
#line 228 "src/parser.y"
                {
    ts = new TablaSimbolos(ts);
}
#line 1570 "src/parser.tab.c"
    break;

  case 23: /* Bloque: llavei $@1 BDecl SeqInstr llaved  */
#line 230 "src/parser.y"
                        {
    (yyval.block) = (yyvsp[-1].block);
    (yyval.block)->symbols = ts;
    ts = ts->getParent();
}
#line 1580 "src/parser.tab.c"
    break;

  case 24: /* BDecl: BDecl DVar  */
#line 236 "src/parser.y"
                   {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1588 "src/parser.tab.c"
    break;

  case 25: /* BDecl: %empty  */
#line 239 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1596 "src/parser.tab.c"
    break;

  case 26: /* $@2: %empty  */
#line 243 "src/parser.y"
            { current_type = (yyvsp[0].attr)->tipo; is_constant = false; }
#line 1602 "src/parser.tab.c"
    break;

  case 27: /* DVar: Tipo $@2 LIdent pyc  */
#line 243 "src/parser.y"
                                                                         {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1610 "src/parser.tab.c"
    break;

  case 28: /* $@3: %empty  */
#line 246 "src/parser.y"
                   { current_type = (yyvsp[0].attr)->tipo; is_constant = true; }
#line 1616 "src/parser.tab.c"
    break;

  case 29: /* DVar: final_token Tipo $@3 LIdent pyc  */
#line 246 "src/parser.y"
                                                                               {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1624 "src/parser.tab.c"
    break;

  case 30: /* DVar: Tipo DimSN id asig new_token Tipo Dimensiones pyc  */
#line 249 "src/parser.y"
                                                    {
    Simbolo s;
    s.nombre = (yyvsp[-5].attr)->lexema;
    s.tipo = (yyvsp[-7].attr)->tipo;
    s.isConstant = false;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    (yyval.attr) = new Atributos();
}
#line 1639 "src/parser.tab.c"
    break;

  case 31: /* DVar: scanner_token id asig new_token scanner_token pari system_token punto in_token pard pyc  */
#line 259 "src/parser.y"
                                                                                          {
    Simbolo s;
    s.nombre = (yyvsp[-9].attr)->lexema;
    s.tipo = SCVAR;
    s.isConstant = false;
    ts->set(s);
    (yyval.attr) = new Atributos();
}
#line 1652 "src/parser.tab.c"
    break;

  case 32: /* DimSN: DimSN cori cord  */
#line 268 "src/parser.y"
                        { (yyval.attr) = (yyvsp[-2].attr); }
#line 1658 "src/parser.tab.c"
    break;

  case 33: /* DimSN: cori cord  */
#line 269 "src/parser.y"
            { (yyval.attr) = new Atributos(); }
#line 1664 "src/parser.tab.c"
    break;

  case 34: /* Dimensiones: cori nentero cord Dimensiones  */
#line 271 "src/parser.y"
                                            { (yyval.attr) = (yyvsp[0].attr); }
#line 1670 "src/parser.tab.c"
    break;

  case 35: /* Dimensiones: cori nentero cord  */
#line 272 "src/parser.y"
                    { (yyval.attr) = new Atributos(); }
#line 1676 "src/parser.tab.c"
    break;

  case 36: /* LIdent: LIdent coma Variable  */
#line 274 "src/parser.y"
                              { (yyval.attr) = (yyvsp[-2].attr); }
#line 1682 "src/parser.tab.c"
    break;

  case 37: /* LIdent: Variable  */
#line 275 "src/parser.y"
           { (yyval.attr) = (yyvsp[0].attr); }
#line 1688 "src/parser.tab.c"
    break;

  case 38: /* Variable: id  */
#line 277 "src/parser.y"
              {
    Simbolo s;
    s.nombre = (yyvsp[0].attr)->lexema;
    s.tipo = current_type;
    s.isConstant = is_constant;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    (yyval.attr) = new Atributos();
}
#line 1703 "src/parser.tab.c"
    break;

  case 39: /* SeqInstr: SeqInstr Instr  */
#line 288 "src/parser.y"
                          {
    if ((yyvsp[0].stmt)) (yyvsp[-1].block)->add((yyvsp[0].stmt));
    (yyval.block) = (yyvsp[-1].block);
}
#line 1712 "src/parser.tab.c"
    break;

  case 40: /* SeqInstr: %empty  */
#line 292 "src/parser.y"
  {
    (yyval.block) = new BlockNode(nlin, ncol);
}
#line 1720 "src/parser.tab.c"
    break;

  case 41: /* Instr: pyc  */
#line 296 "src/parser.y"
            { (yyval.stmt) = nullptr; }
#line 1726 "src/parser.tab.c"
    break;

  case 42: /* Instr: Bloque  */
#line 297 "src/parser.y"
         { (yyval.stmt) = (yyvsp[0].block); }
#line 1732 "src/parser.tab.c"
    break;

  case 43: /* Instr: Ref asig Expr pyc  */
#line 298 "src/parser.y"
                    {
    // Necesitamos convertir Ref (Atributos) a un Nodo adecuado. 
    // Como Ref es complicado, por ahora mantengamos la estructura, pero esto debe evolucionar.
    (yyval.stmt) = new AssignNode(new IdentifierNode((yyvsp[-3].attr)->lexema, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol), (yyvsp[-1].expr), (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol);
}
#line 1742 "src/parser.tab.c"
    break;

  case 44: /* Instr: system_token punto out_token punto println_token pari Expr pard pyc  */
#line 303 "src/parser.y"
                                                                      {
    (yyval.stmt) = new PrintNode((yyvsp[-2].expr), true, (yyvsp[-8].attr)->nlin, (yyvsp[-8].attr)->ncol); 
}
#line 1750 "src/parser.tab.c"
    break;

  case 45: /* Instr: system_token punto out_token punto print_token pari Expr pard pyc  */
#line 306 "src/parser.y"
                                                                    {
    (yyval.stmt) = new PrintNode((yyvsp[-2].expr), false, (yyvsp[-8].attr)->nlin, (yyvsp[-8].attr)->ncol);
}
#line 1758 "src/parser.tab.c"
    break;

  case 46: /* Instr: IfGuard Instr  */
#line 309 "src/parser.y"
                {
    (yyval.stmt) = new IfNode((yyvsp[-1].expr), (yyvsp[0].stmt), nullptr, (yyvsp[-1].expr)->line, (yyvsp[-1].expr)->column);
}
#line 1766 "src/parser.tab.c"
    break;

  case 47: /* Instr: IfGuard Instr else_token Instr  */
#line 312 "src/parser.y"
                                 {
    (yyval.stmt) = new IfNode((yyvsp[-3].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), (yyvsp[-3].expr)->line, (yyvsp[-3].expr)->column);
}
#line 1774 "src/parser.tab.c"
    break;

  case 48: /* Instr: WhileGuard OptInvariant OptVariant Instr  */
#line 315 "src/parser.y"
                                           {
    WhileNode* w = new WhileNode((yyvsp[-3].expr), (yyvsp[0].stmt), (yyvsp[-3].expr)->line, (yyvsp[-3].expr)->column);
    w->invariant.reset((yyvsp[-2].expr));
    w->variant.reset((yyvsp[-1].expr));
    (yyval.stmt) = w;
}
#line 1785 "src/parser.tab.c"
    break;

  case 49: /* Instr: return_token Expr pyc  */
#line 321 "src/parser.y"
                        {
    (yyval.stmt) = new ReturnNode((yyvsp[-1].expr), (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol);
}
#line 1793 "src/parser.tab.c"
    break;

  case 50: /* Instr: return_token pyc  */
#line 324 "src/parser.y"
                   {
    (yyval.stmt) = new ReturnNode(nullptr, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1801 "src/parser.tab.c"
    break;

  case 51: /* Expr: Expr or_token EConj  */
#line 328 "src/parser.y"
                           {
    (yyval.expr) = new BinaryExprNode("||", (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1809 "src/parser.tab.c"
    break;

  case 52: /* Expr: EConj  */
#line 331 "src/parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 1815 "src/parser.tab.c"
    break;

  case 53: /* EConj: EConj and_token ERel  */
#line 333 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode("&&", (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1823 "src/parser.tab.c"
    break;

  case 54: /* EConj: ERel  */
#line 336 "src/parser.y"
       { (yyval.expr) = (yyvsp[0].expr); }
#line 1829 "src/parser.tab.c"
    break;

  case 55: /* ERel: Esimple relop Esimple  */
#line 338 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1837 "src/parser.tab.c"
    break;

  case 56: /* ERel: Esimple  */
#line 341 "src/parser.y"
          { (yyval.expr) = (yyvsp[0].expr); }
#line 1843 "src/parser.tab.c"
    break;

  case 57: /* Esimple: Esimple addop Term  */
#line 343 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1851 "src/parser.tab.c"
    break;

  case 58: /* Esimple: Term  */
#line 346 "src/parser.y"
       { (yyval.expr) = (yyvsp[0].expr); }
#line 1857 "src/parser.tab.c"
    break;

  case 59: /* Term: Term mulop Factor  */
#line 348 "src/parser.y"
                         {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1865 "src/parser.tab.c"
    break;

  case 60: /* Term: Factor  */
#line 351 "src/parser.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 1871 "src/parser.tab.c"
    break;

  case 61: /* Factor: pari Expr pard  */
#line 353 "src/parser.y"
                        {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1879 "src/parser.tab.c"
    break;

  case 62: /* Factor: id  */
#line 356 "src/parser.y"
     {
    (yyval.expr) = new IdentifierNode((yyvsp[0].attr)->lexema, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1887 "src/parser.tab.c"
    break;

  case 63: /* Factor: nentero  */
#line 359 "src/parser.y"
          {
    (yyval.expr) = new IntLiteralNode(atoi((yyvsp[0].attr)->lexema.c_str()), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1895 "src/parser.tab.c"
    break;

  case 64: /* Factor: nreal  */
#line 362 "src/parser.y"
        {
    (yyval.expr) = new FloatLiteralNode(atof((yyvsp[0].attr)->lexema.c_str()), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1903 "src/parser.tab.c"
    break;

  case 65: /* Factor: ctebool  */
#line 365 "src/parser.y"
          {
    (yyval.expr) = new BoolLiteralNode(((yyvsp[0].attr)->lexema == "true"), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1911 "src/parser.tab.c"
    break;

  case 66: /* Factor: Ref  */
#line 368 "src/parser.y"
      {
    (yyval.expr) = new IdentifierNode((yyvsp[0].attr)->lexema, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1919 "src/parser.tab.c"
    break;

  case 67: /* Factor: not_token Factor  */
#line 371 "src/parser.y"
                   {
    (yyval.expr) = new UnaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol); 
}
#line 1927 "src/parser.tab.c"
    break;

  case 68: /* Factor: addop Factor  */
#line 374 "src/parser.y"
               {
    (yyval.expr) = new UnaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1935 "src/parser.tab.c"
    break;

  case 69: /* Factor: id pari pard  */
#line 377 "src/parser.y"
               {
    (yyval.expr) = new CallNode((yyvsp[-2].attr)->lexema, (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol);
}
#line 1943 "src/parser.tab.c"
    break;

  case 70: /* Factor: result_token  */
#line 380 "src/parser.y"
               {
    (yyval.expr) = new ResultNode((yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1951 "src/parser.tab.c"
    break;

  case 71: /* Factor: id punto nextint pari pard  */
#line 383 "src/parser.y"
                             {
    (yyval.expr) = new ReadNode(false, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol);
}
#line 1959 "src/parser.tab.c"
    break;

  case 72: /* Factor: id punto nextdouble pari pard  */
#line 386 "src/parser.y"
                                {
    (yyval.expr) = new ReadNode(true, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol);
}
#line 1967 "src/parser.tab.c"
    break;

  case 73: /* Ref: id  */
#line 390 "src/parser.y"
         {
    (yyval.attr) = (yyvsp[0].attr);
}
#line 1975 "src/parser.tab.c"
    break;

  case 74: /* Ref: Ref cori Esimple cord  */
#line 393 "src/parser.y"
                        {
    (yyval.attr) = (yyvsp[-3].attr);
}
#line 1983 "src/parser.tab.c"
    break;

  case 75: /* IfGuard: if_token pari Expr pard  */
#line 397 "src/parser.y"
                                  {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1991 "src/parser.tab.c"
    break;

  case 76: /* WhileGuard: while_token pari Expr pard  */
#line 401 "src/parser.y"
                                        {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1999 "src/parser.tab.c"
    break;

  case 77: /* PredExpr: Expr implies_token Expr  */
#line 406 "src/parser.y"
                                   {
    (yyval.expr) = new BinaryExprNode("==>", (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 2007 "src/parser.tab.c"
    break;

  case 78: /* PredExpr: Expr  */
#line 409 "src/parser.y"
       { (yyval.expr) = (yyvsp[0].expr); }
#line 2013 "src/parser.tab.c"
    break;

  case 79: /* OptPre: pre_token PredExpr  */
#line 412 "src/parser.y"
                              { (yyval.expr) = (yyvsp[0].expr); }
#line 2019 "src/parser.tab.c"
    break;

  case 80: /* OptPre: %empty  */
#line 413 "src/parser.y"
                                { (yyval.expr) = nullptr; }
#line 2025 "src/parser.tab.c"
    break;

  case 81: /* OptPost: post_token PredExpr  */
#line 415 "src/parser.y"
                              { (yyval.expr) = (yyvsp[0].expr); }
#line 2031 "src/parser.tab.c"
    break;

  case 82: /* OptPost: %empty  */
#line 416 "src/parser.y"
                                { (yyval.expr) = nullptr; }
#line 2037 "src/parser.tab.c"
    break;

  case 83: /* OptInvariant: invariant_token PredExpr  */
#line 419 "src/parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 2043 "src/parser.tab.c"
    break;

  case 84: /* OptInvariant: %empty  */
#line 420 "src/parser.y"
                                          { (yyval.expr) = nullptr; }
#line 2049 "src/parser.tab.c"
    break;

  case 85: /* OptVariant: variant_token PredExpr  */
#line 422 "src/parser.y"
                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 2055 "src/parser.tab.c"
    break;

  case 86: /* OptVariant: %empty  */
#line 423 "src/parser.y"
                                          { (yyval.expr) = nullptr; }
#line 2061 "src/parser.tab.c"
    break;


#line 2065 "src/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 425 "src/parser.y"


#include "ASTVisualizer.h"
#include "DOTVisualizer.h"
#include "SemanticVisitor.h"
#include "IRBuilder.h"
#include "IROptimizer.h"
#include "IRVisualizer.h"
#include "IRLinearizer.h"
#include "X86Generator.h"
#include "RegisterAllocator.h"
#include "SMTExporter.h"
#include <fstream>

int main(int argc, char *argv[]) {
    bool showIR      = false;
    bool showRegAlloc = false;
    bool verify      = false;
    const char* filename = nullptr;

    for (int i = 1; i < argc; ++i) {
        if      (strcmp(argv[i], "--ir")       == 0) showIR = true;
        else if (strcmp(argv[i], "--reg-alloc") == 0) showRegAlloc = true;
        else if (strcmp(argv[i], "--verify")   == 0) verify = true;
        else if (argv[i][0] != '-')                  filename = argv[i];
        else {
            fprintf(stderr, "Uso: %s [--ir] [--reg-alloc] [--verify] <fichero.java>\n", argv[0]);
            return 1;
        }
    }

    if (filename) {
        yyin = fopen(filename, "r");
        if (!yyin) {
            fprintf(stderr, "No se pudo abrir el fichero %s\n", filename);
            return 1;
        }
    }

    if (yyparse() != 0 || !rootAST) return 1;

    SemanticVisitor semantic(ts, &tt);
    rootAST->accept(&semantic);

    if (!semantic.success()) {
        std::cerr << "Error de compilacion: errores semanticos." << std::endl;
        delete rootAST;
        return 1;
    }

    // [VER-7/8/10] Modo verificación formal: genera VCs y consulta Z3
    if (verify) {
        std::vector<VC> allVCs;
        ProgramNode* prog_ = dynamic_cast<ProgramNode*>(rootAST);
        BlockNode* root_   = prog_ ? prog_->root.get() : nullptr;
        if (!root_) { std::cerr << "Error interno: AST invalido\n"; return 1; }
        for (const auto& stmt : root_->statements) {
            auto* m = dynamic_cast<MethodNode*>(stmt.get());
            if (!m) continue;
            auto vcs  = VCGenerator::generate(m);
            auto safe = VCGenerator::generateSafety(m);
            auto term = VCGenerator::generateTermination(m);
            for (auto& v : vcs)  allVCs.push_back(std::move(v));
            for (auto& v : safe) allVCs.push_back(std::move(v));
            for (auto& v : term) allVCs.push_back(std::move(v));
        }

        if (allVCs.empty()) {
            std::cerr << "No hay metodos con @post. Añade @pre/@post para verificar.\n";
            delete rootAST;
            return 0;
        }

        // Determina el fichero .smt2 de salida
        std::string smtFile = "/tmp/verify.smt2";
        if (filename) {
            std::string base(filename);
            size_t dot = base.rfind('.');
            if (dot != std::string::npos) base = base.substr(0, dot);
            smtFile = base + ".smt2";
        }

        // Escribe el fichero SMT2
        std::ofstream smtOut(smtFile);
        SMTExporter exporter(smtOut);
        exporter.exportAll(allVCs, ts);
        smtOut.close();
        std::cerr << "SMT2 escrito en: " << smtFile << "\n";

        // Muestra las VCs en modo legible
        VCGenerator::dump(allVCs, std::cerr);

        // Intenta ejecutar Z3
        std::string z3out = SMTExporter::runZ3(smtFile);
        if (!z3out.empty()) {
            std::cout << "=== Verificacion Formal ===\n";
            SMTExporter::reportResults(z3out, allVCs);
        } else {
            std::cerr << "Z3 no encontrado. Instala con: sudo pacman -S z3\n";
            std::cerr << "Verifica manualmente: z3 " << smtFile << "\n";
        }

        delete rootAST;
        return 0;
    }

    // Pipeline: AST -> IR (cuadruplas) -> optimizacion -> x86-64
    IRProgram prog;
    IRBuilder builder(prog, ts);
    rootAST->accept(&builder);

    IROptimizer::eliminateDeadCode(prog);

    if (showIR) {
        IRVisualizer::print(prog, std::cerr);
        IRLinearizer lin;
        lin.build(prog);
        lin.dump(std::cerr);
    }

    if (showRegAlloc) {
        RegisterAllocator ra;
        RegMap rm = ra.allocate(prog);
        RegisterAllocator::dump(rm, std::cerr);
    }

    X86Generator codegen(std::cout);
    codegen.generate(prog);

    delete rootAST;
    return 0;
}
