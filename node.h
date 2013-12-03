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
}

#endif /* NODE_H */
