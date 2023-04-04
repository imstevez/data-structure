#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include "status.hpp"

#define STACK_INIT_SIZE 100
#define STACK_INCR_SIZE 10


typedef int ElemType;

typedef struct {
    ElemType  *base;
    ElemType  *top;
    int size;
} SqStack;

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, ElemType &e);
Status Push(SqStack &S, ElemType e);
Status Pop(SqStack &S, ElemType &e);
Status StackTraverse(SqStack S, Status(*visit)(ElemType));
void PrintStack (SqStack S);

#endif
