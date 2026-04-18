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
#line 1 "plp4.y"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comun.h"
#include "TablaSimbolos.h"

using namespace std;

extern int nlin, ncol, findefichero;
extern int yylex();
extern char *yytext;
extern FILE *yyin;

void msgError(int nerror, int nlin, int ncol, const char *s);
void errorSemantico(int nerror, char *lexema, int fila, int columna);

string prefix = "";
vector<string> prefixStack;
TablaSimbolos *ts = new TablaSimbolos(NULL);

const int ERRYADECL=1, ERRNODECL=2, ERRTIPOS=3, ERRNOSIMPLE=4, ERRNOENTERO=5;

string itor(tAtributos a) {
    if (a.tipo == ENTERO) return "itor(" + a.cod + ")";
    return a.cod;
}

int yyerror(char *s);


#line 106 "plp4.tab.c"

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

#include "plp4.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_FUN = 4,                        /* FUN  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_PRINT = 7,                      /* PRINT  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_FI = 10,                        /* FI  */
  YYSYMBOL_ID = 11,                        /* ID  */
  YYSYMBOL_NUMENTERO = 12,                 /* NUMENTERO  */
  YYSYMBOL_NUMREAL = 13,                   /* NUMREAL  */
  YYSYMBOL_AS = 14,                        /* AS  */
  YYSYMBOL_MD = 15,                        /* MD  */
  YYSYMBOL_REL = 16,                       /* REL  */
  YYSYMBOL_ASIGN = 17,                     /* ASIGN  */
  YYSYMBOL_DOSPTOS = 18,                   /* DOSPTOS  */
  YYSYMBOL_LLAVEI = 19,                    /* LLAVEI  */
  YYSYMBOL_LLAVED = 20,                    /* LLAVED  */
  YYSYMBOL_PARI = 21,                      /* PARI  */
  YYSYMBOL_PARD = 22,                      /* PARD  */
  YYSYMBOL_PYC = 23,                       /* PYC  */
  YYSYMBOL_COMA = 24,                      /* COMA  */
  YYSYMBOL_YYACCEPT = 25,                  /* $accept  */
  YYSYMBOL_S = 26,                         /* S  */
  YYSYMBOL_Componentes = 27,               /* Componentes  */
  YYSYMBOL_Componente = 28,                /* Componente  */
  YYSYMBOL_Clase = 29,                     /* Clase  */
  YYSYMBOL_30_1 = 30,                      /* $@1  */
  YYSYMBOL_Funcion = 31,                   /* Funcion  */
  YYSYMBOL_32_2 = 32,                      /* $@2  */
  YYSYMBOL_33_3 = 33,                      /* $@3  */
  YYSYMBOL_Argumentos = 34,                /* Argumentos  */
  YYSYMBOL_ArgumentosList = 35,            /* ArgumentosList  */
  YYSYMBOL_Argumento = 36,                 /* Argumento  */
  YYSYMBOL_Tipo = 37,                      /* Tipo  */
  YYSYMBOL_Declaracion = 38,               /* Declaracion  */
  YYSYMBOL_Sentencia = 39,                 /* Sentencia  */
  YYSYMBOL_Asignacion = 40,                /* Asignacion  */
  YYSYMBOL_Print = 41,                     /* Print  */
  YYSYMBOL_IfStmt = 42,                    /* IfStmt  */
  YYSYMBOL_ElsePart = 43,                  /* ElsePart  */
  YYSYMBOL_Bloque = 44,                    /* Bloque  */
  YYSYMBOL_45_4 = 45,                      /* $@4  */
  YYSYMBOL_Exp = 46                        /* Exp  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   89

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  68

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    46,    46,    53,    54,    57,    58,    59,    60,    61,
      64,    64,    79,    84,    79,    99,   100,   103,   104,   107,
     115,   116,   119,   127,   128,   129,   130,   133,   143,   146,
     154,   159,   160,   163,   163,   177,   186,   195,   204,   208,
     214,   218
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
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "FUN", "INT",
  "FLOAT", "PRINT", "IF", "ELSE", "FI", "ID", "NUMENTERO", "NUMREAL", "AS",
  "MD", "REL", "ASIGN", "DOSPTOS", "LLAVEI", "LLAVED", "PARI", "PARD",
  "PYC", "COMA", "$accept", "S", "Componentes", "Componente", "Clase",
  "$@1", "Funcion", "$@2", "$@3", "Argumentos", "ArgumentosList",
  "Argumento", "Tipo", "Declaracion", "Sentencia", "Asignacion", "Print",
  "IfStmt", "ElsePart", "Bloque", "$@4", "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -34,    14,     4,   -34,    10,    27,   -34,   -34,    61,    61,
       8,   -34,   -34,   -34,   -34,   -34,    30,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,    61,   -11,
      71,     5,   -34,   -34,    32,    48,    62,    61,    61,    61,
       4,   -34,   -11,    29,   -34,   -34,    34,   -34,    49,   -34,
      46,   -34,    41,    66,   -34,    39,    50,    48,   -34,     4,
      78,   -34,   -34,   -34,   -34,   -34,    60,   -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,    20,    21,     0,     0,
       0,    33,     9,     3,     5,     6,     0,     7,     8,    23,
      24,    25,    26,    10,    12,    39,    40,    41,     0,    29,
       0,     0,     4,    22,     0,    16,     0,     0,     0,     0,
       0,    28,    27,     0,     4,    13,    15,    18,     0,    38,
      35,    36,    37,    32,    34,     0,     0,     0,    19,     0,
       0,    11,     4,    17,    31,    30,     0,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,   -31,   -20,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,    13,   -33,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,    -9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    13,    14,    34,    15,    35,    56,    45,
      46,    47,    16,    17,    18,    19,    20,    21,    60,    22,
      32,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      30,    43,    48,    37,    38,    39,    41,     4,     5,     6,
       7,     8,     9,    55,     3,    10,    25,    26,    27,    36,
      53,    23,    42,    11,    48,    31,    28,    12,    50,    51,
      52,    66,     4,     5,     6,     7,     8,     9,    24,    64,
      10,    33,     4,     5,     6,     7,     8,     9,    11,    54,
      10,    44,    12,     6,     7,    37,    38,    57,    11,    61,
      58,    38,    12,     4,     5,     6,     7,     8,     9,    62,
      63,    10,    25,    26,    27,    59,    37,    38,    39,    11,
      67,     0,    28,    12,    49,    37,    38,    39,    65,    40
};

static const yytype_int8 yycheck[] =
{
       9,    32,    35,    14,    15,    16,     1,     3,     4,     5,
       6,     7,     8,    44,     0,    11,    11,    12,    13,    28,
      40,    11,    31,    19,    57,    17,    21,    23,    37,    38,
      39,    62,     3,     4,     5,     6,     7,     8,    11,    59,
      11,    11,     3,     4,     5,     6,     7,     8,    19,    20,
      11,    19,    23,     5,     6,    14,    15,    23,    19,    20,
      11,    15,    23,     3,     4,     5,     6,     7,     8,    19,
      57,    11,    11,    12,    13,     9,    14,    15,    16,    19,
      20,    -1,    21,    23,    22,    14,    15,    16,    10,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,     0,     3,     4,     5,     6,     7,     8,
      11,    19,    23,    28,    29,    31,    37,    38,    39,    40,
      41,    42,    44,    11,    11,    11,    12,    13,    21,    46,
      46,    17,    45,    11,    30,    32,    46,    14,    15,    16,
      18,     1,    46,    27,    19,    34,    35,    36,    37,    22,
      46,    46,    46,    28,    20,    27,    33,    23,    11,     9,
      43,    20,    19,    36,    28,    10,    27,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    25,    26,    27,    27,    28,    28,    28,    28,    28,
      30,    29,    32,    33,    31,    34,    34,    35,    35,    36,
      37,    37,    38,    39,    39,    39,    39,    40,    40,    41,
      42,    43,    43,    45,    44,    46,    46,    46,    46,    46,
      46,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       0,     6,     0,     0,     8,     1,     0,     3,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     3,     3,     2,
       6,     2,     0,     0,     4,     3,     3,     3,     3,     1,
       1,     1
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
  case 2: /* S: Componentes  */
