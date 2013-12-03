#ifndef __VARDECL_NODE__
#define __VARDECL_NODE__

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
}
