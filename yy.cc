#include <iostream>
#include <string>
#include <cstdlib>

#include "yy.h"

using namespace std;

int yyerror(string msg, int lineno)
{
  cerr << "ERROR on line " << lineno << ": " << msg << endl;
  exit(1);
}

int yyerror(string s)
{
  cerr << "ERROR at symbol \"" << yytext << "\" on line " << yylineno << ": "
         << s << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}

