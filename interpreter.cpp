#include "interpreter.hpp"

map<int, string> token_names;
map<Identifier, double> vars;

int main()
{

    init_token_names(token_names);
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
            free(line);
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
    }
}