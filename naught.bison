%{
#define YY_NO_UNPUT

#include "node.h"
#include <iostream>
#include <string>
#include <memory>
#include <cstring>

#include "yy.h"
#include "StrUtil.h"

using namespace std;

extern int _WANT_DEBUG;

extern AST_node *AST;

%}

/***************************************
 * These are the union of the data types
 * that are associated with AST nodes.
 * They should all be pointers.
 * The C++ type is the first entry.
 * The second entry is a symbolic
 * name used later in this file.
 ***************************************/
%union {
  StrUtil*                string_val;
  //int32_t*                intlit;
  IntLiteral_node*        int_val;
  AST_node*               node;
  expr_node*              enode;
  variable_node*          var;
  add_node*               add;
  sub_node*               sub;
  div_node*               div;
  mult_node*              mult;
  stmtlist_node*          stmt_list;
  vardecl_list_node*      vardecl_list;
  funcdef_list_node*      funcdef_list;
  funcdecl_list_node*     funcdecl_list;
  arglist_node*           arglist;
  paramlist_node*         param_list;
  funcdef_node*           funcdef;
  sfuncdef_node*	  sfuncdef;
  funcdecl_node*	  funcdecl;
  sfuncdecl_node*	  sfuncdecl;
  block_node*             block;
  assign_node*            assign;
  stringliteral_node*     strlit;
  module_node*            module;
  return_node*            ret;
  ternary_node*           ternary;
  vardecl_node*           vardecl;
  function_node*          function; 
  param_node*             param;
  print_node*             print;
}

/***********************************************************************
 * The order of these next few lines sets operator precedence, which is
 * important to correct operation of the parser.  Don't change them.
 ***********************************************************************/
%right <string_val> ASSIGN
%right <string_val> COLON QUESTION
%left <string_val> ADD SUB
%left <string_val> STAR DIV
%right <string_val> UNARY_OP
/*********************************************************
 * Okay, that's it -- after this order doesn't matter
 *********************************************************/

/**********************************************************
 * Here (and in the precedence/associativity declarations 
 * above, we're defining symbols that can be returned by
 * the lexer. 
 **********************************************************/

%token <string_val> LCBRACE RCBRACE RPAREN LPAREN SEMI COMMA EXTERN FUNCTION SFUNCTION RETURN

%token <string_val> TYPE
%token <string_val> STRING_LITERAL
%token <string_val> INT_LITERAL
%token <string_val> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <node> funcdef
%type <block> block
%type <vardecl> vardecl
%type <node> funcdecl
%type <enode> expr
%type <enode> term
%type <node> stmt

%type <stmt_list> stmt_list
%type <vardecl_list> vardecl_list
%type <funcdecl_list> funcdecl_list
%type <param> param;
%type <param_list> param_list;
%type <funcdef_list> funcdef_list
%type <arglist> arglist;

/*********************************************
 * This is the terminal symbol.  The entire
 * naught program should be reducable to this
 * symbol.
 *********************************************/
%start module

%%

/********************************************************
 * It will take a bit of study, but these rules are
 * the easiest to understand explanation of the grammar.
 ********************************************************/