#line 46 "plp4.y"
                {
        cout << yyvsp[0].cod;
        int tk = yylex();
        if (tk != 0) yyerror("");
    }
#line 1186 "plp4.tab.c"
    break;

  case 3: /* Componentes: Componentes Componente  */
#line 53 "plp4.y"
                                     { yyval.cod = yyvsp[-1].cod + yyvsp[0].cod; }
#line 1192 "plp4.tab.c"
    break;

  case 4: /* Componentes: %empty  */
#line 54 "plp4.y"
              { yyval.cod = ""; }
#line 1198 "plp4.tab.c"
    break;

  case 5: /* Componente: Clase  */
#line 57 "plp4.y"
                   { yyval.cod = yyvsp[0].cod; }
#line 1204 "plp4.tab.c"
    break;

  case 6: /* Componente: Funcion  */
#line 58 "plp4.y"
                     { yyval.cod = yyvsp[0].cod; }
#line 1210 "plp4.tab.c"
    break;

  case 7: /* Componente: Declaracion  */
#line 59 "plp4.y"
                         { yyval.cod = yyvsp[0].cod; }
#line 1216 "plp4.tab.c"
    break;

  case 8: /* Componente: Sentencia  */
#line 60 "plp4.y"
                       { yyval.cod = yyvsp[0].cod; }
