#ifndef __NODE_CC__
#define __NODE_CC__

#include "node.h"
#include <iostream>
using namespace std;

static int temp_count;
// -- BASE CLASS --
void AST_node::generate_code(ofstream& f) {}

AST_node::~AST_node(){}
// -- END BASE --

// -- MODULE CLASS --
module_node::module_node(vardecl_list_node* vardecl_list, funcdef_list_node* funcdef_list,
              funcdecl_list_node* funcdecl_list) {
    this->vardecl_list = vardecl_list;
    this->funcdef_list = funcdef_list;
    this->funcdecl_list = funcdecl_list;
}
void module_node::generate_code(ofstream& f) {
  if(funcdecl_list != nullptr) {
    funcdecl_list->generate_code(f);
  }
  
  if(vardecl_list != nullptr) {
    vardecl_list->generate_code(f);
  }
  if(funcdef_list != nullptr) {
    funcdef_list->generate_code(f);
  }
}
module_node::~module_node() {
    delete funcdecl_list;
    delete funcdef_list;
    delete vardecl_list;
}
// -- END MODULE --

// -- FUNCTION NODES --
// definitions

// funcdef_list_node class
funcdef_list_node::funcdef_list_node(AST_node* funcdef) {
  list.push_back(funcdef);
}

funcdef_list_node::~funcdef_list_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
}

void funcdef_list_node::generate_code(ofstream& f) {
  for (uint32_t i = 0; i < list.size(); i ++) {
    list[i]->generate_code(f);
  }
}

// funcdef_node class
funcdef_node::funcdef_node(string id, AST_node* paramlist, AST_node* block) {
  this->paramlist = paramlist;
  this->block = block;
  this->id=id;
}   

void funcdef_node::generate_code(ofstream& f) {
  f <<"int " << id << "(";
  if (paramlist != nullptr) {
    paramlist->generate_code(f);
  }
  f << ") {" << endl;
  block->generate_code(f);
  f << "}" << endl;
}

funcdef_node::~funcdef_node(){
  delete paramlist;
  delete block;
}

// sfuncdef_node class
sfuncdef_node::sfuncdef_node(string id, AST_node* paramlist, AST_node* block) {
   this->paramlist = paramlist;
   this->block = block;
   this->id = id;
}

sfuncdef_node::~sfuncdef_node(){
  delete paramlist;
  delete block;
}

// funcdecl_list_node class
funcdecl_list_node::funcdecl_list_node(AST_node* funcdecl) {
  list.push_back(funcdecl);
}

funcdecl_list_node::~funcdecl_list_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
}

// declarations

// funcdecl_node class
funcdecl_node::funcdecl_node(string id, AST_node* paramlist) {
  this->paramlist = paramlist;
  this->id=id;
}

funcdecl_node::~funcdecl_node(){
  delete paramlist;
}

// sfuncdecl_node class
sfuncdecl_node::sfuncdecl_node(string id, AST_node* paramlist) {
  this->paramlist = paramlist; 
  this->id = id;
}


sfuncdecl_node::~sfuncdecl_node(){
  delete paramlist;
}

// parameters

// paramlist_node class
paramlist_node::paramlist_node(AST_node* param) {
  list.push_back(param);
}

paramlist_node::~paramlist_node() {
  for(unsigned int i=0; i<list.size(); i++) {
    delete list[i];
  }
}

void paramlist_node::generate_code(ofstream& f) {
  list[0]->generate_code(f);
  for (unsigned int i = 1; i < list.size(); i ++) {
    f << ", ";
    list[i]->generate_code(f);
  }
}

// param_node class
param_node::param_node(string type, string id) {
    this->type = type;
    this->id = id;
}

void param_node::generate_code(ofstream& f) {
  f << type << " " << id;
}



// function calls

// function_node class
function_node::function_node(string id, arglist_node* arg_list) {
  this->id = id;
  argument_list = arg_list;
}


function_node::~function_node(){
  delete argument_list;
}

