#ifndef __NODE_CC__
#define __NODE_CC__

#include "node.h"
using namespace std;


// -- BASE CLASS --
virtual string AST_node::generate_code(ofstream& f){
  return "";
};

virtual AST_node::~AST_node() { };
// -- END BASE --

// -- MODULE CLASS --
module_node::module_node(AST_node* vardecl_list, AST_node* funcdef_list,
              AST_node* funcdecl_list) {
    this->vardecl_list = vardecl_list;
    this->funcdef_list = funcdef_list;
    this->funcdecl_list = funcdecl_list;
};
virtual string module_node::generate_code(ofstream& f) {
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
};
module_node::~module_node() {
    delete funcdecl_list;
};
// -- END MODULE --

// -- FUNCTION NODES --
// definitions

// funcdef_list_node class
funcdef_list_node::funcdef_list_node(AST_node* funcdef) {
  list.push_back(node);
};

funcdef_list_node::~funcdef_list_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
};

virtual string funcdef_list_node::generate_code(ofstream& f) {
  for (uint32_t i = 0; i < list.size(); i ++) {
    list[i]->generate_code(f);
  }
  return "";
};

// funcdef_node class
funcdef_node::funcdef_node(string id, AST_node* paramlist, AST_node* block) {
  this->paramlist = paramlist;
  this->block = block;
  this->id=id;
}   

virtual string funcdef_node::generate_code(ofstream& f) {
  f <<"int " << id << "(";
  if (left != nullptr) {
    f << left->generate_code(f);
  }
  f << ") {" << endl;
  f << right->generate_code(f) << endl;
  f << "}" << endl;
  return "";
};

// sfuncdef_node class
sfuncdef_node::sfuncdef_node(string id, AST_node* paramlist, AST_node* block) {
   this->paramlist = paramlist;
   this->block = block;
   this->id = id;
};

// funcdecl_list_node class
funcdecl_list_node::funcdecl_list_node(AST_node* funcdecl) {
  list.push_back(node);
};

funcdecl_list_node::~funcdecl_list_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
};

// declarations

// funcdecl_node class
funcdecl_node::funcdecl_node(string id, AST_node* paramlist) {
  this->paramlist = paramlist;
  this->id=id;
};

// sfuncdecl_node class
sfuncdecl_node::sfuncdecl_node(string id, AST_node* paramlist) {
  this->paramlist = paramlist; 
  this->id = id;
};

// parameters

// paramlist_node class
paramlist_node::paramlist_node(AST_node* param) {
  list.push_back(node);
};

paramlist_node::~paramlist_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
};

// param_node class
param_node::param_node(string type, string id) {
    this->type = type;
    this->id = id;
};


// function calls

// function_node class
function_node::function_node(string id, AST_node* arg_list) {
  this->id = id;
  argument_list = arg_list;
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

// variable declarations
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

// return
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
// -- END CODE BODY --

// -- OPERATORS --
// ternary
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

// binary
class add_node : public AST_node {
  public:
    add_node(AST_node* left, AST_node* right) : AST_node(left, right) {}

  virtual string generate_code(ofstream& f) {
    string temp = "temp_" + to_string(temp_count);

    temp_count ++;
    f << "int " << temp << " = " << left->generate_code(f) << " + "
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
    f << "int " << temp << " = " << left->generate_code(f) << " * "
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
    f << "int " << temp << " = " << left->generate_code(f) << " - "
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
    f << "int " << temp << " = " << left->generate_code(f) << " / "
      << right->generate_code(f) << ";" << endl;
    return temp;
  }
};

class assign_node : public AST_node {
 public:
 assign_node(AST_node* left, AST_node* right) : AST_node(left, right) {}
};

// unary
class print_node : public AST_node {
  public:
    print_node(AST_node* term) : AST_node(term, nullptr) {}
};
// -- END OPERATORS --


// -- TERMS (VARS/LITS) --
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
// -- END TERMS --

#endif /* NODE_H */
