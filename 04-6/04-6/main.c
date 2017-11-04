//
//  main.c
//  04-树6 Complete Binary Search Tree https://pintia.cn/problem-sets/900290821590183936/problems/911438665550655488
//
//  Created by Qian Hu on 2017/11/4.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1010

void bubleSort(int old[], int n) {
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        int flag = 1;
        for (int j = 0; j < n - i; j++) {
            if (old[j] < old[j - 1]) {
                flag = 0;
                tmp = old[j];
                old[j] = old[j - 1];
                old[j - 1] = tmp;
            }
        }
        if (flag) {
            break;
        }
    }
}

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int newTree[MAX_SIZE];

int getLeftLength(int n) {
    if (n == 1) {
        return 0;
    }
    int l = 1;
    int height = 0;
    int x;
    while (l < n + 1) {
        height += 1;
        l *= 2;
    }
    x = n + 1 - l / 2;
    if (x > l / 4) {
        x = l /4;
    }
    //printf("%d %d\n", n, x + l / 4 - 1);
    return x + l / 4 - 1;
}

void cbt(int old[], int left, int right, int root) {
    int n = right - left + 1;
    if (n == 0) {
        return;
    }
    int length = getLeftLength(n);
    newTree[root] = old[left + length];
    int leftRoot = root * 2 + 1;
    int rightRoot = leftRoot + 1;
    cbt(old, left, left + length - 1, leftRoot);
    cbt(old, left + length + 1, right, rightRoot);
}

int main(int argc, const char * argv[]) {
    int n;
    int old[MAX_SIZE];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &old[i]);
    }
    //bubleSort(old, n);
    qsort(old, n, sizeof(int), compare);
    cbt(old, 0, n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", newTree[i]);
    }
    printf("%d\n", newTree[n - 1]);
    return 0;
}
