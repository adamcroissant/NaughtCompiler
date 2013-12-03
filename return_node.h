#ifndef __RETURN_NODE__
#define __RETURN_NODE__

class return_node : AST_node {
 public:
  // initializes left to point to the expression to return
 return_node(AST_node n) : AST_node(n) {
  }
}

#endif
