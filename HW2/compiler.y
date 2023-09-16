/* Please feel free to modify any content */

/* Definition section */
%{
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
%}

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 *  - you can add new fields if needed.
 */
%union {
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
}

/* Token without return */
%token LET MUT NEWLINE
%token INT FLOAT BOOL STRING
%token TRUE FALSE
%token GTR LSS GEQ LEQ EQL NEQ LOR LAND
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN
%token IF ELSE FOR WHILE LOOP SWITCH CASE DEFAULT 
%token PRINT PRINTLN ADDR
%token FUNC RETURN BREAK
%token ID ARROW AS IN DOTDOT RSHIFT LSHIFT IDENT
%token LBRACE RBRACE LBRACK RBRACK LPAREN RPAREN
%token INC DEC 
%token VAR COLON SEMICOLON COMMA PACKAGE
%token ADD SUB NOT MUL DIV REM

/* Token with return, which need to sepcify type */
%token <val> INT_LIT
%token <val> FLOAT_LIT
%token <val> BOOL_LIT
%token <s_val> STRING_LIT
%token <mut_val> MUT_LIT

/* Nonterminal with return, which need to sepcify type */
%type <type>  Type
%type <type>  PrintStmt
%type <val>   Operand
%type <val>   Literal
%type <val>   UnaryExpr
%type <val>   Expression
%type <s_val> FuncOpen
%type <val>   PrimaryExpr
%type <val>   ConversionExpr
%type <s_val> ParameterList
%type <op>    add_op mul_op unary_op assign_op cmp_op binary_op shift_op

/* %type <s_val> PRINTLN */
/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : {create_symbol(scope);scope++;} GlobalStatementList { dump_symbol(); }
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;

GlobalStatement
    : FunctionDeclStmt
    | NEWLINE
;

Type
    : INT         {$$ = TYPE_INT;}
    | FLOAT       {$$ = TYPE_FLOAT;}
    | STRING      {$$ = TYPE_STRING;}
    | BOOL        {$$ = TYPE_BOOL;}
    | ADDR STRING {$$ = TYPE_STRING;} //reference
;

