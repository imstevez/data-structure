#include <stdlib.h>
#include <stdio.h>
#include "data.hpp"
#include "status.hpp"

#define MAX_SIZE 10000

typedef struct {
    DataType data;
    int cur;
} component, SLinkList[MAX_SIZE];

int LocateItem_SL(SLinkList L, DataType e) {
    int i = L[0].cur;
    while(i && L[i].data != e) i = L[i].cur;
    return i;
}

void InitSpace_SL(SLinkList &space) {
    for (int i = 0; i < MAX_SIZE - 1; ++i) space[i].cur = i+1;
    space[MAX_SIZE - 1].cur = 0;
}

int Malloc_SL(SLinkList &space) {
    int i = space[0].cur;
    if (space[0].cur) space[0].cur = space[i].cur;
    return i;
}

void Free_SL(SLinkList &space, int k) {
    if (k > 0 && k < MAX_SIZE - 1) {
        space[k].cur = space[0].cur;
        space[0].cur = k;
    }
}

void difference(SLinkList &space, int &S) {
    InitSpace_SL(space);
    S = Malloc_SL(space);
    int r = S;
    if (!S) exit(OVERFLOW);

    int m, n;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; ++i) {
        int c = Malloc_SL(space);
        if (!c) exit(OVERFLOW);
        scanf("%d", &space[c].data);
        space[r].cur = c;
        r = c;
    }

    space[r].cur = 0;

    for (int i = 0; i < n; ++i) {
        DataType data;
        scanf("%d", &data);
        int p = S;
        int k = space[S].cur;
        while(k != space[r].cur && space[k].data != data) {
            p = k;
            k = space[k].cur;
        }
        if (k == space[r].cur) {
            int c = Malloc_SL(space);
            if (!c) exit(OVERFLOW);
            space[c].data = data;
            space[c].cur = space[r].cur;
            space[r].cur = c;
        } else {
            space[p].cur = space[k].cur;
            Free_SL(space, k);
            if (k == r) r = p;
        }
    }
}