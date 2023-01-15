#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <cstring>
#include <iostream>

using namespace std;

class NameError : public exception {
 public:
  string name;
  NameError(const string &_name);
  const char *what(void) const throw();
};

#endif