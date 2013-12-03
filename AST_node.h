#ifndef __AST_NODE_H
#define __AST_NODE_H

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

  ~() {
    delete left;
    delete right;
  }
};

#endif /* __AST_NODE_H */
