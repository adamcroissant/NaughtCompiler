#ifndef __NODE_H__
#define __NODE_H__

#include "nstring.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

static int temp_count;

// -- BASE CLASS --
class AST_node {
 public:
  AST_node* left;
  AST_node* right;
  virtual string generate_code(ofstream& f){
    return "";
  }
  AST_node() {
    left = nullptr;
    right = nullptr;
  }

  AST_node(AST_node* left, AST_node* right) {
    this->left = left;
    this->right = right;
  }

  virtual ~AST_node() {
    delete left;
    delete right;
  }
};
// -- END BASE --

// -- MODULE CLASS --
class module_node : public AST_node {
 public:
  AST_node* funcdecl_list;
  module_node(AST_node* vardecl_list, AST_node* funcdef_list,
              AST_node* funcdecl_list) : AST_node(vardecl_list, funcdef_list) {
    this->funcdecl_list = funcdecl_list;
  }
  virtual string generate_code(ofstream& f) {
    if(funcdecl_list != nullptr) {
      funcdecl_list->generate_code(f);
    }

    if(left != nullptr) {
      left->generate_code(f);
    }
    if(right != nullptr) {
      right->generate_code(f);
    }
    return "";
  }
  ~module_node() {
    delete funcdecl_list;
  }
};
// -- END MODULE --

// -- FUNCTION NODES --
// definitions
class funcdef_list_node : public AST_node {
 public:
 funcdef_list_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~funcdef_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }

  virtual string generate_code(ofstream& f) {
    for (uint32_t i = 0; i < list.size(); i ++) {
      list[i]->generate_code(f);
    }
    return "";
  }
};

class funcdef_node : public AST_node {
  public:
    funcdef_node(string id, AST_node* paramlist, AST_node* block) : AST_node(paramlist, block) {
      this->id=id;
    }   
    string id;
    virtual string generate_code(ofstream& f) {
      f <<"int " << id << "(";
      if (left != nullptr) {
        f << left->generate_code(f);
      }
      f << ") {" << endl;
      f << right->generate_code(f) << endl;
      f << "}" << endl;
      return "";
    }
};

class sfuncdef_node : public AST_node {
 public:
  string id;

 sfuncdef_node(string id, AST_node* paramlist, AST_node* block) : AST_node(paramlist, block) {
    this->id = id;
  }
};

class funcdecl_list_node : public AST_node {
  public:
 funcdecl_list_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~funcdecl_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }
};

// declarations
class funcdecl_node : public AST_node {
  public:
    funcdecl_node(string id, AST_node* paramlist) : AST_node(paramlist, nullptr) {
      this->id=id;
    }
    string id;
};

class sfuncdecl_node : public AST_node {
 public:
  string id;

 sfuncdecl_node(string id, AST_node* paramlist) : AST_node(paramlist, nullptr) {
    this->id = id;
  }
};

// parameters
class paramlist_node : public AST_node {
 public:
 paramlist_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~paramlist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }
};

class param_node : public AST_node {
 public:
  string id;
  string type;

 param_node(string type, string id) : AST_node() {
    this->type = type;
    this->id = id;
  }
};


// function calls
class function_node : public AST_node {
 public:
  // initializes left to point to the expression to return                 
  string id;
  AST_node* argument_list; // may need to change this type

 function_node(string id, AST_node* arg_list) : AST_node() {
    this->id = id;
    argument_list = arg_list;
  }
};

class arglist_node : public AST_node {
 public:
 arglist_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~arglist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }
};
// -- END FUNCTIONS --


// -- CODE BODY CLASSES --
class block_node : public AST_node {
  public:
    block_node(AST_node* vdecl_l, AST_node* stmt_l) : AST_node(vdecl_l, stmt_l) {}

  virtual string generate_code(ofstream& f) {
    if (left != nullptr) {
      left->generate_code(f);
    }
    
    if (right != nullptr) {
      right->generate_code(f);
    }
    return "";
  }
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
  // initializes left to point to the expression to return
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
