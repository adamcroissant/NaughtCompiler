#ifndef __NODE_H__
#define __NODE_H__

#include "nstring.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

static int temp_count;

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

class variable_node : public AST_node {
  public:
    variable_node(string s) : AST_node() { 
      var_name=s;
    }

    string var_name;

    virtual string generate_code(ofstream& f) {
      return var_name;
    }
};

class add_node : public AST_node {
  public:
    add_node(AST_node* left, AST_node* right) : AST_node(left, right) {}

  virtual string generate_code(ofstream& f) {
    string temp = "temp_" + to_string(temp_count);
    temp_count ++;
    f << temp << " = " << left->generate_code(f) << " + "
      << right->generate_code(f) << ";" << endl;
    return temp;
  }

};

class mult_node : public AST_node {
  public:
    mult_node(AST_node* left, AST_node* right) : AST_node(left, right) {}

  virtual string generate_code(ofstream& f) {
    string temp = "temp_" + to_string(temp_count);
    temp_count ++;
    f << temp << " = " << left->generate_code(f) << " * "
      << right->generate_code(f) << ";" << endl;
    return temp;
  }
};

class sub_node : public AST_node {
  public:
    sub_node(AST_node* left, AST_node* right) : AST_node(left, right) {}

  virtual string generate_code(ofstream& f) {
    string temp = "temp_" + to_string(temp_count);
    temp_count ++;
    f << temp << " = " << left->generate_code(f) << " - "
      << right->generate_code(f) << ";" << endl;
    return temp;
  }
};

class div_node : public AST_node {
  public:
    div_node(AST_node* left, AST_node* right) : AST_node(left, right) {}

  virtual string generate_code(ofstream& f) {
    string temp = "temp_" + to_string(temp_count);
    temp_count ++;
    f << temp << " = " << left->generate_code(f) << " / "
      << right->generate_code(f) << ";" << endl;
    return temp;
  }
};

class stmtlist_node : public AST_node {
  public:
  vector<AST_node*> list;

 stmtlist_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  virtual string generate_code(ofstream& f) {
    for(size_t i=0; i<list.size(); i++) {
      list[i]->generate_code(f);
    }
    return "";
  }

  
  ~stmtlist_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }

};

class vardecl_list_node : public AST_node {
 public:
 vardecl_list_node(AST_node* node) : AST_node() {
    list.push_back(node);
  }
  vector<AST_node*> list;
  ~vardecl_list_node() {
    for(size_t i=0; i<list.size(); i++) {
      delete list[i];
    }
  }

  virtual string generate_code(ofstream& f) {
    for (size_t i = 0; i < list.size(); i ++) {
      list[i]->generate_code(f);
    }
    return "";
  }
};

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

class assign_node : public AST_node {
 public:
 assign_node(AST_node* left, AST_node* right) : AST_node(left, right) {}
};

class IntLiteral_node : public AST_node {
 public:
  int literal;
 IntLiteral_node(int i) : AST_node() {
    literal = i;
  }
  virtual string generate_code(ofstream& f) {
    return to_string(literal);
  }
};

class stringliteral_node : public AST_node {
 public:
  nstring_st literal;
 stringliteral_node(string str) : AST_node() {
    literal.len = str.length();
    for (size_t i = 0; i < str.length(); i ++) {
      literal.str[i] = str[i];
    }
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

class return_node : public AST_node {
 public:
  // initializes left to point to the expression to return
 return_node(AST_node *n1, AST_node *n2) : AST_node(n1, n2) {
  }

  virtual string generate_code(ofstream& f) {
    f << "return " << left->generate_code(f) << ";";
    return "";
  }

};

class ternary_node : public AST_node {
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
  bool isExtern;


  /*vardecl_node(string type, string id) : AST_node() {
    this->type = type;
    this->id = id;
  }*/

 vardecl_node(string type, string id, AST_node* assign) : AST_node(assign, nullptr) {
    this->type = type;
    this->id = id;
  }

 vardecl_node(string type, string id, bool e = false) : AST_node() {
    isExtern = e;
    this->type = type;
    this->id = id;
  }

  virtual string generate_code(ofstream& f) {
    if (left == nullptr) {
      f << type << " " << id << ";" << endl;
    } else {
      f << type << " " << id << " = " << left->generate_code(f) << ";" << endl;
    }
    return "";
  }
};

// for a function call
class function_node : public AST_node {
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

class print_node : public AST_node {
  public:
    print_node(AST_node* term) : AST_node(term, nullptr) {}
};
#endif /* NODE_H */
