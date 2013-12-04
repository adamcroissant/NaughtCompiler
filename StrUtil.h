#ifndef _STRUTIL_H
#define _STRUTIL_H

#include <iostream>
#include <string>
using namespace std;

// A class that simplfies simply printing which
// grammar rules fire.
// This class is of no use in the naught compiler.
class StrUtil {
 public:
 StrUtil(const string &s) : str(s){}
  StrUtil operator+(const StrUtil &other) {
    return StrUtil(str + " " + other.str);
  }

  friend ostream& operator<<(ostream &os, const StrUtil &obj) {
    os << obj.str;
    return os;
  }

 private:
  string str;
};

#endif // _STRUTIL_H
