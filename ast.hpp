#ifndef __AST_H__
#define __AST_H__

#include <string>

using namespace std;

class AST
{
public:
    virtual double eval() = 0;
    virtual ~AST() = default;
};

class Number : public AST
{
public:
    double value;
    Number(double);
    double eval();
};

class Identifier : public AST
{
public:
    string name;
    Identifier(const string &);
    double eval();

    bool operator<(const Identifier &) const;
};

class Binary : public AST
{
public:
    AST *left;
    AST *right;
    Binary(AST *, AST *);
    virtual ~Binary();
};

class BinaryExpression : public Binary
{
public:
    int op;
    BinaryExpression(int, AST *, AST *);
    double eval();
};

class BinaryAssign : public Binary
{
public:
    BinaryAssign(AST *, AST *);
    double eval();
};

class Unary : public AST
{
public:
    AST *expr;
    Unary(AST *);
    double eval() = 0;
};

class UnarySign : public Unary
{
public:
    int sign;
    UnarySign(int, AST *);
    double eval();
};

#endif