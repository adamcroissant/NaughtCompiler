#ifndef __MODULE_NODE_H
#define __MODULE_NODE_H

class module_node : public AST_node {
 public:
  AST_node* funcdecl_list;
  module_node(AST_node* vardecl_list, AST_node* funcdef_list,
              AST_node* funcdecl_list) : AST_node(vardecl_list, funcdef_list) {
    this->funcdecl_list = funcdecl_list;
  }

  ~() {
    delete funcdecl_list;
  }
};

#endif /* __AST_NODE_H */
