//
// Created by steve.zhang on 2023/4/3.
//

#include <cstdlib>
#include <cstdio>
#include "link_list.hpp"
#include "queue.hpp"


typedef struct {
    int OccurTime;
    int Type;
} Event;

typedef struct {
    int ArrivedTime;
    int Duration;
} Customer;

Status cmp(NodePtr p1, NodePtr p2) {
    auto *d1 = (Event *) NodeGetData(p1);
    auto *d2 = (Event *) NodeGetData(p2);
    if (d1->OccurTime > d2->OccurTime) return TRUE;
    return FALSE;
}

Status visit(int i, NodePtr p) {
    auto *d = (Event *) NodeGetData(p);
    printf("(%d, %d) ", d->OccurTime, d->Type);
    return OK;
}

Status visit_q(DataType d) {
    auto *c = (Customer *) d;
    printf("(%d, %d) ", c->ArrivedTime, c->Duration);
    return OK;
}


LinkList events;
Queue counters[5];
int closedTime = 30;
int customerNum = 0;
int totalTime = 0;

int minCounterIdx() {
    int i = 1;
    int l = QueueLength(counters[i]);
    for (int j = 2; j <= 4; ++j) {
        int m = QueueLength(counters[j]);
        if (m < l) {
            i = j;
            l = m;
        }
    }
    return i;
}

void OpenForDay() {
    InitList(events);
    for (int i = 1; i <= 4; ++i) InitQueue(counters[i]);
    auto *event = (Event *) malloc(sizeof(Event));
    ListInsOrder(events, MakeNode(event), cmp);
}


void CustomerArrive(Event *event) {
    ++customerNum;
    auto *customer = (Customer *) malloc(sizeof(Customer));
    customer->ArrivedTime = event->OccurTime;
    customer->Duration = rand() % 29 + 1;
    int idx = minCounterIdx();
    EnQueue(counters[idx], customer);
    if (QueueLength(counters[idx]) == 1) {
        auto *dEvent = (Event *) malloc(sizeof(Event));
        dEvent->OccurTime = event->OccurTime + customer->Duration;
        dEvent->Type = idx;
        ListInsOrder(events, MakeNode(dEvent), cmp);
    }
    int interTime = rand() % 4 + 1;
    if (event->OccurTime + interTime < closedTime) {
        auto *aEvent = (Event *) malloc(sizeof(Event));
        aEvent->OccurTime = event->OccurTime + interTime;
        aEvent->Type = 0;
        ListInsOrder(events, MakeNode(aEvent), cmp);
    }
    free(event);
}

void CustomerDeparture(Event *event) {
    DataType data;
    int idx = event->Type;
    DeQueue(counters[idx], data);
    auto *customer = (Customer *) data;
    totalTime += event->OccurTime - customer->ArrivedTime;
    free(customer);
    if (!QueueEmpty(counters[idx])) {
        GetHead(counters[idx], data);
        customer = (Customer *) data;
        auto *dEvent = (Event *) malloc(sizeof(Event));
        printf("%d, %d\n", event->OccurTime, customer->Duration);
        dEvent->OccurTime = event->OccurTime + customer->Duration;
        dEvent->Type = idx;
        ListInsOrder(events, MakeNode(dEvent), cmp);
    }
    free(event);
}

void BankSimulation() {
    OpenForDay();
    NodePtr node;
    Event *event;
    while (!ListEmpty(events)) {
        printf("---\n");
        ListTraverse(events, visit);
        printf(("\n"));
        node = ListDelFirst(events);
        event = (Event *) NodeGetData(node);
        FreeNode(node);
        switch (event->Type) {
            case 0:
                CustomerArrive(event);
                break;
            default:
                CustomerDeparture(event);
        }
        for (int i = 1; i <= 4; ++i) {
            printf("counter %d: ", i);
            QueueTraverse(counters[i], visit_q);
            printf("\n");
        }
        ListTraverse(events, visit);
        printf(("\n"));
    }
}

int main() {
    BankSimulation();
    printf("avg time per customer: %d\n", totalTime / customerNum);
}



