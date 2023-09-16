/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "compiler.y"

    #include "compiler_common.h" //Extern variables that communicate with lex
    #define YYDEBUG 1
    int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)
    typedef struct value{
        int i_val;
        float f_val;
        bool b_val;
        char* s_val;
        type_t type;
        bool assign;
    }VALUE;
    typedef struct node{
        int index;
        char name[32]; // variable name
        int mut;
        type_t type;
        int addr;
        int lineno;     
        char * func_sig; // function name
        int mut_val;
        struct node * next;
        type_t ret;      // for function
        struct node * ARR ;      // for array
        int arrnum;
        type_t arrtype;
        VALUE * val;
    }Node;

    typedef struct table{
        Node* head;
        Node* tail;
        int countAddr;           
    }Table;
    int CompNUM = 0;
    int If_cnt =0;
    int ifBlockNumOfTime = 0;
    int while_num = 0;
    int scope = 0;                 // symbol table index
    int addr = -1;
    type_t parameterARR[1024];
    int parameterARR_ID = 0;
    Table* s_table[1024];      // symbol table
    Node* NodeTmp;
    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol();
    static Node*  lookup_symbol();
    static void dump_symbol();
    const char* JavaType();
    /* Global variables */
    bool g_has_error = false;
    FILE *fout = NULL;
    int g_indent_cnt = 0;

    bool HAS_ERROR = false;
    op_t opArr[2048];
    int opArr_ID=0;
    char* arr_name = "";
    int arr_index = 0;
    int arr_num = 0;

    const char* get_type_name(type_t type) {
        switch (type) 
        {
            case TYPE_INT:    return "i32";
            case TYPE_FLOAT:  return "f32";
            case TYPE_BOOL:   return "bool";
            case TYPE_STRING: return "str";
            case TYPE_FUNC:   return "func";
            case TYPE_I2F:    return "i2f";
            case TYPE_F2I:    return "f2i";
            case TYPE_ARR:    return "array";
            default:          return "undefined";
        }
    } 
    const char* get_rettype_name(type_t type) {
        switch (type) 
        {
            case TYPE_INT:    return "ireturn";
            case TYPE_FLOAT:  return "freturn";
            case TYPE_BOOL:   return "breturn";
            case TYPE_STRING: return "sreturn";
            case TYPE_FUNC:   return "func";
            case TYPE_I2F:    return "i2freturn";
            case TYPE_F2I:    return "f2ireturn";
            case TYPE_ARR:    return "arrreturn";
            default:          return "undefined";
        }
    } 
    const char* get_parametertype_name(type_t type) {
        switch (type) 
        {
            case TYPE_INT:    return "I";
            case TYPE_FLOAT:  return "F";
            case TYPE_BOOL:   return "B";
            case TYPE_STRING: return "S";
            case TYPE_FUNC:   return "FUNC";
            case TYPE_I2F:    return "I2F";
            case TYPE_F2I:    return "F2I";
            case TYPE_ARR:    return "ARR";
            default:          return "undefined";
        }
    } 
    const char* get_op_name(op_t op){
        switch (op) 
        {
            case OP_LSHIFT:     return "LSHIFT";
            case OP_RSHIFT:     return "RSHIFT";
            case OP_ADD:        return "ADD";
            case OP_SUB:        return "SUB";
            case OP_MUL:        return "MUL";
            case OP_DIV:        return "DIV";
            case OP_REM:        return "REM"; 
            case OP_EQL:        return "EQL";
            case OP_NEQ:        return "NEQ";
            case OP_LSS:        return "LSS";
            case OP_LEQ:        return "LEQ";
            case OP_GTR:        return "GTR";
            case OP_GEQ:        return "GEQ";
            case OP_POS:        return "POS";
            case OP_NEG:        return "NEG";
            case OP_NOT:        return "NOT";
            case OP_LOR:        return "LOR";
            case OP_LAND:       return "LAND";
            case OP_ASSIGN:     return "ASSIGN";
            case OP_SUB_ASSIGN: return "SUB_ASSIGN";
            case OP_ADD_ASSIGN: return "ADD_ASSIGN";
            case OP_MUL_ASSIGN: return "MUL_ASSIGN";
            case OP_DIV_ASSIGN: return "DIV_ASSIGN";    
            case OP_REM_ASSIGN: return "REM_ASSIGN";
            default:            return "ERROR";
        }
    }

#line 232 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LET = 258,
    MUT = 259,
    NEWLINE = 260,
    INT = 261,
    FLOAT = 262,
    BOOL = 263,
    STRING = 264,
    TRUE = 265,
    FALSE = 266,
    GTR = 267,
    LSS = 268,
    GEQ = 269,
    LEQ = 270,
    EQL = 271,
    NEQ = 272,
    LOR = 273,
    LAND = 274,
    ASSIGN = 275,
    ADD_ASSIGN = 276,
    SUB_ASSIGN = 277,
    MUL_ASSIGN = 278,
    DIV_ASSIGN = 279,
    REM_ASSIGN = 280,
    IF = 281,
    ELSE = 282,
    FOR = 283,
    WHILE = 284,
    LOOP = 285,
    SWITCH = 286,
    CASE = 287,
    DEFAULT = 288,
    PRINT = 289,
    PRINTLN = 290,
    ADDR = 291,
    FUNC = 292,
    RETURN = 293,
    BREAK = 294,
    ID = 295,
    ARROW = 296,
    AS = 297,
    IN = 298,
    DOTDOT = 299,
    RSHIFT = 300,
    LSHIFT = 301,
    IDENT = 302,
    LBRACE = 303,
    RBRACE = 304,
    LBRACK = 305,
    RBRACK = 306,
    LPAREN = 307,
    RPAREN = 308,
    INC = 309,
    DEC = 310,
    VAR = 311,
    COLON = 312,
    SEMICOLON = 313,
    COMMA = 314,
    PACKAGE = 315,
    ADD = 316,
    SUB = 317,
    NOT = 318,
    MUL = 319,
    DIV = 320,
    REM = 321,
    INT_LIT = 322,
    FLOAT_LIT = 323,
    BOOL_LIT = 324,
    STRING_LIT = 325,
    MUT_LIT = 326
  };
#endif
/* Tokens.  */
#define LET 258
#define MUT 259
#define NEWLINE 260
#define INT 261
#define FLOAT 262
#define BOOL 263
#define STRING 264
#define TRUE 265
#define FALSE 266
#define GTR 267
#define LSS 268
#define GEQ 269
#define LEQ 270
#define EQL 271
#define NEQ 272
#define LOR 273
#define LAND 274
#define ASSIGN 275
#define ADD_ASSIGN 276
#define SUB_ASSIGN 277
#define MUL_ASSIGN 278
#define DIV_ASSIGN 279
#define REM_ASSIGN 280
#define IF 281
#define ELSE 282
#define FOR 283
#define WHILE 284
#define LOOP 285
#define SWITCH 286
#define CASE 287
#define DEFAULT 288
#define PRINT 289
#define PRINTLN 290
#define ADDR 291
#define FUNC 292
#define RETURN 293
#define BREAK 294
#define ID 295
#define ARROW 296
#define AS 297
#define IN 298
#define DOTDOT 299
#define RSHIFT 300
#define LSHIFT 301
#define IDENT 302
#define LBRACE 303
#define RBRACE 304
#define LBRACK 305
#define RBRACK 306
#define LPAREN 307
#define RPAREN 308
#define INC 309
#define DEC 310
#define VAR 311
#define COLON 312
#define SEMICOLON 313
#define COMMA 314
#define PACKAGE 315
#define ADD 316
#define SUB 317
#define NOT 318
#define MUL 319
#define DIV 320
#define REM 321
#define INT_LIT 322
#define FLOAT_LIT 323
#define BOOL_LIT 324
#define STRING_LIT 325
#define MUT_LIT 326

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 172 "compiler.y"

     struct {
        union {
            int i_val;
            float f_val;
            bool b_val;
            char* s_val;
        };
        type_t type;
    } val;
    char *s_val;
    op_t op;
    type_t type;
    int mut_val;

#line 442 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   597

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  288

