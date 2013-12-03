#ifndef __STRING_LITERALS__

#define __STRING_LITERALS__

class stringliteral_node : public AST_node {

 public:

  const nstring_st literal;
 stringliteral_node(nstring_st str) : literal(str) , AST_node() {
  }
};

#endif
