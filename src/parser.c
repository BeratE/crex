#include "parser.h"
#include <stdio.h>

static char* _inputStr; // pointer to next input character to be consumed
static Symbol _currToken; // current token

// Retrieve next token from input string
static Symbol getNextToken()
{
    Symbol sym;
    sym.value = '\0';
    switch (_inputStr[0]) {
        case '\0': sym.name=EPSLN; break;
        case '*' : sym.name=KSTAR; _inputStr++; break;
        case '(' : sym.name=GRPOP; _inputStr++; break;
        case ')' : sym.name=GRPCL; _inputStr++; break;
        case '|':  sym.name=DISJN; _inputStr++; break;
        case '?':  sym.name=EXIST; _inputStr++; break;
        case '[':  sym.name=RNGOP; _inputStr++; break;
        case ']':  sym.name=RNGCL; _inputStr++; break;
        case '-':  sym.name=RNGLN; _inputStr++; break;
        case '\\': sym.name=ESCHR; sym.value=_inputStr[1]; _inputStr+=2; break;
        default:   sym.name=CHARA; sym.value=_inputStr[0]; _inputStr++; break;
    }
    return sym;
}

void parse(char *str)
{
    _inputStr = str;
    _currToken = getNextToken();
    rExpr();
    printf("\n");
}

int rExpr ()
{
    printf("\nrE: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case GRPOP:
        case CHARA:
        case RNGOP:
        case ESCHR:
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
    printf("\nrEp: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case DISJN:
            printf("2,");
            _currToken = getNextToken();
            if (!rTerm()) return 0;
            if (!rExprP()) return 0;
            break;
        case EPSLN:
        case GRPCL:
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
    printf("\nrT: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case GRPOP:
        case CHARA:
        case RNGOP:
        case ESCHR:
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
    printf("\nrTp: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case GRPOP:
        case CHARA:
        case RNGOP:
        case ESCHR:
            printf("5,");
            if (!rForm()) return 0;
            if (!rTermP()) return 0;
            break;
        case DISJN:
        case GRPCL:
        case EPSLN:
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
    printf("\nrF: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case GRPOP:
        case CHARA:
        case RNGOP:
        case ESCHR:
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
    printf("\nrFp: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case KSTAR:
            printf("8,");
            _currToken = getNextToken();
            break;
        case EXIST:
            printf("9,");
            _currToken = getNextToken();
            break;
        case GRPOP:
        case GRPCL:
        case DISJN:
        case CHARA:
        case EPSLN:
        case RNGOP:
        case ESCHR:
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
    printf("\nrB: %d, %s ", _currToken.name, _inputStr);
    switch (_currToken.name) {
        case GRPOP:
            printf("11,");
            _currToken = getNextToken();
            if (!rExpr()) return 0;
            if (_currToken.name != GRPCL) {
                printf("\nerror: missing closing paranthesis..\n");
                return 0;
            }
            _currToken = getNextToken();
            break;
        case RNGOP:
            printf("12,");
            
            _currToken = getNextToken();
            break;
        case CHARA:
            printf("13,");
            _currToken = getNextToken();
            break;
        case ESCHR:
            printf("14,");
            _currToken = getNextToken();
            break;
        default:
            printf("\n!error: lookahead does not match..\n");
            return 0;
    }
    return 1;
}