#define YYUNDEFTOK  2
#define YYMAXUTOK   326


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   230,   230,   230,   234,   235,   241,   242,   243,   244,
     245,   294,   295,   298,   299,   300,   303,   306,   307,   307,
     314,   317,   317,   324,   327,   327,   334,   334,   348,   348,
     356,   356,   371,   371,   386,   386,   400,   403,   403,   420,
     423,   423,   458,   461,   462,   470,   471,   472,   475,   475,
     491,   500,   505,   512,   513,   517,   521,   522,   550,   562,
     561,   596,   599,   599,   600,   600,   601,   604,   610,   616,
     621,   628,   629,   630,   631,   632,   633,   637,   684,   685,
     691,   692,   696,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   713,   717,   718,   722,
     723,   724,   728,   728,   736,   741,   746,   753,   753,   758,
     758,   766,   766,   766,   769,   769,   773,   774,   775,   778,
     779,   807,   811,   815,   820,   823,   824,   829,   848,   861,
     883,   896,   910,   925,   940,   940,   957,   972,   992,  1010,
    1031,  1032,  1038,  1037,  1061,  1060,  1089,  1096,  1097,  1105,
    1104,  1121,  1120,  1136,  1135,  1157,  1156,  1184,  1197,  1205,
    1215,  1219
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LET", "MUT", "NEWLINE", "INT", "FLOAT",
  "BOOL", "STRING", "TRUE", "FALSE", "GTR", "LSS", "GEQ", "LEQ", "EQL",
  "NEQ", "LOR", "LAND", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "REM_ASSIGN", "IF", "ELSE", "FOR", "WHILE", "LOOP",
  "SWITCH", "CASE", "DEFAULT", "PRINT", "PRINTLN", "ADDR", "FUNC",
  "RETURN", "BREAK", "ID", "ARROW", "AS", "IN", "DOTDOT", "RSHIFT",
  "LSHIFT", "IDENT", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "LPAREN",
  "RPAREN", "INC", "DEC", "VAR", "COLON", "SEMICOLON", "COMMA", "PACKAGE",
  "ADD", "SUB", "NOT", "MUL", "DIV", "REM", "INT_LIT", "FLOAT_LIT",
  "BOOL_LIT", "STRING_LIT", "MUT_LIT", "$accept", "Program", "$@1",
  "GlobalStatementList", "Type", "add_op", "mul_op", "unary_op",
  "Expression", "$@2", "Expression2", "$@3", "Expression3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "Expression4", "$@10", "Expression5", "$@11",
  "Expression6", "UnaryExpr", "functionCall", "$@12",
  "ParameterListInFunctionCall", "PrimaryExpr", "ConversionExpr",
  "Operand", "$@13", "Interindex", "$@14", "$@15", "Literal", "assign_op",
  "AssignmentStmt", "IncDecStmt", "StatementList", "Statement",
  "LOOPStatement", "DeclarationStmt", "SimpleStmt", "Block", "$@16",
  "IfStmt", "IfBlock", "$@17", "$@18", "WhileStmt", "$@19", "$@20",
  "WhileBlock", "$@21", "ForStmt", "ForClause", "InitStmt", "Condition",
  "PostStmt", "SwitchStmt", "CaseStmt", "LetStatement", "$@22",
  "LiteralList", "LetStatementCon", "PrintStmt", "$@23", "$@24",
  "ReturnStmt", "GlobalStatement", "FunctionDeclStmt", "$@25", "$@26",
  "$@27", "$@28", "FuncOpen", "ParameterList", "FuncBlock",
  "ExpressionStmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326
};
# endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-162)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -109,    31,    18,  -109,  -109,     2,    18,  -109,  -109,     1,
    -109,  -109,    -7,    14,    42,    32,   192,   192,    24,   303,
      33,  -109,  -109,  -109,  -109,    75,  -109,  -109,   458,  -109,
     192,  -109,    35,  -109,    24,    28,  -109,    30,    50,  -109,
      30,    11,    30,    30,    85,    30,   257,   226,  -109,    30,
    -109,  -109,  -109,  -109,  -109,    44,    30,   542,    68,   203,
     -21,    93,  -109,   488,    47,  -109,  -109,  -109,  -109,  -109,
    -109,   218,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    96,  -109,  -109,  -109,  -109,    24,   192,  -109,
      82,     5,   -22,   105,  -109,    79,    58,   493,  -109,    80,
      76,    87,    30,   105,    88,    89,   105,   105,   108,  -109,
     101,    -6,   103,   109,   335,   113,   458,    16,    30,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,    30,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,   192,  -109,  -109,  -109,   257,  -109,
      24,  -109,  -109,     7,   108,   158,   122,   145,   108,   458,
     147,    30,   152,  -109,    87,    87,   137,   138,   -20,  -109,
    -109,  -109,   108,    30,   130,   266,  -109,    27,    30,     3,
      30,    30,    30,    30,    30,    30,    30,    30,    30,  -109,
     144,  -109,   108,   192,   148,   192,    -4,   458,   131,    55,
    -109,   314,    87,   149,    87,   155,  -109,  -109,  -109,  -109,
    -109,   162,   185,   177,   172,   105,   187,  -109,  -109,    68,
     197,  -109,   203,   -21,   -21,   -21,   -21,   -21,   -21,    93,
    -109,  -109,   183,     9,  -109,   184,   503,  -109,   362,  -109,
    -109,  -109,  -109,  -109,    30,  -109,  -109,  -109,   257,  -109,
     200,  -109,   108,  -109,  -109,    72,  -109,   108,    87,  -109,
     190,  -109,  -109,  -109,   458,  -109,   257,  -109,  -109,   201,
     204,   202,  -109,   410,  -109,  -109,   223,  -109,  -109,   211,
    -109,   257,   205,   212,   257,   207,  -109,  -109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,   148,     0,     3,     5,   147,     0,
     157,     4,     0,     0,   149,     0,     0,     0,     0,     0,
       0,     6,     7,     9,     8,     0,   158,   153,     0,   150,
       0,   151,     0,    10,     0,     0,    92,     0,     0,   111,
       0,     0,     0,     0,     0,     0,     0,    57,   102,     0,
      16,    67,    68,    69,    70,     0,     0,   161,    20,    23,
      36,    39,    42,    17,    47,    45,    54,    53,    56,    99,
     101,     0,    81,    95,    82,    83,    84,    85,    93,    86,
      87,    88,   141,    90,    91,   100,   155,     0,     0,   154,
       0,     0,    57,   122,    47,     0,    57,   122,   121,     0,
       0,     0,     0,   124,     0,     0,   142,   144,     0,    57,
       0,     0,     0,    48,    97,     0,     0,     0,     0,    46,
      18,    71,    72,    73,    74,    75,    76,    78,    79,     0,
      21,    32,    28,    34,    30,    24,    26,    11,    12,    37,
      13,    14,    15,    40,     0,    94,   160,    80,     0,    89,
       0,   152,   159,     0,     0,     0,   107,   105,     0,     0,
       0,     0,     0,   112,     0,     0,     0,     0,     0,   146,
      96,    50,     0,     0,     0,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
       0,   156,     0,     0,     0,     0,     0,     0,     0,     0,
     120,     0,     0,     0,     0,     0,   126,   125,   143,   145,
      62,     0,     0,     0,    51,    98,     0,   103,    55,    19,
      43,    77,    22,    33,    29,    35,    31,    25,    27,    38,
      41,   140,     0,     0,   136,     0,     0,   128,     0,   110,
     106,   104,   118,   117,     0,   116,   114,   113,     0,    58,
      64,    49,     0,    60,   133,     0,   130,     0,     0,   131,
       0,   108,   123,   119,     0,    63,     0,    52,   132,     0,
       0,     0,   127,     0,    65,   129,     0,   137,   115,     0,
     134,     0,   139,     0,     0,     0,   138,   135
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,  -109,   -12,  -109,  -109,  -109,   -23,  -109,
      90,  -109,    97,  -109,  -109,  -109,  -109,  -109,  -109,   222,
    -109,    92,  -109,    94,     4,   -28,  -109,    37,  -109,  -109,
     -43,  -109,  -109,  -109,  -109,   -44,   166,  -109,  -109,  -108,
     -68,  -109,  -109,   -32,   -90,  -109,    84,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,   -25,  -109,
    -109,  -109,  -109,  -109,     0,  -109,  -109,  -109,  -109,  -109,
     284,  -109,  -109,  -109,  -109,  -109,  -109,  -109,   -24,  -109
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    55,   139,   143,    56,    57,   178,
      58,   180,    59,   185,   186,   182,   184,   181,   183,    60,
     187,    61,   188,    62,    63,    94,   172,   213,    65,    66,
      67,   115,   211,   248,   266,    68,   129,    69,    70,    71,
      72,    73,    74,    75,    76,   116,    77,   157,   197,   198,
      78,   102,   205,   247,   264,    79,    99,   100,    95,   263,
      80,    81,    82,   281,   283,   149,    83,   166,   167,    84,
       7,     8,    18,    87,    34,   150,     9,    15,    29,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   110,   112,   147,    26,    27,    98,    31,   175,   160,
      89,   162,   120,   101,    93,    97,   236,   103,    86,   106,
     107,   120,   111,     4,   210,   154,   117,   192,   -59,   255,
     113,     3,    90,    13,   120,   114,    21,    22,    23,    24,
     137,   138,    10,    64,   104,   120,    14,    51,    52,    53,
      54,   201,   169,    12,   237,     5,    21,    22,    23,    24,
     119,   221,   155,   151,   193,   110,    44,   256,    91,   176,
      92,    16,    28,    32,   206,   207,   152,   163,   105,    93,
     218,    37,    49,    17,    33,    19,    44,   130,    64,   238,
      96,    20,    88,    50,    33,   177,   118,    51,    52,    53,
      54,   158,    49,    48,   190,   145,   179,   147,   -59,   240,
     113,   194,   243,    50,   245,   200,   148,    51,    52,    53,
      54,   108,   153,   120,   212,   109,   191,   156,   159,   214,
     268,    64,   189,   147,   161,    48,   203,    49,    93,    51,
      52,    53,    54,   196,   108,   164,   165,    64,   109,   232,
     215,   168,    51,    52,    53,    54,   273,   140,   141,   142,
      49,   170,   171,   174,    21,    22,    23,    24,   271,    64,
     147,  -109,   199,    64,   202,    51,    52,    53,    54,   204,
     239,   233,   220,   235,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   260,    25,   208,   209,   216,    21,    22,
      23,    24,   231,   246,   265,   147,   234,   244,   195,   214,
      64,   269,   262,   249,   270,   131,   132,   133,   134,   135,
     136,    35,   274,    36,    21,    22,    23,    24,    25,   250,
     251,   252,    21,    22,    23,    24,    64,   282,   253,   144,
     282,   254,   257,   279,    37,    64,    38,    39,   272,    40,
      41,   -66,    42,    43,    44,   276,    45,    46,    47,   275,
     277,   280,    25,   285,   284,   287,    48,   146,   219,    35,
      49,    36,    21,    22,    23,    24,   -59,   222,   113,   229,
     173,    50,   230,   241,   286,    51,    52,    53,    54,   267,
      11,     0,    37,     0,    38,    39,     0,    40,    41,     0,
      42,    43,    44,     0,    45,    46,    47,     0,     0,    21,
      22,    23,    24,     0,    48,   217,     0,    35,    49,    36,
      21,    22,    23,    24,    51,    52,    53,    54,     0,    50,
       0,     0,     0,    51,    52,    53,    54,     0,     0,    25,
      37,     0,    38,    39,    30,    40,    41,     0,    42,    43,
      44,     0,    45,    46,    47,   121,   122,   123,   124,   125,
     126,     0,    48,   242,     0,    35,    49,    36,    21,    22,
      23,    24,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,    52,    53,    54,     0,     0,     0,    37,     0,
      38,    39,     0,    40,    41,     0,    42,    43,    44,     0,
      45,    46,    47,   223,   224,   225,   226,   227,   228,     0,
      48,   261,     0,    35,    49,    36,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    50,     0,     0,     0,    51,
      52,    53,    54,     0,     0,     0,    37,     0,    38,    39,
       0,    40,    41,     0,    42,    43,    44,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,     0,    48,   278,
       0,    35,    49,    36,    21,    22,    23,    24,     0,     0,
       0,     0,     0,    50,     0,     0,     0,    51,    52,    53,
      54,     0,     0,     0,    37,     0,    38,    39,     0,    40,
      41,     0,    42,    43,    44,     0,    45,    46,    47,     0,
     -43,   -43,   -43,   -43,   -43,   -43,    48,   -43,     0,     0,
      49,   120,     0,   121,   122,   123,   124,   125,   126,     0,
       0,    50,     0,     0,     0,    51,    52,    53,    54,     0,
     144,     0,     0,   258,     0,     0,     0,     0,     0,   108,
       0,     0,     0,   109,     0,     0,     0,   127,   128,   -43,
     -43,  -161,   -43,   -43,   -43,    49,     0,     0,     0,     0,
     120,   259,   121,   122,   123,   124,   125,   126,     0,     0,
      51,    52,    53,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128
};

