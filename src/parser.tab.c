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

using namespace std;

extern int yylex();
extern int nlin, ncol;
extern char *yytext;
extern int findefichero;
extern FILE *yyin;

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

// Returns a temp register guaranteed to be above 'above', so that code
// using registers up to 'above' won't clobber the saved value.
unsigned getSafeTmp(int above) {
    if (above >= 0 && (int)next_tmp <= above) {
        next_tmp = (unsigned)(above + 1);
    }
    return getTemp();
}


#line 185 "src/parser.tab.c"

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
  YYSYMBOL_boolean = 18,                   /* boolean  */
  YYSYMBOL_int_type = 19,                  /* int_type  */
  YYSYMBOL_double_type = 20,               /* double_type  */
  YYSYMBOL_main_token = 21,                /* main_token  */
  YYSYMBOL_system_token = 22,              /* system_token  */
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
  YYSYMBOL_63_3 = 63,                      /* @3  */
  YYSYMBOL_Expr = 64,                      /* Expr  */
  YYSYMBOL_EConj = 65,                     /* EConj  */
  YYSYMBOL_ERel = 66,                      /* ERel  */
  YYSYMBOL_Esimple = 67,                   /* Esimple  */
  YYSYMBOL_Term = 68,                      /* Term  */
  YYSYMBOL_Factor = 69,                    /* Factor  */
  YYSYMBOL_Ref = 70,                       /* Ref  */
  YYSYMBOL_IfGuard = 71,                   /* IfGuard  */
  YYSYMBOL_WhileGuard = 72                 /* WhileGuard  */
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
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

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
       0,   127,   127,   131,   134,   138,   139,   140,   142,   146,
     151,   152,   153,   155,   155,   165,   169,   173,   173,   176,
     212,   224,   228,   233,   242,   252,   256,   260,   276,   280,
     284,   285,   286,   286,   320,   330,   339,   344,   350,   357,
     367,   369,   379,   381,   414,   416,   440,   442,   466,   468,
     481,   489,   497,   502,   507,   513,   514,   521,   531,   543,
     578,   583
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
  "boolean", "int_type", "double_type", "main_token", "system_token",
  "out_token", "in_token", "print_token", "println_token", "string_token",
  "class_token", "import_token", "new_token", "public_token",
  "static_token", "void_token", "scanner_token", "nextint", "nextdouble",
  "else_token", "coma", "pyc", "punto", "pari", "pard", "llavei", "llaved",
  "$accept", "S", "Import", "SecImp", "Class", "Main", "Tipo", "Bloque",
  "$@1", "BDecl", "DVar", "$@2", "DimSN", "Dimensiones", "LIdent",
  "Variable", "SeqInstr", "Instr", "@3", "Expr", "EConj", "ERel",
  "Esimple", "Term", "Factor", "Ref", "IfGuard", "WhileGuard", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -63,    10,    34,   -63,    33,    25,   -63,   -63,    37,    53,
     -63,    -1,    19,   -63,   -63,    35,    47,    40,    61,   -63,
      74,    56,    69,    87,    88,    96,    59,    60,   -63,   -63,
     -63,    51,   -63,   -63,   -63,    99,    93,   -63,    -2,    95,
      94,   104,     8,   -63,    68,    70,    72,   -63,   -63,   -63,
     -63,    71,     5,     5,    78,   -63,   -63,    48,   -63,   100,
     101,    42,    42,    91,   -63,    42,    79,   -63,    81,   104,
     -63,    89,   -63,    77,   -63,   -63,   -63,    42,    20,   -10,
     105,   -63,    82,   112,   -63,   110,    16,    83,    42,     0,
       5,    84,   -63,    54,    55,   -63,    80,    17,    42,   -63,
      42,    42,    42,    42,   -63,    67,    -5,   -63,   -63,   102,
     115,    86,    90,    42,   -63,   105,   -63,   121,   112,   -63,
      92,    97,   -63,   103,   125,    98,   106,   107,   -63,    42,
      42,   108,   118,   -63,   -63,   -63,    36,    38,   109,   115,
     111,   113,   114,   -63,   -63,   -63,   -63
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
       0,     0,     0,     0,    32,     0,    36,    38,     0,     0,
      18,     0,    21,    58,    52,    53,    54,     0,     0,     0,
      40,    42,    44,    46,    48,    49,     0,     0,     0,     0,
       0,     0,    25,     0,     0,    56,     0,     0,     0,    60,
       0,     0,     0,     0,    61,     0,     0,    59,    37,     0,
       0,     0,     0,     0,    55,    39,    41,    43,    45,    47,
       0,     0,    33,     0,     0,     0,     0,     0,    57,     0,
       0,     0,     0,    19,    50,    51,     0,     0,     0,    24,
       0,     0,     0,    23,    35,    34,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,   -63,   -63,   -63,   -18,   117,   -63,   -63,
     -63,   -63,   -63,    -4,   -63,    65,   -63,   -47,   -63,   -62,
      41,    45,   -52,    39,   -49,   -35,   -63,   -63
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     8,     6,    17,    36,    49,    30,    31,
      37,    41,    42,   125,    57,    58,    38,    50,    88,    79,
      80,    81,    82,    83,    84,    85,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      86,    43,    13,    51,    98,    66,    67,   102,    43,    98,
       3,    59,   107,    89,    44,    45,    97,    51,    51,    60,
      46,    44,    45,    73,    74,    75,   106,    46,    95,    76,
      98,    98,    99,    14,   122,    77,     7,    47,    32,    33,
      34,    28,    48,   108,    47,    73,    74,    75,    28,   117,
      98,    76,    98,     9,   119,    51,    12,    77,   104,   114,
      96,    78,    15,     4,   128,     5,    16,   136,   137,    32,
      33,    34,    32,    33,    34,   110,    10,    11,   140,    18,
     141,    64,    65,    78,    19,    35,    69,    70,   101,   102,
     111,   112,   120,   121,    20,    21,    23,    22,    24,    26,
      25,    27,    39,    28,    40,    54,    55,    56,    68,    61,
      71,    62,    63,    72,    87,    91,    90,    94,   100,    93,
     103,    65,   113,   105,   123,   109,   124,   126,   102,   132,
     139,   127,   138,   129,    92,   143,     0,   133,   130,   115,
       0,   118,     0,   131,    29,   116,     0,     0,   134,   135,
     144,   142,   145,   146
};