void function_node::generate_code(ofstream& f) {
  if(argument_list) {
    
    argument_list->generate_code(f);
    f<<id<<"(";
    f<<argument_list->list[0]->id;
    for(size_t i=1; i<argument_list->list.size(); i++) {  
      f<<", "<<argument_list->list[i]->id;
    }
  }else {
    f<<id<<"("; 
  }
  f<<")"<<endl;
}

// arglist_node class
arglist_node::arglist_node(expr_node* node) {
  list.push_back(node);
}
arglist_node::~arglist_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
}

void arglist_node::generate_code(ofstream& f) {
  for(size_t i=0; i<list.size(); i++) {
    list[i]->generate_code(f);
  }

}
// -- END FUNCTIONS --


// -- CODE BODY CLASSES --

// block_node class
block_node::block_node(AST_node* vdecl_l, AST_node* stmt_l) {
  this->vardecl_list = vdecl_l;
  this->stmt_list = stmt_l;
}

void block_node::generate_code(ofstream& f) {
  if (vardecl_list != nullptr) {
    vardecl_list->generate_code(f);
  }
  
  if (stmt_list != nullptr) {
    stmt_list->generate_code(f);
  }
}

block_node::~block_node(){
  delete vardecl_list;
  delete stmt_list;
}

// statements

// stmtlist_node class
stmtlist_node::stmtlist_node(AST_node* node) {
  list.push_back(node);
}

void stmtlist_node::generate_code(ofstream& f) {
  for(size_t i=0; i<list.size(); i++) {
    list[i]->generate_code(f);
  }
}
  
stmtlist_node::~stmtlist_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
}

// variable declarations

// vardecl_list_node class
vardecl_list_node::vardecl_list_node(AST_node* node) {
  list.push_back(node);
}
vardecl_list_node::~vardecl_list_node() {
  for(size_t i=0; i<list.size(); i++) {
    delete list[i];
  }
}

void vardecl_list_node::generate_code(ofstream& f) {
  for (size_t i = 0; i < list.size(); i ++) {
    list[i]->generate_code(f);
  }
}

// vardecl_node class
vardecl_node::vardecl_node(string type, string id, expr_node* assign) {
  this->assign = assign;
  this->type = type;
  this->id = id;
}

vardecl_node::vardecl_node(string type, string id, bool e) {
    isExtern = e;
    this->type = type;
    this->id = id;
}

void vardecl_node::generate_code(ofstream& f) {
  if (assign == nullptr) {
    f << type << " " << id << ";" << endl;
  } else {
    f << type << " " << id << " = "; 
    assign->generate_code(f); 
    f << ";" << endl;
  }
}

vardecl_node::~vardecl_node() {
  delete assign;
}

// return_node class
return_node::return_node(expr_node* ret) {
  this->ret = ret;
}

void return_node::generate_code(ofstream& f) {
  ret->generate_code(f);
  f << "return " << ret->id << ";"<<endl;
}

return_node::~return_node() {
  delete ret;
}

// -- END CODE BODY --

// -- OPERATORS --
// ternary
ternary_node::ternary_node(expr_node* question, expr_node* left, expr_node* right) {
  this->question = question;
  this->left = left;
  this->right = right;
}
  
ternary_node::~ternary_node() {
  delete question;
  delete left;
  delete right;
}

// binary
add_node::add_node(expr_node* left, expr_node* right) {
  this->left = left;
  this->right = right;
}

void add_node::generate_code(ofstream& f) {
  left->generate_code(f);
  right->generate_code(f);
  if (left->type.compare(right->type) != 0){
    cerr << "Improper addition: Adding two expressions of different types" << endl;
    exit(1);
  }

  if (left->type.compare("pointer") == 0 || right->type.compare("pointer") == 0){
    cerr << "Improper expressions: trying to add to a pointer" << endl;
    exit(1);
  }

  string temp = "temp_" + to_string(temp_count);
  temp_count ++;

  type = left->type;
  id = temp;

  f << left->type << " " << temp << " = " << left->id << " + " << right->id << ";" << endl;
}