#line 1222 "plp4.tab.c"
    break;

  case 9: /* Componente: PYC  */
#line 61 "plp4.y"
                 { yyval.cod = ""; }
#line 1228 "plp4.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 64 "plp4.y"
                 {
          prefixStack.push_back(prefix);
          prefix += yyvsp[0].lexema + "_";
          ts = new TablaSimbolos(ts);
        }
#line 1238 "plp4.tab.c"
    break;

  case 11: /* Clase: CLASS ID $@1 LLAVEI Componentes LLAVED  */
#line 69 "plp4.y"
                                  {
          string className = yyvsp[-4].lexema;
          string pre = prefixStack.back();
          prefix = prefixStack.back();
          prefixStack.pop_back();
          ts = ts->padre;
          yyval.cod = "// class " + pre + className + "\n" + yyvsp[-1].cod + "\n";
        }
#line 1251 "plp4.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 79 "plp4.y"
                 {
            prefixStack.push_back(prefix);
            prefix += yyvsp[0].lexema + "_";
            ts = new TablaSimbolos(ts);
          }
#line 1261 "plp4.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 84 "plp4.y"
                     {
            // No podemos poner el cout aqui
          }
#line 1269 "plp4.tab.c"
    break;

  case 14: /* Funcion: FUN ID $@2 Argumentos $@3 LLAVEI Componentes LLAVED  */
#line 87 "plp4.y"
                                    {
            string funcName = yyvsp[-6].lexema;
            string fullFuncName = prefixStack.back() + funcName;
            string args = yyvsp[-4].cod;
            string body = yyvsp[-1].cod;
            prefix = prefixStack.back();
            prefixStack.pop_back();
            ts = ts->padre;
            yyval.cod = "void " + fullFuncName + "(" + args + ") {\n" + body + "} // " + fullFuncName + "\n\n";
          }
#line 1284 "plp4.tab.c"
    break;

  case 15: /* Argumentos: ArgumentosList  */
#line 99 "plp4.y"
                            { yyval.cod = yyvsp[0].cod; }
#line 1290 "plp4.tab.c"
    break;

  case 16: /* Argumentos: %empty  */
#line 100 "plp4.y"
             { yyval.cod = ""; }
#line 1296 "plp4.tab.c"
    break;

  case 17: /* ArgumentosList: ArgumentosList PYC Argumento  */
#line 103 "plp4.y"
                                              { yyval.cod = yyvsp[-2].cod + "," + yyvsp[0].cod; }
#line 1302 "plp4.tab.c"
    break;

  case 18: /* ArgumentosList: Argumento  */
#line 104 "plp4.y"
                           { yyval.cod = yyvsp[0].cod; }
#line 1308 "plp4.tab.c"
    break;

  case 19: /* Argumento: Tipo ID  */
#line 107 "plp4.y"
                    {
              string trad = "arg_" + prefix + yyvsp[0].lexema;
              if (!ts->set({yyvsp[0].lexema, yyvsp[-1].tipo, trad}))
                  errorSemantico(ERRYADECL, (char*)yyvsp[0].lexema.c_str(), yyvsp[0].nlin, yyvsp[0].ncol);
              yyval.cod = (yyvsp[-1].tipo == ENTERO ? "int " : "float ") + trad;
            }
#line 1319 "plp4.tab.c"
    break;

  case 20: /* Tipo: INT  */
