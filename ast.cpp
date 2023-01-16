#include "interpreter.hpp"

Type::Type() : type(NONE_TYPE){};
Type::Type(const short &_type, const double &_value = double()) : type(_type), value(_value) {}
short Type::operator&(const short _type) const { return type & _type; }

Type Type::operator+(const Type &_type) const {
  Type type(LITERAL_TYPE, this->value);

  type.value += _type.value;
  return type;
}
Type Type::operator-(const Type &_type) const {
  Type type(LITERAL_TYPE, this->value);

  type.value -= _type.value;
  return type;
}
Type Type::operator*(const Type &_type) const {
  Type type(LITERAL_TYPE, this->value);

  type.value *= _type.value;
  return type;
}
Type Type::operator/(const Type &_type) const {
  Type type(LITERAL_TYPE, this->value);

  type.value /= _type.value;
  return type;
}

ostream &operator<<(ostream &stream, const Type &_type) {
  stream << _type.value;
  return stream;
}

LiteralType::LiteralType(const double &_value) : value(_value) {}

Type LiteralType::eval() { return Type(LITERAL_TYPE, value); }

Identifier::Identifier(const string name) : name(name) {}

Type Identifier::eval() {
  if (vars.find(name) == vars.end()) throw NameError(name);
  return vars[name];
}

bool Identifier::operator<(const Identifier &rhs) const { return name < rhs.name; }

Binary::Binary(AST *left_, AST *right_) : left(left_), right(right_) {}

Binary::~Binary() {
  delete left;
  delete right;
}

BinaryExpression::BinaryExpression(int op_, AST *left_, AST *right_) : Binary(left_, right_), op(op_) {}

Type BinaryExpression::eval() {
  Type value(LITERAL_TYPE, 0.0);

  if (op == ADD)
    value = left->eval() + right->eval();
  else if (op == SUB)
    value = left->eval() - right->eval();
  else if (op == MUL)
    value = left->eval() * right->eval();
  else if (op == DIV)
    value = left->eval() / right->eval();
  else if (op == POW)
    value = pow(left->eval().value, right->eval().value);

  return value;
}

BinaryAssign::BinaryAssign(AST *ident_, AST *expr_) : Binary(ident_, expr_) {}
Type BinaryAssign::eval() {
  Type value = right->eval();

  // we always expect that the left child is an Identifier
  vars[((Identifier *)left)->name] = value;

  return Type(NONE_TYPE);
}

VariableDeclaraction::VariableDeclaraction() {}

void VariableDeclaraction::add(AST *declaration) { declarations.push_back(declaration); }

Type VariableDeclaraction::eval() {
  for (auto declaration : declarations) declaration->eval();
  return Type(NONE_TYPE);
}

Unary::Unary(AST *expr_) : expr(expr_) {}

UnarySign::UnarySign(int sign_, AST *expr) : Unary(expr), sign(sign_) {}
Type UnarySign::eval() { return Type(LITERAL_TYPE, sign) * expr->eval(); }

CallExpression::CallExpression(const string &_name) : name(_name) {}

void CallExpression::add(AST *arg) { args.push_back(arg); }

// buitin functions
void __print(vector<AST *> args) {
  for (size_t idx = 0; idx < args.size(); idx++) {
    cout << args[idx]->eval();
    if (idx + 1 < args.size()) cout << " ";
  }
  cout << endl;
}

void __clear(void) { vars.clear(); }

void __print_tree(void) {
  if (!last) {
    cerr << "No example available!" << endl;
    return;
  }
  dump_dot(last);
}

Type CallExpression::eval() {
  // buitin functions

  if (name == "print")
    __print(args);
  else if (name == "clear")
    __clear();
  else if (name == "tree")
    __print_tree();
  else if (vars.find(name) == vars.end())
    throw NameError(name);
  return Type(NONE_TYPE);
}
