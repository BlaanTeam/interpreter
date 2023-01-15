#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>

#define NONE_TYPE 1
#define LITERAL_TYPE 2
#define FUNCTION_TYPE 4

using namespace std;

class Type;

class AST {
 public:
  virtual Type eval() = 0;
  virtual ~AST() = default;
};

class Type {
 public:
  short  type;
  double value;
  Type();
  Type(const short &, const double &);
  short operator&(const short) const;

  Type operator+(const Type &) const;
  Type operator-(const Type &) const;
  Type operator*(const Type &) const;
  Type operator/(const Type &) const;
};

ostream &operator<<(ostream &, const Type &);

class LiteralType : public AST {
 public:
  double value;

 public:
  LiteralType(const double &);
  Type eval();
};

class Identifier : public AST {
 public:
  string name;
  Identifier(const string);
  Type eval();

  bool operator<(const Identifier &) const;
};

class Binary : public AST {
 public:
  AST *left;
  AST *right;
  Binary(AST *, AST *);
  virtual ~Binary();
};

class BinaryExpression : public Binary {
 public:
  int op;
  BinaryExpression(int, AST *, AST *);
  Type eval();
};

class BinaryAssign : public Binary {
 public:
  BinaryAssign(AST *, AST *);
  Type eval();
};

class VariableDeclaraction : public AST {
 public:
  vector<AST *> declarations;
  VariableDeclaraction();
  void add(AST *);
  Type eval();
};

class Unary : public AST {
 public:
  AST *expr;
  Unary(AST *);
  Type eval() = 0;
};

class UnarySign : public Unary {
 public:
  int sign;
  UnarySign(int, AST *);
  Type eval();
};

#endif