static const yytype_int16 yycheck[] =
{
      62,     3,     3,    38,    14,    52,    53,     7,     3,    14,
       0,     3,    12,    65,    16,    17,    78,    52,    53,    11,
      22,    16,    17,     3,     4,     5,    88,    22,    77,     9,
      14,    14,    42,    34,    39,    15,     3,    39,    18,    19,
      20,    43,    44,    90,    39,     3,     4,     5,    43,   101,
      14,     9,    14,    28,   103,    90,     3,    15,    42,    42,
      78,    41,    43,    29,   113,    31,    31,   129,   130,    18,
      19,    20,    18,    19,    20,    93,    39,    40,    42,    32,
      42,    10,    11,    41,    44,    34,    38,    39,     6,     7,
      35,    36,    25,    26,    33,    21,    27,    41,    11,     3,
      12,    42,     3,    43,    11,    10,    12,     3,    30,    41,
      10,    41,    40,    12,    23,    34,    37,    40,    13,    30,
       8,    11,    42,    40,    22,    41,    11,    41,     7,     4,
      12,    41,    24,    41,    69,   139,    -1,    39,    41,    98,
      -1,   102,    -1,    40,    27,   100,    -1,    -1,    42,    42,
      39,    42,    39,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    46,    47,     0,    29,    31,    49,     3,    48,    28,
      39,    40,     3,     3,    34,    43,    31,    50,    32,    44,
      33,    21,    41,    27,    11,    12,     3,    42,    43,    52,
      53,    54,    18,    19,    20,    34,    51,    55,    61,     3,
      11,    56,    57,     3,    16,    17,    22,    39,    44,    52,
      62,    70,    71,    72,    10,    12,     3,    59,    60,     3,
      11,    41,    41,    40,    10,    11,    62,    62,    30,    38,
      39,    10,    12,     3,     4,     5,     9,    15,    41,    64,
      65,    66,    67,    68,    69,    70,    64,    23,    63,    67,
      37,    34,    60,    30,    40,    69,    51,    64,    14,    42,
      13,     6,     7,     8,    42,    40,    64,    12,    62,    41,
      51,    35,    36,    42,    42,    65,    66,    67,    68,    69,
      25,    26,    39,    22,    11,    58,    41,    41,    69,    41,
      41,    40,     4,    39,    42,    42,    64,    64,    24,    12,
      42,    42,    42,    58,    39,    39,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    50,
      51,    51,    51,    53,    52,    54,    54,    56,    55,    55,
      55,    57,    57,    58,    58,    59,    59,    60,    61,    61,
      62,    62,    63,    62,    62,    62,    62,    62,    62,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    70,
      71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     3,     1,     6,    11,
       1,     1,     1,     0,     5,     2,     0,     0,     4,     8,
      11,     3,     2,     4,     3,     3,     1,     1,     2,     0,
       1,     1,     0,     5,     9,     9,     2,     4,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       5,     5,     1,     1,     1,     3,     2,     4,     1,     4,
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
#line 127 "src/parser.y"
                 {
    cout << (yyvsp[-1].attr)->codigo << (yyvsp[0].attr)->codigo;
}
#line 1340 "src/parser.tab.c"
    break;

  case 3: /* Import: Import import_token SecImp pyc  */
#line 131 "src/parser.y"
                                        {
    (yyval.attr) = (yyvsp[-3].attr);
}
#line 1348 "src/parser.tab.c"
    break;

  case 4: /* Import: %empty  */
#line 134 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1356 "src/parser.tab.c"
    break;

  case 5: /* SecImp: SecImp punto id  */
#line 138 "src/parser.y"
                         { (yyval.attr) = (yyvsp[-2].attr); }
#line 1362 "src/parser.tab.c"
    break;

  case 6: /* SecImp: SecImp punto scanner_token  */
#line 139 "src/parser.y"
                             { (yyval.attr) = (yyvsp[-2].attr); }
#line 1368 "src/parser.tab.c"
    break;

  case 7: /* SecImp: id  */
#line 140 "src/parser.y"
     { (yyval.attr) = new Atributos(); }
#line 1374 "src/parser.tab.c"
    break;

  case 8: /* Class: public_token class_token id llavei Main llaved  */
#line 142 "src/parser.y"
                                                       {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1382 "src/parser.tab.c"
    break;

  case 9: /* Main: public_token static_token void_token main_token pari string_token cori cord id pard Bloque  */
#line 146 "src/parser.y"
                                                                                                  {
    (yyval.attr) = (yyvsp[0].attr);
    (yyval.attr)->codigo += "halt\n";
}
#line 1391 "src/parser.tab.c"
    break;

  case 10: /* Tipo: int_type  */
#line 151 "src/parser.y"
                { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = ENTERO; (yyval.attr)->tam = 1; }
#line 1397 "src/parser.tab.c"
    break;

  case 11: /* Tipo: double_type  */
#line 152 "src/parser.y"
              { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = REAL; (yyval.attr)->tam = 1; }
#line 1403 "src/parser.tab.c"
    break;

  case 12: /* Tipo: boolean  */
#line 153 "src/parser.y"
          { (yyval.attr) = new Atributos(); (yyval.attr)->tipo = LOGICO; (yyval.attr)->tam = 1; }
#line 1409 "src/parser.tab.c"
    break;

  case 13: /* $@1: %empty  */
#line 155 "src/parser.y"
                {
    ts = new TablaSimbolos(ts);
}
#line 1417 "src/parser.tab.c"
    break;

  case 14: /* Bloque: llavei $@1 BDecl SeqInstr llaved  */
#line 157 "src/parser.y"
                        {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = (yyvsp[-2].attr)->codigo + (yyvsp[-1].attr)->codigo;
    TablaSimbolos *old = ts;
    ts = ts->getParent();
    delete old;
}
#line 1429 "src/parser.tab.c"
    break;

  case 15: /* BDecl: BDecl DVar  */
#line 165 "src/parser.y"
                   {
    (yyval.attr) = (yyvsp[-1].attr);
    (yyval.attr)->codigo += (yyvsp[0].attr)->codigo;
}
#line 1438 "src/parser.tab.c"
    break;

  case 16: /* BDecl: %empty  */
#line 169 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1446 "src/parser.tab.c"
    break;

  case 17: /* $@2: %empty  */
#line 173 "src/parser.y"
            { current_type = (yyvsp[0].attr)->tipo; }
#line 1452 "src/parser.tab.c"
    break;

  case 18: /* DVar: Tipo $@2 LIdent pyc  */
#line 173 "src/parser.y"
                                                    {
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 1460 "src/parser.tab.c"
    break;

  case 19: /* DVar: Tipo DimSN id asig new_token Tipo Dimensiones pyc  */
#line 176 "src/parser.y"
                                                    {
    if (ts->get((yyvsp[-5].attr)->lexema)) {
        msgError(ERR_YADECL, (yyvsp[-5].attr)->nlin, (yyvsp[-5].attr)->ncol, (yyvsp[-5].attr)->lexema.c_str());
    }
    if ((yyvsp[-7].attr)->tipo != (yyvsp[-2].attr)->tipo) {
        msgError(ERR_TIPOSDECLARRAY, (yyvsp[-5].attr)->nlin, (yyvsp[-5].attr)->ncol, (yyvsp[-5].attr)->lexema.c_str());
    }
    if ((yyvsp[-6].attr)->ndims != (yyvsp[-1].attr)->ndims) {
        msgError(ERR_DIMSDECLARRAY, (yyvsp[-5].attr)->nlin, (yyvsp[-5].attr)->ncol, (yyvsp[-5].attr)->lexema.c_str());
    }

    unsigned tbase = (yyvsp[-7].attr)->tipo;
    unsigned total_tam = 1;
    for (int i = 0; i < (yyvsp[-1].attr)->ndims; i++) {
        total_tam *= (yyvsp[-1].attr)->dims[i];
    }

    unsigned tipo_id = tbase;
    for (int i = (yyvsp[-1].attr)->ndims - 1; i >= 0; i--) {
        tipo_id = tt.nuevoTipoArray((yyvsp[-1].attr)->dims[i], tipo_id);
    }

    Simbolo s;
    s.nombre = (yyvsp[-5].attr)->lexema;
    s.tipo = tipo_id;
    s.dir = next_dir;
    s.tam = total_tam;

    if (next_dir + total_tam > 16000) {
        msgError(ERR_NOCABE, (yyvsp[-5].attr)->nlin, (yyvsp[-5].attr)->ncol, (yyvsp[-5].attr)->lexema.c_str());
    }

    ts->set(s);
    next_dir += total_tam;
    (yyval.attr) = new Atributos();
}
#line 1501 "src/parser.tab.c"
    break;

  case 20: /* DVar: scanner_token id asig new_token scanner_token pari system_token punto in_token pard pyc  */
#line 212 "src/parser.y"
                                                                                          {
    Simbolo s;
    s.nombre = (yyvsp[-9].attr)->lexema;
    s.tipo = SCVAR;
    s.dir = 0;
    s.tam = 0;
    if (!ts->set(s)) {
        msgError(ERR_YADECL, (yyvsp[-9].attr)->nlin, (yyvsp[-9].attr)->ncol, (yyvsp[-9].attr)->lexema.c_str());
    }
    (yyval.attr) = new Atributos();
}
#line 1517 "src/parser.tab.c"
    break;

  case 21: /* DimSN: DimSN cori cord  */
#line 224 "src/parser.y"
                        {
    (yyval.attr) = (yyvsp[-2].attr);
    (yyval.attr)->ndims++;
}
#line 1526 "src/parser.tab.c"
    break;

  case 22: /* DimSN: cori cord  */
#line 228 "src/parser.y"
            {
    (yyval.attr) = new Atributos();
    (yyval.attr)->ndims = 1;
}
#line 1535 "src/parser.tab.c"
    break;

  case 23: /* Dimensiones: cori nentero cord Dimensiones  */
#line 233 "src/parser.y"
                                            {
    int val = atoi((yyvsp[-2].attr)->lexema.c_str());
    if (val <= 0) {
        msgError(ERR_DIM, (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol, (yyvsp[-2].attr)->lexema.c_str());
    }
    (yyval.attr) = (yyvsp[0].attr);
    (yyval.attr)->ndims++;
    (yyval.attr)->dims.insert((yyval.attr)->dims.begin(), val);
}
#line 1549 "src/parser.tab.c"
    break;

  case 24: /* Dimensiones: cori nentero cord  */
#line 242 "src/parser.y"
                    {
    int val = atoi((yyvsp[-1].attr)->lexema.c_str());
    if (val <= 0) {
        msgError(ERR_DIM, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, (yyvsp[-1].attr)->lexema.c_str());
    }
    (yyval.attr) = new Atributos();
    (yyval.attr)->ndims = 1;
    (yyval.attr)->dims.push_back(val);
}
#line 1563 "src/parser.tab.c"
    break;

  case 25: /* LIdent: LIdent coma Variable  */
#line 252 "src/parser.y"
                              {
    (yyval.attr) = (yyvsp[-2].attr);
    (yyval.attr)->codigo += (yyvsp[0].attr)->codigo;
}
#line 1572 "src/parser.tab.c"
    break;

  case 26: /* LIdent: Variable  */
#line 256 "src/parser.y"
           {
    (yyval.attr) = (yyvsp[0].attr);
}
#line 1580 "src/parser.tab.c"
    break;

  case 27: /* Variable: id  */
#line 260 "src/parser.y"
              {
    Simbolo s;
    s.nombre = (yyvsp[0].attr)->lexema;
    s.tipo = current_type;
    s.dir = next_dir;
    s.tam = 1;
    if (next_dir + 1 > 16000) {
        msgError(ERR_NOCABE, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol, (yyvsp[0].attr)->lexema.c_str());
    }
    if (!ts->set(s)) {
        msgError(ERR_YADECL, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol, (yyvsp[0].attr)->lexema.c_str());
    }
    next_dir++;
    (yyval.attr) = new Atributos();
}
#line 1600 "src/parser.tab.c"
    break;

  case 28: /* SeqInstr: SeqInstr Instr  */
#line 276 "src/parser.y"
                          {
    (yyval.attr) = (yyvsp[-1].attr);
    (yyval.attr)->codigo += (yyvsp[0].attr)->codigo;
}
#line 1609 "src/parser.tab.c"
    break;

  case 29: /* SeqInstr: %empty  */
#line 280 "src/parser.y"
  {
    (yyval.attr) = new Atributos();
}
#line 1617 "src/parser.tab.c"
    break;

  case 30: /* Instr: pyc  */
#line 284 "src/parser.y"
            { (yyval.attr) = new Atributos(); }
#line 1623 "src/parser.tab.c"
    break;

  case 31: /* Instr: Bloque  */
#line 285 "src/parser.y"
         { (yyval.attr) = (yyvsp[0].attr); }
#line 1629 "src/parser.tab.c"
    break;

  case 32: /* @3: %empty  */
#line 286 "src/parser.y"
           {
    (yyval.attr) = new Atributos();
    (yyval.attr)->dir = ((yyvsp[-1].attr)->ref == "@A") ? getTemp() : -1;
}
#line 1638 "src/parser.tab.c"
    break;

  case 33: /* Instr: Ref asig @3 Expr pyc  */
#line 289 "src/parser.y"
           {
    int tmp_addr = (yyvsp[-2].attr)->dir;
    (yyval.attr) = new Atributos();
    if ((yyvsp[-4].attr)->tipo == SCVAR || (yyvsp[-1].attr)->tipo == SCVAR) {
        msgError(ERR_SCVAR, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, "");
    }
    if (tt.tipos[(yyvsp[-4].attr)->tipo].clase == TIPOARRAY) {
        msgError(ERR_FALTAN, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, "");
    }
    (yyval.attr)->codigo = (yyvsp[-4].attr)->codigo;
    if ((yyvsp[-4].attr)->ref == "@A") {
        (yyval.attr)->codigo += "mov A " + to_string(tmp_addr) + "\n";
        (yyval.attr)->codigo += (yyvsp[-1].attr)->codigo;
        if ((yyvsp[-4].attr)->tipo == REAL && (yyvsp[-1].attr)->tipo == ENTERO) {
            (yyval.attr)->codigo += "itor\n";
        } else if ((yyvsp[-4].attr)->tipo != (yyvsp[-1].attr)->tipo) {
            msgError(ERR_TIPOSASIG, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol, "");
        }
        (yyval.attr)->codigo += "mov " + to_string(tmp_addr) + " B\n";
        (yyval.attr)->codigo += "mov A @B+0\n";
        releaseTemp();
    } else {
        (yyval.attr)->codigo += (yyvsp[-1].attr)->codigo;
        if ((yyvsp[-4].attr)->tipo == REAL && (yyvsp[-1].attr)->tipo == ENTERO) {
            (yyval.attr)->codigo += "itor\n";
        } else if ((yyvsp[-4].attr)->tipo != (yyvsp[-1].attr)->tipo) {
            msgError(ERR_TIPOSASIG, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol, "");
        }
        (yyval.attr)->codigo += "mov A " + (yyvsp[-4].attr)->ref + "\n";
    }
}
#line 1674 "src/parser.tab.c"
    break;

  case 34: /* Instr: system_token punto out_token punto println_token pari Expr pard pyc  */
#line 320 "src/parser.y"
                                                                      {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = (yyvsp[-2].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL) {
        (yyval.attr)->codigo += "wrr A\n";
    } else {
        (yyval.attr)->codigo += "wri A\n";
    }
    (yyval.attr)->codigo += "wrl\n";
}
#line 1689 "src/parser.tab.c"
    break;

  case 35: /* Instr: system_token punto out_token punto print_token pari Expr pard pyc  */
#line 330 "src/parser.y"
                                                                    {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = (yyvsp[-2].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL) {
        (yyval.attr)->codigo += "wrr A\n";
    } else {
        (yyval.attr)->codigo += "wri A\n";
    }
}
#line 1703 "src/parser.tab.c"
    break;

  case 36: /* Instr: IfGuard Instr  */
#line 339 "src/parser.y"
                {
    (yyval.attr) = new Atributos();
    string label = newLabel();
    (yyval.attr)->codigo = (yyvsp[-1].attr)->codigo + "jz " + label + "\n" + (yyvsp[0].attr)->codigo + label + "\n";
}
#line 1713 "src/parser.tab.c"
    break;

  case 37: /* Instr: IfGuard Instr else_token Instr  */
#line 344 "src/parser.y"
                                 {
    (yyval.attr) = new Atributos();
    string label_else = newLabel();
    string label_end = newLabel();
    (yyval.attr)->codigo = (yyvsp[-3].attr)->codigo + "jz " + label_else + "\n" + (yyvsp[-2].attr)->codigo + "jmp " + label_end + "\n" + label_else + "\n" + (yyvsp[0].attr)->codigo + label_end + "\n";
}
#line 1724 "src/parser.tab.c"
    break;

  case 38: /* Instr: WhileGuard Instr  */
#line 350 "src/parser.y"
                   {
    (yyval.attr) = new Atributos();
    string label_start = newLabel();
    string label_end = newLabel();
    (yyval.attr)->codigo = label_start + "\n" + (yyvsp[-1].attr)->codigo + "jz " + label_end + "\n" + (yyvsp[0].attr)->codigo + "jmp " + label_start + "\n" + label_end + "\n";
}
#line 1735 "src/parser.tab.c"
    break;

  case 39: /* Expr: Expr or_token EConj  */
#line 357 "src/parser.y"
                           {
    if ((yyvsp[-2].attr)->tipo != LOGICO || (yyvsp[0].attr)->tipo != LOGICO) msgError(ERR_OPNOBOOL, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, "||");
    (yyval.attr) = new Atributos();
    unsigned pre = next_tmp;
    unsigned tmp = getSafeTmp((yyvsp[-2].attr)->max_tmp_used);
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo + "mov A " + to_string(tmp) + "\n" + (yyvsp[-2].attr)->codigo + "ori " + to_string(tmp) + "\n";
    (yyval.attr)->tipo = LOGICO;
    (yyval.attr)->max_tmp_used = max(max((yyvsp[-2].attr)->max_tmp_used, (yyvsp[0].attr)->max_tmp_used), (int)tmp);
    next_tmp = pre;
}
#line 1750 "src/parser.tab.c"
    break;

  case 40: /* Expr: EConj  */
#line 367 "src/parser.y"
        { (yyval.attr) = (yyvsp[0].attr); (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used; }
#line 1756 "src/parser.tab.c"
    break;

  case 41: /* EConj: EConj and_token ERel  */
#line 369 "src/parser.y"
                             {
    if ((yyvsp[-2].attr)->tipo != LOGICO || (yyvsp[0].attr)->tipo != LOGICO) msgError(ERR_OPNOBOOL, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, "&&");
    (yyval.attr) = new Atributos();
    unsigned pre = next_tmp;
    unsigned tmp = getSafeTmp((yyvsp[-2].attr)->max_tmp_used);
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo + "mov A " + to_string(tmp) + "\n" + (yyvsp[-2].attr)->codigo + "andi " + to_string(tmp) + "\n";
    (yyval.attr)->tipo = LOGICO;
    (yyval.attr)->max_tmp_used = max(max((yyvsp[-2].attr)->max_tmp_used, (yyvsp[0].attr)->max_tmp_used), (int)tmp);
    next_tmp = pre;
}
#line 1771 "src/parser.tab.c"
    break;

  case 42: /* EConj: ERel  */
#line 379 "src/parser.y"
       { (yyval.attr) = (yyvsp[0].attr); (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used; }
#line 1777 "src/parser.tab.c"
    break;

  case 43: /* ERel: Esimple relop Esimple  */
#line 381 "src/parser.y"
                             {
    (yyval.attr) = new Atributos();
    unsigned pre = next_tmp;
    unsigned tmp = getSafeTmp((yyvsp[-2].attr)->max_tmp_used);
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL && (yyvsp[0].attr)->tipo == ENTERO) (yyval.attr)->codigo += "itor\n";
    (yyval.attr)->codigo += "mov A " + to_string(tmp) + "\n";
    (yyval.attr)->codigo += (yyvsp[-2].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == REAL) (yyval.attr)->codigo += "itor\n";

    if (((yyvsp[-2].attr)->tipo == LOGICO && (yyvsp[0].attr)->tipo == LOGICO) || (((yyvsp[-2].attr)->tipo == ENTERO || (yyvsp[-2].attr)->tipo == REAL) && ((yyvsp[0].attr)->tipo == ENTERO || (yyvsp[0].attr)->tipo == REAL))) {
        if ((yyvsp[-2].attr)->tipo == REAL || (yyvsp[0].attr)->tipo == REAL) {
            if ((yyvsp[-1].attr)->lexema == "==") (yyval.attr)->codigo += "eqlr " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "!=") (yyval.attr)->codigo += "neqr " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "<") (yyval.attr)->codigo += "lssr " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "<=") (yyval.attr)->codigo += "leqr " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == ">") (yyval.attr)->codigo += "gtrr " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == ">=") (yyval.attr)->codigo += "geqr " + to_string(tmp) + "\n";
        } else {
            if ((yyvsp[-1].attr)->lexema == "==") (yyval.attr)->codigo += "eqli " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "!=") (yyval.attr)->codigo += "neqi " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "<") (yyval.attr)->codigo += "lssi " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == "<=") (yyval.attr)->codigo += "leqi " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == ">") (yyval.attr)->codigo += "gtri " + to_string(tmp) + "\n";
            else if ((yyvsp[-1].attr)->lexema == ">=") (yyval.attr)->codigo += "geqi " + to_string(tmp) + "\n";
        }
    } else {
        msgError(ERR_TIPOS, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, (yyvsp[-1].attr)->lexema.c_str());
    }
    (yyval.attr)->tipo = LOGICO;
    (yyval.attr)->max_tmp_used = max(max((yyvsp[-2].attr)->max_tmp_used, (yyvsp[0].attr)->max_tmp_used), (int)tmp);
    next_tmp = pre;
}
#line 1815 "src/parser.tab.c"
    break;

  case 44: /* ERel: Esimple  */