static const yytype_int16 yycheck[] =
{
      28,    44,    46,    71,    16,    17,    38,    19,   116,    99,
      34,   101,    18,    38,    37,    38,    20,    40,    30,    42,
      43,    18,    45,     5,    44,    20,    49,    20,    50,    20,
      52,     0,     4,    40,    18,    47,     6,     7,     8,     9,
      61,    62,    40,    71,    33,    18,    53,    67,    68,    69,
      70,   159,    58,    52,    58,    37,     6,     7,     8,     9,
      56,    58,    57,    87,    57,   108,    36,    58,    40,    53,
      40,    57,    48,    40,   164,   165,    88,   102,    67,   102,
      53,    26,    52,    41,     9,    53,    36,    19,   116,   197,
      40,    59,    57,    63,     9,   118,    52,    67,    68,    69,
      70,    43,    52,    48,   148,    58,   129,   175,    50,   199,
      52,   154,   202,    63,   204,   158,    20,    67,    68,    69,
      70,    36,    40,    18,   168,    40,   150,    48,    48,   172,
      58,   159,   144,   201,    58,    48,   161,    52,   161,    67,
      68,    69,    70,   155,    36,    57,    57,   175,    40,   192,
     173,    50,    67,    68,    69,    70,   264,    64,    65,    66,
      52,    58,    53,    50,     6,     7,     8,     9,   258,   197,
     238,    49,    27,   201,    27,    67,    68,    69,    70,    27,
      49,   193,   178,   195,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   236,    36,    58,    58,    67,     6,     7,
       8,     9,    58,    48,   248,   273,    58,    58,    50,   252,
     238,   255,   244,    51,   257,    12,    13,    14,    15,    16,
      17,     3,   266,     5,     6,     7,     8,     9,    36,    44,
      53,    59,     6,     7,     8,     9,   264,   281,    51,    42,
     284,    58,    58,    20,    26,   273,    28,    29,    58,    31,
      32,    51,    34,    35,    36,    51,    38,    39,    40,    58,
      58,    50,    36,    51,    59,    58,    48,    49,   178,     3,
      52,     5,     6,     7,     8,     9,    50,   180,    52,   187,
     114,    63,   188,   199,   284,    67,    68,    69,    70,   252,
       6,    -1,    26,    -1,    28,    29,    -1,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    -1,    -1,     6,
       7,     8,     9,    -1,    48,    49,    -1,     3,    52,     5,
       6,     7,     8,     9,    67,    68,    69,    70,    -1,    63,
      -1,    -1,    -1,    67,    68,    69,    70,    -1,    -1,    36,
      26,    -1,    28,    29,    41,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    20,    21,    22,    23,    24,
      25,    -1,    48,    49,    -1,     3,    52,     5,     6,     7,
       8,     9,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    26,    -1,
      28,    29,    -1,    31,    32,    -1,    34,    35,    36,    -1,
      38,    39,    40,   181,   182,   183,   184,   185,   186,    -1,
      48,    49,    -1,     3,    52,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,    26,    -1,    28,    29,
      -1,    31,    32,    -1,    34,    35,    36,    -1,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,     3,    52,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    26,    -1,    28,    29,    -1,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    40,    -1,
      12,    13,    14,    15,    16,    17,    48,    19,    -1,    -1,
      52,    18,    -1,    20,    21,    22,    23,    24,    25,    -1,
      -1,    63,    -1,    -1,    -1,    67,    68,    69,    70,    -1,
      42,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    54,    55,    61,
      62,    58,    64,    65,    66,    52,    -1,    -1,    -1,    -1,
      18,    58,    20,    21,    22,    23,    24,    25,    -1,    -1,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,    74,     0,     5,    37,    75,   142,   143,   148,
      40,   142,    52,    40,    53,   149,    57,    41,   144,    53,
      59,     6,     7,     8,     9,    36,    76,    76,    48,   150,
      41,    76,    40,     9,   146,     3,     5,    26,    28,    29,
      31,    32,    34,    35,    36,    38,    39,    40,    48,    52,
      63,    67,    68,    69,    70,    76,    79,    80,    82,    84,
      91,    93,    95,    96,    97,   100,   101,   102,   107,   109,
     110,   111,   112,   113,   114,   115,   116,   118,   122,   127,
     132,   133,   134,   138,   141,   151,    76,   145,    57,   150,
       4,    40,    40,    80,    97,   130,    40,    80,   115,   128,
     129,   130,   123,    80,    33,    67,    80,    80,    36,    40,
     102,    80,   107,    52,    76,   103,   117,    80,    52,    96,
      18,    20,    21,    22,    23,    24,    25,    54,    55,   108,
      19,    12,    13,    14,    15,    16,    17,    61,    62,    77,
      64,    65,    66,    78,    42,    58,    49,   112,    20,   137,
     147,   150,    76,    40,    20,    57,    48,   119,    43,    48,
     116,    58,   116,   130,    57,    57,   139,   140,    50,    58,
      58,    53,    98,   108,    50,   111,    53,    80,    81,    80,
      83,    89,    87,    90,    88,    85,    86,    92,    94,    76,
     107,   150,    20,    57,   102,    50,    76,   120,   121,    27,
     102,   111,    27,   130,    27,   124,   116,   116,    58,    58,
      44,   104,   107,    99,   102,    80,    67,    49,    53,    82,
      96,    58,    84,    91,    91,    91,    91,    91,    91,    93,
      95,    58,   102,    76,    58,    76,    20,    58,   111,    49,
     116,   118,    49,   116,    58,   116,    48,   125,   105,    51,
      44,    53,    59,    51,    58,    20,    58,    58,    30,    58,
     102,    49,   115,   131,   126,   107,   106,    99,    58,   107,
     102,   116,    58,   111,   107,    58,    51,    58,    49,    20,
      50,   135,   107,   136,    59,    51,   136,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    74,    73,    75,    75,    76,    76,    76,    76,
      76,    77,    77,    78,    78,    78,    79,    80,    81,    80,
      80,    83,    82,    82,    85,    84,    86,    84,    87,    84,
      88,    84,    89,    84,    90,    84,    84,    92,    91,    91,
      94,    93,    93,    95,    95,    96,    96,    96,    98,    97,
      97,    99,    99,   100,   100,   101,   102,   102,   102,   103,
     102,   102,   105,   104,   106,   104,   104,   107,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   109,   110,   110,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   113,   114,   114,   115,
     115,   115,   117,   116,   118,   118,   118,   120,   119,   121,
     119,   123,   124,   122,   126,   125,   127,   127,   127,   128,
     128,   129,   130,   131,   132,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   135,   134,   134,   134,   136,   136,
     137,   137,   139,   138,   140,   138,   141,   142,   142,   144,
     143,   145,   143,   146,   143,   147,   143,   148,   149,   149,
     150,   151
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     4,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     1,
       0,     4,     1,     1,     3,     1,     2,     1,     0,     5,
       3,     1,     3,     1,     1,     4,     1,     1,     5,     0,
       5,     3,     0,     3,     0,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     3,     2,     4,     1,
       1,     1,     0,     4,     5,     3,     5,     0,     4,     0,
       3,     0,     0,     5,     0,     4,     5,     5,     5,     5,
       3,     1,     1,     1,     2,     4,     4,     7,     5,     8,
       6,     6,     7,     6,     0,    14,     5,     8,     3,     1,
       3,     0,     0,     4,     0,     4,     3,     1,     1,     0,
       5,     0,     7,     0,     7,     0,     8,     2,     3,     5,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 230 "compiler.y"
       {create_symbol(scope);scope++;}
#line 1905 "y.tab.c"
    break;

  case 3:
#line 230 "compiler.y"
                                                           { dump_symbol(); }
#line 1911 "y.tab.c"
    break;

  case 6:
#line 241 "compiler.y"
                  {  (yyval.type) = TYPE_INT; }
#line 1917 "y.tab.c"
    break;

  case 7:
#line 242 "compiler.y"
                  {  (yyval.type) = TYPE_FLOAT; }
#line 1923 "y.tab.c"
    break;

  case 8:
#line 243 "compiler.y"
                  {  (yyval.type) = TYPE_STRING; }
#line 1929 "y.tab.c"
    break;

  case 9:
#line 244 "compiler.y"
                  {  (yyval.type) = TYPE_BOOL; }
#line 1935 "y.tab.c"
    break;

  case 10:
#line 245 "compiler.y"
                  {  (yyval.type) = TYPE_STRING; }
#line 1941 "y.tab.c"
    break;

  case 11:
#line 294 "compiler.y"
           {  (yyval.op) = OP_ADD; }
#line 1947 "y.tab.c"
    break;

  case 12:
#line 295 "compiler.y"
           {  (yyval.op) = OP_SUB; }
#line 1953 "y.tab.c"
    break;

  case 13:
#line 298 "compiler.y"
           {  (yyval.op) = OP_MUL; }
#line 1959 "y.tab.c"
    break;

  case 14:
#line 299 "compiler.y"
           {  (yyval.op) = OP_DIV; }
#line 1965 "y.tab.c"
    break;

  case 15:
#line 300 "compiler.y"
           {  (yyval.op) = OP_REM; }
#line 1971 "y.tab.c"
    break;

  case 16:
#line 303 "compiler.y"
           {  (yyval.op) = OP_NOT; }
#line 1977 "y.tab.c"
    break;

  case 17:
#line 306 "compiler.y"
                { (yyval.val) = (yyvsp[0].val); }
#line 1983 "y.tab.c"
    break;

  case 18:
#line 307 "compiler.y"
                     { opArr[opArr_ID] = OP_LOR; opArr_ID++; }
#line 1989 "y.tab.c"
    break;

  case 19:
#line 308 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        printf("ior");
        CODEGEN("ior\n");
    }
