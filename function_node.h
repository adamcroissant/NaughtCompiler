#ifndef __FUNCTION_NODE__
#define __FUNCTION_NODE__

class function_node : AST_node {
 public:
  // initializes left to point to the expression to return                 
  std::string id;
  AST_node parameter_list; // may need to change this type

 function_node(std::string id, AST_node param_list) : AST_node() {
    this->id = id;
    parameter_list = param_list;
  }
}

#endif



