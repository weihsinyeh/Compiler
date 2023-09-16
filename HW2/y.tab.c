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
    // Put the following code in the Definition section, 
    // then the parser generates a description of the input tokens it receives and 
    // actions it takes for each token while parsing an input stream.
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

    /* Custom variables to maintain symbol table */
    

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
    }Node;

    typedef struct table{
        Node* head;
        Node* tail;
        int countAddr;           
    }Table;

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

    /* Global variables */
    bool HAS_ERROR = false;
    op_t opArr[2048];
    int opArr_ID=0;
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

#line 208 "y.tab.c"

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
#line 148 "compiler.y"

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

#line 418 "y.tab.c"

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
#define YYLAST   666

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  258

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
       0,   207,   207,   207,   211,   212,   216,   217,   221,   222,
     223,   224,   225,   229,   243,   255,   265,   266,   267,   270,
     271,   274,   275,   276,   277,   278,   279,   282,   283,   286,
     287,   288,   291,   294,   295,   315,   314,   342,   343,   348,
     351,   351,   370,   379,   384,   391,   392,   396,   400,   401,
     423,   439,   438,   473,   476,   476,   477,   477,   478,   481,
     487,   493,   506,   513,   514,   515,   516,   517,   518,   522,
     540,   541,   547,   548,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   569,   573,
     574,   578,   579,   580,   584,   584,   592,   593,   594,   598,
     602,   603,   604,   611,   612,   631,   635,   639,   644,   647,
     648,   653,   657,   661,   665,   669,   675,   681,   686,   696,
     701,   709,   710,   713,   714,   719,   719,   720,   720,   724,
     731,   732,   733,   736,   739,   745,   752,   762,   774,   785,
     789,   795,   799
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
  "GlobalStatementList", "GlobalStatement", "Type", "binary_op",
  "shift_op", "cmp_op", "add_op", "mul_op", "unary_op", "Expression",
  "$@2", "UnaryExpr", "functionCall", "$@3", "ParameterListInFunctionCall",
  "PrimaryExpr", "ConversionExpr", "Operand", "$@4", "Interindex", "$@5",
  "$@6", "Literal", "assign_op", "AssignmentStmt", "IncDecStmt",
  "StatementList", "Statement", "LOOPStatement", "DeclarationStmt",
  "SimpleStmt", "Block", "$@7", "IfStmt", "WhileStmt", "ForStmt",
  "ForClause", "InitStmt", "Condition", "PostStmt", "SwitchStmt",
  "CaseStmt", "LetStatement", "LiteralList", "LetStatementCon",
  "PrintStmt", "$@8", "$@9", "ReturnStmt", "PackageStmt",
  "FunctionDeclStmt", "FuncOpen", "ParameterList", "FuncBlock",
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

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-143)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -92,    37,     1,   -92,   -92,     5,    12,     1,   -92,    50,
      59,   -10,   -92,   -92,   -92,   -92,   -92,     6,    22,    66,
     -12,   204,   204,   334,   -92,   196,    41,   -92,   -92,   -92,
     -92,    74,   -92,    43,    26,   -92,    17,    42,    17,    17,
      -2,    17,    17,     4,    17,   166,   599,   -92,    17,   -92,
     -92,   -92,   -92,   -92,    40,    17,   397,    47,    46,   -92,
     -92,   -92,   -92,   -92,   -92,   190,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,    75,   -92,   -92,   -92,
     204,    43,    49,   -92,   -92,    68,    13,    25,   551,   -92,
      67,   259,   375,   -92,    76,    65,    67,    67,   551,    71,
      77,   551,   551,   386,   -92,    89,   452,    82,   -92,   -92,
     -92,   -92,   -92,   -92,    72,   424,    93,    17,   334,   462,
      17,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   204,   -92,   -92,   -92,   166,   -92,
      43,   -92,   204,    19,   386,   151,   117,   386,   334,   120,
      17,   122,   -92,    67,    67,    92,    96,   308,   -92,   -92,
     -92,   386,    17,    17,   474,   238,   -92,   529,    17,   -92,
      97,   -92,   -92,   386,   204,    98,   204,    -4,    10,   -92,
     286,    67,   103,    67,   -92,   -92,   -92,   -92,   -92,   111,
     119,   113,   106,   551,   538,   -92,   -92,   -92,   551,   -92,
     114,     2,   -92,   116,   596,   -92,   -92,   -92,   -92,   -92,
     112,   -92,   166,   -92,   125,   -92,   386,   -92,   -92,    30,
     -92,   386,    67,   -92,   130,   307,   -92,   -92,   -92,   166,
     -92,   -92,   131,   127,   133,   -92,   -92,   -92,   163,   -92,
     121,   166,   141,   156,   166,   134,   -92,   -92
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     7,     0,     0,     3,     5,     0,
       6,     0,   138,   133,     4,   130,   131,     0,     0,     0,
       0,     0,     0,     0,   134,     0,     0,     8,     9,    11,
      10,     0,   139,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    94,     0,    32,
      59,    60,    61,    62,     0,     0,   142,    33,    39,    37,
      46,    45,    48,    91,    93,     0,    73,    87,    74,    75,
      76,    77,    85,    78,    79,    80,   124,    82,    83,    92,
       0,     0,     0,    12,   136,     0,     0,    49,   106,    39,
       0,    49,   106,   105,     0,     0,     0,     0,   108,     0,
       0,   125,   127,     0,    49,     0,     0,     0,    63,    64,
      65,    66,    67,    68,    40,    89,     0,     0,     0,     0,
       0,    38,    25,    23,    26,    24,    21,    22,    13,    14,
      20,    19,    70,    71,    27,    28,    29,    30,    31,    35,
      18,    15,    16,    17,     0,    86,   141,    72,     0,    81,
       0,   135,     0,     0,     0,     0,    97,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,     0,   129,    88,
      42,     0,     0,     0,     0,     0,    53,     0,     0,    34,
       0,   137,   140,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   110,   109,   126,   128,    54,     0,
       0,     0,    43,    90,     0,    69,    95,    47,    36,   123,
       0,     0,   119,     0,     0,   112,    98,    96,   102,   101,
       0,   100,     0,    50,    56,    41,     0,    52,   117,     0,
     114,     0,     0,   115,     0,    49,   107,   103,    55,     0,
      44,   116,     0,     0,     0,   111,    57,   113,     0,   120,
       0,     0,   122,     0,     0,     0,   121,   118
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   -92,   -92,   201,   -17,   -92,   -92,   -92,   -92,
     -92,   -92,   -27,   -92,   159,   -22,   -92,   -11,   -92,   -92,
     -41,   -92,   -92,   -92,   -92,   -45,   102,   -92,   -92,   -91,
     -58,   -92,   -92,   -34,   -62,   -92,    32,   -92,   -92,   -92,
     -92,   -19,   -92,   -92,   -92,   -92,   -31,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -13,   -92
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    54,   139,   140,   141,   142,
     143,    55,    56,   178,    57,    89,   171,   201,    59,    60,
      61,   116,   199,   222,   239,    62,   117,    63,    64,    65,
      66,    67,    68,    69,    70,   118,    71,    72,    73,    94,
      95,    90,   237,    74,    75,    76,   253,   149,    77,   165,
     166,    78,     9,    10,    11,    20,    24,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     107,    58,   105,    93,    32,    33,     4,   147,    81,    88,
      92,    88,    98,    83,   101,   102,   214,   106,    96,    97,
      84,   119,   229,    27,    28,    29,    30,   175,   156,   115,
      85,    99,   159,   154,   161,   162,    36,     3,     5,   183,
     103,    25,    17,    58,   104,    12,    18,    26,    27,    28,
      29,    30,    13,    43,   215,    15,    48,    87,    47,    19,
     230,     6,   105,   150,    16,   100,    86,   190,   151,    48,
     155,    50,    51,    52,    53,   -51,   184,   114,    43,    21,
      49,    82,    91,    83,    50,    51,    52,    53,   241,   144,
     174,    23,   120,   177,    48,   148,    58,    50,    51,    52,
      53,   194,   195,   180,   145,    49,   152,    22,   153,    50,
      51,    52,    53,   185,    23,    47,   189,   147,    27,    28,
      29,    30,   200,   160,   158,   170,   216,   179,   163,   219,
     202,   221,   147,    88,   164,   182,    58,   181,   187,   167,
     169,   192,   210,   173,   188,   203,   204,   191,    43,   193,
     196,   208,   235,    58,   197,   209,   212,    27,    28,    29,
      30,   220,   223,   224,    48,   226,   225,   211,    58,   213,
     244,   251,   228,   234,   231,    49,   -58,   238,   248,    50,
      51,    52,    53,   250,   242,   202,   236,    31,   245,   247,
     243,   249,   257,    34,   246,    35,    27,    28,    29,    30,
     254,   186,    27,    28,    29,    30,   252,   255,    14,   252,
      27,    28,    29,    30,   121,   240,    36,   172,    37,    38,
     217,    39,    40,   256,    41,    42,    43,     0,    44,    45,
      46,     0,    31,    50,    51,    52,    53,    80,    47,   146,
      31,    34,    48,    35,    27,    28,    29,    30,     0,     0,
       0,     0,     0,    49,     0,     0,     0,    50,    51,    52,
      53,     0,     0,     0,    36,     0,    37,    38,     0,    39,
      40,     0,    41,    42,    43,     0,    44,    45,    46,   108,
     109,   110,   111,   112,   113,     0,    47,   206,     0,    34,
      48,    35,    27,    28,    29,    30,     0,     0,     0,     0,
       0,    49,   157,     0,     0,    50,    51,    52,    53,   -51,
       0,   114,    36,     0,    37,    38,     0,    39,    40,     0,
      41,    42,    43,     0,    44,    45,    46,   108,   109,   110,
     111,   112,   113,     0,    47,   218,     0,    34,    48,    35,
      27,    28,    29,    30,     0,     0,     0,     0,     0,    49,
       0,     0,   198,    50,    51,    52,    53,   -51,     0,   114,
      36,     0,    37,    38,     0,    39,    40,     0,    41,    42,
      43,     0,    44,    45,    46,    50,    51,    52,    53,     0,
       0,     0,    47,     0,     0,     0,    48,   122,   123,   124,
     125,   126,   127,   128,   129,     0,     0,    49,     0,     0,
       0,    50,    51,    52,    53,     0,     0,     0,     0,   122,
     123,   124,   125,   126,   127,   128,   129,     0,     0,     0,
     130,   131,   103,     0,     0,     0,   104,     0,     0,   132,
     133,     0,     0,  -142,     0,     0,   134,   135,    48,   136,
     137,   138,   130,   131,   108,   109,   110,   111,   112,   113,
       0,   132,   133,    50,    51,    52,    53,     0,   134,   135,
       0,   136,   137,   138,   122,   123,   124,   125,   126,   127,
     128,   129,     0,     0,   122,   123,   124,   125,   126,   127,
     128,   129,     0,     0,     0,     0,   122,   123,   124,   125,
     126,   127,   128,   129,     0,     0,     0,   130,   131,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,     0,
     168,     0,     0,   134,   135,   176,   136,   137,   138,   130,
     131,     0,     0,   134,   135,     0,   136,   137,   138,     0,
       0,     0,   205,     0,     0,   134,   135,     0,   136,   137,
     138,   122,   123,   124,   125,   126,   127,   128,   129,     0,
     122,   123,   124,   125,   126,   127,   128,   129,     0,     0,
       0,     0,     0,   122,   123,   124,   125,   126,   127,   128,
     129,     0,     0,     0,   130,   131,     0,     0,     0,     0,
       0,     0,   207,   130,   131,     0,     0,     0,     0,   227,
     134,   135,     0,   136,   137,   138,   130,   131,     0,   134,
     135,     0,   136,   137,   138,    27,    28,    29,    30,     0,
       0,     0,   134,   135,     0,   136,   137,   138,     0,   108,
     109,   110,   111,   112,   113,     0,   232,     0,     0,     0,
       0,     0,   103,     0,     0,    31,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,   -51,
       0,   114,     0,     0,   233,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53
};

