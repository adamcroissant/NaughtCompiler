#ifndef __TERNARY_NODE_H
#define __TERNARY_NODE_H

class ternary_node : AST_node {
  AST_node* question;
  
 ternary_node(AST_node* question, AST_node* left, AST_node* right) :
  AST_node(left, right) {
    this->question = question;
  }

  ~() {
    delete question;
  }
}

#endif /* TERNARY_NODE_H */
