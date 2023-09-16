/* Please feel free to modify any content */

/* Definition section */
%{
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
%type <val>   Expression Expression2 Expression3 Expression4 Expression5 Expression6
%type <s_val> FuncOpen
%type <val>   PrimaryExpr
%type <val>   ConversionExpr
%type <s_val> ParameterList
%type <op>    add_op mul_op unary_op assign_op cmp_op binary_op shift_op

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    :  {create_symbol(scope);scope++;} GlobalStatementList { dump_symbol(); }
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;



Type
    : INT         {  $$ = TYPE_INT; }
    | FLOAT       {  $$ = TYPE_FLOAT; }
    | STRING      {  $$ = TYPE_STRING; }
    | BOOL        {  $$ = TYPE_BOOL; }
    | ADDR STRING {  $$ = TYPE_STRING; } //reference
;

binary_op 
    : LOR 
    { 
        $$ = OP_LOR;
        if(opArr_ID > 0 && opArr[opArr_ID-1] != OP_LOR && opArr[opArr_ID-1] != OP_LAND)
        {
            opArr_ID--;
            while (opArr_ID >=0 && opArr[opArr_ID] != OP_LOR && opArr[opArr_ID] != OP_LAND)
                opArr_ID--;
        }
        if(opArr_ID < 0) opArr_ID =0; 
        
    }
    | LAND  
    { 
        $$ = OP_LAND;
        if(opArr_ID > 0 && opArr[opArr_ID-1] != OP_LOR && opArr[opArr_ID-1] != OP_LAND)
        {
            opArr_ID--;
            while (opArr_ID >= 0 && opArr[opArr_ID] != OP_LOR && opArr[opArr_ID] != OP_LAND)
                opArr_ID--;
        }
        if(opArr_ID < 0)opArr_ID = 0;
    }
    | cmp_op 
    { 
        opArr_ID--;
        while (opArr_ID >=0 ) { opArr_ID--; }
        if(opArr_ID < 0) opArr_ID = 0;
    }
    | add_op 
    | shift_op
;
shift_op
    : LSHIFT {  $$ = OP_LSHIFT; }
    | RSHIFT {  $$ = OP_RSHIFT; }
;
cmp_op
    : EQL  {  $$ = OP_EQL; }
    | NEQ  {  $$ = OP_NEQ; }
    | LSS  {  $$ = OP_LSS; }
    | LEQ  {  $$ = OP_LEQ; }
    | GTR  {  $$ = OP_GTR; }
    | GEQ  {  $$ = OP_GEQ; }
;
add_op 
    : ADD  {  $$ = OP_ADD; }
    | SUB  {  $$ = OP_SUB; }
;
mul_op 
    : MUL  {  $$ = OP_MUL; }
    | DIV  {  $$ = OP_DIV; }
    | REM  {  $$ = OP_REM; }
;
unary_op 
    : NOT  {  $$ = OP_NOT; }
;
Expression 
    : UnaryExpr { $$ = $1; }
    | Expression LOR { opArr[opArr_ID] = OP_LOR; opArr_ID++; } Expression2
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        printf("ior");
        CODEGEN("ior\n");
    }
    | Expression2 { $$ = $1;}
;
Expression2
    : Expression2 LAND { opArr[opArr_ID] = OP_LAND; opArr_ID++; } Expression3
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val & $4.b_val;
        printf("iand\n");
        CODEGEN("iand\n");
    }
    | Expression3 { $$ = $1;}
