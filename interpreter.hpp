#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <math.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "ast.hpp"
#include "exception.hpp"
#include "global_utils.hpp"
#include "parser.hpp"

using namespace std;

enum token_type {
  ADD = 1 << 0,
  SUB = 1 << 1,
  MUL = 1 << 2,
  DIV = 1 << 3,
  MOD = 1 << 4,  // add support
  POW = 1 << 5,
  NUM = 1 << 6,
  IDENT = 1 << 7,
  OP = 1 << 8,
  CP = 1 << 9,
  EQ = 1 << 10,
  NONE = 1 << 11,
  LET = 1 << 12,
  COMMA = 1 << 13,
  END = 1 << 14,
};

// abstract syntax tree prototypes

// global variables
extern map<Identifier, Type> vars;
extern AST *last;

#endif