#include "interpreter.hpp"

map<int, string>      token_names;
map<Identifier, Type> vars;

AST *last = nullptr;

int main() {
  init_token_names(token_names);
  while (true) {
    try {
      char *line = readline("console >> ");
      if (!line) break;

      add_history(line);  // add the line to readline history !
      string block(line);
      
      Parser parser(block);

      AST *tree = parser.init();
      if (tree) tree->eval();
      free(last);
      last = tree;
      free(line);
    } catch (exception &e) {
      cerr << e.what() << endl;
    }
  }
  clear_history();
}