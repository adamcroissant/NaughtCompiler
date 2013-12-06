#ifndef __NODE_H__
#define __NODE_H__

#include "nstring.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class variable_node;
class sub_node;
class div_node;
class mult_node;
class vardecl_node;
class vardecl_list_node;
class stmtlist_node;
class funcdef_node;
class funcdef_list_node;
class funcdecl_node;
class funcdecl_list_node;
class block_node;
class module_node;
class ternary_node;
class arglist_node;
class paramlist_node;
class assign_node;
class IntLiteral_node;
class StringLiteral_node;
class return_node;
class sfuncdef_node;
class sfuncdecl_node;
class funcion_node;
class param_node;
class print_node;

// -- BASE CLASS --
class AST_node {
 public:
  virtual string generate_code(ofstream &f);
  
  virtual ~AST_node();
};
// -- END BASE --

// -- MODULE CLASS --
class module_node : public AST_node {
 public:
  AST_node* vardecl_list;
  AST_node* funcdef_list;
  AST_node* funcdecl_list;

  module_node(vardecl_list_node* vardecl_list, funcdef_list_node* funcdef_list,
              funcdecl_list_node* funcdecl_list);

  virtual string generate_code(ofstream& f);

  ~module_node();
};
// -- END MODULE --

// -- FUNCTION NODES --
// definitions
class funcdef_list_node : public AST_node {
 public:
  vector<AST_node*> list;

  funcdef_list_node(AST_node* funcdef);  

  virtual string generate_code(ofstream& f);

  ~funcdef_list_node();
};

class funcdef_node : public AST_node {
  public:
  AST_node* paramlist;
  AST_node* block;
  string id;

  funcdef_node(string id, AST_node* paramlist, AST_node* block);

  virtual string generate_code(ofstream& f);

  ~funcdef_node();
};

class sfuncdef_node : public AST_node {
 public:
  AST_node* paramlist;
  AST_node* block;
  string id;

  sfuncdef_node(string id, AST_node* paramlist, AST_node* block);

  ~sfuncdef_node();
};

class funcdecl_list_node : public AST_node {
 public:
  vector<AST_node*> list;
    
  funcdecl_list_node(AST_node* funcdecl);

  ~funcdecl_list_node();
};

// declarations
class funcdecl_node : public AST_node {
 public:
  AST_node* paramlist;
  string id;

  funcdecl_node(string id, AST_node* paramlist);

  ~funcdecl_node();
};

class sfuncdecl_node : public AST_node {
 public:
  AST_node* paramlist;
  string id;

  sfuncdecl_node(string id, AST_node* paramlist);

  ~sfuncdecl_node();
};

// parameters
class paramlist_node : public AST_node {
 public:
  vector<AST_node*> list;

  paramlist_node(AST_node* param);

  ~paramlist_node();
};

class param_node : public AST_node {
 public:
  string id;
  string type;

  param_node(string type, string id);
};


// function calls
class function_node : public AST_node {
 public:
  string id;
  AST_node* argument_list;

  function_node(string id, AST_node* arg_list);

  ~function_node();
};

class arglist_node : public AST_node {
 public:
  vector<AST_node*> list;

  arglist_node(AST_node* node);

  ~arglist_node();
};
// -- END FUNCTIONS --


// -- CODE BODY CLASSES --
class block_node : public AST_node {
  public:
  AST_node* vardecl_list;
  AST_node* stmt_list;

  block_node(AST_node* vdecl_l, AST_node* stmt_l);

  virtual string generate_code(ofstream& f);

  ~block_node();
};

// statements
class stmtlist_node : public AST_node {
  public:
  vector<AST_node*> list;

  stmtlist_node(AST_node* node);
  virtual string generate_code(ofstream& f);
  ~stmtlist_node();

};

// variable declarations
class vardecl_list_node : public AST_node {
 public:
  vardecl_list_node(AST_node* node);
  vector<AST_node*> list;
  ~vardecl_list_node();
  virtual string generate_code(ofstream& f);
};

class vardecl_node : public AST_node {
 public:
  string type;
  string id;
  bool isExtern;
  AST_node* assign;

  /*vardecl_node(string type, string id) : AST_node() {
    this->type = type;
    this->id = id;
  }*/

  vardecl_node(string type, string id, AST_node* assign);

  vardecl_node(string type, string id, bool e = false);
  ~vardecl_node();
  virtual string generate_code(ofstream& f);
};

// return
class return_node : public AST_node {
 public:
  AST_node* ret;
  return_node(AST_node *ret);
  ~return_node();

  virtual string generate_code(ofstream& f);
};
// -- END CODE BODY --

// -- OPERATORS --
// ternary
class ternary_node : public AST_node {
  public:
    AST_node* question;
    AST_node* left;
    AST_node* right;

    ~ternary_node();
    ternary_node(AST_node* question, AST_node* left, AST_node* right);
  
};

// binary
class add_node : public AST_node {
  public:
    AST_node* left;
    AST_node* right;

    add_node(AST_node* left, AST_node* right);
    ~add_node();
    virtual string generate_code(ofstream& f);
};

class mult_node : public AST_node {
  public:
    AST_node* left;
    AST_node* right;

    mult_node(AST_node* left, AST_node* right);
    ~mult_node();
    virtual string generate_code(ofstream& f);
};

class sub_node : public AST_node {
  public:
    AST_node* left;
    AST_node* right;

    sub_node(AST_node* left, AST_node* right);
    ~sub_node();
    virtual string generate_code(ofstream& f);
};

class div_node : public AST_node {
  public:
    AST_node* left;
    AST_node* right;

    div_node(AST_node* left, AST_node* right);
    ~div_node();
    virtual string generate_code(ofstream& f);
};

class assign_node : public AST_node {
 public:
  AST_node* left;
  AST_node* right;
  assign_node(AST_node* left, AST_node* right);
  ~assign_node();
};

// unary
class print_node : public AST_node {
  public:
    AST_node* term;
    print_node(AST_node* term);
    ~print_node();
};
// -- END OPERATORS --


// -- TERMS (VARS/LITS) --
class variable_node : public AST_node {
  public:
    variable_node(string s);

    string var_name;
    virtual string generate_code(ofstream& f);
};

class IntLiteral_node : public AST_node {
 public:
  int literal;
  IntLiteral_node(int i);
  virtual string generate_code(ofstream& f);
};

class stringliteral_node : public AST_node {
 public:
  nstring_st literal;
  stringliteral_node(string str);
};
// -- END TERMS --

#endif /* NODE_H */
