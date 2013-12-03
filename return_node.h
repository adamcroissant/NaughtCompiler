#ifndef __RETURN_NODE__
#define __RETURN_NODE__

class return_node : AST_node {
 public:
  // initializes left to point to the expression to return
 return_node(AST_node *n1, AST_node *n2) : AST_node(n1, n2) {
  }
}

#endif