#line 414 "src/parser.y"
          { (yyval.attr) = (yyvsp[0].attr); (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used; }
#line 1821 "src/parser.tab.c"
    break;

  case 45: /* Esimple: Esimple addop Term  */
#line 416 "src/parser.y"
                             {
    (yyval.attr) = new Atributos();
    unsigned pre = next_tmp;
    unsigned tmp = getSafeTmp((yyvsp[-2].attr)->max_tmp_used);
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL && (yyvsp[0].attr)->tipo == ENTERO) (yyval.attr)->codigo += "itor\n";
    (yyval.attr)->codigo += "mov A " + to_string(tmp) + "\n";
    (yyval.attr)->codigo += (yyvsp[-2].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == REAL) (yyval.attr)->codigo += "itor\n";

    if ((yyvsp[-2].attr)->tipo == REAL || (yyvsp[0].attr)->tipo == REAL) {
        if ((yyvsp[-1].attr)->lexema == "+") (yyval.attr)->codigo += "addr " + to_string(tmp) + "\n";
        else (yyval.attr)->codigo += "subr " + to_string(tmp) + "\n";
        (yyval.attr)->tipo = REAL;
    } else if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == ENTERO) {
        if ((yyvsp[-1].attr)->lexema == "+") (yyval.attr)->codigo += "addi " + to_string(tmp) + "\n";
        else (yyval.attr)->codigo += "subi " + to_string(tmp) + "\n";
        (yyval.attr)->tipo = ENTERO;
    } else {
        msgError(ERR_NUM, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, (yyvsp[-1].attr)->lexema.c_str());
    }
    (yyval.attr)->max_tmp_used = max(max((yyvsp[-2].attr)->max_tmp_used, (yyvsp[0].attr)->max_tmp_used), (int)tmp);
    next_tmp = pre;
}
#line 1850 "src/parser.tab.c"
    break;

  case 46: /* Esimple: Term  */