static const yytype_int16 yycheck[] =
{
      45,    23,    43,    37,    21,    22,     5,    65,    25,    36,
      37,    38,    39,     9,    41,    42,    20,    44,    37,    38,
      33,    48,    20,     6,     7,     8,     9,   118,    90,    46,
       4,    33,    94,    20,    96,    97,    26,     0,    37,    20,
      36,    53,    52,    65,    40,    40,    40,    59,     6,     7,
       8,     9,    40,    36,    58,     5,    52,    40,    48,    53,
      58,    60,   103,    80,     5,    67,    40,   158,    81,    52,
      57,    67,    68,    69,    70,    50,    57,    52,    36,    57,
      63,    40,    40,     9,    67,    68,    69,    70,    58,    42,
     117,    48,    52,   120,    52,    20,   118,    67,    68,    69,
      70,   163,   164,   148,    58,    63,    57,    41,    40,    67,
      68,    69,    70,   154,    48,    48,   157,   175,     6,     7,
       8,     9,   167,    58,    48,    53,   188,   144,    57,   191,
     171,   193,   190,   160,    57,   152,   158,   150,   155,    50,
      58,   160,   183,    50,    27,   172,   173,    27,    36,    27,
      58,   178,    40,   175,    58,    58,    58,     6,     7,     8,
       9,    58,    51,    44,    52,    59,    53,   184,   190,   186,
     232,    50,    58,   214,    58,    63,    51,   222,    51,    67,
      68,    69,    70,    20,   229,   226,   220,    36,    58,    58,
     231,    58,    58,     3,   239,     5,     6,     7,     8,     9,
      59,    50,     6,     7,     8,     9,   251,    51,     7,   254,
       6,     7,     8,     9,    55,   226,    26,   115,    28,    29,
     188,    31,    32,   254,    34,    35,    36,    -1,    38,    39,
      40,    -1,    36,    67,    68,    69,    70,    41,    48,    49,
      36,     3,    52,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    26,    -1,    28,    29,    -1,    31,
      32,    -1,    34,    35,    36,    -1,    38,    39,    40,    20,
      21,    22,    23,    24,    25,    -1,    48,    49,    -1,     3,
      52,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    63,    43,    -1,    -1,    67,    68,    69,    70,    50,
      -1,    52,    26,    -1,    28,    29,    -1,    31,    32,    -1,
      34,    35,    36,    -1,    38,    39,    40,    20,    21,    22,
      23,    24,    25,    -1,    48,    49,    -1,     3,    52,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    44,    67,    68,    69,    70,    50,    -1,    52,
      26,    -1,    28,    29,    -1,    31,    32,    -1,    34,    35,
      36,    -1,    38,    39,    40,    67,    68,    69,    70,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    52,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    63,    -1,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      45,    46,    36,    -1,    -1,    -1,    40,    -1,    -1,    54,
      55,    -1,    -1,    58,    -1,    -1,    61,    62,    52,    64,
      65,    66,    45,    46,    20,    21,    22,    23,    24,    25,
      -1,    54,    55,    67,    68,    69,    70,    -1,    61,    62,
      -1,    64,    65,    66,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,
      58,    -1,    -1,    61,    62,    53,    64,    65,    66,    45,
      46,    -1,    -1,    61,    62,    -1,    64,    65,    66,    -1,
      -1,    -1,    58,    -1,    -1,    61,    62,    -1,    64,    65,
      66,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    45,    46,    -1,    -1,    -1,    -1,    51,
      61,    62,    -1,    64,    65,    66,    45,    46,    -1,    61,
      62,    -1,    64,    65,    66,     6,     7,     8,     9,    -1,
      -1,    -1,    61,    62,    -1,    64,    65,    66,    -1,    20,
      21,    22,    23,    24,    25,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    36,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    50,
      -1,    52,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,    74,     0,     5,    37,    60,    75,    76,   124,
     125,   126,    40,    40,    76,     5,     5,    52,    40,    53,
     127,    57,    41,    48,   128,    53,    59,     6,     7,     8,
       9,    36,    77,    77,     3,     5,    26,    28,    29,    31,
      32,    34,    35,    36,    38,    39,    40,    48,    52,    63,
      67,    68,    69,    70,    77,    83,    84,    86,    87,    90,
      91,    92,    97,    99,   100,   101,   102,   103,   104,   105,
     106,   108,   109,   110,   115,   116,   117,   120,   123,   129,
      41,    77,    40,     9,   128,     4,    40,    40,    84,    87,
     113,    40,    84,   105,   111,   112,   113,   113,    84,    33,
      67,    84,    84,    36,    40,    92,    84,    97,    20,    21,
      22,    23,    24,    25,    52,    77,    93,    98,   107,    84,
      52,    86,    12,    13,    14,    15,    16,    17,    18,    19,
      45,    46,    54,    55,    61,    62,    64,    65,    66,    78,
      79,    80,    81,    82,    42,    58,    49,   102,    20,   119,
      77,   128,    57,    40,    20,    57,   106,    43,    48,   106,
      58,   106,   106,    57,    57,   121,   122,    50,    58,    58,
      53,    88,    98,    50,    84,   101,    53,    84,    85,    77,
      97,   128,    77,    20,    57,    92,    50,    77,    27,    92,
     101,    27,   113,    27,   106,   106,    58,    58,    44,    94,
      97,    89,    92,    84,    84,    58,    49,    53,    84,    58,
      92,    77,    58,    77,    20,    58,   106,   108,    49,   106,
      58,   106,    95,    51,    44,    53,    59,    51,    58,    20,
      58,    58,    30,    58,    92,    40,   105,   114,    97,    96,
      89,    58,    97,    92,   106,    58,    97,    58,    51,    58,
      20,    50,    97,   118,    59,    51,   118,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    74,    73,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    81,    81,    82,
      82,    82,    83,    84,    84,    85,    84,    86,    86,    86,
      88,    87,    87,    89,    89,    90,    90,    91,    92,    92,
      92,    93,    92,    92,    95,    94,    96,    94,    94,    97,
      97,    97,    97,    98,    98,    98,    98,    98,    98,    99,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   103,   104,
     104,   105,   105,   105,   107,   106,   108,   108,   108,   109,
     110,   110,   110,   111,   111,   112,   113,   114,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   119,   119,   121,   120,   122,   120,   123,
      76,    76,    76,   124,   125,   125,   125,   125,   126,   127,
     127,   128,   129
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     1,     2,     1,
       0,     5,     3,     1,     3,     1,     1,     4,     1,     1,
       5,     0,     5,     3,     0,     3,     0,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     2,     1,     3,     2,
       4,     1,     1,     1,     0,     4,     5,     3,     5,     3,
       5,     5,     5,     5,     3,     1,     1,     1,     2,     4,
       4,     7,     5,     8,     6,     6,     7,     6,    13,     5,
       8,     3,     1,     3,     0,     0,     4,     0,     4,     3,
       2,     2,     1,     2,     4,     6,     6,     7,     2,     3,
       5,     3,     1
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
#line 207 "compiler.y"
      {create_symbol(scope);scope++;}
#line 1873 "y.tab.c"
    break;

  case 3:
#line 207 "compiler.y"
                                                          { dump_symbol(); }
#line 1879 "y.tab.c"
    break;

  case 8:
#line 221 "compiler.y"
                  {(yyval.type) = TYPE_INT;}
#line 1885 "y.tab.c"
    break;

  case 9:
#line 222 "compiler.y"
                  {(yyval.type) = TYPE_FLOAT;}
#line 1891 "y.tab.c"
    break;

  case 10:
#line 223 "compiler.y"
                  {(yyval.type) = TYPE_STRING;}
#line 1897 "y.tab.c"
    break;

  case 11:
#line 224 "compiler.y"
                  {(yyval.type) = TYPE_BOOL;}
#line 1903 "y.tab.c"
    break;

  case 12:
#line 225 "compiler.y"
                  {(yyval.type) = TYPE_STRING;}
#line 1909 "y.tab.c"
    break;

  case 13:
#line 230 "compiler.y"
    { 
        (yyval.op) = OP_LOR;
        if(opArr_ID > 0 && opArr[opArr_ID-1] != OP_LOR && opArr[opArr_ID-1] != OP_LAND)
        {
            opArr_ID--;
            while (opArr_ID >=0 && opArr[opArr_ID] != OP_LOR && opArr[opArr_ID] != OP_LAND)
            {
                printf("%s\n",get_op_name(opArr[opArr_ID]));
                opArr_ID--;
            }
        }
        if(opArr_ID < 0) opArr_ID =0; 
    }
#line 1927 "y.tab.c"
    break;

  case 14:
#line 244 "compiler.y"
    { 
        (yyval.op) = OP_LAND;
        if(opArr_ID > 0 && opArr[opArr_ID-1] != OP_LOR && opArr[opArr_ID-1] != OP_LAND){
            opArr_ID--;
            while (opArr_ID >= 0 && opArr[opArr_ID] != OP_LOR && opArr[opArr_ID] != OP_LAND){
                printf("%s\n",get_op_name(opArr[opArr_ID]));
                opArr_ID--;
            }
        }
        if(opArr_ID < 0)opArr_ID = 0;
    }
#line 1943 "y.tab.c"
    break;

  case 15:
#line 256 "compiler.y"
    { 
        opArr_ID--;
        while (opArr_ID >=0 )
        {
            printf("%s\n",get_op_name(opArr[opArr_ID]));
            opArr_ID--;
        }
        if(opArr_ID < 0) opArr_ID = 0;
    }
#line 1957 "y.tab.c"
    break;

  case 19:
#line 270 "compiler.y"
             { (yyval.op) = OP_LSHIFT;}
#line 1963 "y.tab.c"
    break;

  case 20:
#line 271 "compiler.y"
             { (yyval.op) = OP_RSHIFT;}
#line 1969 "y.tab.c"
    break;

  case 21:
#line 274 "compiler.y"
           { (yyval.op) = OP_EQL;}
#line 1975 "y.tab.c"
    break;

  case 22:
#line 275 "compiler.y"
           { (yyval.op) = OP_NEQ;}
#line 1981 "y.tab.c"
    break;

  case 23:
#line 276 "compiler.y"
           { (yyval.op) = OP_LSS;}
#line 1987 "y.tab.c"
    break;

  case 24:
#line 277 "compiler.y"
           { (yyval.op) = OP_LEQ;}
#line 1993 "y.tab.c"
    break;

  case 25:
#line 278 "compiler.y"
           { (yyval.op) = OP_GTR;}
#line 1999 "y.tab.c"
    break;

  case 26:
#line 279 "compiler.y"
           { (yyval.op) = OP_GEQ;}
#line 2005 "y.tab.c"
    break;

  case 27:
#line 282 "compiler.y"
           { (yyval.op) = OP_ADD;}
#line 2011 "y.tab.c"
    break;

  case 28:
#line 283 "compiler.y"
           { (yyval.op) = OP_SUB;}
#line 2017 "y.tab.c"
    break;

  case 29:
#line 286 "compiler.y"
           { (yyval.op) = OP_MUL;}
#line 2023 "y.tab.c"
    break;

  case 30:
#line 287 "compiler.y"
           { (yyval.op) = OP_DIV;}
#line 2029 "y.tab.c"
    break;

  case 31:
#line 288 "compiler.y"
           { (yyval.op) = OP_REM;}
#line 2035 "y.tab.c"
    break;

  case 32:
#line 291 "compiler.y"
          { (yyval.op) = OP_NOT; }
#line 2041 "y.tab.c"
    break;

  case 33:
#line 294 "compiler.y"
                { (yyval.val).type = (yyvsp[0].val).type;}
#line 2047 "y.tab.c"
    break;

  case 34:
#line 296 "compiler.y"
    { 
        if( (yyvsp[-2].val).type == TYPE_INT && (yyvsp[0].type) == TYPE_FLOAT)
        {
            printf("i2f\n"); 
            (yyval.val).type = (yyvsp[0].type);
            //$$.type = TYPE_I2F;
        }
        else if( (yyvsp[-2].val).type == TYPE_FLOAT && (yyvsp[0].type) == TYPE_INT)
        {
            printf("f2i\n"); 
            (yyval.val).type = (yyvsp[0].type);
            //$$.type = TYPE_F2I;
        }
        else 
        {
            (yyval.val).type = (yyvsp[0].type);
        }
    }
#line 2070 "y.tab.c"
    break;

  case 35:
#line 315 "compiler.y"
    {
        opArr[opArr_ID] = (yyvsp[0].op); opArr_ID++;
    }
#line 2078 "y.tab.c"
    break;

  case 36:
#line 319 "compiler.y"
    {
        if ((((yyvsp[-3].val).type == TYPE_FLOAT) && ((yyvsp[0].val).type == TYPE_INT ))
         || (((yyvsp[-3].val).type == TYPE_INT) && ((yyvsp[0].val).type == TYPE_FLOAT ) )
         || ((((yyvsp[-3].val).type == TYPE_BOOL) && ((yyvsp[0].val).type != TYPE_BOOL )) && ((opArr[opArr_ID] == OP_EQL)||(opArr[opArr_ID] == OP_NEQ)||(opArr[opArr_ID] == OP_LSS)||(opArr[opArr_ID] == OP_LEQ)||(opArr[opArr_ID] == OP_GTR)||(opArr[opArr_ID] == OP_GEQ))))
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        if ((yyvsp[-3].val).type == TYPE_NULL || (yyvsp[0].val).type == TYPE_NULL)
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        if ((((yyvsp[-3].val).type == TYPE_FLOAT) || ((yyvsp[0].val).type == TYPE_FLOAT)) && (opArr[opArr_ID] == OP_REM))               //REM  
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name((yyvsp[-2].op)),get_type_name((yyvsp[-3].val).type),get_type_name((yyvsp[0].val).type));
        if (((yyvsp[-3].val).type == TYPE_BOOL) || ((yyvsp[0].val).type == TYPE_BOOL))        (yyval.val).type = (yyvsp[0].val).type;
        else if (((yyvsp[-3].val).type == TYPE_FLOAT) || ((yyvsp[0].val).type == TYPE_FLOAT)) (yyval.val).type = (yyvsp[0].val).type;
        (yyval.val).type = (yyvsp[0].val).type;
        opArr_ID--;
        while(opArr_ID>=0)
        {
            printf("%s\n",get_op_name(opArr[opArr_ID]));  
            opArr_ID--;
        }
        opArr_ID =0;  
    }
