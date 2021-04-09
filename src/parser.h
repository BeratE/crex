#ifndef _PARSER_H
#define _PARSER_H

/*******************************************************************************/
/* LL(1) Grammar for RegEx                                                     */
/* Rule        : Production                          : Lookahead               */
/* 1           : Expr  ->   Term Expr'               : {(,c,[,\}               */
/* 2,3         : Expr' -> + Term Expr' | e           : {+},{e,)}               */
/* 4           : Term  ->   Form Term'               : {(,c, [,\}              */
/* 5,6         : Term' ->   Form Term' | e           : {(,c, [,\},{+,e,)}      */
/* 7           : Form  ->   Base Form'               : {(,c, [,\}              */
/* 8,9,10      : Form' -> * | ? | e                  : {*},{?},{(,c,[,+,e,),\} */
/* 11,12,13,14 : Base  -> ( Expr ) | [c-c] | c | \.  : {(},{[},{c},{\}         */
/*******************************************************************************/

// Terminal symbols
typedef enum Terminal {
    EPSLN,
    GRPOP,
    GRPCL,
    KSTAR,
    DISJN,
    CHARA,
    EXIST,
    RNGOP,
    RNGCL,
    RNGLN,
    ESCHR,
} SymbolClass; // Each terminal describes a symbol class

typedef struct {
  SymbolClass name;
  char value;
} Symbol;

typedef struct {
    
} Node;

// Recursive descent parser
void parse(char* string);
int rExpr ();
int rExprP();
int rTerm ();
int rTermP();
int rForm ();
int rFormP();
int rBase ();

#endif // _PARSER_H
