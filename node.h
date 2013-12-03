#ifndef __NODE_H__
#define __NODE_H__

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

class stmtlist_node : public AST_node {
  public:
    stmtlist_node(AST_node* node) : AST_node() {
      list.push_back(node);;
    }
    vector<AST_node*> list;
    ~stmtlist_node() {
      for(size_t i=0; i<list.size(); i++) {
        delete list[i];
      }
    }
};

class vardecl_list_node : public AST_node {
  public:
    vardecl_list_node(AST_node* node) : AST_node() {
      list.push_back(node);;
    }
    vector<AST_node*> list;
    ~vardecl_list_node() {
      for(size_t i=0; i<list.size(); i++) {
        delete list[i];
      }
    }
};

class funcdef_list_node : public AST_node {
  public:
    funcdef_list_node(AST_node* node) : AST_node() {
      list.push_back(node);;
    }
    vector<AST_node*> list;
    ~funcdef_list_node() {
      for(size_t i=0; i<list.size(); i++) {
        delete list[i];
      }
    }
};

class funcdecl_list_node : public AST_node {
  public:
    funcdecl_list_node(AST_node* node) : AST_node() {
      list.push_back(node);;
    }
    vector<AST_node*> list;
    ~funcdecl_list_node() {
      for(size_t i=0; i<list.size(); i++) {
        delete list[i];
      }
    }
};

class arglist_node : public AST_node {
  public:
    arglist_node(AST_node* node) : AST_node() {
      list.push_back(node);;
    }
    vector<AST_node*> list;
    ~arglist_node() {
      for(size_t i=0; i<list.size(); i++) {
        delete list[i];
      }
    }
};

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

class funcdef_node : public AST_node {
  public:
    funcdef_node(string id, AST_node* param, AST_node* block) : AST_node(param, block) {
      this->id=id;
    }   
    string id;
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
enum var_type {
  INT, STRING, POINTER
};

class vardecl_node : public AST_node {
 public:
  enum var_type t;
  bool isExtern = false;


 vardecl_node(var_type t, AST_node* id) : AST_node(id, nullptr) {
    this->t = t;
  }

 vardecl_node(var_type t, AST_node* id, AST_node* assign) : AST_node(id, assign) {
    this->t = t;
  }

 vardecl_node(bool e, var_type t, AST_node* id) : AST_node(id, nullptr) {
    isExtern = e;
    this->t = t;
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

#endif /* NODE_H */