#line 2103 "y.tab.c"
    break;

  case 38:
#line 344 "compiler.y"
    {
        (yyval.val).type = (yyvsp[0].val).type;
        printf("%s\n", get_op_name((yyvsp[-1].op)));
    }
#line 2112 "y.tab.c"
    break;

  case 40:
#line 351 "compiler.y"
                {parameterARR_ID=0;}
#line 2118 "y.tab.c"
    break;

  case 41:
#line 352 "compiler.y"
    {
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++)
            strcat(sig,get_parametertype_name(parameterARR[i]));

        if(parameterARR_ID==0) strcat(sig,"V");

        strcat(sig,")");

        Node * func = lookup_symbol((yyvsp[-4].s_val),0);

        if(func!=NULL)
        {
            strcat(sig,get_parametertype_name(func->ret));
            func->func_sig = sig;
        }
        printf("call: %s%s\n",(yyvsp[-4].s_val),sig);
    }
#line 2141 "y.tab.c"
    break;

  case 42:
#line 371 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-2].s_val),0);
        char *sig = "(V)V";
        func->func_sig = sig;
        printf("call: %s(V)V\n",(yyvsp[-2].s_val));
    }
#line 2152 "y.tab.c"
    break;

  case 43:
#line 380 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[0].val).type;
        parameterARR_ID++;
    }