binary_op 
    : LOR 
    { 
        $$ = OP_LOR;
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
    | LAND  
    { 
        $$ = OP_LAND;
        if(opArr_ID > 0 && opArr[opArr_ID-1] != OP_LOR && opArr[opArr_ID-1] != OP_LAND){
            opArr_ID--;
            while (opArr_ID >= 0 && opArr[opArr_ID] != OP_LOR && opArr[opArr_ID] != OP_LAND){
                printf("%s\n",get_op_name(opArr[opArr_ID]));
                opArr_ID--;
            }
        }
        if(opArr_ID < 0)opArr_ID = 0;
    }
    | cmp_op 
    { 
        opArr_ID--;
        while (opArr_ID >=0 )
        {
            printf("%s\n",get_op_name(opArr[opArr_ID]));
            opArr_ID--;
        }
        if(opArr_ID < 0) opArr_ID = 0;
    }
    | add_op 
    | mul_op 
    | shift_op
;
shift_op
    : LSHIFT { $$ = OP_LSHIFT;}
    | RSHIFT { $$ = OP_RSHIFT;}
;
cmp_op
    : EQL  { $$ = OP_EQL;}
    | NEQ  { $$ = OP_NEQ;}
    | LSS  { $$ = OP_LSS;}
    | LEQ  { $$ = OP_LEQ;}
    | GTR  { $$ = OP_GTR;}
    | GEQ  { $$ = OP_GEQ;}
;
add_op 
    : ADD  { $$ = OP_ADD;}
    | SUB  { $$ = OP_SUB;}
;
mul_op 
    : MUL  { $$ = OP_MUL;}
    | DIV  { $$ = OP_DIV;}
    | REM  { $$ = OP_REM;}
;
unary_op 
    : NOT { $$ = OP_NOT; }
;
Expression 
    : UnaryExpr { $$.type = $1.type;}
    | UnaryExpr AS Type 
    { 
        if( $1.type == TYPE_INT && $3 == TYPE_FLOAT)
        {
            printf("i2f\n"); 
            $$.type = $3;
            //$$.type = TYPE_I2F;
        }
        else if( $1.type == TYPE_FLOAT && $3 == TYPE_INT)
        {
            printf("f2i\n"); 
            $$.type = $3;
            //$$.type = TYPE_F2I;
        }
        else 
        {
            $$.type = $3;
        }
    }
    | Expression binary_op 
    {
        opArr[opArr_ID] = $2; opArr_ID++;
    } 
    Expression
    {
        if ((($1.type == TYPE_FLOAT) && ($4.type == TYPE_INT ))
         || (($1.type == TYPE_INT) && ($4.type == TYPE_FLOAT ) )
         || ((($1.type == TYPE_BOOL) && ($4.type != TYPE_BOOL )) && ((opArr[opArr_ID] == OP_EQL)||(opArr[opArr_ID] == OP_NEQ)||(opArr[opArr_ID] == OP_LSS)||(opArr[opArr_ID] == OP_LEQ)||(opArr[opArr_ID] == OP_GTR)||(opArr[opArr_ID] == OP_GEQ))))
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        if ($1.type == TYPE_NULL || $4.type == TYPE_NULL)
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        if ((($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) && (opArr[opArr_ID] == OP_REM))               //REM  
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        if (($1.type == TYPE_BOOL) || ($4.type == TYPE_BOOL))        $$.type = $4.type;
        else if (($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) $$.type = $4.type;
        $$.type = $4.type;
        opArr_ID--;
        while(opArr_ID>=0)
        {
            printf("%s\n",get_op_name(opArr[opArr_ID]));  
            opArr_ID--;
        }
        opArr_ID =0;  
    }
;

UnaryExpr 
    : PrimaryExpr 
    | unary_op UnaryExpr
    {
        $$.type = $2.type;
        printf("%s\n", get_op_name($<op>1));
    }
    | functionCall 
;
functionCall
    : ID LPAREN {parameterARR_ID=0;}ParameterListInFunctionCall RPAREN 
    {
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++)
            strcat(sig,get_parametertype_name(parameterARR[i]));

        if(parameterARR_ID==0) strcat(sig,"V");

        strcat(sig,")");

        Node * func = lookup_symbol($<s_val>1,0);

        if(func!=NULL)
        {
            strcat(sig,get_parametertype_name(func->ret));
            func->func_sig = sig;
        }
        printf("call: %s%s\n",$<s_val>1,sig);
    }
    | ID LPAREN RPAREN
    {
        Node * func = lookup_symbol($<s_val>1,0);
        char *sig = "(V)V";
        func->func_sig = sig;
        printf("call: %s(V)V\n",$<s_val>1);
    }
;
ParameterListInFunctionCall 
    : Operand 
    {
        parameterARR[parameterARR_ID] = $1.type;
        parameterARR_ID++;
    }
    | Operand COMMA ParameterListInFunctionCall
    {
        parameterARR[parameterARR_ID] = $1.type;
        parameterARR_ID++;
    }
;
PrimaryExpr 
    : Operand {$$.type = $1.type;}
    | ConversionExpr
;

ConversionExpr 
    : Type LPAREN Expression RPAREN
;

Operand 
    : Literal 
    | ID 
    {
        if(scope >0)
        {
            bool find = false;
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol($<s_val>1,i);
                if (goal!=NULL) {
                    $$.type = goal->type;
                    find = true;
                    printf("IDENT (name=%s, address=%d)\n", goal->name, goal->addr);
                    break;
                }
            }
            if(find == false)
            {
                printf("error:%d: undefined: %s\n",yylineno+1,$<s_val>1);
                $$.type = TYPE_NULL;
            }
        } 
    }
    | ADDR Operand LBRACK Interindex RBRACK
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol($<s_val>2,i);
                if (goal!=NULL) 
                {
                    $$.type = goal->type;
                    break;
                }
            }
        } 
    }
    | ID
    {
        if(scope >0)
        {
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol($<s_val>1,i);
                if (goal!=NULL) 
                {
                    printf("IDENT (name=%s, address=%d)\n", goal->name, goal->addr);
                    break;
                }
            }
        } 
    } 
    LBRACK Expression RBRACK 
    {
        if(scope >0){
            bool find = false;
            for(int i= scope-1;i>=0;i--){
                Node * goal = lookup_symbol($<s_val>1,i);
                if (goal!=NULL) 
                {
                    find = true;
                    $$.type = goal->type;
                    break;
                }
            }
            if(find == false)
            {
                printf("error:%d: undefined: %s\n",yylineno+1,$<s_val>1);
                $$.type = TYPE_NULL;
            }
        } 
    }
    | LPAREN Expression RPAREN { $$.type = $2.type; } 
;
Interindex
    : DOTDOT {printf("DOTDOT\n");}Literal
    | Literal DOTDOT {printf("DOTDOT\n");}Literal
    | Literal DOTDOT {printf("DOTDOT\n");}
