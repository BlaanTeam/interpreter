#include "interpreter.hpp"

Number::Number(double _value) : value(_value) {}

double Number::eval()
{
    return this->value;
}

Identifier::Identifier(const string &name) : name(name) {}

double Identifier::eval()
{
    if (vars.find(name) == vars.end())
        throw NameError(name);
    return vars[name];
}

bool Identifier::operator<(const Identifier &rhs) const
{
    return name < rhs.name;
}

Binary::Binary(AST *left_, AST *right_) : left(left_), right(right_) {}

Binary::~Binary()
{
    delete left;
    delete right;
}

BinaryExpression::BinaryExpression(int op_, AST *left_, AST *right_) : Binary(left_, right_), op(op_) {}

double BinaryExpression::eval()
{
    double value = 0.0;

    if (op == ADD)
        value = left->eval() + right->eval();
    else if (op == SUB)
        value = left->eval() - right->eval();
    else if (op == MUL)
        value = left->eval() * right->eval();
    else if (op == DIV)
        value = left->eval() / right->eval();
    else if (op == POW)
        value = pow(left->eval(), right->eval());

    return value;
}

BinaryAssign::BinaryAssign(AST *ident_, AST *expr_) : Binary(ident_, expr_) {}
double BinaryAssign::eval()
{
    double value = right->eval();
    vars[*((Identifier *)left)] = value;
    return value;
}

Unary::Unary(AST *expr_) : expr(expr_) {}

UnarySign::UnarySign(int sign_, AST *expr) : Unary(expr), sign(sign_) {}
double UnarySign::eval()
{
    return sign * expr->eval();
}
