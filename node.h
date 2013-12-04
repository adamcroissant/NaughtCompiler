#ifndef __NODE_H__
#define __NODE_H__

#include "nstring.h"
#include <string>
#include <vector>
using namespace std;
class AST_node {
 public:
  AST_node* left;
  AST_node* right;

  AST_node() {
    left = nullptr;
    right = nullptr;
  }

  AST_node(AST_node* left, AST_node* right) {
    this->left = left;
    this->right = right;
  }

  ~AST_node() {
    delete left;
    delete right;
  }
};

class variable_node : public AST_node {
  public:
    variable_node(string s) : AST_node() { 
      var_name=s;
    }
    //~variable_node();
    string var_name;
};

class add_node : public AST_node {

};

class mult_node : public AST_node {

};

class sub_node : public AST_node {

};

class div_node : public AST_node {

};

class stmtlist_node : public AST_node {
  public:
 stmtlist_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~stmtlist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class vardecl_list_node : public AST_node {
 public:
 vardecl_list_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~vardecl_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class funcdef_list_node : public AST_node {
 public:
 funcdef_list_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);;
  }
  vector<AST_node*> list;
  ~funcdef_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class funcdecl_list_node : public AST_node {
  public:
 funcdecl_list_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);;
  }
  vector<AST_node*> list;
  ~funcdecl_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class arglist_node : public AST_node {
 public:
 arglist_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~arglist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class paramlist_node : public AST_node {
 public:
 paramlist_node(AST_node* node) : AST_node() {
    list = new vector<AST_node*>();
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~paramlist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
    delete list;
  }
};

class funcdef_node : public AST_node {
  public:
    funcdef_node(string id, AST_node* paramlist, AST_node* block) : AST_node(paramlist, block) {
      this->id=id;
    }   
    string id;
};

class sfuncdef_node : public AST_node {
 public:
  string id;

 sfuncdef_node(string id, AST_node* paramlist, AST_node* block) : AST_node(paramlist, block) {
    this->id = id;
  }
};

class funcdecl_node : public AST_node {
  public:
    funcdef_node(string id, AST_node* paramlist) : AST_node(paramlist, nullptr) {
      this->id=id;
    }
    string id;
};

class sfuncdecl_node : public AST_node {
 public:
  string id;

 sfuncdef_node(string id, AST_node* paramlist) : AST_node(paramlist, nullptr) {
    this->id = id;
  }
};

class block_node : public AST_node {
  public:
    block_node(AST_node* vdecl_l, AST_node* stmt_l) : AST_node(vdecl_l, stmt_l) {}
};

class assign_node : public AST_node {
 public:
 assign_node(AST_node* left, AST_node* right) : AST_node(left, right) {}
};

class IntLiteral_node : public AST_node {
 public:
  const int literal;
 IntLiteral_node(int i) : literal(i) , AST_node() {}
};

class stringliteral_node : public AST_node {
 public:
  const nstring_st literal;
 stringliteral_node(nstring_st str) : literal(str) , AST_node() {
  }
};

class module_node : public AST_node {
 public:
  AST_node* funcdecl_list;
  module_node(AST_node* vardecl_list, AST_node* funcdef_list,
              AST_node* funcdecl_list) : AST_node(vardecl_list, funcdef_list) {
    this->funcdecl_list = funcdecl_list;
  }

  ~module_node() {
    delete funcdecl_list;
  }
};

class return_node : AST_node {
 public:
  // initializes left to point to the expression to return
 return_node(AST_node *n1, AST_node *n2) : AST_node(n1, n2) {
  }
};

class ternary_node : AST_node {
 public:
  AST_node* question;
  
 ternary_node(AST_node* question, AST_node* left, AST_node* right) :
  AST_node(left, right) {
    this->question = question;
  }
  
  ~ternary_node() {
    delete question;
  }
};

// for tracking type of variable declaration
/*enum var_type {
  INT, STRING, POINTER
  };*/

class vardecl_node : public AST_node {
 public:
  string type;
  string id;
  bool isExtern = false;


 vardecl_node(string type, string id) : AST_node() {
    this->type = type;
    this->id = id;
  }

 vardecl_node(string type, string id, AST_node* assign) : AST_node(assign, nullptr) {
    this->type = type;
    this->id = id;
  }

 vardecl_node(bool e, string type, string id) : AST_node() {
    isExtern = e;
    this->type = type;
    this->id = id;
  }
};

// for a function call
class function_node : AST_node {
 public:
  // initializes left to point to the expression to return                 
  string id;
  AST_node* parameter_list; // may need to change this type

 function_node(string id, AST_node* param_list) : AST_node() {
    this->id = id;
    parameter_list = param_list;
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

#endif /* NODE_H */