#line 2000 "y.tab.c"
    break;

  case 20:
#line 314 "compiler.y"
                  { (yyval.val) = (yyvsp[0].val);}
#line 2006 "y.tab.c"
    break;

  case 21:
#line 317 "compiler.y"
                       { opArr[opArr_ID] = OP_LAND; opArr_ID++; }
#line 2012 "y.tab.c"
    break;

  case 22:
#line 318 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val & (yyvsp[0].val).b_val;
        printf("iand\n");
        CODEGEN("iand\n");
    }
#line 2023 "y.tab.c"
    break;

  case 23:
#line 324 "compiler.y"
                  { (yyval.val) = (yyvsp[0].val);}
#line 2029 "y.tab.c"
    break;

  case 24:
#line 327 "compiler.y"
                      { opArr[opArr_ID] = OP_EQL; opArr_ID++; }
#line 2035 "y.tab.c"
    break;

  case 25:
#line 328 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }      
    }
#line 2046 "y.tab.c"
    break;

  case 26:
#line 334 "compiler.y"
                      { opArr[opArr_ID] = OP_NEQ; opArr_ID++; }
#line 2052 "y.tab.c"
    break;

  case 27:
#line 335 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }     
        CODEGEN("ifle comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;          
    }
#line 2070 "y.tab.c"
    break;

  case 28:
