#include <stdlib.h>
#include <stdio.h>
#include "status.hpp"

#define LIST_INIT_SIZE 100
#define LIST_INCREAMENT 10

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int length;
    int size;
} SqList;

Status ListInit_Sq(SqList &L) {
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) {
        exit(OVERFLOW);
    }
    L.length = 0;
    L.size = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) return ERROR;
    if (L.length >= L.size) {
		ElemType *newbase;
        newbase = (ElemType *)realloc(L.elem, (L.size + LIST_INCREAMENT) * sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.size += LIST_INCREAMENT;
    }
	ElemType *p, *q;
    q = &(L.elem[i-1]);
    for(p = &(L.elem[L.length - 1]); p >= q; --p) *(p+1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {
	if (i < 1 || i > L.length) return ERROR; 
	ElemType *p, *q;
	p = &(L.elem[i-1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (; p < q; ++p) *p = *(p+1);
	--L.length;
	return OK;
}

void ListMerge_Sq(SqList La, SqList Lb, SqList &Lc) {
    ElemType *pc = Lc.elem = (ElemType *)malloc((La.length + Lb.length) * sizeof(ElemType));
    if (!pc) exit(OVERFLOW);
    Lc.size = Lc.length = La.length + Lb.length;
    ElemType *pa = La.elem;
    ElemType *pb = Lb.elem;
    ElemType *pa_last = La.elem + La.length - 1;
    ElemType *pb_last = Lb.elem + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last)
    {
        if (*pa < *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while (pa <= pa_last) *pc++ = *pa++;
    while (pb <= pb_last) *pc++ = *pb++;
}

int LocateElem_Sq(SqList &L, ElemType e, Status (*compare) (ElemType, ElemType)) {
    int i = 1;
    ElemType *p = L.elem;
    while (i <= L.length && !compare(*p++, e)) ++i;
    if (i > L.length) return 0;
    return i;
}

Status equal(ElemType e1, ElemType e2) {
    if (e1 == e2) return TRUE;
    return FALSE;
}

void ListPrint_Sq(SqList &L) {
    for (int i = 0; i < L.length - 1; ++i) printf("%d, ", L.elem[i]);
    if (L.length > 0) printf("%d\n", L.elem[L.length-1]);
}