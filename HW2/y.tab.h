/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 215 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
