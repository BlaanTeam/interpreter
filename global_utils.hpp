#ifndef __GLOBAL_UTILS_H__
#define __GLOBAL_UTILS_H__

#include <string>

#include "ast.hpp"

using namespace std;

// global utils prototypes

string get_number(const string &line, int &idx);
string get_identifier(const string &line, int &idx);

void init_token_names(map<int, string> &);

void dump_dot(AST *);

#endif