;
Literal
    : INT_LIT   { 
                    $$.type = TYPE_INT;
                    $$.i_val = atoi($<s_val>1); 
                    if($$.i_val < 0)  printf("INT_LIT %d\nNEG\n", -($$.i_val));
                    else              printf("INT_LIT %d\n", ($$.i_val));
                }
    | FLOAT_LIT {   
                    $$.type = TYPE_FLOAT;
                    $$.f_val = atof($<s_val>1); 
                    if($$.f_val < 0)  printf("FLOAT_LIT %f\nNEG\n", -($$.f_val));
                    else              printf("FLOAT_LIT %f\n", $$.f_val);
                }
    | BOOL_LIT  {  
                    $$.type = TYPE_BOOL; 
                    if(strcmp($<s_val>1,"true")==0)
                    {
                        $$.b_val = true;
                        printf("bool %s\n", "TRUE"); 
                    }
                    else
                    {
                        $$.b_val = false;
                        printf("bool %s\n", "FALSE"); 
                    }
                }
    | STRING_LIT{ 
                    $$.type = TYPE_STRING; 
                    $$.s_val = $<s_val>1;
                    printf("STRING_LIT \"%s\"\n", $<s_val>1); 
                }
;
assign_op
    : ASSIGN     {$$= OP_ASSIGN;}
    | ADD_ASSIGN {$$ = OP_ADD_ASSIGN;}
    | SUB_ASSIGN {$$= OP_SUB_ASSIGN;}
    | MUL_ASSIGN {$$ = OP_MUL_ASSIGN;}
    | DIV_ASSIGN {$$ = OP_DIV_ASSIGN;}
    | REM_ASSIGN {$$ = OP_REM_ASSIGN;}
;

AssignmentStmt 
    : ID assign_op Expression SEMICOLON 
    {
        bool find = false;
        for(int i=scope-1;i>=0;i--)
        {
            Node * goal = lookup_symbol($<s_val>1,i);
            if(goal!=NULL)
            {
                find = true;
                printf("%s\n",get_op_name($<op>2));
                break;
            }
        }
        if(!find )
            printf("error:%d: undefined: %s\n",yylineno+1,$<s_val>1);
    }
;
IncDecStmt 
    : Expression INC 
    | Expression DEC 
;

/* Statement ***************************************/

StatementList 
    : StatementList Statement
    | Statement   
;

Statement 
    : DeclarationStmt 
    | SimpleStmt  
    | Block
    | IfStmt
    | ForStmt
    | SwitchStmt
    | CaseStmt 
    | LetStatement LetStatementCon
    | PrintStmt 
    | ReturnStmt
    | NEWLINE
    | WhileStmt
    | functionCall SEMICOLON 
    | LOOPStatement 
;

LOOPStatement
    : BREAK Literal SEMICOLON
;

DeclarationStmt 
    : ID Type  
    | ID Type assign_op Expression 
;

SimpleStmt 
    : AssignmentStmt
    | ExpressionStmt 
    | IncDecStmt  
;

Block
    : LBRACE {create_symbol(scope); scope++;} StatementList RBRACE
    {
        dump_symbol();
    }
;

/* IF statement **************************************/
IfStmt 
    : IF Condition Block ELSE IfStmt 
    | IF Condition Block
    | IF Condition Block ELSE Block 
;
/* IF statement **************************************/
WhileStmt
    : WHILE Condition Block
;
/* For statement *************************************/
ForStmt
    : FOR Condition Block ELSE Block
    | FOR ForClause Block ELSE Block
    | FOR ForClause LBRACE StatementList RBRACE
    {
        dump_symbol();
    }
;
;
ForClause 
    : InitStmt SEMICOLON Condition SEMICOLON PostStmt
    | ID IN Operand
    {
        create_symbol(scope);
        scope++; 
        Node * goal = NULL;
        for(int i = scope-2;i>=0;i--)
        {
            goal = lookup_symbol($3.s_val,i);         
            if(goal!=NULL)
            {
                insert_symbol($<s_val>1, goal->arrtype, yylineno,0);
                break;
            }
        }
        //insert_symbol($<s_val>1, goal->arrtype, yylineno,0);
    }
;

InitStmt 
    : SimpleStmt
;

Condition 
    : Expression
;

PostStmt 
    : SimpleStmt
;
/* For statement *************************************/

SwitchStmt 
    : SWITCH Expression 
;
CaseStmt 
    : CASE INT_LIT COLON Block
    | CASE DEFAULT COLON Block
