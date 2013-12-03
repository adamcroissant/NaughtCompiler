#ifndef __INT_LITERALS__                                                               
#define __INT_LITERALS__                                                                  
                                                                                       
class IntLiteral_node : public AST_node {                                                      
 public:                                                                               
  const int literal;
 IntLiteral_node(int i) : literal(i) , AST_node() {
  }
};
#endif