module :
         funcdecl_list vardecl_list funcdef_list
          { AST = new module_node($2, $3, $1);
          }
        |              vardecl_list funcdef_list
          { AST = new module_node($1, $2, nullptr);
          }
        | funcdecl_list             funcdef_list
          { AST = new module_node(nullptr, $2, $1);
          }
        |                            funcdef_list
          { AST = new module_node(nullptr, $1, nullptr);
          }
        | funcdecl_list vardecl_list
          { AST = new module_node($2, nullptr, $1);
          }
        |              vardecl_list
          { AST = new module_node($1, nullptr, nullptr);
          }
        | funcdecl_list             
          { AST = new module_node(nullptr, nullptr, $1);
          }
        |
          { AST = new module_node(nullptr, nullptr, nullptr);
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $1->list.push_back($2);
	    $$ = $1;

            delete $3;
          }
        | funcdecl SEMI
          { $$ = new funcdecl_list_node($1);

            delete $2;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node($2->getString(), $4);

            delete $1;
            delete $2;
            delete $3;
            delete $5;
          }
        | FUNCTION ID LPAREN  RPAREN
          { $$ = new funcdecl_node($2->getString(), nullptr);

            delete $1;
            delete $2;
            delete $3;
            delete $4;
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new sfuncdecl_node($2->getString(), $4);  

            delete $1;
            delete $2;
            delete $3;
            delete $5;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { $$ = new sfuncdecl_node($2->getString(), nullptr); 

            delete $1;
            delete $2;
            delete $3;
            delete $4;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $1->list.push_back($2);
            $$ = $1;
            
            delete $3;
          }
        | vardecl SEMI
          { $$ = new vardecl_list_node($1);
            
            delete $2;
          }
        ;

vardecl : 
         TYPE ID
          { $$ = new vardecl_node($1->getString(), $2->getString());
            
            delete $1;
            delete $2;
          }
       | TYPE ID ASSIGN expr
          { $$ = new vardecl_node($1->getString(), $2->getString(),
               new assign_node(new variable_node($2->getString()), $4));
            
            delete $1;  
            delete $2;  
            delete $3;
          }
       | EXTERN TYPE ID  /* extern variable */
          {
            $$ = new vardecl_node($2->getString(), $3->getString(), true);
            
            delete $1;  
            delete $2;
            delete $3;
          }
       ;


funcdef_list :
         funcdef
         { $$ = new funcdef_list_node($1);
         }
       | funcdef_list funcdef
         { $1->list.push_back($2);
           $$ = $1;
         }
        ;

funcdef :
	  FUNCTION ID LPAREN param_list RPAREN block
          { $$ = new funcdef_node($2->getString(), $4, $6);
            
            delete $1;
            delete $2;
            delete $3;
            delete $5;
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new funcdef_node($2->getString(), nullptr, $5);
            
            delete $1;
            delete $2;
            delete $3;
            delete $4;
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new sfuncdef_node($2->getString(), $4, $6);
            
            delete $1;
            delete $2;
            delete $3;
            delete $5;
          }
        | SFUNCTION ID LPAREN RPAREN block
          { $$ = new sfuncdef_node($2->getString(), nullptr, $5);
            
            delete $1;
            delete $2;
            delete $3;
            delete $4;
          }
        ;

param_list : 
          param_list COMMA param
          { $1->list.push_back($3);
            $$ = $1;
            
            delete $2;
          }
        | param
          { $$ = new paramlist_node($1);
          }
        ;

param :
         TYPE ID
          { $$ = new param_node($1->getString(), $2->getString());
            
            delete $1;
            delete $2;
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new block_node($2, $3);
            
            delete $1;
            delete $4;
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new block_node(nullptr, $2);
            
            delete $1;
            delete $3;
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new block_node($2, nullptr);

            delete $1;
            delete $3;
          }
        | LCBRACE RCBRACE
          { $$ = new block_node(nullptr, nullptr);

            delete $1;
            delete $2;
          }
        ;

stmt_list :
          stmt_list stmt
          { $1->list.push_back($2);
	    $$ = $1;
          }
        | stmt
          { $$ = new stmtlist_node($1);
          }
       ;

stmt : 
         expr SEMI
          { $$ = $1;

            delete $2;
          }
       | RETURN expr SEMI
          { $$ = new return_node($2);
          
            delete $1;
            delete $3;
          }
     ;

expr : 
        expr ADD expr
        { $$ = new add_node($1, $3);
        
          delete $2;
        }
      | expr SUB expr
        { $$ = new sub_node($1, $3);
        
          delete $2;
        }
      | expr STAR expr
        { $$ = new mult_node($1, $3);
        
          delete $2;
        }
      | expr DIV expr
        { $$ = new div_node($1, $3);
        
          delete $2;
        }
      | term  ASSIGN expr
        { $$ = new assign_node($1, $3);

          delete $2;
        }
      | expr QUESTION expr COLON expr
        { $$ = new ternary_node($1, $3, $5);
        
          delete $2;
          delete $4;
        }
      | term
        { $$ = $1;
        }
      ;

term :
        STRING_LITERAL
        { $$ = new stringliteral_node($1->getString());
        
          delete $1; 
        }
      | INT_LITERAL
        { $$ = new IntLiteral_node(atoi(($1->getString()).c_str()));
          
          delete $1;
        }
      | ID
        { $$ = new variable_node($1->getString());
          
          delete $1;
        }
      | LPAREN expr RPAREN
       { $$ = $2;

         delete $1;
         delete $3;
        }
      | UNARY_OP term
        { if($1->getString().compare("print")==0) {
          $$ = new print_node($2);
          }else if($1->getString().compare("@")==0) {
            $$= new dereference_node($2);
          }else {
            $$= new address_node($2);
          }

          delete $1;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       { $$ = new function_node($1->getString(), $3);
         
         delete $1;
         delete $2;
         delete $4;
       }
      | ID LPAREN RPAREN  /* function call - no params */
       { $$ = new function_node($1->getString(), nullptr);
         
         delete $1;
         delete $2;
         delete $3;         
       }
      ;

arglist :
        expr
        { $$ = new arglist_node($1);
        }
      | arglist COMMA expr
        { $1->list.push_back($3);
          $$ = $1;

          delete $2;
        }
      ;

%%
