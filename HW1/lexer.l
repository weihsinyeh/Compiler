/*
    filename: lexer.l
*/

/* Definition section */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #define print_token(token) \
        printf("%-8s \t %s\n", strcmp(token, "NEWLINE")? yytext: "", token)
   
    int line_num = 0;
    int comment_num = 0;
    int sentense = 0;
    int new_comment =1;
%}


/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
word [^ \t\n]+

%x STRING 
%x COMMENT
/* Rules section */
%%
\"              {   print_token("QUOTA"); if(sentense == 0) BEGIN STRING; }
<STRING>\"            { print_token("QUOTA"); sentense = 0;BEGIN 0;}
<STRING>([^\\"]|\\.)* { print_token("STRING_LIT"); sentense = 1; }
"//".*                { print_token("COMMENT"); 
                        if(new_comment==1) comment_num++;
                        //printf("00 : %d\n",comment_num); 
                        }

"/*" { printf("/*"); BEGIN COMMENT; }
<COMMENT>(([^*]|\*+[^*/])&&(^(\n)))*  { print_token("COMMENT");}
<COMMENT>(\n)               {   printf("\n"); 
                                line_num++; 
                                if(new_comment == 1){
                                    comment_num++;
                                }
                            }
<COMMENT>\*+"/"             {   print_token("MUTI_LINE_COMMENT"); 
                                comment_num++;
                                new_comment = 0;
                                BEGIN 0;
                            }

">="            { print_token("GEQ"); }
"<="            { print_token("LEQ"); }
"=="            { print_token("EQL"); }
"!="            { print_token("NEQ"); }
"+="            { print_token("ADD_ASSIGN"); }
"-="            { print_token("SUB_ASSIGN"); }
"*="            { print_token("MUL_ASSIGN"); }
"/="            { print_token("QUO_ASSIGN"); }
"%="            { print_token("REM_ASSIGN"); }
">>"            { print_token("RSHIFT");}
"&&"            { print_token("LAND");}
"||"            { print_token("LOR"); }

"\+"            { print_token("ADD"); }
"-"             { print_token("SUB"); }
"*"             { print_token("MUL"); }
"\/"            { print_token("QUO"); }
"%"             { print_token("REM"); }
">"             { print_token("GTR"); }
"<"             { print_token("LSS"); }

"="             { print_token("ASSIGN"); }
"&"             { print_token("BAND"); }
"|"             { print_token("BOR"); }
"~"             { print_token("BNOT"); }

"!"             { print_token("NOT"); }
"("             { print_token("LPAREN"); }
")"             { print_token("RPAREN"); }
"["             { print_token("LBRACK"); }
"]"             { print_token("RBRACK"); }
"{"             { print_token("LBRACE"); }
"}"	            { print_token("RBRACE"); }

","             { print_token("COMMA"); }



"\n"            { print_token("NEWLINE"); line_num++; new_comment=1;}
":"             { print_token("COLON"); }

(([0-9]+)?)     { print_token("INT_LIT"); }
(([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?)  { print_token("FLOAT_LIT");}

"->"            { print_token("ARROW"); }
"<<"            { print_token("LSHIFT"); }
"print"         { print_token("PRINT"); }
"println"       { print_token("PRINTLN"); }
"if"            { print_token("IF"); }
"else"          { print_token("ELSE"); }
"for"           { print_token("FOR"); }
"i32"           { print_token("INT"); }
"f32"           { print_token("FLOAT"); }
".."            { print_token("DOTDOT"); } 
"bool"          { print_token("BOOL"); }
"true"          { print_token("TRUE");}
"false"         { print_token("FALSE");}
"let"	        { print_token("LET"); }
"mut"	        { print_token("MUT"); }
"fn"	        { print_token("FUNC"); }
"return"	    { print_token("RETURN"); }
"break"	        { print_token("BREAK"); }
"as"	        { print_token("AS"); }
"in"	        { print_token("IN"); }
"while"	        { print_token("WHILE"); }
"loop"	        { print_token("LOOP"); }
"\;"            { print_token("SEMICOLON"); }
-?((([a-z]|_)+)?)    { print_token("IDENT"); }
[a-zA-Z][a-zA-Z0-9]+   { print_token("IDENT"); }
<<EOF>>         { line_num++; yyterminate(); }
[ \t]+          { /*ignore whitespace*/ ;}
.               {;}

%%

/*  C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    yylex();
    printf("\nFinish scanning,\n");
    printf("total line: %d\n", line_num);
    printf("comment line: %d\n", comment_num);
    fclose(yyin);
    return 0;
}