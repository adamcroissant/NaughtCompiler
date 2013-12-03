#ifndef __ASSIGN_NODE__
#define __ASSIGN_NODE__

class assign_node : public AST_node {

 public:
 assign_node(AST_node* left, AST_node* right) : AST_node(left, right) {}
};

#endif /*__ASSIGN_NODE__*/
