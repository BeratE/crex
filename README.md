# crex
## A simple recursive descent parser for regular expressions
The recursive descent parser is based on the following LL(1) grammar for regular expressions. The grammar contains some small extensions, like 'a?' for the possibility of the occurance of the symbol a and '[c1-c2]' for the range of characters between c1 and c2. It is also possible to escape a special character with a backslash.

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
