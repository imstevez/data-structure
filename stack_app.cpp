#include <stdlib.h>
#include <stdio.h>
#include "stack.hpp"

void conv_10_8() {
    SqStack S;
    InitStack(S);
    int n;
    scanf("%d", &n);
    while(n) {
        Push(S, n%8);
        n /= 8;
    }
    int e;
    while(!StackEmpty(S)) {
        Pop(S, e);
        printf("%d", e);
    }
    printf("\n");
    DestroyStack(S);
}


int is_match(char a, char b) {
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

void match_c() {
    int c, e;
    SqStack S;
    InitStack(S);
    while((c = getchar()) != EOF && c != '\n') {
        switch (c) {
        case '(':
        case '[': Push(S, c); break;
        case ')':
        case ']':
            if (!Pop(S, e) || !is_match(e, c)) {
                DestroyStack(S);
                printf("not match\n");
                return;
            }
            break;
        }
    }
    if(!StackEmpty(S)) printf("not match\n");
    else printf("match\n");
    DestroyStack(S);
}

Status print_c(ElemType e) {
    printf("%c", e);
    return OK;
}

void line_edit() {
    SqStack S;
    InitStack(S);
    int c, e;
    c = getchar();
    while(c != EOF) {
        while(c != EOF && c != '\n') {
            switch (c) {
                case '#': Pop(S, e); break;
                case '@': ClearStack(S); break;
                default: Push(S, c); break;
            }
            c = getchar();
        }
        StackTraverse(S, print_c);
        printf("\n");
        ClearStack(S);
        if (c != EOF) c = getchar();
    }
    DestroyStack(S);
}

int main() {
    line_edit();
    return 0;
}