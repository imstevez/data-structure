//
// Created by steve.zhang on 2023/3/13.
//

#ifndef DATA_STRUCTURE_QUEUE_HPP
#define DATA_STRUCTURE_QUEUE_HPP

#include "status.hpp"
#include "data_type.hpp"

typedef struct QNode {
    DataType data;
    QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
} Queue;

Status InitQueue(Queue &Q);
Status DestroyQueue(Queue &Q);
Status ClearQueue(Queue &Q);
Status QueueEmpty(Queue Q);
int QueueLength(Queue Q);
Status GetHead(Queue Q, DataType &data);
Status EnQueue(Queue &Q, DataType data);
Status DeQueue(Queue &Q, DataType &data);
Status QueueTraverse(Queue Q, Status (* visit)(DataType));
void PrintQueue(Queue Q);

#endif //DATA_STRUCTURE_QUEUE_HPP
