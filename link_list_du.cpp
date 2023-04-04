
#include <stdlib.h>
#include <stdio.h>
#include "data.hpp"
#include "status.hpp"



typedef struct DuLNode {
    DataType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

Status ListInsert_DuL(DuLinkList &L, int i, DataType data) {
    int j = 0;
    DuLNode *p = L;
    while(p->next != L && j < i-1) {
        p = p->next;
        ++j;
    }
    if (j != i-1) return ERROR;
    DuLNode *n = (DuLNode *)malloc(sizeof(DuLNode));
    n->data = data;
    n->next = p->next;
    p->next->prior = n;
    n->prior = p;
    p->next = n;
}