;
Expression3
    : Expression3 EQL { opArr[opArr_ID] = OP_EQL; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }      
    }
    | Expression3 NEQ { opArr[opArr_ID] = OP_NEQ; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }     
        CODEGEN("ifle comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;          
    }
    | Expression3 LSS { opArr[opArr_ID] = OP_LSS; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }                                 

    }
    | Expression3 LEQ { opArr[opArr_ID] = OP_LEQ; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else                                     { CODEGEN("isub\n");  }    
        CODEGEN("ifle comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;                             
    
    }
    | Expression3 GTR { opArr[opArr_ID] = OP_GTR; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else{                      CODEGEN("isub\n");  }   
        CODEGEN("ifgt comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;                              
       
    }
    | Expression3 GEQ { opArr[opArr_ID] = OP_GEQ; opArr_ID++; } Expression4
    {
        $$.type = $4.type;
        $$.b_val = $1.b_val | $4.b_val;
        if(!strcmp(get_type_name($4.type),"f32")){ CODEGEN("fcmpl\n"); }
        else{                      CODEGEN("isub\n");  }   
        CODEGEN("ifge comp_true_%d\n",CompNUM);
        CODEGEN("iconst_0\n");
        CODEGEN("goto comp_end_%d\n",CompNUM);
        CODEGEN("comp_true_%d:\n",CompNUM);
        CODEGEN("iconst_1\n");
        CODEGEN("comp_end_%d:\n",CompNUM);
        CompNUM++;  
    }
    | Expression4 { $$ = $1;}
;
Expression4 
    : Expression4 add_op { opArr[opArr_ID] = $2; opArr_ID++; } Expression5
    {
        opArr_ID--;
        while(opArr_ID>=0){ opArr_ID--; }
        opArr_ID =0;  
        switch($2){
            case OP_ADD:
                if($4.type == TYPE_INT )                           { CODEGEN("iadd\n"); }
                else                                               { CODEGEN("fadd\n"); }
                break;
            case OP_SUB:
                if($4.type == TYPE_INT)                            { CODEGEN("isub\n"); }
                else                                               { CODEGEN("fsub\n"); }
                break;
        }
        $$ = $4;
    }
    | Expression5 
;
Expression5 
    : Expression5 mul_op { opArr[opArr_ID] = $2; opArr_ID++; } Expression6
    {
        if ((($1.type == TYPE_FLOAT) && ($4.type == TYPE_INT ))|| (($1.type == TYPE_INT) && ($4.type == TYPE_FLOAT ))){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        }
        if ($1.type == TYPE_NULL || $4.type == TYPE_NULL){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        }
        if ((($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) && (opArr[opArr_ID] == OP_REM)){
            g_has_error = true;
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",yylineno+1,get_op_name($2),get_type_name($1.type),get_type_name($4.type));
        }
        else if (($1.type == TYPE_FLOAT) || ($4.type == TYPE_FLOAT)) $$.type = $4.type;
        $$.type = $4.type;
        $$ = $4;
        opArr_ID--;
        while(opArr_ID>=0) { printf("%s\n",get_op_name(opArr[opArr_ID])); opArr_ID--; }
        opArr_ID =0;  
        switch($2){
            case OP_MUL:
                if($4.type == TYPE_INT){ CODEGEN("imul\n"); }
                else                   { CODEGEN("fmul\n"); }
                break;
            case OP_DIV:
                if($4.type == TYPE_INT){ CODEGEN("idiv\n"); }
                else{                    CODEGEN("fdiv\n"); }
                break;
            case OP_REM:
                if($4.type == TYPE_INT){ CODEGEN("irem\n"); }
                break;
        }
        $$ = $4;
    }
    | Expression6 {$$ = $1;}
;
Expression6 
    : UnaryExpr {$$ = $1;}
    | UnaryExpr AS Type 
    { 
        if     ( $1.type == TYPE_INT && $3 == TYPE_FLOAT) { CODEGEN("i2f\n");$$.f_val = $1.i_val; $$.type = $3; }
        else if( $1.type == TYPE_FLOAT && $3 == TYPE_INT) { CODEGEN("f2i\n");$$.i_val = $1.f_val; $$.type = $3; }
        else                                              { $$.s_val = $1.s_val; $$.type = $3; }
    }
;
UnaryExpr 
    : PrimaryExpr { $$ = $1; $$.type = $1.type; }
    | unary_op UnaryExpr { $$.type = $2.type; $$ = $2; }
    | functionCall 
;
functionCall
    : ID LPAREN { parameterARR_ID=0;} ParameterListInFunctionCall RPAREN 
    {
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));
        //if(parameterARR_ID==0) strcat(sig,"V");
        strcat(sig,")");

        Node * func = lookup_symbol($<s_val>1,0);

        if(func!=NULL)
        {
            strcat(sig,get_parametertype_name(func->ret));
            func->func_sig = sig;
        }
        CODEGEN("\tinvokestatic Main/%s%s\n", $<s_val>1, sig);
    }
    | ID LPAREN RPAREN
    {
        Node * func = lookup_symbol($<s_val>1,0);
        char *sig = "()V";
        func->func_sig = sig;
        CODEGEN("\tinvokestatic Main/%s%s\n", $<s_val>1, sig);
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
    : Operand { $$ = $1; }
    | ConversionExpr
;

ConversionExpr 
    : Type LPAREN Expression RPAREN
;

Operand 
    : Literal { $$ = $1; }
    | ID 
    {
        if(scope >0)
        {
            bool find = false;
            for(int i= scope-1;i>=0;i--)
            {
                Node * goal = lookup_symbol($<s_val>1,i);
                if (goal!=NULL) 
                {
                    $$.type = goal->type;
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
                if (goal!=NULL) { $$.type = goal->type; break; }
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
            }
        }
    } LBRACK INT_LIT RBRACK 
    {
        if(scope >0){
            bool find = false;
            for(int i= scope-1;i>=0;i--){
                char * name= $<s_val>4;
                Node * goal = lookup_symbol(name,i);
    
                if (goal!=NULL) { 
           
                    find = true; 
                    $$.type = goal->type;
                    if(goal->type == TYPE_INT)   CODEGEN("iload %d\n",goal->addr);
                    if(goal->type == TYPE_FLOAT) CODEGEN("fload %d\n",goal->addr);
                    if(goal->type == TYPE_STRING) CODEGEN("aload %d\n",goal->addr);
                    if(goal->type == TYPE_BOOL)   CODEGEN("iload %d\n",goal->addr);
                    break; }
            }
            if(find == false)
            {
                g_has_error = true;
                printf("error:%d: undefined: %s\n",yylineno+1,$<s_val>1);
                $$.type = TYPE_NULL;
            }
        } 
    }
    | LPAREN Expression RPAREN { $$.type = $2.type; $$.s_val = $2.s_val; } 
;
Interindex
    : DOTDOT         { printf("DOTDOT\n"); } Literal
    | Literal DOTDOT { printf("DOTDOT\n"); } Literal
    | Literal DOTDOT { printf("DOTDOT\n"); }
;
Literal
    : INT_LIT   { 
                    $$.type = TYPE_INT; $$.i_val = atoi($<s_val>1); 
                    if($$.i_val < 0)  printf("INT_LIT %d\nNEG\n", -($$.i_val));
                    else              printf("INT_LIT %d\n", ($$.i_val));
                    CODEGEN("ldc %d\n", $$.i_val);
                }
    | FLOAT_LIT {   
                    $$.type = TYPE_FLOAT; $$.f_val = atof($<s_val>1); 
                    if($$.f_val < 0)  printf("FLOAT_LIT %f\nNEG\n", -($$.f_val));
                    else              printf("FLOAT_LIT %f\n", $$.f_val);
                    CODEGEN("ldc %f\n", $$.f_val);
                }
    | BOOL_LIT  {  
                    $$.type = TYPE_BOOL; 
                    if(strcmp($<s_val>1,"true")==0) { $$.b_val = true; printf("bool %s\n", "TRUE");CODEGEN("iconst_1\n"); }
                    else                            { $$.b_val = false; printf("bool %s\n", "FALSE");CODEGEN("iconst_0\n"); }
                }
    | STRING_LIT{ 
                    $$.type = TYPE_STRING; $$.s_val = $<s_val>1;
                    printf("STRING_LIT \"%s\"\n", $<s_val>1); 
                    CODEGEN("ldc \"%s\"\n", $$.s_val);
                }
;
assign_op
    : ASSIGN     {   $$ = OP_ASSIGN; }
    | ADD_ASSIGN {   $$ = OP_ADD_ASSIGN; }
    | SUB_ASSIGN {   $$ = OP_SUB_ASSIGN; }
    | MUL_ASSIGN {   $$ = OP_MUL_ASSIGN; }
    | DIV_ASSIGN {   $$ = OP_DIV_ASSIGN; }
    | REM_ASSIGN {   $$ = OP_REM_ASSIGN; }
;

AssignmentStmt 
    : Expression assign_op Expression SEMICOLON 
    {        
                                                          
        if(strcmp(get_op_name($<op>2),"ADD_ASSIGN")==0){                 
            if(!strcmp(get_type_name($3.type),"i32")){      CODEGEN("iadd\n"); CODEGEN("istore %d\n",get_addr($<s_val>1)); }
            else{                                           CODEGEN("fadd\n"); CODEGEN("fstore %d\n",get_addr($<s_val>1)); }
        }
        else if(strcmp(get_op_name($<op>2),"ASSIGN")==0){
            if(!strcmp(get_type_name($3.type),"i32"))       CODEGEN("istore %d\n",get_addr($<s_val>1));
            else if(!strcmp(get_type_name($3.type),"f32"))  CODEGEN("fstore %d\n",get_addr($<s_val>1));
            else if(!strcmp(get_type_name($3.type),"str"))  CODEGEN("astore %d\n",get_addr($<s_val>1));
            else                                            CODEGEN("istore %d\n",get_addr($<s_val>1));
            
        }
        else if(strcmp(get_op_name($<op>2),"SUB_ASSIGN")==0){                     
            if(!strcmp(get_type_name($3.type),"i32")){      CODEGEN("isub\n"); CODEGEN("istore %d\n",get_addr($<s_val>1));}
            else                                     {      CODEGEN("fsub\n"); CODEGEN("fstore %d\n",get_addr($<s_val>1));}
        }
        else if(strcmp(get_op_name($<op>2),"MUL_ASSIGN")==0){  
            if(!strcmp(get_type_name($3.type),"i32")){      CODEGEN("imul\n"); CODEGEN("istore %d\n",get_addr($<s_val>1)); }
            else{                                           CODEGEN("fmul\n"); CODEGEN("fstore %d\n",get_addr($<s_val>1)); }
        }
        else if(strcmp(get_op_name($<op>2),"DIV_ASSIGN")==0){                                                  
            if(!strcmp(get_type_name($3.type),"i32")){      CODEGEN("idiv\n"); CODEGEN("istore %d\n",get_addr($<s_val>1)); }
            else{                                           CODEGEN("fdiv\n"); CODEGEN("fstore %d\n",get_addr($<s_val>1)); }
        }
        else if(strcmp(get_op_name($<op>2),"REM_ASSIGN")==0){CODEGEN("irem\n");CODEGEN("istore %d\n",get_addr($<s_val>1)); }
                             
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
        {
            g_has_error = true;
            printf("error:%d: undefined: %s\n",yylineno+1,$<s_val>1);
        }
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
    : LBRACE { create_symbol(scope); scope++; } StatementList RBRACE
    {
        dump_symbol();
    }
;

/* IF statement **************************************/
IfStmt 
    : IF Condition IfBlock ELSE IfStmt 
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
    | IF Condition IfBlock
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
    | IF Condition IfBlock ELSE Block 
    {
        CODEGEN("if_end_%d:\n", If_cnt);
        If_cnt++;
    }
;
IfBlock
    : LBRACE  { create_symbol(scope); scope++; CODEGEN("ifne if_false_%d\n", ifBlockNumOfTime); } StatementList RBRACE 
    {   
        CODEGEN("goto if_end_%d\nif_false_%d:\n", If_cnt,ifBlockNumOfTime++);
        dump_symbol();                            
    }
    | LBRACE {  create_symbol(scope); scope++; CODEGEN("ifne if_false_%d\n",ifBlockNumOfTime);}  RBRACE
    {
        CODEGEN("goto if_end_%d\nif_false_%d:\n", If_cnt,ifBlockNumOfTime++);
        dump_symbol();
    }
;
/* IF statement **************************************/
WhileStmt
    : WHILE {  CODEGEN("L%d_for_begin:\nL%d_ForCondition:\n", while_num,while_num); }Condition { CODEGEN("ifeq L%d_for_Exit \ngoto L%d_FBlock\n", while_num,while_num);  } WhileBlock { CODEGEN("goto L%d_ForCondition \n", while_num);   CODEGEN("L%d_for_Exit:\n", while_num); }
; 
WhileBlock
     : LBRACE {CODEGEN("L%d_FBlock:\n",while_num);  create_symbol(scope); scope++; } StatementList RBRACE {dump_symbol();}
;
/* For statement *************************************/
ForStmt
    : FOR Condition Block ELSE Block
    | FOR ForClause Block ELSE Block
    | FOR ForClause LBRACE StatementList RBRACE { dump_symbol();}
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
                VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
                switch($3.type)
                {
                    case TYPE_INT:    { temp->i_val = goal->val->i_val; break; }
                    case TYPE_FLOAT:  { temp->f_val = goal->val->f_val; break; }
                    case TYPE_BOOL:   { temp->b_val = goal->val->b_val; break; }
                    case TYPE_STRING: { temp->s_val = goal->val->s_val; break; }
                    case TYPE_NULL:   { temp->s_val = goal->val->s_val; break; }
                }
                insert_symbol($<s_val>1, goal->arrtype, yylineno,0);
                break;
            }
        }
        insert_symbol($<s_val>1, goal->arrtype, yylineno,0);
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
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        switch($4)
        {
            case TYPE_INT:    temp->i_val = $6.i_val; break;
            case TYPE_FLOAT:  temp->f_val = $6.f_val; break;
            case TYPE_BOOL:   temp->b_val = $6.b_val; break;
            case TYPE_STRING: temp->s_val = $6.s_val; break;
        }
        insert_symbol($<s_val>2, $<type>4, yylineno,0, temp);
        switch($<type>4)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>2)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr($<s_val>2)); break;
        }
    }
    | LET ID COLON Type SEMICOLON
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>2, $<type>4, yylineno,0,temp);
        switch($<type>4)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>2)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr($<s_val>2)); break;
        }
    }
    | LET MUT ID COLON Type ASSIGN Literal SEMICOLON
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = true;
        switch($<type>5)
        {
            case TYPE_INT:    temp->i_val = $7.i_val; break;
            case TYPE_FLOAT:  temp->f_val = $7.f_val; break;
            case TYPE_BOOL:   temp->b_val = $7.b_val; break;
            case TYPE_STRING: temp->s_val = $7.s_val; break;
        }
        insert_symbol($<s_val>3, $<type>5, yylineno,1,temp);
        Node* goal = lookup_symbol($<s_val>3,scope-1);
        switch($<type>5)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>3)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr($<s_val>3)); break;
        }
       
    }
    | LET MUT ID COLON Type SEMICOLON
    {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>3, $<type>5, yylineno,1,temp);
        switch($<type>5)
        {
            case TYPE_INT:    CODEGEN("ldc 0\n"); CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_FLOAT:  CODEGEN("ldc 0.0\n"); CODEGEN("fstore %d\n",get_addr($<s_val>3)); break;
            case TYPE_BOOL:   CODEGEN("ldc iconst_1\n"); CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_STRING: CODEGEN("ldc ""\n"); CODEGEN("astore %d\n",get_addr($<s_val>3)); break;
        }
    }
    | LET ID COLON Type ASSIGN SEMICOLON
    {
        /**** for "" string literal ****/ 
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>2, $<type>4, yylineno,0,temp);
        switch($<type>4)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>2)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_STRING: CODEGEN("astore %d\n",get_addr($<s_val>2)); break;
        }
    }
    | LET MUT ID COLON Type ASSIGN SEMICOLON  
    {
        /**** for "" string literal ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>3, $<type>5, yylineno,1,temp);
        Node* goal = lookup_symbol($<s_val>3,scope-1);
        switch($<type>5)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>3)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr($<s_val>3)); break;
        }
    }
    | LET MUT ID ASSIGN Operand SEMICOLON
    {
        /**** for assign ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->i_val = $<s_val>5;
        insert_symbol($<s_val>3, TYPE_INT, yylineno,1,temp);
        switch($<type>5)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>3)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>3)); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr($<s_val>3)); break;
        }
           
    }
    | LET ID COLON LBRACK Type SEMICOLON Operand RBRACK ASSIGN LBRACK{arr_name = $<s_val>2;arr_num = $7.i_val - 1;} LiteralList RBRACK SEMICOLON
    {
        /**** for array ****/   
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false; 
        insert_symbol($<s_val>2, TYPE_ARR, yylineno,0,temp);
        Node * arrNode = lookup_symbol($<s_val>2,scope-1);
        arr_name = $<s_val>2;
        arr_index = 0;

        
        lookup_symbol($<s_val>2,scope-1)->arrnum = 0;
        if(arrNode){ 
            arrNode->arrtype = $5;
           
        }
    }
    | LET ID ASSIGN Operand SEMICOLON
    {
        /**** for assign ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        Node * goal = lookup_symbol($<s_val>2,scope-1);
        
        insert_symbol($<s_val>3, $4.type, yylineno,0,temp);
        switch($4.type)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>2)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr($<s_val>2)); break;
        }
    }
    | LET ID COLON Type ASSIGN LOOP Block SEMICOLON
    {
        /**** for loop ****/
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>2, $<type>4, yylineno,0,temp);
        switch($<type>4)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",get_addr($<s_val>2)); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",get_addr($<s_val>2)); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",get_addr($<s_val>2)); break;
        }
    }
