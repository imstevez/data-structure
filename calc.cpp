#include <cstdio>
#include "stack.hpp"
#include "status.hpp"

#define TYPE_OPND 1
#define TYPE_OPTR 2
#define TYPE_SPCE 3
#define TYPE_UNDF 4

int c_type(int c) {
    if (c == ' ') return TYPE_SPCE;
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '\n') return TYPE_OPTR;
    if (c >= '0' && c <= '9') return TYPE_OPND;
    return TYPE_UNDF;
}

int precede_value(int optr) {
    switch (optr) {
        case '\n':
            return 0;
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '(':
            return 4;
        default:
            return -1;
    }
}

int precede(int optr1, int optr2) {
    if (optr1 == '(' && optr2 == ')') return '=';
    if (optr1 == '(') return '<';
    int optr1_v = precede_value(optr1);
    int optr2_v = precede_value(optr2);
    if (optr1_v >= optr2_v) return '>';
    return '<';
}

int operate(int opnd1, int optr, int opnd2) {
    if (optr == '+') return opnd1 + opnd2;
    if (optr == '-') return opnd1 - opnd2;
    if (optr == '*') return opnd1 * opnd2;
    if (optr == '/') return opnd1 / opnd2;
    return 0;
}

void evaluate_express() {
    SqStack OPTR, OPND;
    InitStack(OPTR);
    InitStack(OPND);
    int c = getchar();
    int opnd1, opnd2 = 0;
    int optr = '\n';
    Push(OPTR, optr);
    while (optr != '\n' || c != '\n') {
        int ct = c_type(c);
        if (ct == TYPE_UNDF) {
            c = '\n';
            continue;
        }
        if (ct == TYPE_SPCE) {
            c = getchar();
            continue;
        }
        if (ct == TYPE_OPND) {
            Push(OPND, c - 48);
            c = getchar();
            continue;
        }
        int pe = precede(optr, c);
        if (pe == '<') {
            optr = c;
            Push(OPTR, optr);
            c = getchar();
            continue;
        }
        if (pe == '=') {
            Pop(OPTR, optr);
            GetTop(OPTR, optr);
            c = getchar();
            continue;
        }
        Pop(OPND, opnd2);
        Pop(OPND, opnd1);
        int val = operate(opnd1, optr, opnd2);
        Push(OPND, val);
        Pop(OPTR, optr);
        GetTop(OPTR, optr);
    }
    int result;
    GetTop(OPND, result);
    printf("The result is %d.\n", result);
}

int main() {
    evaluate_express();
}


