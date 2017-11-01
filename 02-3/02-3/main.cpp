#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PtrNode {
    char nextAddress[6];
    char address[6];
    int data;
    struct PtrNode *next;
} PtrNode, *Ptr;

Ptr reverse(Ptr head, int k, int n) {
    int round = n / k;
    Ptr newNode, returnHeadNode;
    Ptr oldNode, tmpNode;
    returnHeadNode = head;
    newNode = head->next;
    oldNode = newNode->next;
    while (round--) {
        int count = 1 ;
        while (count < k) {
            tmpNode = oldNode->next;
            oldNode->next = newNode;
            newNode = oldNode;
            oldNode = tmpNode;
            count++;
        }
        head->next->next = oldNode;
        head->next = newNode;
        while (count--) {
            head = head->next;
        }
        if (oldNode) {
            newNode = oldNode;
            oldNode = oldNode->next;
        }
    }
    return returnHeadNode->next;
}

void swap(PtrNode *nodeList, int index1, int index2) {
    PtrNode tmp;
    tmp = nodeList[index1];
    nodeList[index1] = nodeList[index2];
    nodeList[index2] = tmp;
}

int main()
{
    int n, k;
    Ptr ptr_point;
    Ptr ptrHead = (Ptr)malloc(sizeof(PtrNode));
    scanf("%s %d %d", ptrHead->nextAddress, &n, &k);
    Ptr ptr = (Ptr)malloc(sizeof(PtrNode) * n);
    for (int i = 0; i < n; i++) {
        scanf("%s%d%s", ptr[i].address, &ptr[i].data, ptr[i].nextAddress);
    }
    ptr_point = ptrHead;
    int this_length = -1;
    while(1) {
        for (int i = this_length + 1; i < n; i++) {
            if (strcmp(ptr_point->nextAddress, ptr[i].address) == 0) {
                ptr_point->next = &ptr[i];
                ptr_point = ptr_point->next;
                this_length++;
                swap(ptr, i, this_length);
                ptr_point = &ptr[this_length];
                break;
            }
        }
        if (strcmp(ptr_point->nextAddress, "-1") == 0) {
            ptr_point->next = NULL;
            break;
        }
    }
    ptrHead->next = ptr;
    for (int i = 0; i < this_length; i++) {
        ptr[i].next = &ptr[i + 1];
    }
    ptr_point = reverse(ptrHead, k, this_length + 1);
    while (ptr_point) {
        printf("%s %d ", ptr_point->address, ptr_point->data);
        if (ptr_point->next) {
            printf("%s\n", ptr_point->next->address);
        } else {
            printf("-1\n");
        }
        ptr_point = ptr_point->next;
    }
    return 0;
}
