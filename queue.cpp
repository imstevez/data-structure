//
// Created by steve.zhang on 2023/3/13.
//
#include <cstdlib>
#include <cstdio>
#include "status.hpp"
#include "queue.hpp"

Status InitQueue(Queue &Q) {
    Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
    if(!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}

Status DestroyQueue(Queue &Q) {
    while(Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

Status ClearQueue(Queue &Q) {
    while(Q.front->next) {
        Q.rear = Q.front->next->next;
        free(Q.front->next);
        Q.front->next = Q.rear;
    }
    Q.rear = Q.front;
    return OK;
}

Status QueueEmpty(Queue Q) {
    if (Q.rear == Q.front) return TRUE;
    return FALSE;
}

int QueueLength(Queue Q) {
    int n = 0;
    QNode *p = Q.front;
    while(p->next) {
        ++n;
        p = p->next;
    }
    return n;
}

Status GetHead(Queue Q, DataType &data) {
    if(!Q.front->next) return ERROR;
    data = Q.front->next->data;
    return OK;
}

Status EnQueue(Queue &Q, DataType data) {
    QNode *p = (QNode *) malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = data;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(Queue &Q, DataType &data) {
    QNode *p = Q.front->next;
    if(!p) return ERROR;
    data = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return OK;
}

Status QueueTraverse(Queue Q, Status (* visit)(DataType)) {
    QNode *p = Q.front->next;
    while(p) {
        if (!visit(p->data)) return FALSE;
        p = p->next;
    }
    return TRUE;
}


Status print_elem(DataType data) {
    printf("%d ", data);
    return OK;
}

void PrintQueue(Queue Q) {
    QueueTraverse(Q, print_elem);
}