#line 2161 "y.tab.c"
    break;

  case 44:
#line 385 "compiler.y"
    {
        parameterARR[parameterARR_ID] = (yyvsp[-2].val).type;
        parameterARR_ID++;
    }
#line 2170 "y.tab.c"
    break;

  case 45:
#line 391 "compiler.y"
              {(yyval.val).type = (yyvsp[0].val).type;}
#line 2176 "y.tab.c"
    break;

  case 49:
#line 402 "compiler.y"
    {
        if(scope >0)
        {
            bool find = false;
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[0].s_val),i);
                if (goal!=NULL) {
                    (yyval.val).type = goal->type;
                    find = true;
                    printf("IDENT (name=%s, address=%d)\n", goal->name, goal->addr);
                    break;
                }
            }
            if(find == false)
            {
                printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[0].s_val));
                (yyval.val).type = TYPE_NULL;
            }
        } 
    }
#line 2202 "y.tab.c"
    break;

  case 50:
#line 424 "compiler.y"
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[-3].s_val),i);
                if (goal!=NULL) 
                {
                    (yyval.val).type = goal->type;
                    break;
                }
            }
        } 
    }
#line 2221 "y.tab.c"
    break;

  case 51:
#line 439 "compiler.y"
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol((yyvsp[0].s_val),i);
                if (goal!=NULL) 
                {
                    printf("IDENT (name=%s, address=%d)\n", goal->name, goal->addr);
                    break;
                }
            }
        } 
    }
