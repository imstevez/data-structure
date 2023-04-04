#ifndef link_stack_hpp
#define link_stack_hpp

#include <stdio.h>
#include "status.hpp"

typedef int ElemType;

typedef struct LinkStackNode {
    ElemType data;
    LinkStackNode *next;
} LinkStackNode; 

typedef struct {
    LinkStackNode *base;
    LinkStackNode *top;
} LinkStack;

Status InitStack(LinkStack &S);
Status DestroyStack(LinkStack &S);
Status ClearStack(LinkStack &S);
Status StackEmpty(LinkStack S);
int StackLength(LinkStack S);
Status GetTop(LinkStack S, ElemType &e);
Status Push(LinkStack &S, ElemType e);
Status Pop(LinkStack &S, ElemType &e);
Status StackTraverse(LinkStack S, Status(*visit)(ElemType));

#endif
