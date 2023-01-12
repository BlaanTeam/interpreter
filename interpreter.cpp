#include "interpreter.hpp"

map<int, string> token_names;
map<Identifier, double> vars;

int main()
{

    token_names[ADD] = "+";
    token_names[SUB] = "-";
    token_names[MUL] = "*";
    token_names[DIV] = "/";
    token_names[MOD] = "%";
    token_names[OP] = "(";
    token_names[CP] = ")";
    token_names[EQ] = "=";
    token_names[CALL] = "CALL";
    token_names[NONE] = "#";
    while (true)
    {
        try
        {
            char *line = readline("console >> ");
            if (!line)
                break;
            string block(line);
            Parser parser(block);
            // parser.display_tokens();
            AST *tree = parser.init();
            dump_dot(tree);
            if (tree)
                tree->eval();
            cout << "Variables :" << endl;
            for (auto var : vars)
                cout << var.first.name << " = " << var.second << endl;
            delete tree;
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
    }
}