#line 2240 "y.tab.c"
    break;

  case 52:
#line 454 "compiler.y"
    {
        if(scope >0){
            bool find = false;
            for(int i= scope-1;i>=0;i--){
                Node * goal = lookup_symbol((yyvsp[-4].s_val),i);
                if (goal!=NULL) 
                {
                    find = true;
                    (yyval.val).type = goal->type;
                    break;
                }
            }
            if(find == false)
            {
                printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[-4].s_val));
                (yyval.val).type = TYPE_NULL;
            }
        } 
    }
#line 2264 "y.tab.c"
    break;

  case 53:
#line 473 "compiler.y"
                               { (yyval.val).type = (yyvsp[-1].val).type; }
#line 2270 "y.tab.c"
    break;

  case 54:
#line 476 "compiler.y"
             {printf("DOTDOT\n");}
#line 2276 "y.tab.c"
    break;

  case 56:
#line 477 "compiler.y"
                     {printf("DOTDOT\n");}
#line 2282 "y.tab.c"
    break;

  case 58:
#line 478 "compiler.y"
                     {printf("DOTDOT\n");}
#line 2288 "y.tab.c"
    break;

  case 59:
#line 481 "compiler.y"
                { 
                    (yyval.val).type = TYPE_INT;
                    (yyval.val).i_val = atoi((yyvsp[0].s_val)); 
                    if((yyval.val).i_val < 0)  printf("INT_LIT %d\nNEG\n", -((yyval.val).i_val));
                    else              printf("INT_LIT %d\n", ((yyval.val).i_val));
                }