#line 115 "plp4.y"
           { yyval.tipo = ENTERO; }
#line 1325 "plp4.tab.c"
    break;

  case 21: /* Tipo: FLOAT  */
#line 116 "plp4.y"
             { yyval.tipo = REAL; }
#line 1331 "plp4.tab.c"
    break;

  case 22: /* Declaracion: Tipo ID  */
#line 119 "plp4.y"
                      {
                string trad = prefix + yyvsp[0].lexema;
                if (!ts->set({yyvsp[0].lexema, yyvsp[-1].tipo, trad}))
                    errorSemantico(ERRYADECL, (char*)yyvsp[0].lexema.c_str(), yyvsp[0].nlin, yyvsp[0].ncol);
                yyval.cod = "\n" + string(yyvsp[-1].tipo == ENTERO ? "int " : "float ") + trad + ";\n\n";
              }
#line 1342 "plp4.tab.c"
    break;

  case 23: /* Sentencia: Asignacion  */
#line 127 "plp4.y"
                       { yyval.cod = yyvsp[0].cod; }
#line 1348 "plp4.tab.c"
    break;

  case 24: /* Sentencia: Print  */
#line 128 "plp4.y"
                  { yyval.cod = yyvsp[0].cod; }
#line 1354 "plp4.tab.c"
    break;

  case 25: /* Sentencia: IfStmt  */
#line 129 "plp4.y"
                   { yyval.cod = yyvsp[0].cod; }
#line 1360 "plp4.tab.c"
    break;

  case 26: /* Sentencia: Bloque  */
#line 130 "plp4.y"
                   { yyval.cod = yyvsp[0].cod; }
#line 1366 "plp4.tab.c"
    break;

  case 27: /* Asignacion: ID ASIGN Exp  */
#line 133 "plp4.y"
                          {
               Simbolo *s = ts->get(yyvsp[-2].lexema);
               if (!s) errorSemantico(ERRNODECL, (char*)yyvsp[-2].lexema.c_str(), yyvsp[-2].nlin, yyvsp[-2].ncol);
               if (s->tipo == ENTERO && yyvsp[0].tipo == REAL)
                   errorSemantico(ERRTIPOS, (char*)"=", yyvsp[-1].nlin, yyvsp[-1].ncol);
               
               string res = yyvsp[0].cod;
               if (s->tipo == REAL && yyvsp[0].tipo == ENTERO) res = "itor(" + res + ")";
               yyval.cod = "  " + s->nomtrad + " = " + res + ";\n";
             }
#line 1381 "plp4.tab.c"
    break;

  case 28: /* Asignacion: ID ASIGN error  */
#line 143 "plp4.y"
                            { yyerrok; yyval.cod = ""; }
#line 1387 "plp4.tab.c"
    break;

  case 29: /* Print: PRINT Exp  */
#line 146 "plp4.y"
                  {
          if (yyvsp[0].tipo == ENTERO)
              yyval.cod = "  printf(\"%d\"," + yyvsp[0].cod + ");\n";
          else
              yyval.cod = "  printf(\"%f\"," + yyvsp[0].cod + ");\n";
        }
#line 1398 "plp4.tab.c"
    break;

  case 30: /* IfStmt: IF Exp DOSPTOS Componente ElsePart FI  */
#line 154 "plp4.y"
                                               {
           yyval.cod = "if (" + yyvsp[-4].cod + ")\n" + yyvsp[-2].cod + yyvsp[-1].cod;
         }
#line 1406 "plp4.tab.c"
    break;

  case 31: /* ElsePart: ELSE Componente  */
#line 159 "plp4.y"
                           { yyval.cod = "else\n" + yyvsp[0].cod; }
#line 1412 "plp4.tab.c"
    break;

  case 32: /* ElsePart: %empty  */
#line 160 "plp4.y"
           { yyval.cod = ""; }
#line 1418 "plp4.tab.c"
    break;

  case 33: /* $@4: %empty  */
#line 163 "plp4.y"
                {
           prefixStack.push_back(prefix);
           prefix += "_";
           ts = new TablaSimbolos(ts);
         }
#line 1428 "plp4.tab.c"
    break;

  case 34: /* Bloque: LLAVEI $@4 Componentes LLAVED  */
