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

unsigned next_dir = 0;
unsigned next_tmp = 16000;
unsigned next_label = 1;
int current_type;

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


#line 186 "src/parser.tab.c"

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
  YYSYMBOL_boolean = 19,                   /* boolean  */
  YYSYMBOL_int_type = 20,                  /* int_type  */
  YYSYMBOL_double_type = 21,               /* double_type  */
  YYSYMBOL_main_token = 22,                /* main_token  */
  YYSYMBOL_out_token = 23,                 /* out_token  */
  YYSYMBOL_in_token = 24,                  /* in_token  */
  YYSYMBOL_print_token = 25,               /* print_token  */
  YYSYMBOL_println_token = 26,             /* println_token  */
  YYSYMBOL_string_token = 27,              /* string_token  */
  YYSYMBOL_class_token = 28,               /* class_token  */
  YYSYMBOL_import_token = 29,              /* import_token  */
  YYSYMBOL_new_token = 30,                 /* new_token  */
  YYSYMBOL_public_token = 31,              /* public_token  */
  YYSYMBOL_static_token = 32,              /* static_token  */
  YYSYMBOL_void_token = 33,                /* void_token  */
  YYSYMBOL_scanner_token = 34,             /* scanner_token  */
  YYSYMBOL_nextint = 35,                   /* nextint  */
  YYSYMBOL_nextdouble = 36,                /* nextdouble  */
  YYSYMBOL_else_token = 37,                /* else_token  */
  YYSYMBOL_coma = 38,                      /* coma  */
  YYSYMBOL_pyc = 39,                       /* pyc  */
  YYSYMBOL_punto = 40,                     /* punto  */
  YYSYMBOL_pari = 41,                      /* pari  */
  YYSYMBOL_pard = 42,                      /* pard  */
  YYSYMBOL_llavei = 43,                    /* llavei  */
  YYSYMBOL_llaved = 44,                    /* llaved  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_S = 46,                         /* S  */
  YYSYMBOL_Import = 47,                    /* Import  */
  YYSYMBOL_SecImp = 48,                    /* SecImp  */
  YYSYMBOL_Class = 49,                     /* Class  */
  YYSYMBOL_Main = 50,                      /* Main  */
  YYSYMBOL_Tipo = 51,                      /* Tipo  */
  YYSYMBOL_Bloque = 52,                    /* Bloque  */
  YYSYMBOL_53_1 = 53,                      /* $@1  */
  YYSYMBOL_BDecl = 54,                     /* BDecl  */
  YYSYMBOL_DVar = 55,                      /* DVar  */
  YYSYMBOL_56_2 = 56,                      /* $@2  */
  YYSYMBOL_DimSN = 57,                     /* DimSN  */
  YYSYMBOL_Dimensiones = 58,               /* Dimensiones  */
  YYSYMBOL_LIdent = 59,                    /* LIdent  */
  YYSYMBOL_Variable = 60,                  /* Variable  */
  YYSYMBOL_SeqInstr = 61,                  /* SeqInstr  */
  YYSYMBOL_Instr = 62,                     /* Instr  */
  YYSYMBOL_Expr = 63,                      /* Expr  */
  YYSYMBOL_EConj = 64,                     /* EConj  */
  YYSYMBOL_ERel = 65,                      /* ERel  */
  YYSYMBOL_Esimple = 66,                   /* Esimple  */
  YYSYMBOL_Term = 67,                      /* Term  */
  YYSYMBOL_Factor = 68,                    /* Factor  */
  YYSYMBOL_Ref = 69,                       /* Ref  */
  YYSYMBOL_IfGuard = 70,                   /* IfGuard  */
  YYSYMBOL_WhileGuard = 71                 /* WhileGuard  */
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
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   141,   141,   145,   148,   152,   153,   154,   156,   160,
     164,   165,   166,   168,   168,   176,   179,   183,   183,   186,
     195,   203,   204,   206,   207,   209,   210,   212,   222,   226,
     230,   231,   232,   235,   238,   241,   244,   247,   251,   254,
     256,   259,   261,   264,   266,   269,   271,   274,   276,   279,
     282,   285,   288,   291,   294,   297,   300,   303,   307,   310,
     314,   318
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
  "system_token", "boolean", "int_type", "double_type", "main_token",
  "out_token", "in_token", "print_token", "println_token", "string_token",
  "class_token", "import_token", "new_token", "public_token",
  "static_token", "void_token", "scanner_token", "nextint", "nextdouble",
  "else_token", "coma", "pyc", "punto", "pari", "pard", "llavei", "llaved",
  "$accept", "S", "Import", "SecImp", "Class", "Main", "Tipo", "Bloque",
  "$@1", "BDecl", "DVar", "$@2", "DimSN", "Dimensiones", "LIdent",
  "Variable", "SeqInstr", "Instr", "Expr", "EConj", "ERel", "Esimple",
  "Term", "Factor", "Ref", "IfGuard", "WhileGuard", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -68,    56,    41,   -68,    60,    43,   -68,   -68,   -26,    78,
     -68,     4,    39,   -68,   -68,    52,    53,    44,    51,   -68,
      64,    46,    62,    79,    80,    88,    55,    57,   -68,   -68,
     -68,    30,   -68,   -68,   -68,    90,    83,   -68,     2,    85,
      84,    95,    50,   -68,    58,    61,    63,   -68,   -68,   -68,
     -68,    24,     5,     5,    71,   -68,   -68,    35,   -68,    94,
      93,    21,    21,    86,    21,    21,    70,   -68,    72,    95,
     -68,    81,   -68,    -1,   -68,   -68,    21,   -68,    21,    21,
      -2,    97,   -68,    69,   100,   -68,   101,    13,    73,    19,
      40,     5,    74,   -68,    48,    42,   -68,   -68,    15,    21,
     -68,    21,    21,    21,    21,   -68,    54,   -68,   -68,   -68,
      96,   105,    76,    77,   -68,    97,   -68,   112,   100,   -68,
      82,    87,    89,   116,    91,    92,    98,    21,    21,   102,
     109,   -68,   -68,   -68,    17,    18,    99,   105,   103,   104,
     106,   -68,   -68,   -68,   -68
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,     7,     0,     0,
       3,     0,     0,     5,     6,     0,     0,     0,     0,     8,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     9,
      16,    29,    12,    10,    11,     0,    17,    15,     0,     0,
       0,     0,     0,    58,     0,     0,     0,    30,    14,    31,
      28,     0,     0,     0,     0,    22,    27,     0,    26,     0,
       0,     0,     0,     0,     0,     0,    35,    37,     0,     0,
      18,     0,    21,    49,    50,    51,     0,    52,     0,     0,
       0,    39,    41,    43,    45,    47,    53,     0,     0,     0,
       0,     0,     0,    25,     0,     0,    55,    54,     0,     0,
      60,     0,     0,     0,     0,    61,     0,    32,    59,    36,
       0,     0,     0,     0,    48,    38,    40,    42,    44,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,    56,    57,     0,     0,     0,    24,     0,     0,
       0,    23,    34,    33,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,   -68,   -68,   -68,    28,   108,   -68,   -68,
     -68,   -68,   -68,   -13,   -68,    67,   -68,   -49,   -62,    26,
      31,   -59,    34,   -67,   -37,   -68,   -68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     8,     6,    17,    36,    49,    30,    31,
      37,    41,    42,   124,    57,    58,    38,    50,    80,    81,
      82,    83,    84,    85,    86,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,    51,    89,    66,    67,    43,    90,    13,    43,    96,
     -58,    97,    99,    10,    11,    51,    51,    98,    44,    45,
      46,    44,    45,    46,    73,    74,    75,    99,    76,    99,
      77,    99,    99,    99,    64,    65,    78,   119,    14,    95,
     100,    47,   109,   117,    47,    28,    48,   103,    28,    32,
      33,    34,   108,    59,    51,   105,     3,   114,   107,   138,
     139,    60,    79,     7,    35,   134,   135,    32,    33,    34,
       4,     9,     5,    69,    70,   102,   103,   112,   113,   120,
     121,    12,    15,    16,    20,    18,    21,    22,    19,    23,
      24,    26,    25,    39,    40,    54,    55,    27,    56,    61,
      28,    68,    62,    63,    71,    72,    92,    91,   104,    88,
     101,    94,    65,   106,   122,   110,   123,   125,   126,   103,
     130,   137,   111,   127,   141,   115,   136,     0,   128,   129,
     131,     0,   116,     0,   132,    29,    93,   118,     0,     0,
     133,   140,   142,   143,     0,   144
};