#line 440 "src/parser.y"
       { (yyval.attr) = (yyvsp[0].attr); (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used; }
#line 1856 "src/parser.tab.c"
    break;

  case 47: /* Term: Term mulop Factor  */
#line 442 "src/parser.y"
                         {
    (yyval.attr) = new Atributos();
    unsigned pre = next_tmp;
    unsigned tmp = getSafeTmp((yyvsp[-2].attr)->max_tmp_used);
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL && (yyvsp[0].attr)->tipo == ENTERO) (yyval.attr)->codigo += "itor\n";
    (yyval.attr)->codigo += "mov A " + to_string(tmp) + "\n";
    (yyval.attr)->codigo += (yyvsp[-2].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == REAL) (yyval.attr)->codigo += "itor\n";

    if ((yyvsp[-2].attr)->tipo == REAL || (yyvsp[0].attr)->tipo == REAL) {
        if ((yyvsp[-1].attr)->lexema == "*") (yyval.attr)->codigo += "mulr " + to_string(tmp) + "\n";
        else (yyval.attr)->codigo += "divr " + to_string(tmp) + "\n";
        (yyval.attr)->tipo = REAL;
    } else if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == ENTERO) {
        if ((yyvsp[-1].attr)->lexema == "*") (yyval.attr)->codigo += "muli " + to_string(tmp) + "\n";
        else (yyval.attr)->codigo += "divi " + to_string(tmp) + "\n";
        (yyval.attr)->tipo = ENTERO;
    } else {
        msgError(ERR_NUM, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, (yyvsp[-1].attr)->lexema.c_str());
    }
    (yyval.attr)->max_tmp_used = max(max((yyvsp[-2].attr)->max_tmp_used, (yyvsp[0].attr)->max_tmp_used), (int)tmp);
    next_tmp = pre;
}
#line 1885 "src/parser.tab.c"
    break;

  case 48: /* Term: Factor  */