#line 348 "compiler.y"
                      { opArr[opArr_ID] = OP_LSS; opArr_ID++; }
#line 2076 "y.tab.c"
    break;

  case 29:
#line 349 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }                                 

    }
#line 2088 "y.tab.c"
    break;

  case 30:
#line 356 "compiler.y"
                      { opArr[opArr_ID] = OP_LEQ; opArr_ID++; }
#line 2094 "y.tab.c"
    break;

  case 31:
#line 357 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }    
        CODEGEN("ifle comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;                             
    
    }
#line 2113 "y.tab.c"
    break;

  case 32:
#line 371 "compiler.y"
                      { opArr[opArr_ID] = OP_GTR; opArr_ID++; }
#line 2119 "y.tab.c"
    break;

  case 33:
#line 372 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else{                      CODEGEN("isub\n");  }   
        CODEGEN("ifgt comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;                              
       
    }
#line 2138 "y.tab.c"
    break;

  case 34:
#line 386 "compiler.y"
                      { opArr[opArr_ID] = OP_GEQ; opArr_ID++; }
#line 2144 "y.tab.c"
    break;

  case 35:
#line 387 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).b_val = (yyvsp[-3].val).b_val | (yyvsp[0].val).b_val;
        if(!strcmp(get_type_name((yyvsp[0].val).type),"f32")){ CODEGEN("fcmpl\n"); }
        else{                      CODEGEN("isub\n");  }   
        CODEGEN("ifge comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;  
    }
#line 2162 "y.tab.c"
    break;

  case 36:
#line 400 "compiler.y"
                  { (yyval.val) = (yyvsp[0].val);}
#line 2168 "y.tab.c"
    break;

  case 37:
#line 403 "compiler.y"
                         { opArr[opArr_ID] = (yyvsp[0].op); opArr_ID++; }
#line 2174 "y.tab.c"
    break;

  case 38:
#line 404 "compiler.y"
    {
        opArr_ID--;
        while(opArr_ID>=0){ opArr_ID--; }
        opArr_ID =0;  
        switch((yyvsp[-2].op)){
            case OP_ADD:
                if((yyvsp[0].val).type == TYPE_INT )                           { CODEGEN("iadd\n"); }
                else                                               { CODEGEN("fadd\n"); }
                break;
            case OP_SUB:
                if((yyvsp[0].val).type == TYPE_INT)                            { CODEGEN("isub\n"); }
                else                                               { CODEGEN("fsub\n"); }
                break;
        }
        (yyval.val) = (yyvsp[0].val);
    }
#line 2195 "y.tab.c"
    break;

  case 40:
#line 423 "compiler.y"
                         { opArr[opArr_ID] = (yyvsp[0].op); opArr_ID++; }
#line 2201 "y.tab.c"
    break;

  case 41:
#line 424 "compiler.y"
    {
        if ((((yyvsp[-3].val).type == TYPE_FLOAT) && ((yyvsp[0].val).type == TYPE_INT ))|| (((yyvsp[-3].val).type == TYPE_INT) && ((yyvsp[0].val).type == TYPE_FLOAT ))){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        }
        if ((yyvsp[-3].val).type == TYPE_NULL || (yyvsp[0].val).type == TYPE_NULL){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        }
        if ((((yyvsp[-3].val).type == TYPE_FLOAT) || ((yyvsp[0].val).type == TYPE_FLOAT)) && (opArr[opArr_ID] == OP_REM)){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        }
        else if (((yyvsp[-3].val).type == TYPE_FLOAT) || ((yyvsp[0].val).type == TYPE_FLOAT)) (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val) = (yyvsp[0].val);
        opArr_ID--;
        while(opArr_ID>=0) { printf("%s\n",get_op_name(opArr[opArr_ID])); opArr_ID--; }
        opArr_ID =0;  
        switch((yyvsp[-2].op)){
            case OP_MUL:
                if((yyvsp[0].val).type == TYPE_INT){ CODEGEN("imul\n"); }
                else                   { CODEGEN("fmul\n"); }
                break;
            case OP_DIV:
                if((yyvsp[0].val).type == TYPE_INT){ CODEGEN("idiv\n"); }
                else{                    CODEGEN("fdiv\n"); }
                break;
            case OP_REM:
                if((yyvsp[0].val).type == TYPE_INT){ CODEGEN("irem\n"); }
                break;
        }
        (yyval.val) = (yyvsp[0].val);
    }
#line 2240 "y.tab.c"
    break;

  case 42:
#line 458 "compiler.y"
                  {(yyval.val) = (yyvsp[0].val);}
#line 2246 "y.tab.c"
    break;

  case 43:
#line 461 "compiler.y"
                {(yyval.val) = (yyvsp[0].val);}
#line 2252 "y.tab.c"
    break;

  case 44:
#line 463 "compiler.y"
    { 
        if     ( (yyvsp[-2].val).type == TYPE_INT && (yyvsp[0].type) == TYPE_FLOAT) { CODEGEN("i2f\n");(yyval.val).f_val = (yyvsp[-2].val).i_val; (yyval.val).type = (yyvsp[0].type); }
        else if( (yyvsp[-2].val).type == TYPE_FLOAT && (yyvsp[0].type) == TYPE_INT) { CODEGEN("f2i\n");(yyval.val).i_val = (yyvsp[-2].val).f_val; (yyval.val).type = (yyvsp[0].type); }
        else                                              { (yyval.val).s_val = (yyvsp[-2].val).s_val; (yyval.val).type = (yyvsp[0].type); }
    }
#line 2262 "y.tab.c"
    break;

  case 45:
#line 470 "compiler.y"
                  { (yyval.val) = (yyvsp[0].val); (yyval.val).type = (yyvsp[0].val).type; }
#line 2268 "y.tab.c"
    break;

  case 46:
#line 471 "compiler.y"
                         { (yyval.val).type = (yyvsp[0].val).type; (yyval.val) = (yyvsp[0].val); }
#line 2274 "y.tab.c"
    break;

  case 48:
#line 475 "compiler.y"
                { parameterARR_ID=0;}
#line 2280 "y.tab.c"
    break;

  case 49:
#line 476 "compiler.y"
    {
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));
        //if(parameterARR_ID==0) strcat(sig,"V");
        strcat(sig,")");

        Node * func = lookup_symbol((yyvsp[-4].s_val),0);

        if(func!=NULL)
        {
            strcat(sig,get_parametertype_name(func->ret));
            func->func_sig = sig;
        }
        CODEGEN("\tinvokestatic Main/%s%s\n", (yyvsp[-4].s_val), sig);
    }
#line 2300 "y.tab.c"
    break;

  case 50:
#line 492 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-2].s_val),0);
        char *sig = "()V";
        func->func_sig = sig;
        CODEGEN("\tinvokestatic Main/%s%s\n", (yyvsp[-2].s_val), sig);
    }
#line 2311 "y.tab.c"
    break;

  case 51:
#line 501 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[0].val).type;
        parameterARR_ID++;
    }
#line 2320 "y.tab.c"
    break;

  case 52:
#line 506 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[-2].val).type;
        parameterARR_ID++;
    }
#line 2329 "y.tab.c"
    break;

  case 53:
#line 512 "compiler.y"
              { (yyval.val) = (yyvsp[0].val); }
#line 2335 "y.tab.c"
    break;

  case 56:
#line 521 "compiler.y"
              { (yyval.val) = (yyvsp[0].val); }
#line 2341 "y.tab.c"
    break;

  case 57:
#line 523 "compiler.y"
    {
        if(scope >0)
        {
            bool find = false;
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[0].s_val),i);
                if (goal!=NULL) 
                {
                    (yyval.val).type = goal->type;
                    find = true;
                    //printf("IDENT (name=%s, address=%d)\n", goal->name, goal->addr);
                    if(goal->type == TYPE_INT)   CODEGEN("iload %d\n",goal->addr);
                    if(goal->type == TYPE_FLOAT) CODEGEN("fload %d\n",goal->addr);
                    if(goal->type == TYPE_STRING) CODEGEN("aload %d\n",goal->addr);
                    if(goal->type == TYPE_BOOL)   CODEGEN("iload %d\n",goal->addr);
                    break;
                }
            }
            if(find == false)
            {
                g_has_error = true;
                printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[0].s_val));
                (yyval.val).type = TYPE_NULL;
            }
        } 
    }