#line 2299 "y.tab.c"
    break;

  case 60:
#line 487 "compiler.y"
                {   
                    (yyval.val).type = TYPE_FLOAT;
                    (yyval.val).f_val = atof((yyvsp[0].s_val)); 
                    if((yyval.val).f_val < 0)  printf("FLOAT_LIT %f\nNEG\n", -((yyval.val).f_val));
                    else              printf("FLOAT_LIT %f\n", (yyval.val).f_val);
                }
#line 2310 "y.tab.c"
    break;

  case 61:
#line 493 "compiler.y"
                {  
                    (yyval.val).type = TYPE_BOOL; 
                    if(strcmp((yyvsp[0].s_val),"true")==0)
                    {
                        (yyval.val).b_val = true;
                        printf("bool %s\n", "TRUE"); 
                    }
                    else
                    {
                        (yyval.val).b_val = false;
                        printf("bool %s\n", "FALSE"); 
                    }
                }
#line 2328 "y.tab.c"
    break;

  case 62:
#line 506 "compiler.y"
                { 
                    (yyval.val).type = TYPE_STRING; 
                    (yyval.val).s_val = (yyvsp[0].s_val);
                    printf("STRING_LIT \"%s\"\n", (yyvsp[0].s_val)); 
                }
#line 2338 "y.tab.c"
    break;

  case 63:
#line 513 "compiler.y"
                 {(yyval.op)= OP_ASSIGN;}
#line 2344 "y.tab.c"
    break;

  case 64:
#line 514 "compiler.y"
                 {(yyval.op) = OP_ADD_ASSIGN;}
#line 2350 "y.tab.c"
    break;

  case 65:
#line 515 "compiler.y"
                 {(yyval.op)= OP_SUB_ASSIGN;}
#line 2356 "y.tab.c"
    break;

  case 66:
#line 516 "compiler.y"
                 {(yyval.op) = OP_MUL_ASSIGN;}
#line 2362 "y.tab.c"
    break;

  case 67:
#line 517 "compiler.y"
                 {(yyval.op) = OP_DIV_ASSIGN;}
#line 2368 "y.tab.c"
    break;

  case 68:
#line 518 "compiler.y"
                 {(yyval.op) = OP_REM_ASSIGN;}
#line 2374 "y.tab.c"
    break;

  case 69:
#line 523 "compiler.y"
    {
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
            printf("error:%d: undefined: %s\n",yylineno+1,(yyvsp[-3].s_val));
    }
#line 2394 "y.tab.c"
    break;

  case 94:
#line 584 "compiler.y"
             {create_symbol(scope); scope++;}
#line 2400 "y.tab.c"
    break;

  case 95:
#line 585 "compiler.y"
    {
        dump_symbol();
    }
#line 2408 "y.tab.c"
    break;

  case 102:
#line 605 "compiler.y"
    {
        dump_symbol();
    }
#line 2416 "y.tab.c"
    break;

  case 104:
#line 613 "compiler.y"
    {
        create_symbol(scope);
        scope++; 
        Node * goal = NULL;
        for(int i = scope-2;i>=0;i--)
        {
            goal = lookup_symbol((yyvsp[0].val).s_val,i);         
            if(goal!=NULL)
            {
                insert_symbol((yyvsp[-2].s_val), goal->arrtype, yylineno,0);
                break;
            }
        }
        //insert_symbol($<s_val>1, goal->arrtype, yylineno,0);
    }
#line 2436 "y.tab.c"
    break;

  case 111:
#line 654 "compiler.y"
    {
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].type), yylineno,0);
    }
#line 2444 "y.tab.c"
    break;

  case 112:
#line 658 "compiler.y"
    {
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), yylineno,0);
    }
#line 2452 "y.tab.c"
    break;

  case 113:
#line 662 "compiler.y"
    {
        insert_symbol((yyvsp[-5].s_val), (yyvsp[-3].type), yylineno,1);
    }
#line 2460 "y.tab.c"
    break;

  case 114:
#line 666 "compiler.y"
    {
        insert_symbol((yyvsp[-3].s_val), (yyvsp[-1].type), yylineno,1);
    }
