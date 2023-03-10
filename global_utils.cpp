#include "interpreter.hpp"

static void label(AST *node, int &id) {
  if (!node) return;

  cout << "\tNode" << id << "[label=\"";

  if (dynamic_cast<BinaryExpression *>(node))
    cout << token_names[((BinaryExpression *)node)->op];
  else if (dynamic_cast<UnarySign *>(node))
    cout << "[" << ((UnarySign *)node)->sign << "]";
  else if (dynamic_cast<VariableDeclaraction *>(node))
    cout << "VD";
  else if (dynamic_cast<CallExpression *>(node))
    cout << "CE";
  else if (dynamic_cast<LambdaDeclaration *>(node))
    cout << "LD[" << ((LambdaDeclaration *)node)->name << "]";
  else if (dynamic_cast<LiteralType *>(node))
    cout << ((LiteralType *)node)->value;
  else if (dynamic_cast<Identifier *>(node))
    cout << ((Identifier *)node)->name;
  else if (dynamic_cast<BinaryAssign *>(node))
    cout << "=";

  cout << "\"]\n";
}

static void edge(int from, int to) {
  cout << "\tNode" << from << " -> "
       << "Node" << to << "[wieght=9]\n";
}

static int dfs(AST *node, int &id) {
  int my_id = 0, l, r;

  my_id = id++;

  if (node) {
    label(node, my_id);
    if (dynamic_cast<Binary *>(node)) {
      l = dfs(((Binary *)node)->left, id);
      r = dfs(((Binary *)node)->right, id);
      edge(my_id, l);
      edge(my_id, r);
    } else if (dynamic_cast<Unary *>(node)) {
      l = dfs(((Unary *)node)->expr, id);
      edge(my_id, l);
    } else if (dynamic_cast<VariableDeclaraction *>(node)) {
      VariableDeclaraction *vd = (VariableDeclaraction *)node;
      for (auto declaration : vd->declarations) {
        l = dfs(declaration, id);
        edge(my_id, l);
      }
    } else if (dynamic_cast<CallExpression *>(node)) {
      CallExpression *callExpr = (CallExpression *)node;
      for (auto arg : callExpr->args) {
        l = dfs(arg, id);
        edge(my_id, l);
      }
    } else if (dynamic_cast<LambdaDeclaration *>(node)) {
      LambdaDeclaration *lambdaDeclaration = (LambdaDeclaration *)node;
      l = dfs(lambdaDeclaration->expr, id);
      edge(my_id, l);
    }
  }

  return my_id;
}

void dump_dot(AST *tree) {
  if (!tree) return;
  cout << "digraph {\n";
  int id = 0;
  dfs(tree, id);
  cout << "}\n";
}

string get_number(const string &line, int &idx) {
  int len = 0;
  while (isdigit(line[idx])) {
    idx++;
    len++;
  }
  return line.substr(idx - len, len);
}

string get_identifier(const string &line, int &idx) {
  int len = 0;
  while (isalnum(line[idx]) || line[idx] == '_') {
    len++;
    idx++;
  }
  return line.substr(idx - len, len);
}

void init_token_names(map<int, string> &token_names) {
  token_names[ADD] = "+";
  token_names[SUB] = "-";
  token_names[MUL] = "*";
  token_names[DIV] = "/";
  token_names[MOD] = "%";
  token_names[OP] = "(";
  token_names[CP] = ")";
  token_names[EQ] = "=";
  token_names[POW] = "^";
  token_names[COMMA] = ",";
  token_names[COLON] = ":";
  token_names[NONE] = "#";
}