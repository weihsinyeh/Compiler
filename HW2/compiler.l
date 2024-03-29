/* Definition section */
%{
    #include "compiler_common.h"
    #include "y.tab.h"	/* header file generated by bison */
    extern YYSTYPE yylval;

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #define XXX printf("not implemented yet!\n")
%}

/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
id {letter}+({letter}|{digit})*
inumber {digit}+
fnumber ({digit}*\.{digit}+)

%x CMT
%x STRCOND
%option yylineno

/* Rules section */
%%

"/*"        { BEGIN(CMT); }
<CMT>"*/"   { BEGIN(INITIAL); }
<CMT>\n     { ; }
<CMT>.      { ; }
"//".*      { ; }
"\""        { BEGIN(STRCOND);
               
         
            }
<STRCOND>"\""   { BEGIN(INITIAL);
               
            }
<STRCOND>[^\"]* { yylval.s_val = strdup(yytext);
                return STRING_LIT;
            }
"str"       { return STRING; }
">>"        { return RSHIFT; }
"<<"        { return LSHIFT; }
"++"        { return INC; }
"--"        { return DEC; }
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return REM; }
">"         { return GTR; }
"<"         { return LSS; }
">="        { return GEQ; }
"<="        { return LEQ; }
"=="        { return EQL; }
"!="        { return NEQ; }
"="         { return ASSIGN; }
"+="        { return ADD_ASSIGN; }
"-="        { return SUB_ASSIGN; }
"*="        { return MUL_ASSIGN; }
"/="        { return DIV_ASSIGN; }
"%="        { return REM_ASSIGN; }
"&&"        { return LAND; }
"||"        { return LOR; }
"!"         { return NOT; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"["         { return LBRACK; }
"]"         { return RBRACK; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
":"         { return COLON; }
";"         { return SEMICOLON; }
","         { return COMMA; }
"->"        { return ARROW; }
"i32"       { return INT; }
"f32"       { return FLOAT; }
".."        { return DOTDOT; } 
"bool"      { return BOOL; }
"print"     { return PRINT; }
"println"   { return PRINTLN; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"as"        { return AS; }
"if"        { return IF; }
"else"      { return ELSE; }
"for"       { return FOR; }
"while"     { return WHILE; }
"loop"      { return LOOP; }
"true"      { yylval.s_val = strdup(yytext); return BOOL_LIT; }
"false"     { yylval.s_val = strdup(yytext); return BOOL_LIT; }
"fn"        { return FUNC; }
"return"    { return RETURN; }
"mut"       { return MUT; }
"let"       { return LET; }
"in"        { return IN; }
"&"         { return ADDR;}
"break"     { return BREAK; }
"var"       { return VAR; }
"default"   { return DEFAULT; }
"package"   { return PACKAGE;}

{inumber}   { yylval.s_val = strdup(yytext);
                return INT_LIT;
            }
(-{inumber})   { yylval.s_val = strdup(yytext);
                return INT_LIT;
            }
{fnumber}   { yylval.s_val = strdup(yytext);
                return FLOAT_LIT;
            }
(-{fnumber})   { yylval.s_val = strdup(yytext);
                return FLOAT_LIT;
            }
{id}        { yylval.s_val = strdup(yytext); return ID;}
<<EOF>>     { static int once = 0;
                if (once++) {
                    yyterminate();
                }
                yylineno++;
                ;
            }
"\\n"        { return NEWLINE;}
[ \t\n]+      {;}
%%
/*  C Code section */
int yywrap(void)
{
    return 1;
}