#line 2468 "y.tab.c"
    break;

  case 115:
#line 670 "compiler.y"
    {
        // for "" string literal
        printf("STRING_LIT \"\"\n", (yyvsp[-5].s_val)); 
        insert_symbol((yyvsp[-4].s_val), (yyvsp[-2].type), yylineno,0);
    }
#line 2478 "y.tab.c"
    break;

  case 116:
#line 676 "compiler.y"
    {
        // for "" string literal
        printf("STRING_LIT \"\"\n", (yyvsp[-6].s_val)); 
        insert_symbol((yyvsp[-4].s_val), (yyvsp[-2].type), yylineno,1);
    }
#line 2488 "y.tab.c"
    break;

  case 117:
#line 682 "compiler.y"
    {
        // for assign
        insert_symbol((yyvsp[-3].s_val), TYPE_INT, yylineno,1);
    }
#line 2497 "y.tab.c"
    break;

  case 118:
#line 687 "compiler.y"
    {
        // for array 
        insert_symbol((yyvsp[-11].s_val), TYPE_ARR, yylineno,0);
        Node * arrNode = lookup_symbol((yyvsp[-11].s_val),scope-1);
        if(arrNode){ 
            arrNode->arrtype = (yyvsp[-8].type);
            //arrNode->arrnum = atoi($7.i_val); //store value
        }
    }
#line 2511 "y.tab.c"
    break;

  case 119:
#line 697 "compiler.y"
    {
        // for assign
        insert_symbol((yyvsp[-2].s_val), (yyvsp[-1].val).type, yylineno,0);
    }
#line 2520 "y.tab.c"
    break;

  case 120:
#line 702 "compiler.y"
    {
        // for loop
        insert_symbol((yyvsp[-6].s_val), (yyvsp[-4].type), yylineno,0);
    }
#line 2529 "y.tab.c"
    break;

  case 125:
#line 719 "compiler.y"
                         { printf("PRINT %s\n",get_type_name((yyvsp[0].val).type));   }
#line 2535 "y.tab.c"
    break;

  case 127:
#line 720 "compiler.y"
                         { printf("PRINTLN %s\n",get_type_name((yyvsp[0].val).type)); }
#line 2541 "y.tab.c"
    break;

  case 129:
#line 725 "compiler.y"
    {
        printf("%s\n",get_rettype_name((yyvsp[-1].val).type));
    }
#line 2549 "y.tab.c"
    break;

  case 134:
#line 740 "compiler.y"
    {  
        Node * func = lookup_symbol((yyvsp[-3].s_val),0);
        func -> ret = TYPE_NULL;
        dump_symbol();
    }
#line 2559 "y.tab.c"
    break;

  case 135:
#line 746 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-5].s_val),0);
        if(func != NULL)
            func -> ret = TYPE_NULL;
        dump_symbol();
    }
#line 2570 "y.tab.c"
    break;

  case 136:
#line 753 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-5].s_val),0);
        if(func != NULL)
        {
            func -> ret = (yyvsp[-1].type);
            printf("%s\n",get_rettype_name((yyvsp[-1].type)));
        }
        dump_symbol();
    }
#line 2584 "y.tab.c"
    break;

  case 137:
#line 763 "compiler.y"
    {
        Node * func = lookup_symbol((yyvsp[-6].s_val),0);
        if(func != NULL)
        {
            func -> ret = (yyvsp[-1].type);
            printf("%s\n",get_rettype_name((yyvsp[-1].type)));
        }
        dump_symbol();
    }
#line 2598 "y.tab.c"
    break;

  case 138:
#line 775 "compiler.y"
    { 
        addr = -1;
        printf("func: %s\n",(yyvsp[0].s_val)); 
        insert_symbol((yyvsp[0].s_val), TYPE_FUNC,yylineno,-1);
        create_symbol(scope); 
        scope++;
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 2611 "y.tab.c"
    break;

  case 139:
#line 786 "compiler.y"
    {
        insert_symbol((yyvsp[-2].s_val), (yyvsp[0].type), yylineno,0);
    }
#line 2619 "y.tab.c"
    break;

  case 140:
#line 790 "compiler.y"
    {
        insert_symbol((yyvsp[-2].s_val), (yyvsp[0].type),yylineno,0);
    }
#line 2627 "y.tab.c"
    break;


#line 2631 "y.tab.c"

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
#line 802 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) 
    {
        yyin = fopen(argv[1], "r");
    } 
    else 
    {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol(int scope) {
    printf("> Create symbol table (scope level %d)\n",scope);
    Table * newTable = (Table *) malloc(sizeof(Table));         
    newTable -> countAddr = 0;
    newTable -> head = NULL;
    newTable -> tail = NULL;
    s_table[scope] = newTable;
}

static void insert_symbol(char* name, type_t type, int lineno,int mut) 
{
    Node * newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode -> type = type;
    newNode -> lineno = lineno +1;
    newNode -> addr = addr++;
    s_table[scope-1] -> countAddr++;
    newNode -> next = NULL;
    newNode -> mut_val = mut;
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
