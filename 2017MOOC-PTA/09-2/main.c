//
//  main.c
//  09-排序2 Insert or Merge  https://pintia.cn/problem-sets/900290821590183936/problems/924489002731429888
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

int main(int argc, const char * argv[]) {
    int n, tmp, i, j, k;
    int flag;
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
        for (i = 0; i < n - 1; i++) {
            printf("%d ", partial[i]);
        }
        printf("%d\n", partial[i]);
    } else {
        printf("Merge Sort\n");
        flag = 1;
        for (i = 2; i < n && flag; i *= 2) {
            for (j = 0; j + i < n && flag; j += i) {
                for (k = j; k < j + i - 1; k++) {
                    if (partial[k] > partial[k + 1]) {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        i = i / 2;
        for (j = 0; j + i < n; j += i) {
            qsort(partial + j, i, sizeof(int), cmp);
        }
        if (j != n) {
            qsort(partial + j, n - j, sizeof(int), cmp);
        }
        for (i = 0; i < n - 1; i++) {
            printf("%d ", partial[i]);
        }
        printf("%d\n", partial[i]);
    }
    
    return 0;
}
