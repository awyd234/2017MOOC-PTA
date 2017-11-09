//
//  main.c
//  009-排序3 Insertion or Heap Sort  https://pintia.cn/problem-sets/900290821590183936/problems/924489079524941824
//
//  Created by Qian Hu on 2017/11/9.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 110

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void show(int array[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        printf("%d ", array[i]);
    }
    printf("%d\n", array[n - 1]);
}

int main(int argc, const char * argv[]) {
    int n, tmp, i, j, k;

    int initial[MAX_SIZE];
    int partial[MAX_SIZE];
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        scanf("%d", &initial[i]);
    }
    
    for (i = 0; i < n; i++) {
        scanf("%d", &partial[i]);
    }
    
    for (i = 1; i < n && partial[i] >= partial[i - 1]; i++) {
    }
    
    for (j = i; j < n && partial[j] == initial[j]; j++) {
    }
    
    if (j == n) {
        printf("Insertion Sort\n");
        tmp = partial[i];
        for ( j = i; j > 0; j--) {
            if (partial[j - 1] > tmp ) {
                partial[j] = partial[j - 1];
            } else {
                break;
            }
        }
        partial[j] = tmp;
        show(partial, n);
    } else {
        printf("Heap Sort\n");
        for (i = 0; i < n && partial[i] <= partial[0]; i++) {
        }
        i--;
        tmp = partial[i];
        partial[i] = partial[0];
        for (j = 0; j * 2 < i; j = k) {
            k = 2 * j + 1;
            if (k + 1 < i && partial[k + 1]  > partial[k]) {
                k++;
            }
            if (tmp >= partial[k]) {
                break;
            } else {
                partial[j] = partial[k];
            }
        }
        partial[j] = tmp;
        show(partial, n);
    }
    
    return 0;
}

