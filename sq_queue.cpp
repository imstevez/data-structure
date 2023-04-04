//
// Created by steve.zhang on 2023/3/13.
//

#include <cstdlib>
#include <cstdio>
#include "status.hpp"

#define MAX_QUEUE_SIZE 100


typedef int SQElemType;

typedef struct {
    SQElemType *base;
    int front;
    int rear;
} SqQueue;

Status InitSqQueue(SqQueue &Q) {
    Q.base = (SQElemType *)malloc(MAX_QUEUE_SIZE * sizeof(SQElemType));
    if (!Q.base) exit(OVERFLOW);
    Q.front = Q.rear = 0;
}

Status DestroySqQueue(SqQueue &Q) {
    free(Q.base);
    Q.front = Q.rear = 0;
}

Status ClearSqQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

Status QueueEmpty(SqQueue Q) {
    if (Q.front == Q.rear) return TRUE;
    return FALSE;
}

int QueueLength(SqQueue Q) {
    if (Q.front <= Q.rear) return Q.rear - Q.front;
    return MAX_QUEUE_SIZE - (Q.front - Q.rear);
}

Status GetHead(SqQueue Q, SQElemType &data) {
    if (Q.front == Q.rear) return ERROR;
    data = Q.base[Q.front];
    return OK;
}

Status EnQueue(SqQueue &Q, SQElemType data) {
    if((Q.rear + 1) % MAX_QUEUE_SIZE == Q.front) return ERROR;
    Q.base[Q.rear] = data;
    Q.rear = (Q.rear + 1) % MAX_QUEUE_SIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, SQElemType &data) {
    if(Q.front == Q.rear) return ERROR;
    data = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAX_QUEUE_SIZE;
    return OK;
}


Status QueueTraverse(SqQueue Q, Status (* visit)(SQElemType)) {
    int i = Q.front;
    while(i != Q.rear) {
        visit(Q.base[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    return OK;
}


Status print_elem(SQElemType data) {
    printf("%d ", data);
    return OK;
}

void PrintQueue(SqQueue Q) {
    QueueTraverse(Q, print_elem);
}



