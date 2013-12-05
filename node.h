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

  module_node(AST_node* vardecl_list, AST_node* funcdef_list,
              AST_node* funcdecl_list);

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
    
  funcdecl_list_node(AST_node* node);

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

  paramlist_node(AST_node* node);

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
