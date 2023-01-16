#include "parser.hpp"

Token::Token(const int &type_, const string &value_) : type(type_), value(value_) {}

bool Token::operator&(int types) const { return type & types; }

Parser::Parser(const string &line) {
  int idx = 0;
  while (idx < (int)line.size()) {
    if (isdigit(line[idx]))
      tokens.push(Token(NUM, get_number(line, idx)));
    else if (isalpha(line[idx]) || line[idx] == '_') {
      string name = get_identifier(line, idx);
      Token  token(IDENT, name);
      if (name == "let")
        token.type = LET;
      else if (name == "lambda")
        token.type = LAMBDA;
      tokens.push(token);
    } else {
      bool found = false;
      for (auto token_name : token_names) {
        string to_macth(1, line[idx]);
        if (token_name.second == to_macth) {
          tokens.push(Token(token_name.first, to_macth));
          found = true;
        }
      }
      if (!found && !isspace(line[idx])) tokens.push(Token(NONE, "#"));
      idx++;
    }
  }
  if (!is_empty()) tokens.push(Token(END, ""));
}

bool Parser::match(int types) const {
  if (is_empty()) return false;
  return tokens.front() & types;
}

bool Parser::accept(int types) {
  if (match(types)) {
    next();
    return true;
  }
  return false;
}
bool Parser::is_empty(void) const { return tokens.empty(); }

int    Parser::peek_type(void) const { return tokens.front().type; }
string Parser::peek_value(void) const { return tokens.front().value; }

void Parser::next(void) { tokens.pop(); }

AST *Parser::factor(void) {
  if (is_empty()) return nullptr;
  AST *ret = nullptr;

  const string value = peek_value();
  if (accept(IDENT))
    ret = new Identifier(value);
  else if (accept(NUM))
    ret = new LiteralType(stod(value));
  else if (accept(OP)) {
    ret = expression();
    if (!accept(CP)) return nullptr;
  }
  return ret;
}
AST *Parser::term(void) {
  if (is_empty()) return nullptr;

  AST   *ret = nullptr;
  string value = peek_value();
  if (accept(ADD | SUB)) {
    ret = new UnarySign(value == "+" ? 1 : -1, factor());
    if (!((UnarySign *)ret)->expr || match(NONE)) return nullptr;
  } else
    ret = factor();

  if (!ret || match(NONE)) return nullptr;

  while (match(MUL | DIV | POW)) {
    ret = new BinaryExpression(peek_type(), ret, nullptr);
    next();
    ((BinaryExpression *)ret)->right = factor();
    if (!((BinaryExpression *)ret)->right || match(NONE)) return nullptr;
  }
  return ret;
}

AST *Parser::expression(void) {
  if (is_empty()) return nullptr;

  AST *ret = term();
  if (!ret) return nullptr;

  while (match(ADD | SUB)) {
    ret = new BinaryExpression(peek_type(), ret, nullptr);
    next();
    ((BinaryExpression *)ret)->right = term();
    if (!((BinaryExpression *)ret)->right || match(NONE)) return nullptr;
  }
  return ret;
}

AST *Parser::assignment(void) {
  if (is_empty()) return nullptr;
  const string value = peek_value();
  AST         *ret = nullptr;
  if (accept(IDENT)) {
    if (!accept(EQ)) return nullptr;
    ret = new BinaryAssign(new Identifier(value), expression());
    if (!((Binary *)ret)->right || match(NONE)) return nullptr;
  }
  return ret;
}

AST *Parser::multiple_assignment() {
  if (is_empty() || !accept(LET)) return nullptr;

  AST *ret = assignment();

  if (!ret || match(NONE)) return nullptr;

  if (match(COMMA)) {
    VariableDeclaraction *vd = new VariableDeclaraction();

    vd->add(ret);

    while (accept(COMMA)) {
      ret = assignment();
      if (!ret || match(NONE)) return nullptr;
      vd->add(ret);
    }
    ret = (AST *)vd;
  }
  return ret;
}

AST *Parser::call_expression() {
  if (is_empty()) return nullptr;

  const string &func_name = peek_value();

  if (!accept(IDENT))
    return nullptr;
  else if (match(LAMBDA))
    return lambda_declaration(func_name);

  CallExpression *ret = new CallExpression(func_name);
  if (!accept(OP)) return nullptr;

  string arg_name = peek_value();
  int    type = peek_type();
  if (accept(IDENT | NUM)) {
    if (type & IDENT)
      ret->add(new Identifier(arg_name));
    else
      ret->add(new LiteralType(stod(arg_name)));
    while (accept(COMMA)) {
      arg_name = peek_value();
      type = peek_type();
      if (!accept(IDENT | NUM)) return nullptr;
      if (type & IDENT)
        ret->add(new Identifier(arg_name));
      else
        ret->add(new LiteralType(stod(arg_name)));
    }
  }
  if (!accept(CP)) return nullptr;
  return ret;
}

AST *Parser::lambda_declaration(const string &func_name) {
  if (is_empty()) return nullptr;

  if (!accept(LAMBDA)) return nullptr;
  string             arg_name = peek_value();
  LambdaDeclaration *ret = new LambdaDeclaration(func_name);
  if (accept(IDENT)) {
    ret->add(arg_name);
    while (accept(COMMA)) {
      arg_name = peek_value();
      if (!accept(IDENT)) return nullptr;
      ret->add(arg_name);
    }
  }

  if (!accept(COLON)) return nullptr;
  ret->expr = expression();
  if (!ret->expr) return nullptr;
  return ret;
}

AST *Parser::init(void) {
  if (is_empty()) return nullptr;
  AST *ret = nullptr;

  if (match(LET))
    ret = multiple_assignment();
  else if (match(IDENT))
    ret = call_expression();
  if (!ret || !accept(END)) {
    cerr << "Syntax Error !" << endl;
    return nullptr;
  }
  return ret;
}
