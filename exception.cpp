#include "exception.hpp"

NameError::NameError(const string &_name) : name(_name) {}

const char *NameError::what(void) const throw()
{
    return strdup((name + " is not defined").c_str());
}