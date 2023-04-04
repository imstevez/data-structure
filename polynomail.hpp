#ifndef POLYN_H__
#define POLYN_H__

#include "link_list.hpp"

typedef struct {
    float coef;
    int expn;
} TermData;

typedef NodePtr TermPtr;
typedef LinkList Polynomail;

Status CreatePolyn(Polynomail &l);
void DestroyPloyn(Polynomail &l);
void PrintPolyn(Polynomail l);
int PolynLength(Polynomail l);
void AddPolyn(Polynomail &la, Polynomail &lb);
Status MultiPolyn(Polynomail &la, Polynomail &lb); 

#endif