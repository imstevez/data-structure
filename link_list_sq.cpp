#include <stdlib.h>
#include <stdio.h>
#include "data.hpp"
#include "status.hpp"

typedef struct LNode
{
    DataType data;
    struct LNode *next;
}LNode, *LinkListSq;

Status GetData_L(LinkListSq L, int i, DataType &data) {
    LNode *p = L->next;
    int j = 1;
    while(p && j < i)
    {
        p = p->next; ++j;
    }
    if (!p || j > i) return ERROR;
    data = p->data;
    return OK;
}

Status ListInsert_L(LinkListSq L, int i, DataType data) {
    int j = 0; LNode *p = L;
    while (p && j < i-1)
    {
        p = p->next; ++j;
    }
    if (!p || j > i-1) return ERROR;
    LNode *node = (LNode *)malloc(sizeof(LNode));
    node->data = data;
    node->next = p->next;
    p->next = node;
    return OK;
}

Status ListDelete_L(LinkListSq L, int i, DataType &data) {
    int j = 0; LNode *p = L;
    while (p->next && j < i-1)
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i) return ERROR;
    LNode *q = p->next;
    data = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

void CreateList_L(LinkListSq &L, int n) {
    L = (LinkListSq)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    for(int i = n; i > 0; --i) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (!node) exit(OVERFLOW);
        scanf("%d", &node->data);
        node->next = L->next;
        L->next = node;
    }
}

void MergeList_L(LinkListSq La, LinkListSq Lb, LinkListSq &Lc) {
    if (!Lc) exit(OVERFLOW);
    LNode *pa = La->next;
    LNode *pb = Lb->next;
    LNode *pc = Lc = La;
    while(pa && pb) {
        if (pa->data < pb->data) {
            pc->next = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pb = pb->next;
        }
        pc = pc->next;
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}