add_node::~add_node() {
  delete left;
  delete right;
}


// mult_node class
mult_node::mult_node(expr_node* left, expr_node* right) {
  this->left = left;
  this->right = right;
  type = "int";
}

void mult_node::generate_code(ofstream& f) {
  left->generate_code(f); 
  right->generate_code(f); 

  if (left->type.compare(right->type) != 0){
    cerr << "Improper multiplications: multiplying two expressions of different types" << endl;
    exit(1);
  }

  if (left->type.compare("int") != 0 || right->type.compare("int") != 0){
    cerr << "Improper expressions: trying to multiply to a non-integer" << endl;
    exit(1);
  }


  string temp = "temp_" + to_string(temp_count);
  temp_count ++;
  id = temp;
  f << type << " " << temp << " = " << left->id << " * " << right->id << ";" << endl;
  //return temp;
}

mult_node::~mult_node() {
  delete left;
  delete right;
}

// sub_node class
sub_node::sub_node(expr_node* left, expr_node* right) {
  this->left = left;
  this->right = right;
  type = "int";
}

void sub_node::generate_code(ofstream& f) {
  left->generate_code(f);
  right->generate_code(f);

  if (left->type.compare(right->type) != 0){
    cerr << "Improper subtraction: subtracting two expressions of different types" << endl;
    exit(1);
  }

  if (left->type.compare("int") != 0 || right->type.compare("int") != 0){
    cerr << "Improper expressions: trying to subtract with a non-integer" << endl;
    exit(1);
  }

  string temp = "temp_" + to_string(temp_count);
  temp_count ++;
  id = temp;
  f << type << " " << temp << " = " << left->id << " - " << right->id << ";" << endl;
}

sub_node::~sub_node() {
  delete left;
  delete right;
}

// div_node class
div_node::div_node(expr_node* left, expr_node* right) {
  this->left = left;
  this->right = right;
  type = "int";
}

void div_node::generate_code(ofstream& f) {
  left->generate_code(f);
  right->generate_code(f);

  if (left->type.compare(right->type) != 0){
    cerr << "Improper division: dividing two expressions of different types" << endl;
    exit(1);
  }

  if (left->type.compare("int") != 0 || right->type.compare("int") != 0){
    cerr << "Improper expressions: trying to divide with a non-integer" << endl;
    exit(1);
  }

  string temp = "temp_" + to_string(temp_count);
  temp_count ++;
  id = temp;
  f << type << " " << temp << " = " << left->id << " / " << right->id << ";" << endl;
  //return temp;
}

div_node::~div_node() {
  delete left;
  delete right;
}

// assign_node class
assign_node::assign_node(expr_node* left, expr_node* right) {
  this->left = left;
  this->right = right;
}

assign_node::~assign_node() {
  delete left;
  delete right;
}

assign_node::generate_code(ofstream &f){
  left->generate_code(f);
  right->generate_code(f);

  if (left.type.compare(right.compare) != 0){
    cerr << "Improper Assign: assigning a " << right.type 
	 << " to a " << left.type << endl;
    exit(1);
  }
  
  type = left->type;
  id = left->id;

  f << left.id << " = " << right.id << endl;
    
}
// unary ops
// print_node class
print_node::print_node(expr_node* term) {
  this->term = term;
}

print_node::~print_node() {
  delete term;
}
// -- END OPERATORS --


// -- TERMS (VARS/LITS) --

// variable node class
variable_node::variable_node(string s) { 
  id = s;
}

void variable_node::generate_code(ofstream& f) {
  type = "int";
}

// intliteral_node class
IntLiteral_node::IntLiteral_node(int i) {
  type = "int";
  literal = i;
}
void IntLiteral_node::generate_code(ofstream& f) {
  id = to_string(literal);
}

// stringliteral_node class
stringliteral_node::stringliteral_node(string str) {
  type = "string";
  literal.len = str.length();
  for (size_t i = 0; i < str.length(); i ++) {
    literal.str[i] = str[i];
  }
}
// -- END TERMS --

#endif /* NODE_H */
