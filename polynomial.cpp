#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "polynomail.hpp"

Status ge_expn(DataType d, DataType e){
    TermData *td = (TermData *)d; TermData *te = (TermData *)e;
    if (td->expn >= te->expn) return TRUE;
    return FALSE;
}

Status scanf_term(float *coef, int *expn) {
    scanf("%f,%d", coef, expn); 
    int c;
    while ((c = getchar())) {   
        if (!isspace(c)) {
            ungetc(c, stdin);
            break;
        } else if (c == '\n') {
            return FALSE;
        }
    }
    return TRUE;
}

Status CreatePolyn(Polynomail &l) {
    if (!InitList(l)) return ERROR;
    TermPtr p, q; TermData *d;
    float coef; int expn;
    Status conti;
    do {
        conti = scanf_term(&coef, &expn);
        if (coef == 0.0 || expn < 0) continue;
        d = (TermData *)malloc(sizeof(TermData));
        if (!d) return ERROR;
        d->coef = coef; d->expn = expn;
        p = ListLocateByData(l, d, ge_expn);
        int expn = p ? ((TermData *)NodeGetData(p))->expn : -1;
        if (expn != d->expn) {
            q = MakeNode(d);
            if (!q) return ERROR;
            ListInsBeforeCursor(l, q);
        } else {
            free(d);
        }
    } while (conti);
    
    return OK;
}

void DestroyPloyn(Polynomail &l) {
    DestroyList(l);
}

Status print_term(int i, TermPtr p) {
    TermData *d = (TermData *)p->data;
    printf("%3.2f*(x^%d)", d->coef, d->expn);
    if (p->next) printf(" + ");
    return TRUE;
}

void PrintPolyn(Polynomail l) {
    ListTraverse(l, print_term);
}

int PolynLength(Polynomail l) {
    return ListLength(l);
}

TermData *GetTermData(TermPtr p) {
    return (TermData *)NodeGetData(p);
}

int cmp_term(TermData *d1, TermData *d2) {
    if (d1->expn < d2->expn) return -1;
    else if(d1->expn == d2->expn) return 0;
    else return 1;
}

void AddPolyn(Polynomail &la, Polynomail &lb) {
    ListReturnCursor(la); 
    ListReturnCursor(lb);
    TermPtr p = ListGetCursor(la);
    TermPtr q = ListGetCursor(lb);
    while(p && q) {
        TermData *dp = GetTermData(p); 
        TermData *dq = GetTermData(q);
        switch (cmp_term(dp, dq)) {
        case -1:
            ListMoveCursorNext(la);
            p = ListGetCursor(la);
            break;
        case 0:
            dp->coef += dq->coef;
            if (dp->coef == 0.0) {
                ListDelAtCursor(la);
                FreeNode(p);
            } else {
                ListMoveCursorNext(la);
            }
            ListDelAtCursor(lb);
            FreeNode(q);
            p = ListGetCursor(la);
            q = ListGetCursor(lb);
            break;
        case 1:
            ListDelAtCursor(lb);
            ListInsBeforeCursor(la, q);
            q = ListGetCursor(lb);
            break;
        }
    }
    if(q) {
        ListDelFromCursor(lb);
        ListPrependToCursor(la, q);
    }
    DestroyPloyn(lb);
}

Status MultiPolyn(Polynomail &la, Polynomail &lb) {
    Polynomail lc;
    if (!InitList(lc)) return ERROR;
    TermPtr p, q, r; TermData *d, *e, *f, *g;
    while((p = ListDelFirst(la))) {
        ListReturnCursor(lb);
        ListReturnCursor(lc);
        d = (TermData *)NodeGetData(p);
        while((q = ListGetCursor(lb))) {
            ListMoveCursorNext(lb);
            e = (TermData *)NodeGetData(q);
            f = (TermData *)malloc(sizeof(TermData));
            if (!f) return ERROR;
            f->coef = d->coef * e->coef;
            f->expn = d->expn + e->expn;
            ListMoveCursorByData(lc, f, ge_expn);
            r = ListGetCursor(lc);
            if (!r) {
                r = MakeNode(f);
                ListInsBeforeCursor(lc, r);
                continue;
            }
            g = (TermData *)NodeGetData(r);
            if (f->expn != g->expn) {
                r = MakeNode(f);
                ListInsBeforeCursor(lc, r);
                continue;
            }
            g->coef += f->coef;
            free(f);
            if (g->coef == 0.0) {
                ListDelAtCursor(lc);
                FreeNode(r);
                continue;
            }
            ListMoveCursorNext(lc);
        }
        FreeNode(p);
    }
    SwapList(la, lc);
    DestroyList(lc);
    DestroyList(lb);
    return OK;
}