;




LiteralList
    : Literal COMMA LiteralList {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        char name[100];
        name[0] ='0' +arr_num - arr_index;
        name[1] = '\0';
        insert_symbol(name, $1.type, yylineno,0,temp);
        Node * goal = lookup_symbol(name,scope-1);
        CODEGEN("istore %d\n",goal->addr );
        arr_index++;
        switch($<type>1)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",goal->addr); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",goal->addr); break;
        }
    }
    | Literal {
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        char name[100];
        name[0] ='0' +arr_num - arr_index;
        name[1] = '\0';

        insert_symbol(name, $1.type, yylineno,0,temp);
        Node * goal = lookup_symbol(name,scope-1);
        CODEGEN("istore %d\n",goal->addr );
        arr_index++;
        switch($<type>1)
        {
            case TYPE_INT:    CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_FLOAT:  CODEGEN("fstore %d\n",goal->addr); break;
            case TYPE_BOOL:   CODEGEN("istore %d\n",goal->addr); break;
            case TYPE_STRING: CODEGEN("ldc \"\"\n"); CODEGEN("astore %d\n",goal->addr); break;
        }
    }
;
LetStatementCon
    : ASSIGN Literal SEMICOLON
    |
;
/* Let statement *************************************/

PrintStmt 
    : PRINT Expression   
    { 
        if($2.type == TYPE_INT){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(I)V\n");
        }
        else if($2.type == TYPE_STRING){
	        CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
	        CODEGEN("swap\n");
	        CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }
        else if($2.type == TYPE_FLOAT){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(F)V\n");
        }
        else if($2.type == TYPE_BOOL){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/print(Z)V\n");
        }
    } SEMICOLON
    | PRINTLN Expression 
    { 
        if($2.type == TYPE_INT){
            // CODEGEN("dddkk ldc %d\n",$2.i_val);
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(I)V\n");
        }
        else if($2.type == TYPE_STRING){
           // CODEGEN("ldc \"%s\"\n",$2.s_val);
	       CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
	       CODEGEN("swap\n");
	       CODEGEN("invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        }
        else if($2.type == TYPE_FLOAT){
            //CODEGEN("ldc %f\n",$2.f_val);
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(F)V\n");
        }
        else if($2.type == TYPE_BOOL){
            CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            CODEGEN("swap\n");
            CODEGEN("invokevirtual java/io/PrintStream/println(Z)V\n");
        }
    } SEMICOLON
;

ReturnStmt 
    : RETURN Expression SEMICOLON
    {
        printf("%s\n",get_rettype_name($2.type));
    }
;

GlobalStatement  
    : FunctionDeclStmt 
    | NEWLINE
;
PackageStmt 
    : PACKAGE ID
;

FunctionDeclStmt 
    : FuncOpen LPAREN RPAREN 
    {  
        Node * func = lookup_symbol($<s_val>1,0);
        func -> ret = TYPE_NULL;
        dump_symbol();
        if (!strcmp($<s_val>1, "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                            CODEGEN(".method public static %s()V\n", $1);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }FuncBlock 
    {
        Node * func = lookup_symbol($<s_val>1,0);
        if(func->ret == TYPE_NULL) CODEGEN("\treturn\n");
        else                       CODEGEN("\t%s\n",get_rettype_name(func->ret));
        CODEGEN(".end method\n");
    }
    | FuncOpen LPAREN ParameterList RPAREN Type
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL) func -> ret = TYPE_NULL;
        dump_symbol();
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));

        strcat(sig,")");
        strcat(sig,get_rettype_name($5));
        CODEGEN(".method public static %s%s\n", $<s_val>1, func->func_sig);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }FuncBlock

    | FuncOpen LPAREN RPAREN ARROW Type  
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL)
        {
            func -> ret = $5;
            printf("%s\n",get_rettype_name($5));
        }
        dump_symbol();

        if (!strcmp($<s_val>1, "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                            CODEGEN(".method public static %s(V)%s\n", $1,get_type_name($5));
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }FuncBlock
    {
        Node * func = lookup_symbol($1,0);
        if(func->ret == TYPE_NULL)      CODEGEN("\treturn\n");
        else                            CODEGEN("\t%s\n",get_rettype_name(func->ret));
        CODEGEN(".end method\n");
    }
    | FuncOpen LPAREN ParameterList RPAREN ARROW Type 
    {
        Node * func = lookup_symbol($1,0);
        if(func != NULL)
        {
            func -> ret = $6;
            printf("%s\n",get_rettype_name($6));
        }
        dump_symbol();
        char sig[128]="(";
        for(int i=0;i<parameterARR_ID;i++) strcat(sig,get_parametertype_name(parameterARR[i]));

        strcat(sig,")");
        strcat(sig,get_parametertype_name($6));

        CODEGEN(".method public static %s%s\n", $<s_val>1, sig);
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
    }
    FuncBlock
    {
        Node * func = lookup_symbol($1,0);
        if(func->ret == TYPE_NULL) CODEGEN("return\n");
        else CODEGEN("ireturn\n");
        CODEGEN(".end method\n");
    }
;
FuncOpen
    : FUNC ID 
    { 
        addr = -1; 
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>2, TYPE_FUNC,yylineno,-1,temp);
        create_symbol(scope); 
        scope++;
        $$ = $<s_val>2;
    } 
;

ParameterList 
    : ID COLON Type 
    {
        parameterARR[parameterARR_ID] = $3;
        parameterARR_ID++;
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>1, $3, yylineno,0,temp);
    }
    | ParameterList COMMA ID COLON Type 
    {
        parameterARR[parameterARR_ID] = $5;
        parameterARR_ID++;
        VALUE * temp = (VALUE*) malloc(sizeof(VALUE));
        temp->assign = false;
        insert_symbol($<s_val>3, $5,yylineno,0,temp);
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