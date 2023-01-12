#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <iostream>
#include <cstring>

using namespace std;

class NameError : public exception
{

public:
    string name;
    NameError(const string &_name);
    const char *what(void) const throw();
};

#endif