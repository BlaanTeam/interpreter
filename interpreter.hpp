#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <readline/readline.h>
#include <readline/history.h>
#include <math.h>

#include "ast.hpp"
#include "parser.hpp"
#include "exception.hpp"
#include "global_utils.hpp"

using namespace std;

enum token_type
{
    ADD = 1 << 0,
    SUB = 1 << 1,
    MUL = 1 << 2,
    DIV = 1 << 3,
    MOD = 1 << 4, // add support
    POW = 1 << 5,
    NUM = 1 << 6,
    IDENT = 1 << 7,
    OP = 1 << 8,
    CP = 1 << 9,
    EQ = 1 << 10,
    NONE = 1 << 11,
    CALL = 1 << 12,
    END = 1 << 13,
};

// abstract syntax tree prototypes

// global variables
extern map<Identifier, double> vars;

#endif