#include "parser.h"
#include <stdio.h>

static char* strp;

void parse(char *str)
{
    strp = str;
    rExpr();
    printf("\n");
}

Token getToken(char c)
{
    Token t = CHR;
    switch (c) {
        case '\0': t = EPS; break;
        case '*' : t = KLS; break;
        case '(' : t = POP; break;
        case ')':  t = PCL; break;
        case '.':  t = CON; break;
        case '?':  t = QST; break;
        case '|':  t = DIS; break;
        case '[':  t = BRO; break;
        case ']':  t = BRC; break;
        case '-':  t = DSH; break;            
        default: t = CHR; break;
    }
    return t;
}

int rExpr ()
{
    //printf("rE: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case POP:
        case CHR:
        case BRO:
            printf("1,");
            if (!rTerm()) return 0;
            if (!rExprP()) return 0;;
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rExprP()
{
    //printf("rEp: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case DIS:
            printf("2,");
            strp++;
            if (!rTerm()) return 0;
            if (!rExprP()) return 0;
            break;
        case EPS:
        case PCL:
            printf("3,");
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rTerm()
{    
    //printf("rT: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case POP:
        case CHR:
        case BRO:
            printf("4,");
            if (!rForm()) return 0;
            if (!rTermP()) return 0;
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rTermP()
{
    //printf("rTp: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case POP:
        case CHR:
        case BRO:
            printf("5,");
            if (!rForm()) return 0;
            if (!rTermP()) return 0;
            break;
        case DIS:
        case PCL:
        case EPS:
            printf("6,");
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rForm()
{
    //printf("rF: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case POP:
        case CHR:
        case BRO:
            printf("7,");
            if (!rBase()) return 0;
            if (!rFormP()) return 0;
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rFormP()
{
    //printf("rFp: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case KLS:
            printf("8,");
            strp++;
            break;
        case QST:
            printf("9,");
            strp++;
            break;
        case POP:
        case PCL:
        case DIS:
        case CHR:
        case EPS:
        case BRO:
            printf("10,");
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}

int rBase()
{
    //printf("rB: %s \n", strp);
    Token t = getToken(strp[0]);
    switch (t) {
        case POP:
            printf("11,");
            strp++;
            if (!rExpr()) return 0;
            if (getToken(strp[0]) == PCL) {
                strp++;
            } else {
                printf("\nerror: missing closing paranthesis..\n");
                return 0;
            }
            break;
        case CHR:
            printf("12,");
            strp++;
            break;
        case BRO:
            printf("13,");
            if (getToken(strp[0]) == BRO && getToken(strp[1]) == CHR &&
                getToken(strp[2]) == DSH && getToken(strp[3]) == CHR &&
                getToken(strp[4]) == BRC) {
                strp += 5;
            } else {
                printf("\n!error: range is not correctly formateed..\n");
                return -1;
            }
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}
