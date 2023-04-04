#include <stdlib.h>
#include <string.h>
#include "link_list.hpp"

Status equal_data(DataType d, DataType e) {
    if (d == e) return TRUE;
    return FALSE;
}

Status equal_node(NodePtr p, NodePtr q) {
    if (p == q) return TRUE;
    return FALSE;
}

Status equal_order(int i, int j) {
    if (i == j) return TRUE;
    return FALSE;
}

NodePtr MakeNode(DataType data) {
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    if (!p) return NULL;
    p->data = data;
    return p;
}

void FreeNode(NodePtr p) {
    free(p);
}

void NodeSetData(NodePtr p, DataType data) {
    p->data = data;
}

DataType NodeGetData(NodePtr p) {
    return p->data;
}

Status InitList(LinkList &l) {
    l.head = l.tail = l.prior = (NodePtr)malloc(sizeof(Node));
    if (!(l.head)) return ERROR;
    l.cursor = l.head->next = NULL;
    l.length = 0;
    l.order = 1;
    return OK;
}

void DestroyList(LinkList &l) {
    NodePtr p = l.head;
    while(p) {
        NodePtr q = p;
        p = p->next;
        FreeNode(q);
    }
    l.head = l.tail = l.cursor = l.prior = NULL;
    l.length = l.order = 0;
}

void ClearList(LinkList &l) {
    NodePtr p = l.head->next;
    while(p) {
        NodePtr q = p;
        p = p->next;
        FreeNode(q);
    }
    l.tail = l.prior = l.head;
    l.cursor = l.head->next = NULL;
    l.length = 0;
    l.order  = 1;
}

void SwapList(LinkList &la, LinkList &lb) {
    LinkList tm;
    memcpy(&tm, &la, sizeof(LinkList));
    memcpy(&la, &lb, sizeof(LinkList));
    memcpy(&lb, &tm, sizeof(LinkList));
}

Status ListEmpty(LinkList l) {
    if (l.length == 0) return TRUE;
    return FALSE;
}

int ListLength(LinkList l) {
    return l.length;
}

NodePtr ListGetHead(LinkList l) {
    return l.head;
}

NodePtr ListGetTail(LinkList l) {
    return l.tail;
}

NodePtr ListGetFirst(LinkList l) {
    return l.head->next;
}

NodePtr ListGetLast(LinkList l) {
    if (l.tail == l.head) return NULL;
    return l.tail;
}

NodePtr ListGetCursor(LinkList l) {
    return l.cursor;
}

NodePtr ListGetPrior(LinkList l) {
    return l.prior;
}

int ListGetOrder(LinkList l) {
    return l.order;
}

void ListReturnCursor(LinkList &l) {
    l.prior = l.head;
    l.cursor = l.head->next;
    l.order = 1;
}

void ListMoveCursorNext(LinkList &l) {
    if (!l.cursor) return;
    l.cursor = l.cursor->next;
    l.prior = l.prior->next;
    ++l.order;
}

void ListSetCursorAfterTail(LinkList &l) {
    l.prior = l.tail;
    l.cursor = NULL;
    l.order = l.length+1;
}

Status ListInsAfterCursor(LinkList &l, NodePtr p) {
    if (!l.cursor) return ERROR;
    if (!p) return OK;
    p->next = l.cursor->next;
    l.cursor->next = p;
    if (!p->next) l.tail = p;
    ++l.length;
    return OK;
}

Status ListInsBeforeCursor(LinkList &l, NodePtr p) {
    if (!p) return OK;
    p->next = l.cursor;
    l.prior->next = p;
    l.prior = p;
    if (!l.prior->next) l.tail = p;
    ++l.length;
    ++l.order;
    return OK;
}

NodePtr ListDelAtCursor(LinkList &l) {
    if(!l.cursor) return NULL;
    NodePtr p = l.cursor;
    l.cursor = p->next;
    p->next = NULL;
    l.prior->next = l.cursor;
    if (!l.prior->next) l.tail = l.prior;
    --l.length;
    return p;
}

NodePtr ListDelFromCursor(LinkList &l) {
    if (!l.cursor) return NULL;
    NodePtr p = l.cursor;
    l.cursor = NULL;
    l.prior->next = l.cursor;
    l.tail = l.prior;
    l.length = l.order-1;
    return p;
}

NodePtr ListDelToCursor(LinkList &l) {
    if (!l.cursor) return NULL;
    NodePtr p = l.head->next;
    l.cursor = l.cursor->next;
    l.prior->next = NULL;
    l.prior = l.head;
    l.prior->next = l.cursor;
    if (!l.prior->next) l.tail = l.prior;
    l.length -= l.order;
    return p;
}

Status ListAppendToCursor(LinkList &l, NodePtr p) {
    if (!l.cursor) return ERROR;
    NodePtr q = l.cursor->next;
    l.cursor->next = p;
    NodePtr r = l.cursor;
    while(r->next) {
        ++l.length;
        r = r->next;
    }
    r->next = q;
    if (!r->next) l.tail = r;
    return OK;
}

Status ListPrependToCursor(LinkList &l, NodePtr p) {
    l.prior->next = p;
    while(l.prior->next) {
        ++l.length;
        ++l.order;
        l.prior = l.prior->next;
    }
    l.prior->next = l.cursor; 
    if (!l.prior->next) l.tail = l.prior;
    return OK;
}

void ListTraverse(LinkList l, Status(* visit)(int, NodePtr)) {
    int i = 1;
    NodePtr p = l.head->next;
    while(p && visit(i, p)) {
        ++i;
        p = p->next;
    }
}