#line 466 "src/parser.y"
         { (yyval.attr) = (yyvsp[0].attr); (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used; }
#line 1891 "src/parser.tab.c"
    break;

  case 49: /* Factor: Ref  */
#line 468 "src/parser.y"
             {
    if (tt.tipos[(yyvsp[0].attr)->tipo].clase == TIPOARRAY) {
        msgError(ERR_FALTAN, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol, "");
    }
    (yyval.attr) = new Atributos();
    if ((yyvsp[0].attr)->ref == "@A") {
        (yyval.attr)->codigo = (yyvsp[0].attr)->codigo + "mov @A A\n";
    } else {
        (yyval.attr)->codigo = (yyvsp[0].attr)->codigo + "mov " + (yyvsp[0].attr)->ref + " A\n";
    }
    (yyval.attr)->tipo = (yyvsp[0].attr)->tipo;
    (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used;
}
#line 1909 "src/parser.tab.c"
    break;

  case 50: /* Factor: id punto nextint pari pard  */
#line 481 "src/parser.y"
                             {
    Simbolo *s = ts->get((yyvsp[-4].attr)->lexema);
    if (!s) msgError(ERR_NODECL, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, (yyvsp[-4].attr)->lexema.c_str());
    if (s->tipo != SCVAR) msgError(ERR_NOSC, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, (yyvsp[-4].attr)->lexema.c_str());
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = "rdi A\n";
    (yyval.attr)->tipo = ENTERO;
}
#line 1922 "src/parser.tab.c"
    break;

  case 51: /* Factor: id punto nextdouble pari pard  */
#line 489 "src/parser.y"
                                {
    Simbolo *s = ts->get((yyvsp[-4].attr)->lexema);
    if (!s) msgError(ERR_NODECL, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, (yyvsp[-4].attr)->lexema.c_str());
    if (s->tipo != SCVAR) msgError(ERR_NOSC, (yyvsp[-4].attr)->nlin, (yyvsp[-4].attr)->ncol, (yyvsp[-4].attr)->lexema.c_str());
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = "rdr A\n";
    (yyval.attr)->tipo = REAL;
}
#line 1935 "src/parser.tab.c"
    break;

  case 52: /* Factor: nentero  */
#line 497 "src/parser.y"
          {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = "mov #" + (yyvsp[0].attr)->lexema + " A\n";
    (yyval.attr)->tipo = ENTERO;
}
#line 1945 "src/parser.tab.c"
    break;

  case 53: /* Factor: nreal  */
#line 502 "src/parser.y"
        {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = "mov $" + (yyvsp[0].attr)->lexema + " A\n";
    (yyval.attr)->tipo = REAL;
}
#line 1955 "src/parser.tab.c"
    break;

  case 54: /* Factor: ctebool  */
#line 507 "src/parser.y"
          {
    (yyval.attr) = new Atributos();
    if ((yyvsp[0].attr)->lexema == "true") (yyval.attr)->codigo = "mov #1 A\n";
    else (yyval.attr)->codigo = "mov #0 A\n";
    (yyval.attr)->tipo = LOGICO;
}
#line 1966 "src/parser.tab.c"
    break;

  case 55: /* Factor: pari Expr pard  */
#line 513 "src/parser.y"
                 { (yyval.attr) = (yyvsp[-1].attr); (yyval.attr)->max_tmp_used = (yyvsp[-1].attr)->max_tmp_used; }
#line 1972 "src/parser.tab.c"
    break;

  case 56: /* Factor: not_token Factor  */
#line 514 "src/parser.y"
                   {
    if ((yyvsp[0].attr)->tipo != LOGICO) msgError(ERR_OPNOBOOL, (yyvsp[-1].attr)->nlin, (yyvsp[-1].attr)->ncol, "!");
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo + "noti\n";
    (yyval.attr)->tipo = LOGICO;
    (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used;
}
#line 1984 "src/parser.tab.c"
    break;

  case 57: /* Factor: pari Tipo pard Factor  */
#line 521 "src/parser.y"
                        {
    (yyval.attr) = new Atributos();
    (yyval.attr)->codigo = (yyvsp[0].attr)->codigo;
    if ((yyvsp[-2].attr)->tipo == REAL && (yyvsp[0].attr)->tipo == ENTERO) (yyval.attr)->codigo += "itor\n";
    else if ((yyvsp[-2].attr)->tipo == ENTERO && (yyvsp[0].attr)->tipo == REAL) (yyval.attr)->codigo += "rtoi\n";
    else if ((yyvsp[-2].attr)->tipo == LOGICO && (yyvsp[0].attr)->tipo == ENTERO) (yyval.attr)->codigo += "noti\nnoti\n";
    (yyval.attr)->tipo = (yyvsp[-2].attr)->tipo;
    (yyval.attr)->max_tmp_used = (yyvsp[0].attr)->max_tmp_used;
}
#line 1998 "src/parser.tab.c"
    break;

  case 58: /* Ref: id  */
#line 531 "src/parser.y"
         {
    Simbolo *s = ts->get((yyvsp[0].attr)->lexema);
    if (!s) msgError(ERR_NODECL, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol, (yyvsp[0].attr)->lexema.c_str());
    if (s->tipo == SCVAR) msgError(ERR_SCVAR, (yyvsp[0].attr)->nlin, (yyvsp[0].attr)->ncol, (yyvsp[0].attr)->lexema.c_str());

    (yyval.attr) = new Atributos();
    (yyval.attr)->ref = to_string(s->dir);
    (yyval.attr)->tipo = s->tipo;
    (yyval.attr)->codigo = "";
    (yyval.attr)->nlin = (yyvsp[0].attr)->nlin;
    (yyval.attr)->ncol = (yyvsp[0].attr)->ncol;
}
#line 2015 "src/parser.tab.c"
    break;

  case 59: /* Ref: Ref cori Esimple cord  */
#line 543 "src/parser.y"
                        {
    if (tt.tipos[(yyvsp[-3].attr)->tipo].clase != TIPOARRAY) msgError(ERR_SOBRAN, (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol, "");
    if ((yyvsp[-1].attr)->tipo != ENTERO) msgError(ERR_INDICE_ENTERO, (yyvsp[-2].attr)->nlin, (yyvsp[-2].attr)->ncol, "");
    
    (yyval.attr) = new Atributos();
    unsigned tbase = tt.tipos[(yyvsp[-3].attr)->tipo].tipoBase;
    unsigned tam_base = 1;
    unsigned t = tbase;
    while (tt.tipos[t].clase == TIPOARRAY) {
        tam_base *= tt.tipos[t].tamano;
        t = tt.tipos[t].tipoBase;
    }
    
    (yyval.attr)->codigo = (yyvsp[-3].attr)->codigo;
    if ((yyvsp[-3].attr)->ref == "@A") {
        unsigned pre = next_tmp;
        unsigned tmp = getSafeTmp((yyvsp[-1].attr)->max_tmp_used);
        (yyval.attr)->codigo += "mov A " + to_string(tmp) + "\n";
        (yyval.attr)->codigo += (yyvsp[-1].attr)->codigo;
        if (tam_base > 1) (yyval.attr)->codigo += "muli #" + to_string(tam_base) + "\n";
        (yyval.attr)->codigo += "addi " + to_string(tmp) + "\n";
        (yyval.attr)->max_tmp_used = max(max((yyvsp[-3].attr)->max_tmp_used, (yyvsp[-1].attr)->max_tmp_used), (int)tmp);
        next_tmp = pre;
    } else {
        (yyval.attr)->codigo += (yyvsp[-1].attr)->codigo;
        if (tam_base > 1) (yyval.attr)->codigo += "muli #" + to_string(tam_base) + "\n";
        (yyval.attr)->codigo += "addi #" + (yyvsp[-3].attr)->ref + "\n";
        (yyval.attr)->max_tmp_used = max((yyvsp[-3].attr)->max_tmp_used, (yyvsp[-1].attr)->max_tmp_used);
    }
    (yyval.attr)->ref = "@A";
    (yyval.attr)->tipo = tbase;
    (yyval.attr)->nlin = (yyvsp[0].attr)->nlin;
    (yyval.attr)->ncol = (yyvsp[0].attr)->ncol;
}
#line 2054 "src/parser.tab.c"
    break;

  case 60: /* IfGuard: if_token pari Expr pard  */
#line 578 "src/parser.y"
                                  {
    if ((yyvsp[-1].attr)->tipo != LOGICO) msgError(ERR_TIPOSIFW, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol, "");
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 2063 "src/parser.tab.c"
    break;

  case 61: /* WhileGuard: while_token pari Expr pard  */
#line 583 "src/parser.y"
                                        {
    if ((yyvsp[-1].attr)->tipo != LOGICO) msgError(ERR_TIPOSIFW, (yyvsp[-3].attr)->nlin, (yyvsp[-3].attr)->ncol, "");
    (yyval.attr) = (yyvsp[-1].attr);
}
#line 2072 "src/parser.tab.c"
    break;


#line 2076 "src/parser.tab.c"

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

#line 588 "src/parser.y"


int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "No se pudo abrir el fichero %s\n", argv[1]);
            exit(1);
        }
    }
    yyparse();
    return 0;
}
