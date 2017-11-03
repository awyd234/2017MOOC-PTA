//
//  main.c
//  05-8
//
//  Created by Qian Hu on 2017/11/2.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#define ElementType int
#define MAX_SIZE 10010

typedef struct SetNode {
    ElementType data;
    int parent;
} SetNode;

typedef int SetName;
typedef ElementType SetType[MAX_SIZE];

SetName setFind(SetType s, ElementType x) {
    if (s[x] < 0) {
        return x;
    } else {
        return s[x] = setFind(s, s[x]);
    }
}

void setUnion(SetType s, SetName root1, SetName root2) {
    if (s[root1] < s[root2]) {
        s[root1] += s[root2];
        s[root2] = root1;
    } else {
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

void setInitial(SetType s, int n) {
    for (int i = 0; i < n; i++) {
        s[i] = -1;
    }
}

void inputConnection(SetType s) {
    ElementType u, v;
    SetName root1, root2;
    scanf("%d %d", &u, &v);
    root1 = setFind(s, u - 1);
    root2 = setFind(s, v - 1);
    if (root1 != root2) {
        setUnion(s, root1, root2);
    }
}

void checkConnection(SetType s) {
    ElementType u, v;
    SetName root1, root2;
    scanf("%d %d", &u, &v);
    root1 = setFind(s, u - 1);
    root2 = setFind(s, v - 1);
    if (root1 == root2) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
}

void checkNetwork(SetType s, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] < 0) {
            count ++;
        }
    }
    if (count == 1) {
        printf("The network is connected.\n");
    } else {
        printf("There are %d components.\n", count);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    SetType s;
    int n;
    char in;
    scanf("%d\n", &n);
    setInitial(s, n);
    do {
        scanf("%c", &in);
        switch (in) {
            case 'I':
                inputConnection(s);
                break;
            case 'C':
                checkConnection(s);
                break;
            case 'S':
                checkNetwork(s, n);
                break;
        }
    } while (in != 'S');
    return 0;
}

int oldFind(SetNode s[], ElementType x) {
    int i = 0;
    for (; i < MAX_SIZE && s[i].data != x; i++);
    if ( i > MAX_SIZE) {
        return -1;
    }
    for (; s[i].parent >= 0; i = s[i].parent);
    return i;
}