void ListMoveCursorByNode(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr)) {
    while(ListGetCursor(l) && !cmp(ListGetCursor(l), p)) {
        ListMoveCursorNext(l);
    }
}

void ListMoveCursorByData(LinkList &l, DataType data, Status(* cmp)(DataType, DataType)) {
    while(ListGetCursor(l) && !cmp(NodeGetData(ListGetCursor(l)), data)) {
        ListMoveCursorNext(l);
    }
}

void ListMoveCursorByOrder(LinkList &l, int i, Status(* cmp)(int, int)) {
    while(ListGetCursor(l) && !cmp(ListGetOrder(l), i)) {
        ListMoveCursorNext(l);
    }
}

void ListSetCursorByData(LinkList &l, DataType data, Status(* cmp)(DataType, DataType)) {
    ListReturnCursor(l);
    ListMoveCursorByData(l, data, cmp);
}

void ListSetCursorByNode(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr)) {
    ListReturnCursor(l);
    ListMoveCursorByNode(l, p, cmp);
}

void ListSetCursorByOrder(LinkList &l, int i, Status(* cmp)(int, int)) {
    ListReturnCursor(l);
    ListMoveCursorByOrder(l, i, cmp);
}

void ListInsOrder(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr)) {
    ListSetCursorByNode(l, p, cmp);
    ListInsBeforeCursor(l, p);
}

void ListInsFirst(LinkList &l, NodePtr p) {
    ListReturnCursor(l);
    ListInsBeforeCursor(l, p);
}

void ListInsTail(LinkList &l, NodePtr p) {
    ListSetCursorAfterTail(l);
    ListInsBeforeCursor(l, p);
}

void ListAppend(LinkList &l, NodePtr p) {
    ListSetCursorAfterTail(l);
    ListPrependToCursor(l, p);
}

NodePtr ListLocateByData(LinkList &l, DataType d, Status (* cmp) (DataType, DataType)) {
    ListSetCursorByData(l, d, cmp);
    return ListGetCursor(l);
}

NodePtr ListLocateByNode(LinkList &l, NodePtr p, Status (* cmp) (NodePtr, NodePtr)) {
    ListSetCursorByNode(l, p, cmp);
    return ListGetCursor(l);
}


NodePtr ListLocateByOrder(LinkList &l, int i, Status (* cmp) (int, int)) {
    ListSetCursorByOrder(l, i, cmp);
    return ListGetCursor(l);
}

Status ListInsAfter(LinkList &l, NodePtr p, NodePtr q) {
    ListSetCursorByNode(l, p, equal_node);
    if (ListGetCursor(l) == NULL) return ERROR;
    ListInsAfterCursor(l, q);
    return OK;
}

Status ListInsBefore(LinkList &l, NodePtr p, NodePtr q) {
    ListSetCursorByNode(l, p, equal_node);
    if (ListGetCursor(l) == NULL) return ERROR;
    ListInsBeforeCursor(l, q);
    return OK;
}

Status ListInsNth(LinkList &l, int i, NodePtr p) {
    ListSetCursorByOrder(l, i, equal_order);
    if (ListGetOrder(l) != i) return ERROR;
    ListInsBeforeCursor(l, p);
    return OK;
}

NodePtr ListDelFirst(LinkList &l) {
    ListReturnCursor(l);
    return ListDelAtCursor(l);
}

NodePtr ListDelLast(LinkList &l) {
    ListSetCursorByOrder(l, ListLength(l) - 1, equal_order);
    return ListDelAtCursor(l);
}

NodePtr ListDelFromData(LinkList &l, DataType d) {
    ListSetCursorByData(l, d, equal_data);
    return ListDelFromCursor(l);
}

NodePtr ListDelToData(LinkList &l, DataType d) {
    ListSetCursorByData(l, d, equal_data);
    return ListDelToCursor(l);
}

NodePtr ListDelToData(LinkList &l, NodePtr p) {
    ListSetCursorByNode(l, p, equal_node);
    return ListDelToCursor(l);
}

NodePtr ListDelFromNode(LinkList &l, NodePtr p) {
    ListSetCursorByNode(l, p, equal_node);
    return ListDelFromCursor(l);
}

NodePtr ListDelToNode(LinkList &l, NodePtr p) {
    ListSetCursorByNode(l, p, equal_node);
    return ListDelToCursor(l);
}

NodePtr ListDelFromOrder(LinkList &l, int n) {
    ListSetCursorByOrder(l, n, equal_order);
    return ListDelFromCursor(l);
}

NodePtr ListDelToOrder(LinkList &l, int n) {
    ListSetCursorByOrder(l, n, equal_order);
    return ListDelToCursor(l);
}

Status ListMerge(LinkList &la, LinkList &lb, LinkList &lc) {
    if (!InitList(lc)) return ERROR;

    NodePtr fa = ListGetFirst(la);
    NodePtr fb = ListGetFirst(lb);
    int *d, *e;

    while(fa && fb) {
        d = (int *)NodeGetData(fa);
        e = (int *)NodeGetData(fb);
        if(*d <= *e) {
            ListInsTail(lc, ListDelFirst(la));
            fa = ListGetFirst(la);
        } else {
            ListInsTail(lc, ListDelFirst(lb));
            fb = ListGetFirst(lb);
        }
    }

    if (fa) {
        ListDelFromNode(la, fa);
        ListAppend(lc, fa); 
    } 
    if (fb) {
        ListDelFromNode(lb, fb);
        ListAppend(lc, fb);
    }

    return OK;
}