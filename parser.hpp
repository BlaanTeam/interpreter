#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <map>
#include <queue>
#include <string>

#include "ast.hpp"
#include "global_utils.hpp"
#include "interpreter.hpp"

using namespace std;

extern map<int, string> token_names;

class Token {
 public:
  int    type;
  string value;
  Token(const int &, const string &);

  bool operator&(int) const;
};

class Parser {
 public:
  queue<Token> tokens;
  AST         *ast;
  Parser(const string &);

  bool match(int) const;
  bool is_empty(void) const;
  bool accept(int);

  int    peek_type(void) const;
  string peek_value(void) const;

  void next(void);

  AST *factor(void);
  AST *term(void);
  AST *expression(void);
  AST *assignment(void);
  AST *multiple_assignment(void);
  AST *init(void);
};

#endif