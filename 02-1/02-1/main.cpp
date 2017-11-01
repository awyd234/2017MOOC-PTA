//
//  main.cpp
//  02-1
//
//  Created by Qian Hu on 2017/10/16.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read() {
    int n, c;
    PtrToNode rear;
    List newList = (List)malloc(sizeof(Node));
    rear = newList;
    scanf("%d", &n);
    while (n --) {
        PtrToNode p = (PtrToNode)malloc(sizeof(struct Node));
        scanf("%d", &c);
        p->Next = NULL;
        p->Data = c;
        rear->Next = p;
        rear = rear->Next;
    }
    return newList;
}
void Print( List L ) {
    while (L->Next) {
        printf("%d ", L->Next->Data);
        L = L->Next;
    }
    printf("\n");
}

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge( List L1, List L2 ) {
    List newList, temp;
    PtrToNode p, t1, t2, q1, q2;
    newList = (List)malloc(sizeof(struct Node));
    newList->Next = NULL;
    temp = newList;
    t1 = L1->Next;
    t2 = L2->Next;
    while (t1 && t2) {
        if (t1->Data > t2->Data) {
            p = t2;
            temp->Next = p;
            temp = temp->Next;
            t2 = t2->Next;
        } else {
            p = t1;
            temp->Next = p;
            temp = temp->Next;
            t1 = t1->Next;
        }
    }
    if (t1) {
        temp->Next = t1;
    }
    if (t2) {
        temp->Next = t2;
    }
    L1->Next = NULL;
    L2->Next = NULL;
    return newList;
}

