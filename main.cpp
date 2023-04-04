#include <stdlib.h>
#include <stdio.h>
#include "polynomail.hpp"

int main(void) {
    Polynomail polyn1, polyn2;

    printf("输入第一个多项式的项以回车(Enter)结束: ");
    if (!CreatePolyn(polyn1)) return 1;
    printf("第一项: ");
    PrintPolyn(polyn1);
    printf("\n");

    printf("输入第二个多项式的项以回车(Enter)结束: ");
    if (!CreatePolyn(polyn2)) return 1;
    printf("第二项: ");
    PrintPolyn(polyn2);
    printf("\n");

    AddPolyn(polyn1, polyn2);
    printf("相加得: ");
    PrintPolyn(polyn1);
    printf("\n");

    return 0;
}