#line 2373 "y.tab.c"
    break;

  case 58:
#line 551 "compiler.y"
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[-3].s_val),i);
                if (goal!=NULL) { (yyval.val).type = goal->type; break; }
            }
        } 
    }
#line 2388 "y.tab.c"
    break;

  case 59:
#line 562 "compiler.y"
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[0].s_val),i);
            }
        }
    }
#line 2402 "y.tab.c"
    break;

  case 60:
#line 571 "compiler.y"
    {
        if(scope >0){
            bool find = false;
            for(int i= scope-1;i>=0;i--){
                char * name= (yyvsp[-1].s_val);
                Node * goal = lookup_symbol(name,i);
    
                if (goal!=NULL) { 
           
                    find = true; 
                    (yyval.val).type = goal->type;
                    if(goal->type == TYPE_INT)   CODEGEN("iload %d\n",goal->addr);
                    if(goal->type == TYPE_FLOAT) CODEGEN("fload %d\n",goal->addr);
                    if(goal->type == TYPE_STRING) CODEGEN("aload %d\n",goal->addr);
                    if(goal->type == TYPE_BOOL)   CODEGEN("iload %d\n",goal->addr);
                    break; }
            }
            if(find == false)
            {
                g_has_error = true;
                printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[-4].s_val));
                (yyval.val).type = TYPE_NULL;
            }
        } 
    }
#line 2432 "y.tab.c"
    break;

  case 61:
#line 596 "compiler.y"
                               { (yyval.val).type = (yyvsp[-1].val).type; (yyval.val).s_val = (yyvsp[-1].val).s_val; }
#line 2438 "y.tab.c"
    break;

  case 62:
#line 599 "compiler.y"
                     { printf("DOTDOT\n"); }
#line 2444 "y.tab.c"
    break;

  case 64:
#line 600 "compiler.y"
                     { printf("DOTDOT\n"); }
#line 2450 "y.tab.c"
    break;

  case 66:
#line 601 "compiler.y"
                     { printf("DOTDOT\n"); }
#line 2456 "y.tab.c"
    break;

  case 67:
#line 604 "compiler.y"
                { 
                    (yyval.val).type = TYPE_INT; (yyval.val).i_val = atoi((yyvsp[0].s_val)); 
                    if((yyval.val).i_val < 0)  printf("INT_LIT %d\nNEG\n", -((yyval.val).i_val));
                    else              printf("INT_LIT %d\n", ((yyval.val).i_val));
                    CODEGEN("ldc %d\n", (yyval.val).i_val);
                }
#line 2467 "y.tab.c"
    break;

  case 68:
#line 610 "compiler.y"
                {   
                    (yyval.val).type = TYPE_FLOAT; (yyval.val).f_val = atof((yyvsp[0].s_val)); 
                    if((yyval.val).f_val < 0)  printf("FLOAT_LIT %f\nNEG\n", -((yyval.val).f_val));
                    else              printf("FLOAT_LIT %f\n", (yyval.val).f_val);
                    CODEGEN("ldc %f\n", (yyval.val).f_val);
                }
#line 2478 "y.tab.c"
    break;

  case 69:
#line 616 "compiler.y"
                {  
                    (yyval.val).type = TYPE_BOOL; 
                    if(strcmp((yyvsp[0].s_val),"true")==0) { (yyval.val).b_val = true; printf("bool %s\n", "TRUE");CODEGEN("iconst_1\n"); }
                    else                            { (yyval.val).b_val = false; printf("bool %s\n", "FALSE");CODEGEN("iconst_0\n"); }
                }
#line 2488 "y.tab.c"
    break;

  case 70:
#line 621 "compiler.y"
                { 
                    (yyval.val).type = TYPE_STRING; (yyval.val).s_val = (yyvsp[0].s_val);
                    printf("STRING_LIT \"%s\"\n", (yyvsp[0].s_val)); 
                    CODEGEN("ldc \"%s\"\n", (yyval.val).s_val);
                }
#line 2498 "y.tab.c"
    break;

  case 71:
#line 628 "compiler.y"
                 {   (yyval.op) = OP_ASSIGN; }
#line 2504 "y.tab.c"
    break;

  case 72:
#line 629 "compiler.y"
                 {   (yyval.op) = OP_ADD_ASSIGN; }
#line 2510 "y.tab.c"
    break;

  case 73:
#line 630 "compiler.y"
                 {   (yyval.op) = OP_SUB_ASSIGN; }
#line 2516 "y.tab.c"
    break;

  case 74:
#line 631 "compiler.y"
                 {   (yyval.op) = OP_MUL_ASSIGN; }
#line 2522 "y.tab.c"
    break;

  case 75:
#line 632 "compiler.y"
                 {   (yyval.op) = OP_DIV_ASSIGN; }
#line 2528 "y.tab.c"
    break;

  case 76:
#line 633 "compiler.y"
                 {   (yyval.op) = OP_REM_ASSIGN; }
#line 2534 "y.tab.c"
    break;

  case 77:
#line 638 "compiler.y"
    {        
                                                          
        if(strcmp(get_op_name((yyvsp[-2].op)),"ADD_ASSIGN")==0){                 
            if(!strcmp(get_type_name((yyvsp[-1].val).type),"i32")){      CODEGEN("iadd\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); }
            else{                                           CODEGEN("fadd\n"); CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); }
        }
        else if(strcmp(get_op_name((yyvsp[-2].op)),"ASSIGN")==0){
            if(!strcmp(get_type_name((yyvsp[-1].val).type),"i32"))       CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val)));
            else if(!strcmp(get_type_name((yyvsp[-1].val).type),"f32"))  CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val)));
            else if(!strcmp(get_type_name((yyvsp[-1].val).type),"str"))  CODEGEN("astore %d\n",get_addr((yyvsp[-3].s_val)));
            else                                            CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val)));
            
        }
        else if(strcmp(get_op_name((yyvsp[-2].op)),"SUB_ASSIGN")==0){                     
            if(!strcmp(get_type_name((yyvsp[-1].val).type),"i32")){      CODEGEN("isub\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val)));}
            else                                     {      CODEGEN("fsub\n"); CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val)));}
        }
        else if(strcmp(get_op_name((yyvsp[-2].op)),"MUL_ASSIGN")==0){  
            if(!strcmp(get_type_name((yyvsp[-1].val).type),"i32")){      CODEGEN("imul\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); }
            else{                                           CODEGEN("fmul\n"); CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); }
        }
        else if(strcmp(get_op_name((yyvsp[-2].op)),"DIV_ASSIGN")==0){                                                  
            if(!strcmp(get_type_name((yyvsp[-1].val).type),"i32")){      CODEGEN("idiv\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); }
            else{                                           CODEGEN("fdiv\n"); CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); }
        }
        else if(strcmp(get_op_name((yyvsp[-2].op)),"REM_ASSIGN")==0){CODEGEN("irem\n");CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); }
                             
        bool find = false;
        for(int i=scope-1;i>=0;i--)
        {
            Node * goal = lookup_symbol((yyvsp[-3].s_val),i);
            if(goal!=NULL)
            {
                find = true;
                printf("%s\n",get_op_name((yyvsp[-2].op)));
                break;
            }
        }
        if(!find ) 
        {
            g_has_error = true;
            printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[-3].s_val));
        }
    }
#line 2583 "y.tab.c"
    break;

  case 102:
#line 728 "compiler.y"
             { create_symbol(scope); scope++; }
#line 2589 "y.tab.c"
    break;

  case 103:
#line 729 "compiler.y"
    {
        dump_symbol();
    }
#line 2597 "y.tab.c"
    break;

  case 104:
#line 737 "compiler.y"
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
#line 2606 "y.tab.c"
    break;

  case 105:
#line 742 "compiler.y"
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
#line 2615 "y.tab.c"
    break;

  case 106:
#line 747 "compiler.y"
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
#line 2624 "y.tab.c"
    break;

  case 107:
#line 753 "compiler.y"
              { create_symbol(scope); scope++; CODEGEN("ifne if_false_%d\n", ifBlockNumOfTime); }
#line 2630 "y.tab.c"
    break;

  case 108:
#line 754 "compiler.y"
    {   
        CODEGEN("goto if_end_%d\nif_false_%d:\n", If_cnt,ifBlockNumOfTime++);
        dump_symbol();                            
    }
#line 2639 "y.tab.c"
    break;

  case 109:
#line 758 "compiler.y"
             {  create_symbol(scope); scope++; CODEGEN("ifne if_false_%d\n",ifBlockNumOfTime);}
#line 2645 "y.tab.c"
    break;

  case 110:
#line 759 "compiler.y"
    {
        CODEGEN("goto if_end_%d\nif_false_%d:\n", If_cnt,ifBlockNumOfTime++);
        dump_symbol();
    }
#line 2654 "y.tab.c"
    break;

  case 111:
#line 766 "compiler.y"
            {  CODEGEN("L%d_for_begin:\nL%d_ForCondition:\n", while_num,while_num); }
#line 2660 "y.tab.c"
    break;

  case 112:
#line 766 "compiler.y"
                                                                                               { CODEGEN("ifeq L%d_for_Exit \ngoto L%d_FBlock\n", while_num,while_num);  }
#line 2666 "y.tab.c"
    break;

  case 113:
#line 766 "compiler.y"
                                                                                                                                                                                      { CODEGEN("goto L%d_ForCondition \n", while_num);   CODEGEN("L%d_for_Exit:\n", while_num); }
#line 2672 "y.tab.c"
    break;

  case 114:
#line 769 "compiler.y"
              {CODEGEN("L%d_FBlock:\n",while_num);  create_symbol(scope); scope++; }
#line 2678 "y.tab.c"
    break;

  case 115:
#line 769 "compiler.y"
                                                                                                          {dump_symbol();}
#line 2684 "y.tab.c"
    break;

  case 118:
#line 775 "compiler.y"
                                                { dump_symbol();}
#line 2690 "y.tab.c"
    break;

  case 120:
#line 780 "compiler.y"
    {      
        create_symbol(scope);
        scope++; 
        Node * goal = NULL;
        for(int i = scope-2;i>=0;i--)
        {
            goal = lookup_symbol((yyvsp[0].val).s_val,i);         
            if(goal!=NULL)
            {
                VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
                switch((yyvsp[0].val).type)
                {
                    case TYPE_INT:    { temp->i_val = goal->val->i_val; break; }
                    case TYPE_FLOAT:  { temp->f_val = goal->val->f_val; break; }
                    case TYPE_BOOL:   { temp->b_val = goal->val->b_val; break; }
                    case TYPE_STRING: { temp->s_val = goal->val->s_val; break; }
                    case TYPE_NULL:   { temp->s_val = goal->val->s_val; break; }
                }
                insert_symbol((yyvsp[-2].s_val), goal->arrtype, yylineno,0);
                break;
            }
        }
        insert_symbol((yyvsp[-2].s_val), goal->arrtype, yylineno,0);
    }
#line 2719 "y.tab.c"
    break;

  case 127:
#line 830 "compiler.y"
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        switch((yyvsp[-3].type))
        {
            case TYPE_INT:    temp->i_val = (yyvsp[-1].val).i_val; break;
            case TYPE_FLOAT:  temp->f_val = (yyvsp[-1].val).f_val; break;
            case TYPE_BOOL:   temp->b_val = (yyvsp[-1].val).b_val; break;
            case TYPE_STRING: temp->s_val = (yyvsp[-1].val).s_val; break;
        }
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].type), yylineno,0, temp);
        switch((yyvsp[-3].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr((yyvsp[-5].s_val))); break;
        }
    }
#line 2742 "y.tab.c"
    break;

  case 128:
#line 849 "compiler.y"
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), yylineno,0,temp);
        switch((yyvsp[-1].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-3].s_val))); break;
        }
    }
#line 2759 "y.tab.c"
    break;

  case 129:
#line 862 "compiler.y"
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = true;
        switch((yyvsp[-3].type))
        {
            case TYPE_INT:    temp->i_val = (yyvsp[-1].val).i_val; break;
            case TYPE_FLOAT:  temp->f_val = (yyvsp[-1].val).f_val; break;
            case TYPE_BOOL:   temp->b_val = (yyvsp[-1].val).b_val; break;
            case TYPE_STRING: temp->s_val = (yyvsp[-1].val).s_val; break;
        }
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].type), yylineno,1,temp);
        Node* goal = lookup_symbol((yyvsp[-5].s_val),scope-1);
        switch((yyvsp[-3].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-5].s_val))); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr((yyvsp[-5].s_val))); break;
        }
       
    }
#line 2785 "y.tab.c"
    break;

  case 130:
#line 884 "compiler.y"
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), yylineno,1,temp);
        switch((yyvsp[-1].type))
        {
            case TYPE_INT:    CODEGEN("ldc 0\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("ldc 0.0\n"); CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_BOOL:   CODEGEN("ldc iconst_1\n"); CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc ""\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-3].s_val))); break;
        }
    }
#line 2802 "y.tab.c"
    break;

  case 131:
#line 897 "compiler.y"
    {
        /**** for "" string literal ****/ 
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-4].s_val), (yyvsp[-2].type), yylineno,0,temp);
        switch((yyvsp[-2].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr((yyvsp[-4].s_val))); break;
        }
    }
#line 2820 "y.tab.c"
    break;

  case 132:
#line 911 "compiler.y"
    {
        /**** for "" string literal ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-4].s_val), (yyvsp[-2].type), yylineno,1,temp);
        Node* goal = lookup_symbol((yyvsp[-4].s_val),scope-1);
        switch((yyvsp[-2].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-4].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-4].s_val))); break;
        }
    }
#line 2839 "y.tab.c"
    break;

  case 133:
#line 926 "compiler.y"
    {
        /**** for assign ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->i_val = (yyvsp[-1].s_val);
        insert_symbol((yyvsp[-3].s_val), TYPE_INT, yylineno,1,temp);
        switch((yyvsp[-1].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-3].s_val))); break;
        }
           
    }
#line 2858 "y.tab.c"
    break;

  case 134:
#line 940 "compiler.y"
                                                                     {arr_name = (yyvsp[-8].s_val);arr_num = (yyvsp[-3].val).i_val - 1;}
#line 2864 "y.tab.c"
    break;

  case 135:
#line 941 "compiler.y"
    {
        /**** for array ****/   
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false; 
        insert_symbol((yyvsp[-12].s_val), TYPE_ARR, yylineno,0,temp);
        Node * arrNode = lookup_symbol((yyvsp[-12].s_val),scope-1);
        arr_name = (yyvsp[-12].s_val);
        arr_index = 0;

        
        lookup_symbol((yyvsp[-12].s_val),scope-1)->arrnum = 0;
        if(arrNode){ 
            arrNode->arrtype = (yyvsp[-9].type);
           
        }
    }
#line 2885 "y.tab.c"
    break;

  case 136:
#line 958 "compiler.y"
    {
        /**** for assign ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        Node * goal = lookup_symbol((yyvsp[-3].s_val),scope-1);
        
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-1].val).type, yylineno,0,temp);
        switch((yyvsp[-1].val).type)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-3].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-3].s_val))); break;
        }
    }
#line 2904 "y.tab.c"
    break;

  case 137:
#line 973 "compiler.y"
    {
        /**** for loop ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-6].s_val), (yyvsp[-4].type), yylineno,0,temp);
        switch((yyvsp[-4].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr((yyvsp[-6].s_val))); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr((yyvsp[-6].s_val))); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr((yyvsp[-6].s_val))); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr((yyvsp[-6].s_val))); break;
        }
    }
#line 2922 "y.tab.c"
    break;

  case 138:
#line 992 "compiler.y"
                                {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        char name[100];
        name[0] ='0' +arr_num - arr_index;
        name[1] = '\0';
        insert_symbol(name, (yyvsp[-2].val).type, yylineno,0,temp);
        Node * goal = lookup_symbol(name,scope-1);
        CODEGEN("istore %d\n",goal->addr );
        arr_index++;
        switch((yyvsp[-2].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",goal->addr); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",goal->addr); break;
        }
    }
#line 2945 "y.tab.c"
    break;

  case 139:
#line 1010 "compiler.y"
              {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        char name[100];
        name[0] ='0' +arr_num - arr_index;
        name[1] = '\0';

        insert_symbol(name, (yyvsp[0].val).type, yylineno,0,temp);
        Node * goal = lookup_symbol(name,scope-1);
        CODEGEN("istore %d\n",goal->addr );
        arr_index++;
        switch((yyvsp[0].type))
        {
            case TYPE_INT:    CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",goal->addr); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",goal->addr); break;
        }
    }
#line 2969 "y.tab.c"
    break;

  case 142:
#line 1038 "compiler.y"
    { 
        if((yyvsp[0].val).type == TYPE_INT){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(I)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_STRING){
	        CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
	        CODEGEN("swap\n");
	        CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_FLOAT){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(F)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_BOOL){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Z)V\n");
        }
    }
#line 2996 "y.tab.c"
    break;

  case 144:
#line 1061 "compiler.y"
    { 
        if((yyvsp[0].val).type == TYPE_INT){
            // CODEGEN("dddkk ldc %d\n",$2.i_val);
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(I)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_STRING){
           // CODEGEN("ldc \"%s\"\n",$2.s_val);
	       CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
	       CODEGEN("swap\n");
	       CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_FLOAT){
            //CODEGEN("ldc %f\n",$2.f_val);
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(F)V\n");
        }
        else if((yyvsp[0].val).type == TYPE_BOOL){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Z)V\n");
        }
    }
#line 3026 "y.tab.c"
    break;

  case 146:
#line 1090 "compiler.y"
    {
        printf("%s\n",get_rettype_name((yyvsp[-1].val).type));
    }
#line 3034 "y.tab.c"
    break;

  case 149:
#line 1105 "compiler.y"
    {  
        Node * func = lookup_symbol((yyvsp[-2].s_val),0);
        func -> ret = TYPE_NULL;
        dump_symbol();
        if (!strcmp((yyvsp[-2].s_val), "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                            CODEGEN(".method public static %s()V\n", (yyvsp[-2].s_val));
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }
#line 3048 "y.tab.c"
    break;

  case 150:
#line 1114 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-4].s_val),0);
        if(func->ret == TYPE_NULL) CODEGEN("\treturn\n");
        else                       CODEGEN("\t%s\n",get_rettype_name(func->ret));
        CODEGEN(".end method\n");
    }
#line 3059 "y.tab.c"
    break;

  case 151:
#line 1121 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-4].s_val),0);
        if(func != NULL) func -> ret = TYPE_NULL;
        dump_symbol();
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));

        strcat(sig,")");
        strcat(sig,get_rettype_name((yyvsp[0].type)));
        CODEGEN(".method public static %s%s\n", (yyvsp[-4].s_val), func->func_sig);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }
#line 3077 "y.tab.c"
    break;

  case 153:
#line 1136 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-4].s_val),0);
        if(func != NULL)
        {
            func -> ret = (yyvsp[0].type);
            printf("%s\n",get_rettype_name((yyvsp[0].type)));
        }
        dump_symbol();

        if (!strcmp((yyvsp[-4].s_val), "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                            CODEGEN(".method public static %s(V)%s\n", (yyvsp[-4].s_val),get_type_name((yyvsp[0].type)));
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }
#line 3096 "y.tab.c"
    break;

  case 154:
#line 1150 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-6].s_val),0);
        if(func->ret == TYPE_NULL)      CODEGEN("\treturn\n");
        else                            CODEGEN("\t%s\n",get_rettype_name(func->ret));
        CODEGEN(".end method\n");
    }
#line 3107 "y.tab.c"
    break;

  case 155:
#line 1157 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-5].s_val),0);
        if(func != NULL)
        {
            func -> ret = (yyvsp[0].type);
            printf("%s\n",get_rettype_name((yyvsp[0].type)));
        }
        dump_symbol();
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));

        strcat(sig,")");
        strcat(sig,get_parametertype_name((yyvsp[0].type)));

        CODEGEN(".method public static %s%s\n", (yyvsp[-5].s_val), sig);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }
#line 3130 "y.tab.c"
    break;

  case 156:
#line 1176 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-7].s_val),0);
        if(func->ret == TYPE_NULL) CODEGEN("return\n");
        else CODEGEN("ireturn\n");
        CODEGEN(".end method\n");
    }
#line 3141 "y.tab.c"
    break;

  case 157:
#line 1185 "compiler.y"
    { 
        addr = -1; 
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[0].s_val), TYPE_FUNC,yylineno,-1,temp);
        create_symbol(scope); 
        scope++;
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 3155 "y.tab.c"
    break;

  case 158:
#line 1198 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[0].type);
        parameterARR_ID++;
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-2].s_val), (yyvsp[0].type), yylineno,0,temp);
    }
#line 3167 "y.tab.c"
    break;

  case 159:
#line 1206 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[0].type);
        parameterARR_ID++;
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol((yyvsp[-2].s_val), (yyvsp[0].type),yylineno,0,temp);
    }
#line 3179 "y.tab.c"
    break;


#line 3183 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1222 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");

    /* Symbol table init */
    // Add your code

    yylineno = 0;
    yyparse();

    /* Symbol table dump */
    // Add your code

	printf("Total lines: %d\n", yylineno);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
    return 0;
}

static void create_symbol(int scope) {
    //printf("> Create symbol table (scope level %d)\n",scope);
    Table * newTable = (Table *) malloc(sizeof(Table));         
    newTable -> countAddr = 0;
    newTable -> head = NULL;
    newTable -> tail = NULL;
    s_table[scope] = newTable;
}

static void insert_symbol(char* name, type_t type, int lineno,int mut,VALUE * val) 
{
    Node * newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode -> type = type;
    newNode -> lineno = lineno +1;
    newNode -> addr = addr++;
    s_table[scope-1] -> countAddr++;
    newNode -> next = NULL;
    newNode -> mut_val = mut;
    newNode -> val = val;
    /**define signature ***/
    char *sig ;
    if(strcmp(get_type_name(type),"func")==0) sig = "(V)V";
    else                                      sig = "-";
    newNode->func_sig = sig;
    /**define signature ***/

    if(s_table[scope-1] -> head == NULL)      s_table[scope-1] -> head = newNode;
    else                                      s_table[scope-1] -> tail -> next = newNode;

    s_table[scope-1] -> tail = newNode;
    printf("> Insert `%s` (addr: %d) to scope level %d\n", newNode->name, newNode->addr, scope -1 );
}

static Node* lookup_symbol(char * name,int scope) 
{
    Node * current = s_table[scope]->head;
    for(int i=0;i<s_table[scope]->countAddr;i++) 
    {
        if(strcmp(current->name, name) == 0 ) return current;
        current = current -> next;
    }
    return NULL;
}

static void dump_symbol() 
{
    scope --;
    printf("\n> Dump symbol table (scope level: %d)\n", scope);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    Node * current = s_table[scope]->head;
    for(int i=0;i<s_table[scope]->countAddr;i++)
    {
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",i, current->name, current->mut_val, get_type_name(current->type), current->addr, current->lineno, current->func_sig);
        current = current -> next;
    }
}
const char* JavaType(type_t type) {
    switch (type) {
        case TYPE_INT:    return "I";
        case TYPE_FLOAT:  return "F";
        case TYPE_BOOL:   return "Z";
        case TYPE_STRING: return "Ljava/lang/String;";
        case TYPE_FUNC:   return "func";
        default:          return "ERROR";
    }
}
int get_addr(char* str){
    if(scope >0){
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol(str,i);
                if (goal!=NULL)
                    return goal->addr;
            }
    }
    return 0;
} 
