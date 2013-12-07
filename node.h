#ifndef __NODE_H__
#define __NODE_H__

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
  virtual void generate_code(ofstream &f);
  
  virtual ~AST_node();
  
  virtual void add_to_symbol_table(bool isGlobal);
};
// -- END BASE --

// -- MODULE CLASS --
class module_node : public AST_node {
 public:
  vardecl_list_node* vardecl_list;
  funcdef_list_node* funcdef_list;
  funcdecl_list_node* funcdecl_list;

  module_node(vardecl_list_node* vardecl_list, funcdef_list_node* funcdef_list,
              funcdecl_list_node* funcdecl_list);

  virtual void generate_code(ofstream& f);

  ~module_node();
};
// -- END MODULE --

// -- FUNCTION NODES --
// definitions
class funcdef_list_node : public AST_node {
 public:
  vector<AST_node*> list;

  funcdef_list_node(AST_node* funcdef);  

  virtual void generate_code(ofstream& f);

  virtual void add_to_symbol_table(bool isGlobal);

  ~funcdef_list_node();
};

class funcdef_node : public AST_node {
  public:
  paramlist_node* paramlist;
  AST_node* block;
  string id;

  funcdef_node(string id, paramlist_node* paramlist, AST_node* block);

  virtual void generate_code(ofstream& f);

  virtual void add_to_symbol_table(bool isGlobal);

  ~funcdef_node();
};

class sfuncdef_node : public AST_node {
 public:
  paramlist_node* paramlist;
  AST_node* block;
  string id;
  void generate_code(ofstream& f);
  void add_to_symbol_table(bool);
  sfuncdef_node(string id, AST_node* paramlist, AST_node* block);
  ~sfuncdef_node();
};

class funcdecl_list_node : public AST_node {
 public:
  vector<AST_node*> list;
    
  funcdecl_list_node(AST_node* funcdecl);
  void generate_code(ofstream& f);
  void add_to_symbol_table(bool isGlobal);
  ~funcdecl_list_node();
};

// declarations
class funcdecl_node : public AST_node {
 public:
  AST_node* paramlist;
  string id;
  void generate_code(ofstream& f);
  funcdecl_node(string id, AST_node* paramlist);
  void add_to_symbol_table(bool isGlobal);
  ~funcdecl_node();
};

class sfuncdecl_node : public AST_node {
 public:
  AST_node* paramlist;
  string id;

  sfuncdecl_node(string id, AST_node* paramlist);
  void generate_code(ofstream& f);
  void add_to_symbol_table(bool isGlobal);
  ~sfuncdecl_node();
};

// parameters
class paramlist_node : public AST_node {
 public:
  vector<param_node*> list;

  paramlist_node(param_node* param);

  ~paramlist_node();

  virtual void generate_code(ofstream& f);
};

class param_node : public AST_node {
 public:
  string id;
  string type;

  param_node(string type, string id);

  virtual void generate_code(ofstream& f);
};

// -- EXPRESSION NODE --
class expr_node : public AST_node {
 public:
  string id;
  string type;
};
// -- END EXPR NODE --

// function calls
class function_node : public expr_node {
 public:
  arglist_node* argument_list;

  function_node(string id, arglist_node* arg_list);
  virtual void generate_code(ofstream& f);
  ~function_node();
};

class arglist_node : public AST_node {
 public:
  vector<expr_node*> list;

  arglist_node(expr_node* node);
  virtual void generate_code(ofstream& f);
  ~arglist_node();
};
// -- END FUNCTIONS --


// -- CODE BODY CLASSES --
class block_node : public AST_node {
  public:
  AST_node* vardecl_list;
  AST_node* stmt_list;

  block_node(AST_node* vdecl_l, AST_node* stmt_l);

  virtual void generate_code(ofstream& f);

  ~block_node();
};

// statements
class stmtlist_node : public AST_node {
  public:
  vector<AST_node*> list;

  stmtlist_node(AST_node* node);
  virtual void generate_code(ofstream& f);
  ~stmtlist_node();

};

// variable declarations
class vardecl_list_node : public AST_node {
 public:
  vardecl_list_node(AST_node* node);
  vector<AST_node*> list;
  ~vardecl_list_node();
  virtual void generate_code(ofstream& f);
  void add_to_symbol_table(bool isGlobal);
};

class vardecl_node : public AST_node {
 public:
  string type;
  string id;
  bool isExtern;
  expr_node* assign;

  /*vardecl_node(string type, string id) : AST_node() {
    this->type = type;
    this->id = id;
  }*/

  vardecl_node(string type, string id, expr_node* assign);

  vardecl_node(string type, string id, bool e = false);
  ~vardecl_node();
  virtual void generate_code(ofstream& f);
  virtual void add_to_symbol_table(bool isGlobal);
};

// return
class return_node : public AST_node {
 public:
  expr_node* ret;
  return_node(expr_node *ret);
  ~return_node();

  virtual void generate_code(ofstream& f);
};
// -- END CODE BODY --

// -- OPERATORS --
// ternary
class ternary_node : public expr_node {
  public:
    expr_node* question;
    expr_node* left;
    expr_node* right;

    ~ternary_node();
    ternary_node(expr_node* question, expr_node* left, expr_node* right);

    virtual void generate_code(ofstream& f);
};

// binary
class add_node : public expr_node {
  public:
    expr_node* left;
    expr_node* right;

    add_node(expr_node* left, expr_node* right);
    ~add_node();
    virtual void generate_code(ofstream& f);
};

class mult_node : public expr_node {
  public:
    expr_node* left;
    expr_node* right;

    mult_node(expr_node* left, expr_node* right);
    ~mult_node();
    virtual void generate_code(ofstream& f);
};

class sub_node : public expr_node {
 public:
  expr_node* left;
  expr_node* right;
  
  sub_node(expr_node* left, expr_node* right);
  ~sub_node();
  virtual void generate_code(ofstream& f);
};

class div_node : public expr_node {
 public:
  expr_node* left;
  expr_node* right;
  
  div_node(expr_node* left, expr_node* right);
  ~div_node();
  virtual void generate_code(ofstream& f);  
};

class assign_node : public expr_node {
 public:
  expr_node* left;
  expr_node* right;
  assign_node(expr_node* left, expr_node* right);
  ~assign_node();

  virtual void generate_code(ofstream& f);
};

// unary
class print_node : public expr_node {
  public:
    expr_node* term;
    print_node(expr_node* term);
    ~print_node();
    virtual void generate_code(ofstream& f);
};

class address_node : public expr_node {
  public:
    expr_node* ptr;
    address_node(expr_node* ptr);
    virtual void generate_code(ofstream& f);
    ~address_node();
};

class dereference_node : public expr_node {
  public:
    expr_node* ptr;
    dereference_node(expr_node* ptr);
    virtual void generate_code(ofstream& f);
    ~dereference_node();
};
// -- END OPERATORS --


// -- TERMS (VARS/LITS) --
class variable_node : public expr_node {
  public:
    variable_node(string s);
    virtual void generate_code(ofstream& f);
};

class IntLiteral_node : public expr_node {
 public:
  int literal;
  IntLiteral_node(int i);
  virtual void generate_code(ofstream& f);
};

class stringliteral_node : public expr_node {
 public:
  string literal;
  stringliteral_node(string str);
  virtual void generate_code(ofstream& f);
};
// -- END TERMS --

#endif /* NODE_H */