#line 168 "plp4.y"
                            {
           string body = yyvsp[-1].cod;
           prefix = prefixStack.back();
           prefixStack.pop_back();
           ts = ts->padre;
           yyval.cod = "{\n" + body + "}\n\n";
         }
#line 1440 "plp4.tab.c"
    break;

  case 35: /* Exp: Exp AS Exp  */
#line 177 "plp4.y"
                 {
        if (yyvsp[-2].tipo == REAL || yyvsp[0].tipo == REAL) {
            yyval.tipo = REAL;
            yyval.cod = itor(yyvsp[-2]) + " " + yyvsp[-1].lexema + "r " + itor(yyvsp[0]);
        } else {
            yyval.tipo = ENTERO;
            yyval.cod = yyvsp[-2].cod + " " + yyvsp[-1].lexema + "i " + yyvsp[0].cod;
        }
      }
#line 1454 "plp4.tab.c"
    break;

  case 36: /* Exp: Exp MD Exp  */
#line 186 "plp4.y"
                 {
        if (yyvsp[-2].tipo == REAL || yyvsp[0].tipo == REAL) {
            yyval.tipo = REAL;
            yyval.cod = itor(yyvsp[-2]) + " " + yyvsp[-1].lexema + "r " + itor(yyvsp[0]);
        } else {
            yyval.tipo = ENTERO;
            yyval.cod = yyvsp[-2].cod + " " + yyvsp[-1].lexema + "i " + yyvsp[0].cod;
        }
      }
#line 1468 "plp4.tab.c"
    break;

  case 37: /* Exp: Exp REL Exp  */
#line 195 "plp4.y"
                  {
        yyval.tipo = ENTERO;
        string op = yyvsp[-1].lexema;
        if (yyvsp[-2].tipo == REAL || yyvsp[0].tipo == REAL) {
            yyval.cod = itor(yyvsp[-2]) + " " + op + "r " + itor(yyvsp[0]);
        } else {
            yyval.cod = yyvsp[-2].cod + " " + op + "i " + yyvsp[0].cod;
        }
      }
#line 1482 "plp4.tab.c"
    break;

  case 38: /* Exp: PARI Exp PARD  */
#line 204 "plp4.y"
                    {
        yyval.tipo = yyvsp[-1].tipo;
        yyval.cod = "(" + yyvsp[-1].cod + ")";
      }
#line 1491 "plp4.tab.c"
    break;

  case 39: /* Exp: ID  */
#line 208 "plp4.y"
         {
        Simbolo *s = ts->get(yyvsp[0].lexema);
        if (!s) errorSemantico(ERRNODECL, (char*)yyvsp[0].lexema.c_str(), yyvsp[0].nlin, yyvsp[0].ncol);
        yyval.tipo = s->tipo;
        yyval.cod = s->nomtrad;
      }
#line 1502 "plp4.tab.c"
    break;

  case 40: /* Exp: NUMENTERO  */
#line 214 "plp4.y"
                {
        yyval.tipo = ENTERO;
        yyval.cod = yyvsp[0].lexema;
      }
#line 1511 "plp4.tab.c"
    break;

  case 41: /* Exp: NUMREAL  */
#line 218 "plp4.y"
              {
        yyval.tipo = REAL;
        yyval.cod = yyvsp[0].lexema;
      }
#line 1520 "plp4.tab.c"
    break;


#line 1524 "plp4.tab.c"

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

#line 224 "plp4.y"


void errorSemantico(int nerror, char *lexema, int fila, int columna)
{
    fprintf(stderr,"Error semantico (%d,%d): en '%s', ",fila,columna,lexema);
    switch (nerror) {
      case ERRYADECL: fprintf(stderr,"ya existe en este ambito\n");
         break;
      case ERRNODECL: fprintf(stderr,"no ha sido declarado\n");
         break;
      case ERRTIPOS: fprintf(stderr,"tipos incompatibles entero/real\n");
         break;
      case ERRNOSIMPLE: fprintf(stderr,"debe ser de tipo entero o real\n");
         break;
      case ERRNOENTERO: fprintf(stderr,"la expresion debe ser de tipo entero\n");
         break;
    }
    exit(-1);
}

void msgError(int nerror, int nlin, int ncol, const char *s)
{
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
     }
     exit(1);
}

int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,-1,-1,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fent;

    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        yyparse();
    return 0;
}
