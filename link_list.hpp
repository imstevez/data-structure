#ifndef LINK_LIST_H__
#define LINK_LIST_H__

#include "status.hpp"
#include "data_type.hpp"

typedef struct Node {
    DataType data;
    struct Node *next;
}Node, *NodePtr;

typedef struct {
    NodePtr head, tail;
    NodePtr prior, cursor;
    int length;
    int order;
} LinkList;

NodePtr MakeNode(DataType data);
void FreeNode(NodePtr p);
void NodeSetData(NodePtr p, DataType data);
DataType NodeGetData(NodePtr p);
Status InitList(LinkList &l);
void DestroyList(LinkList &l);
void ClearList(LinkList &l);
void SwapList(LinkList &la, LinkList &lb);

Status ListEmpty(LinkList l);
int ListLength(LinkList l);
NodePtr ListGetHead(LinkList l);
NodePtr ListGetTail(LinkList l);
NodePtr ListGetFirst(LinkList l);
NodePtr ListGetLast(LinkList l);
NodePtr ListGetCursor(LinkList l); 
NodePtr ListGetPrior(LinkList l); 
int ListGetOrder(LinkList l); 
void ListReturnCursor(LinkList &l); 
void ListMoveCursorNext(LinkList &l);
void ListSetCursorAfterTail(LinkList &l); 
Status ListInsAfterCursor(LinkList &l, NodePtr p); 
Status ListInsBeforeCursor(LinkList &l, NodePtr p); 
NodePtr ListDelAtCursor(LinkList &l); 
NodePtr ListDelFromCursor(LinkList &l); 
NodePtr ListDelToCursor(LinkList &l); 
Status ListAppendToCursor(LinkList &l, NodePtr p); 
Status ListPrependToCursor(LinkList &l, NodePtr p); 

void ListTraverse(LinkList l, Status(* visit)(int, NodePtr)); 
void ListMoveCursorByNode(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr)); 
void ListMoveCursorByData(LinkList &l, DataType data, Status(* cmp)(DataType, DataType)); 
void ListMoveCursorByOrder(LinkList &l, int i, Status(* cmp)(int, int)); 
void ListSetCursorByData(LinkList &l, DataType data, Status(* cmp)(DataType, DataType)); 
void ListSetCursorByNode(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr)); 
void ListSetCursorByOrder(LinkList &l, int i, Status(* cmp)(int, int)); 

void ListInsOrder(LinkList &l, NodePtr p, Status(* cmp)(NodePtr, NodePtr));
void ListInsFirst(LinkList &l, NodePtr p);
void ListInsTail(LinkList &l, NodePtr p); 
void ListAppend(LinkList &l, NodePtr p); 
NodePtr ListLocateByData(LinkList &l, DataType d, Status (* cmp) (DataType, DataType)); 
NodePtr ListLocateByNode(LinkList &l, NodePtr p, Status (* cmp) (NodePtr, NodePtr)); 
NodePtr ListLocateByOrder(LinkList &l, int i, Status (* cmp) (int, int)); 
Status ListInsAfter(LinkList &l, NodePtr p, NodePtr q); 
Status ListInsBefore(LinkList &l, NodePtr p, NodePtr q); 
Status ListInsNth(LinkList &l, int i, NodePtr p); 
NodePtr ListDelFirst(LinkList &l); 
NodePtr ListDelLast(LinkList &l); 
NodePtr ListDelFromData(LinkList &l, DataType d); 
NodePtr ListDelToData(LinkList &l, DataType d); 
NodePtr ListDelToData(LinkList &l, NodePtr p); 
NodePtr ListDelFromNode(LinkList &l, NodePtr p); 
NodePtr ListDelToNode(LinkList &l, NodePtr p); 
NodePtr ListDelFromOrder(LinkList &l, int n); 
NodePtr ListDelToOrder(LinkList &l, int n); 
Status ListMerge(LinkList &la, LinkList &lb, LinkList &lc); 

#endif