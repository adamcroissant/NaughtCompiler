%{
#define YY_NO_UNPUT

#include <iostream>
#include <string>
#include <memory>
#include <cstring>

#include "yy.h"
#include "StrUtil.h"
#include "node.h"

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
  string*                 string_val;
  int32_t*                intlit;
  IntLiteral_node*        int_val;
  AST_node*               node;
  variable_node*          var;
  add_node*               add;
  sub_node*               sub;
  div_node*               div;
  mult_node*              mult;
  stmtlist_node*          stmtlist;
  vardecl_list_node*      vardecl_list;
  funcdef_list_node*      funcdef_list;
  funcdecl_list_node*     funcdecl_list;
  arglist_node*           arglist;
  paramlist_node*         paramlist;
  funcdef_node*           funcdef;
  block_node*             block;
  assign_node*            assign;
  stringliteral_node*     strlit;
  module_node*            module;
  return_node*            return;
  ternary_node*           ternary;
  vardecl_node*           vardecl;
  function_node*          function; 
  param_node*             param;
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
%token <intlit> INT_LITERAL
%token <string_val> ID

/**********************************************************
 * Now we're defining the type associated with nodes
 * corresponding to non-terminals.
 **********************************************************/

%type <module> module
%type <funcdef> funcdef
%type <block> block
%type <vardecl> vardecl
%type <funcdecl> funcdecl
%type <node> expr
%type <node> term
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
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        |              vardecl_list funcdef_list
          { AST = new module_node($1, $2, nullptr);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list             funcdef_list
          { AST = new module_node(nullptr, $2, $1);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        |                            funcdef_list
          { AST = new module_node(nullptr, $1, nullptr);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list vardecl_list
          { AST = new module_node($2, nullptr, $1);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        |              vardecl_list
          { AST = new module_node($1, nullptr, nullptr);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        | funcdecl_list             
          { AST = new module_node(nullptr, nullptr, $1);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        |
          { AST = new module_node(nullptr, nullptr, nullptr);
            $$ = AST;
//            cout << *$$ << " -> module " << endl;
          }
        ;

funcdecl_list :
          funcdecl_list funcdecl SEMI
          { $1->list.push_back($2);
	    $$ = $1;
//          cout << *$$ << " -> funcdecl_list " << endl;
          }
        | funcdecl SEMI
          { $$ = new funcdecl_list_node($1);
//            cout << *$$ << " -> funcdecl_list " << endl;
          }
       ;
 
funcdecl :
          FUNCTION ID LPAREN param_list RPAREN
          { $$ = new funcdecl_node($2, $4);
          }
        | FUNCTION ID LPAREN  RPAREN
          { $$ = new funcdecl_node($2, nullptr);
          }
        | SFUNCTION ID LPAREN param_list RPAREN
          { $$ = new sfuncdecl_node($2, $4);  
            //cout << *$$ << " -> funcdecl " << endl;
          }
        | SFUNCTION ID LPAREN  RPAREN
          { $$ = new sfuncdecl_node($2, nullptr); 
            //cout << *$$ << " -> funcdecl " << endl;
          }
	;


vardecl_list : 
          vardecl_list vardecl SEMI
          { $1->list.push_back($2);
            $$ = $1;
            /*
            $$ = new StrUtil(*$1 + *$2 +*$3);
            cout << *$$ << " -> vardecl_list " << endl;
            */
          }
        | vardecl SEMI
          { $$ = new vardecl_list_node($1);
            /*
            $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> vardecl_list " << endl;
            */
          }
        ;

vardecl : 
         TYPE ID
          { $$ = new vardecl_node($1, *$2);
            /*
            $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> vardecl " << endl;
            */
          }
       | TYPE ID ASSIGN expr
          { $$ = new vardecl_node($1, *$2,
               new assign_node(new variable_node($2), $4));
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
            cout << *$$ << " -> vardecl " << endl;
            */
          }
       | EXTERN TYPE ID  /* extern variable */
          {
            $$ = new vardecl_node(true, $2, *$3);
            /*
            $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> vardecl " << endl;
            */
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
          { $$ = new funcdef_node(*$2, $4, $6);
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5 + *$6);
            cout << *$$ << " -> funcdef " << endl;
            */
          }
        | FUNCTION ID LPAREN RPAREN block
          { $$ = new funcdef_node(*$2, nullptr, $5);
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
            cout << *$$ << " -> funcdef " << endl;
            */
          }
	| SFUNCTION ID LPAREN param_list RPAREN block
          { $$ = new sfuncdef_node(*$2, $4, $6);
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5 + *$6);
            cout << *$$ << " -> funcdef " << endl;
            */
          }
        | SFUNCTION ID LPAREN RPAREN block
          { $$ = new sfuncdef_node(*$2, nullptr, $5);
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3 + *$4 + *$5);
            cout << *$$ << " -> funcdef " << endl;
            */
          }
        ;

param_list : 
          param_list COMMA param
          { $1->list.push_back($3);
            $$ = $1;
            /*
            $$ = new StrUtil(*$1 + *$2 + *$3);
            cout << *$$ << " -> param_list " << endl;
            */
          }
        | param
          { $$ = new paramlist_node($1);
            /*
            $$ = new StrUtil(*$1);
            cout << *$$ << " -> param_list " << endl;
            */
          }
        ;

param :
         TYPE ID
          { $$ = new param_node(*$1, *$2);
            /*
            $$ = new StrUtil(*$1 + *$2);
            cout << *$$ << " -> param " << endl;
            */
          }
        ;

block : 
	  LCBRACE vardecl_list stmt_list RCBRACE
          { $$ = new block_node($2, $3);
          }
	| LCBRACE              stmt_list RCBRACE
          { $$ = new block_node(nullptr, $3);
          }
	| LCBRACE vardecl_list           RCBRACE
          { $$ = new block_node($2, nullptr);
          }
        | LCBRACE RCBRACE
          { $$ = new block_node($2, $3);
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
          }
       | RETURN expr SEMI
          { $$ = new return_node($2, nullptr);
          }
     ;

expr : 
        expr ADD expr
        { $$ = new add_node($1, $3);
        }
      | expr SUB expr
        { $$ = new sud_node($1, $3);
        }
      | expr STAR expr
        { $$ = new mult_node($1, $3);
        }
      | expr DIV expr
        { $$ = new div_node($1, $3);
        }
      | term  ASSIGN expr
        { $$ = new assign_node($1, $3);
        }
      | expr QUESTION expr COLON expr
      // check this constructor's node order
        { $$ = new ternary_node($1, $3, $5);
        }
      | term
        { $$ = $1;
        }
      ;

term :
        STRING_LITERAL
        { $$ = new stringliteral_node(*$1);
        }
      | INT_LITERAL
        { $$ = new IntLiteral_node(*$1);
        }
      | ID
        { $$ = new variable_node(*$1);
          /*
          $$ = new StrUtil(*$1);
          cout << *$$ << " -> term" << endl;
          */
        }
      | LPAREN expr RPAREN
       { $$ = $2;
         /*
         $$ = new StrUtil( *$1 + *$2 + *$3 );
         cout << *$$ << " -> term" << endl;
         */
        }
      | UNARY_OP term
        { $$ = new StrUtil( *$1 + *$2);
          cout << *$$ << " -> term" << endl;
        }
      | ID LPAREN arglist RPAREN  /* function call */
       { $$ = new function_node(*$1, $2);
         /*
         $$ = new StrUtil(*$1 + *$2 + *$3 + *$4);
         cout << *$$ << " -> term" << endl;
         */
       }
      | ID LPAREN RPAREN  /* function call - no params */
       { $$ = new function_node(*$1, nullptr);
         /*
         $$ = new StrUtil(*$1 + *$2 + *$3);
         cout << *$$ << " -> term" << endl;
         */
       }
      ;

arglist :
        expr
        { $$ = new StrUtil(*$1);
          cout << *$$ << " -> arglist" << endl;
        }
      | arglist COMMA expr
        { $$ = new StrUtil( *$1 + *$2 + *$3 );
        cout << *$$ << " -> arglist" << endl;
        }
      ;

%%
