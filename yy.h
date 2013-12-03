#ifndef _YY_H
#define _YY_H

extern int yylineno;	// defined and maintained in lex.c
extern char *yytext;	// defined and maintained in lex.c
  
int yyerror(std::string s, int lineno);
int yyerror(std::string s);
int yyerror(char *s);
int yylex(void);

// prototype of bison-generated parser function
int yyparse();

#endif // _YY_H
