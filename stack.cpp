#include <stdlib.h>
#include <stdio.h>
#include "stack.hpp"

Status InitStack(SqStack &S) {
    S.base = S.top = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base) exit(OVERFLOW);
    S.size = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack &S) {
    free(S.base);
    S.base = S.top = NULL;
    S.size = 0;
    return OK;
}

Status ClearStack(SqStack &S) {
    S.top = S.base;
    return OK;
}

Status StackEmpty(SqStack S) {
    if (S.top == S.base) return TRUE;
    return FALSE;
}

int StackLength(SqStack S) {
    int n = 0;
    ElemType *p = S.base;
    while (p != S.top) {++p; ++n;} 
    return n;
}

Status GetTop(SqStack S, ElemType &e) {
    if (S.top == S.base) return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status Push(SqStack &S, ElemType e) {
    if (S.top - S.base >= S.size) {
        S.base = (ElemType *)realloc(S.base, (S.size + STACK_INCR_SIZE) * sizeof(ElemType));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + S.size;
        S.size += STACK_INCR_SIZE;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, ElemType &e) {
    if (S.top == S.base) return ERROR;
    e = * --S.top;
    return OK;
}

Status StackTraverse(SqStack S, Status( *visit)(ElemType)) {
    ElemType *p = S.base;
    while(p != S.top && visit(*p)) ++p;
    if (p == S.top) return TRUE;
    return FALSE;
}

Status print_stack(ElemType e) {
    printf("%d ", e);
    return TRUE;
}

void PrintStack(SqStack S) {
    StackTraverse(S, print_stack);
}