;

/* Let statement *************************************/
LetStatement
    : LET ID COLON Type ASSIGN Operand SEMICOLON
    {
        insert_symbol($<s_val>2, $<type>4, yylineno,0);
    }
    | LET ID COLON Type SEMICOLON
    {
        insert_symbol($<s_val>2, $<type>4, yylineno,0);
    }
    | LET MUT ID COLON Type ASSIGN Literal SEMICOLON
    {
        insert_symbol($<s_val>3, $<type>5, yylineno,1);
    }
    | LET MUT ID COLON Type SEMICOLON
    {
        insert_symbol($<s_val>3, $<type>5, yylineno,1);
    }
    | LET ID COLON Type ASSIGN SEMICOLON
    {
        // for "" string literal
        printf("STRING_LIT \"\"\n", $<s_val>1); 
        insert_symbol($<s_val>2, $<type>4, yylineno,0);
    }
    | LET MUT ID COLON Type ASSIGN SEMICOLON  
    {
        // for "" string literal
        printf("STRING_LIT \"\"\n", $<s_val>1); 
        insert_symbol($<s_val>3, $<type>5, yylineno,1);
    }
    | LET MUT ID ASSIGN Operand SEMICOLON
    {
        // for assign
        insert_symbol($<s_val>3, TYPE_INT, yylineno,1);
    }
    | LET ID COLON LBRACK Type SEMICOLON Operand RBRACK ASSIGN LBRACK LiteralList RBRACK SEMICOLON
    {
        // for array 
        insert_symbol($<s_val>2, TYPE_ARR, yylineno,0);
        Node * arrNode = lookup_symbol($<s_val>2,scope-1);
        if(arrNode){ 
            arrNode->arrtype = $5;
            //arrNode->arrnum = atoi($7.i_val); //store value
        }
    }
    | LET ID ASSIGN Operand SEMICOLON
    {
        // for assign
        insert_symbol($<s_val>3, $4.type, yylineno,0);
    }
    | LET ID COLON Type ASSIGN LOOP Block SEMICOLON
    {
        // for loop
        insert_symbol($<s_val>2, $<type>4, yylineno,0);
    }
;

LiteralList
    : Literal COMMA LiteralList
    | Literal 
;
LetStatementCon
    : ASSIGN Literal SEMICOLON
    |
;
/* Let statement *************************************/

PrintStmt 
    : PRINT Expression   { printf("PRINT %s\n",get_type_name($2.type));   } SEMICOLON
    | PRINTLN Expression { printf("PRINTLN %s\n",get_type_name($2.type)); } SEMICOLON
;

ReturnStmt 
    : RETURN Expression SEMICOLON
    {
        printf("%s\n",get_rettype_name($2.type));
    }
;

GlobalStatement 
    : PackageStmt NEWLINE 
    | FunctionDeclStmt NEWLINE
    | NEWLINE
;
PackageStmt 
    : PACKAGE ID
;
FunctionDeclStmt 
    : FuncOpen LPAREN RPAREN FuncBlock 
    {  
        Node * func = lookup_symbol($<s_val>1,0);
        func -> ret = TYPE_NULL;
        dump_symbol();
    }
    | FuncOpen LPAREN ParameterList RPAREN Type FuncBlock
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL)
            func -> ret = TYPE_NULL;
        dump_symbol();
    }
    | FuncOpen LPAREN RPAREN ARROW Type FuncBlock 
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL)
        {
            func -> ret = $5;
            printf("%s\n",get_rettype_name($5));
        }
        dump_symbol();
    }
    | FuncOpen LPAREN ParameterList RPAREN ARROW Type FuncBlock 
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL)
        {
            func -> ret = $6;
            printf("%s\n",get_rettype_name($6));
        }
        dump_symbol();
    }
;
FuncOpen
    : FUNC ID 
    { 
        addr = -1;
        printf("func: %s\n",$<s_val>2); 
        insert_symbol($<s_val>2, TYPE_FUNC,yylineno,-1);
        create_symbol(scope); 
        scope++;
        $$ = $<s_val>2;
    } 
;
ParameterList 
    : ID COLON Type 
    {
        insert_symbol($<s_val>1, $3, yylineno,0);
    }
    | ParameterList COMMA ID COLON Type 
    {
        insert_symbol($<s_val>3, $5,yylineno,0);
    }
;
FuncBlock 
    : LBRACE StatementList RBRACE 
;

ExpressionStmt 
    : Expression
;

%%

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
