//
// Created by steve.zhang on 2023/3/12.
//
#include <cstdio>
#include <cctype>
#include "stack.hpp"

void move(SqStack &a, SqStack &b) {
    int v;
    Pop(a, v);
    Push(b, v);
}

void hanoi(int n, SqStack &x, SqStack &y, SqStack &z) {
    if (n <= 1) {
        move(x, z);
    } else {
        hanoi(n-1, x, z, y);
        move(x, z);
        hanoi(n-1, y, x, z);
    }
}

Status print_e(ElemType e) {
    printf("%c ", e);
    return TRUE;
}

void print_hanoi(SqStack x, SqStack y, SqStack z) {
    printf("x: ");
    StackTraverse(x, print_e);
    printf("\n");

    printf("y: ");
    StackTraverse(y, print_e);
    printf("\n");

    printf("z: ");
    StackTraverse(z, print_e);
    printf("\n");
}

int main() {
    SqStack x, y, z;
    InitStack(x);
    InitStack(y);
    InitStack(z);

    int c;
    int n = 0;
    while((c = getchar()) != EOF && c != '\n') {
        if (!isspace(c)) {
            Push(x, c);
            ++n;
        }
    }

    print_hanoi(x, y, z);
    hanoi(n, x, y, z);
    print_hanoi(x, y, z);

    return 0;
}