static const yytype_int16 yycheck[] =
{
      62,    38,    64,    52,    53,     3,    65,     3,     3,    76,
      11,    78,    14,    39,    40,    52,    53,    79,    16,    17,
      18,    16,    17,    18,     3,     4,     5,    14,     7,    14,
       9,    14,    14,    14,    10,    11,    15,   104,    34,    40,
      42,    39,    91,   102,    39,    43,    44,     7,    43,    19,
      20,    21,    12,     3,    91,    42,     0,    42,    39,    42,
      42,    11,    41,     3,    34,   127,   128,    19,    20,    21,
      29,    28,    31,    38,    39,     6,     7,    35,    36,    25,
      26,     3,    43,    31,    33,    32,    22,    41,    44,    27,
      11,     3,    12,     3,    11,    10,    12,    42,     3,    41,
      43,    30,    41,    40,    10,    12,    34,    37,     8,    23,
      13,    30,    11,    40,    18,    41,    11,    41,    41,     7,
       4,    12,    94,    41,   137,    99,    24,    -1,    41,    40,
      39,    -1,   101,    -1,    42,    27,    69,   103,    -1,    -1,
      42,    42,    39,    39,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    46,    47,     0,    29,    31,    49,     3,    48,    28,
      39,    40,     3,     3,    34,    43,    31,    50,    32,    44,
      33,    22,    41,    27,    11,    12,     3,    42,    43,    52,
      53,    54,    19,    20,    21,    34,    51,    55,    61,     3,
      11,    56,    57,     3,    16,    17,    18,    39,    44,    52,
      62,    69,    70,    71,    10,    12,     3,    59,    60,     3,
      11,    41,    41,    40,    10,    11,    62,    62,    30,    38,
      39,    10,    12,     3,     4,     5,     7,     9,    15,    41,
      63,    64,    65,    66,    67,    68,    69,    63,    23,    63,
      66,    37,    34,    60,    30,    40,    68,    68,    63,    14,
      42,    13,     6,     7,     8,    42,    40,    39,    12,    62,
      41,    51,    35,    36,    42,    64,    65,    66,    67,    68,
      25,    26,    18,    11,    58,    41,    41,    41,    41,    40,
       4,    39,    42,    42,    63,    63,    24,    12,    42,    42,
      42,    58,    39,    39,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    50,
      51,    51,    51,    53,    52,    54,    54,    56,    55,    55,
      55,    57,    57,    58,    58,    59,    59,    60,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     3,     1,     6,    11,
       1,     1,     1,     0,     5,     2,     0,     0,     4,     8,
      11,     3,     2,     4,     3,     3,     1,     1,     2,     0,
       1,     1,     4,     9,     9,     2,     4,     2,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     2,     2,     5,     5,     1,     4,
       4,     4
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
#line 141 "src/parser.y"
                 {
    rootAST = (yyvsp[0].node);
}
#line 1338 "src/parser.tab.c"
    break;

  case 3: /* Import: Import import_token SecImp pyc  */
#line 145 "src/parser.y"
                                        {
    (yyval.attr) = (yyvsp[-3].attr);
}
#line 1346 "src/parser.tab.c"
    break;

  case 4: /* Import: %empty  */
#line 148 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1354 "src/parser.tab.c"
    break;

  case 5: /* SecImp: SecImp punto id  */
#line 152 "src/parser.y"
                         { (yyval.attr) = (yyvsp[-2].attr); }
#line 1360 "src/parser.tab.c"
    break;

  case 6: /* SecImp: SecImp punto scanner_token  */
#line 153 "src/parser.y"
                             { (yyval.attr) = (yyvsp[-2].attr); }
#line 1366 "src/parser.tab.c"
    break;

  case 7: /* SecImp: id  */
#line 154 "src/parser.y"
     { (yyval.attr) = new Atributos(); }
#line 1372 "src/parser.tab.c"
    break;

  case 8: /* Class: public_token class_token id llavei Main llaved  */
#line 156 "src/parser.y"
                                                       {
    (yyval.node) = (yyvsp[-1].node);
}
#line 1380 "src/parser.tab.c"
    break;

  case 9: /* Main: public_token static_token void_token main_token pari string_token cori cord id pard Bloque  */
#line 160 "src/parser.y"
                                                                                                  {
    (yyval.node) = new ProgramNode((yyvsp[0].block));
}
#line 1388 "src/parser.tab.c"
    break;

  case 10: /* Tipo: int_type  */
#line 164 "src/parser.y"
                { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = ENTERO; (yyval.attr)->tam = 1; }
#line 1394 "src/parser.tab.c"
    break;

  case 11: /* Tipo: double_type  */
#line 165 "src/parser.y"
              { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = REAL; (yyval.attr)->tam = 1; }
#line 1400 "src/parser.tab.c"
    break;

  case 12: /* Tipo: boolean  */
#line 166 "src/parser.y"
          { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = LOGICO; (yyval.attr)->tam = 1; }
#line 1406 "src/parser.tab.c"
    break;

  case 13: /* $@1: %empty  */
#line 168 "src/parser.y"
                {
    ts = new TablaSimbolos(ts);
}
#line 1414 "src/parser.tab.c"
    break;

  case 14: /* Bloque: llavei $@1 BDecl SeqInstr llaved  */
#line 170 "src/parser.y"
                        {
    (yyval.block) = (yyvsp[-1].block);
    (yyval.block)->symbols = ts;
    ts = ts->getParent();
}
#line 1424 "src/parser.tab.c"
    break;

  case 15: /* BDecl: BDecl DVar  */
#line 176 "src/parser.y"
                   {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1432 "src/parser.tab.c"
    break;

  case 16: /* BDecl: %empty  */
#line 179 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1440 "src/parser.tab.c"
    break;

  case 17: /* $@2: %empty  */
#line 183 "src/parser.y"
            { current_type = (yyvsp[0].attr)->tipo; }
#line 1446 "src/parser.tab.c"
    break;

  case 18: /* DVar: Tipo $@2 LIdent pyc  */
#line 183 "src/parser.y"
                                                    {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1454 "src/parser.tab.c"
    break;

  case 19: /* DVar: Tipo DimSN id asig new_token Tipo Dimensiones pyc  */
#line 186 "src/parser.y"
                                                    {
    Simbolo s;
    s.nombre = (yyvsp[-5].attr)->lexema;
    s.tipo = (yyvsp[-7].attr)->tipo;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    (yyval.attr) = new Atributos();
}
#line 1468 "src/parser.tab.c"
    break;

  case 20: /* DVar: scanner_token id asig new_token scanner_token pari system_token punto in_token pard pyc  */
#line 195 "src/parser.y"
                                                                                          {
    Simbolo s;
    s.nombre = (yyvsp[-9].attr)->lexema;
    s.tipo = SCVAR;
    ts->set(s);
    (yyval.attr) = new Atributos();
}
#line 1480 "src/parser.tab.c"
    break;

  case 21: /* DimSN: DimSN cori cord  */
#line 203 "src/parser.y"
                        { (yyval.attr) = (yyvsp[-2].attr); }
#line 1486 "src/parser.tab.c"
    break;

  case 22: /* DimSN: cori cord  */
#line 204 "src/parser.y"
            { (yyval.attr) = new Atributos(); }
#line 1492 "src/parser.tab.c"
    break;

  case 23: /* Dimensiones: cori nentero cord Dimensiones  */
#line 206 "src/parser.y"
                                            { (yyval.attr) = (yyvsp[0].attr); }
#line 1498 "src/parser.tab.c"
    break;

  case 24: /* Dimensiones: cori nentero cord  */
#line 207 "src/parser.y"
                    { (yyval.attr) = new Atributos(); }
#line 1504 "src/parser.tab.c"
    break;

  case 25: /* LIdent: LIdent coma Variable  */
#line 209 "src/parser.y"
                              { (yyval.attr) = (yyvsp[-2].attr); }
#line 1510 "src/parser.tab.c"
    break;

  case 26: /* LIdent: Variable  */
#line 210 "src/parser.y"
           { (yyval.attr) = (yyvsp[0].attr); }
#line 1516 "src/parser.tab.c"
    break;

  case 27: /* Variable: id  */
#line 212 "src/parser.y"
              {
    Simbolo s;
    s.nombre = (yyvsp[0].attr)->lexema;
    s.tipo = current_type;
    s.dir = next_dir;
    ts->set(s);
    next_dir++;
    (yyval.attr) = new Atributos();
}
#line 1530 "src/parser.tab.c"
    break;

  case 28: /* SeqInstr: SeqInstr Instr  */
#line 222 "src/parser.y"
                          {
    if ((yyvsp[0].stmt)) (yyvsp[-1].block)->add((yyvsp[0].stmt));
    (yyval.block) = (yyvsp[-1].block);
}
#line 1539 "src/parser.tab.c"
    break;

  case 29: /* SeqInstr: %empty  */
#line 226 "src/parser.y"
  {
    (yyval.block) = new BlockNode(nlin, ncol);
}
#line 1547 "src/parser.tab.c"
    break;

  case 30: /* Instr: pyc  */
#line 230 "src/parser.y"
            { (yyval.stmt) = nullptr; }
#line 1553 "src/parser.tab.c"
    break;

  case 31: /* Instr: Bloque  */
#line 231 "src/parser.y"
         { (yyval.stmt) = (yyvsp[0].block); }
#line 1559 "src/parser.tab.c"
    break;

  case 32: /* Instr: Ref asig Expr pyc  */
#line 232 "src/parser.y"
                    {
    (yyval.stmt) = new AssignNode(new IdentifierNode((yyvsp[-3].attr)->lexema, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol), (yyvsp[-1].expr), (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol);
}
#line 1567 "src/parser.tab.c"
    break;

  case 33: /* Instr: system_token punto out_token punto println_token pari Expr pard pyc  */
#line 235 "src/parser.y"
                                                                      {
    (yyval.stmt) = new PrintNode((yyvsp[-2].expr), true, (yyvsp[-8].attr)->nlin, (yyvsp[-8].attr)->ncol); 
}
#line 1575 "src/parser.tab.c"
    break;

  case 34: /* Instr: system_token punto out_token punto print_token pari Expr pard pyc  */
#line 238 "src/parser.y"
                                                                    {
    (yyval.stmt) = new PrintNode((yyvsp[-2].expr), false, (yyvsp[-8].attr)->nlin, (yyvsp[-8].attr)->ncol);
}
#line 1583 "src/parser.tab.c"
    break;

  case 35: /* Instr: IfGuard Instr  */
#line 241 "src/parser.y"
                {
    (yyval.stmt) = new IfNode((yyvsp[-1].expr), (yyvsp[0].stmt), nullptr, (yyvsp[-1].expr)->line, (yyvsp[-1].expr)->column);
}
#line 1591 "src/parser.tab.c"
    break;

  case 36: /* Instr: IfGuard Instr else_token Instr  */
#line 244 "src/parser.y"
                                 {
    (yyval.stmt) = new IfNode((yyvsp[-3].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), (yyvsp[-3].expr)->line, (yyvsp[-3].expr)->column);
}
#line 1599 "src/parser.tab.c"
    break;

  case 37: /* Instr: WhileGuard Instr  */
#line 247 "src/parser.y"
                   {
    (yyval.stmt) = new WhileNode((yyvsp[-1].expr), (yyvsp[0].stmt), (yyvsp[-1].expr)->line, (yyvsp[-1].expr)->column);
}
#line 1607 "src/parser.tab.c"
    break;

  case 38: /* Expr: Expr or_token EConj  */
#line 251 "src/parser.y"
                           {
    (yyval.expr) = new BinaryExprNode("||", (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1615 "src/parser.tab.c"
    break;

  case 39: /* Expr: EConj  */
#line 254 "src/parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 1621 "src/parser.tab.c"
    break;

  case 40: /* EConj: EConj and_token ERel  */
#line 256 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode("&&", (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1629 "src/parser.tab.c"
    break;

  case 41: /* EConj: ERel  */
#line 259 "src/parser.y"
       { (yyval.expr) = (yyvsp[0].expr); }
#line 1635 "src/parser.tab.c"
    break;

  case 42: /* ERel: Esimple relop Esimple  */
#line 261 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1643 "src/parser.tab.c"
    break;

  case 43: /* ERel: Esimple  */
#line 264 "src/parser.y"
          { (yyval.expr) = (yyvsp[0].expr); }
#line 1649 "src/parser.tab.c"
    break;

  case 44: /* Esimple: Esimple addop Term  */
#line 266 "src/parser.y"
                             {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1657 "src/parser.tab.c"
    break;

  case 45: /* Esimple: Term  */
#line 269 "src/parser.y"
       { (yyval.expr) = (yyvsp[0].expr); }
#line 1663 "src/parser.tab.c"
    break;

  case 46: /* Term: Term mulop Factor  */
#line 271 "src/parser.y"
                         {
    (yyval.expr) = new BinaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1671 "src/parser.tab.c"
    break;

  case 47: /* Term: Factor  */
#line 274 "src/parser.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 1677 "src/parser.tab.c"
    break;

  case 48: /* Factor: pari Expr pard  */
#line 276 "src/parser.y"
                        {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1685 "src/parser.tab.c"
    break;

  case 49: /* Factor: id  */
#line 279 "src/parser.y"
     {
    (yyval.expr) = new IdentifierNode((yyvsp[0].attr)->lexema, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1693 "src/parser.tab.c"
    break;

  case 50: /* Factor: nentero  */
#line 282 "src/parser.y"
          {
    (yyval.expr) = new IntLiteralNode(atoi((yyvsp[0].attr)->lexema.c_str()), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1701 "src/parser.tab.c"
    break;

  case 51: /* Factor: nreal  */
#line 285 "src/parser.y"
        {
    (yyval.expr) = new FloatLiteralNode(atof((yyvsp[0].attr)->lexema.c_str()), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1709 "src/parser.tab.c"
    break;

  case 52: /* Factor: ctebool  */
#line 288 "src/parser.y"
          {
    (yyval.expr) = new BoolLiteralNode(((yyvsp[0].attr)->lexema == "true"), (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1717 "src/parser.tab.c"
    break;

  case 53: /* Factor: Ref  */
#line 291 "src/parser.y"
      {
    (yyval.expr) = new IdentifierNode((yyvsp[0].attr)->lexema, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol);
}
#line 1725 "src/parser.tab.c"
    break;

  case 54: /* Factor: not_token Factor  */
#line 294 "src/parser.y"
                   {
    (yyval.expr) = new UnaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol); 
}
#line 1733 "src/parser.tab.c"
    break;

  case 55: /* Factor: addop Factor  */
#line 297 "src/parser.y"
               {
    (yyval.expr) = new UnaryExprNode((yyvsp[-1].attr)->lexema, (yyvsp[0].expr), (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol);
}
#line 1741 "src/parser.tab.c"
    break;

  case 56: /* Factor: id punto nextint pari pard  */
#line 300 "src/parser.y"
                             {
    (yyval.expr) = new IntLiteralNode(0, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol);
}
#line 1749 "src/parser.tab.c"
    break;

  case 57: /* Factor: id punto nextdouble pari pard  */
#line 303 "src/parser.y"
                                {
    (yyval.expr) = new FloatLiteralNode(0.0, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol);
}
#line 1757 "src/parser.tab.c"
    break;

  case 58: /* Ref: id  */
#line 307 "src/parser.y"
         {
    (yyval.attr) = (yyvsp[0].attr);
}
#line 1765 "src/parser.tab.c"
    break;

  case 59: /* Ref: Ref cori Esimple cord  */
#line 310 "src/parser.y"
                        {
    (yyval.attr) = (yyvsp[-3].attr);
}
#line 1773 "src/parser.tab.c"
    break;

  case 60: /* IfGuard: if_token pari Expr pard  */
#line 314 "src/parser.y"
                                  {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1781 "src/parser.tab.c"
    break;

  case 61: /* WhileGuard: while_token pari Expr pard  */
#line 318 "src/parser.y"
                                        {
    (yyval.expr) = (yyvsp[-1].expr);
}
#line 1789 "src/parser.tab.c"
    break;


#line 1793 "src/parser.tab.c"

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

#line 322 "src/parser.y"


#include "ASTVisualizer.h"
#include "DOTVisualizer.h"
#include "CodeGenerator.h"
#include "SemanticVisitor.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "No se pudo abrir el fichero %s\n", argv[1]);
            exit(1);
        }
    }
    if (yyparse() == 0 && rootAST) {
        SemanticVisitor semantic(ts, &tt);
        rootAST->accept(&semantic);
        
        if (semantic.success()) {
            CodeGenerator gen;
            gen.generate(rootAST, 4096);
        } else {
            std::cerr << "Compilation failed due to semantic errors." << std::endl;
        }
        delete rootAST;
    }
    return 0;
}
