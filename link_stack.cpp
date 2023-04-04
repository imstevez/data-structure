#include <stdlib.h>
#include <stdio.h>
#include "link_stack.hpp"


Status InitStack(LinkStack &S) {
    S.base = S.top = NULL;
    return OK;
}

Status DestroyStack(LinkStack &S) {
    ClearStack(S);
    return OK;
}

Status ClearStack(LinkStack &S) {
    while(S.top) {
        LinkStackNode *p = S.top;
        S.top = S.top->next;
        free(p);
    }
    S.base = S.top = NULL;
    return OK;
}

Status StackEmpty(LinkStack S) {
    if(S.top == NULL) return TRUE;
    return FALSE;
}

int StackLength(LinkStack S) {
    LinkStackNode *p = S.top;
    int n = 0;
    while(p) {
        ++n;
        p = p->next;
    }
    return n;
}

Status GetTop(LinkStack S, ElemType &e) {
    if(!S.top) return ERROR;
    e = S.top->data;
    return OK;
}

Status Push(LinkStack &S, ElemType e) {
    LinkStackNode *p = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = S.top;
    S.top = p;
    if(!S.top->next) S.base = S.top; 
    return OK;
}

Status Pop(LinkStack &S, ElemType &e) {
    if (!S.top) return ERROR;
    e = S.top->data;
    S.top = S.top->next;
    if(!S.top) S.base = NULL;
    return OK;
}

Status StackTraverse(LinkStack S, Status( *visit)(ElemType)) {
    LinkStackNode *p = S.top;
    while(p && visit(p->data)) p = p->next;
    if(!p) return TRUE;
    return FALSE;
}