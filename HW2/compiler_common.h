#ifndef COMPILER_COMMON_H
#define COMPILER_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* Add what you need */
typedef enum {
        OP_LSHIFT,
        OP_RSHIFT,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
        OP_REM,
        OP_EQL,
        OP_NEQ,
        OP_LSS,
        OP_LEQ,
        OP_GTR,
        OP_GEQ,
        OP_POS,
        OP_NEG,
        OP_NOT,
        OP_LOR,
        OP_LAND,
        OP_ASSIGN,
        OP_ADD_ASSIGN,
        OP_SUB_ASSIGN,
        OP_MUL_ASSIGN,
        OP_DIV_ASSIGN,
        OP_REM_ASSIGN,
    } op_t;

    typedef enum {
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_BOOL,
        TYPE_STRING,
        TYPE_FUNC,
        TYPE_I2F,
        TYPE_F2I,
        TYPE_NULL,
        TYPE_ARR
    } type_t;
    
#endif /* COMPILER_COMMON_H */
