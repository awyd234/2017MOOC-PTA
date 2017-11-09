//
//  main.c
//  09-排序1 排序  https://pintia.cn/problem-sets/900290821590183936/problems/924488938671824896
//
//  Created by Qian Hu on 2017/11/8.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void swap(int data[], int i, int j) {
    int tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

void bubbleSort(int data[], int n) {
    
}

int main(int argc, const char * argv[]) {
    int *data;
    int n;
    scanf("%d", &n);
    data = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }
    qsort(data, n, sizeof(int), cmp);
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", data[i]);
    }
    printf("%d\n", data[n - 1]);
    return 0;
}
