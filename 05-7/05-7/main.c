//
//  main.c
//  05-树7 堆中的路径
//
//  Created by Qian Hu on 2017/11/2.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#define MAXN 1001
#define MINH -10001

int heap[MAXN], size;

void create() {
    size = 0;
    heap[0] = MINH;
}

void insert(int x) {
    int i;
    for (i = ++size; heap[i / 2] > x; i /= 2) {
        heap[i] = heap[i / 2];
    }
    heap[i] = x;
}

int main(int argc, const char * argv[]) {
    int n, m, x, j;
    scanf("%d %d", &n, &m);
    create();
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insert(x);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &j);
        printf("%d", heap[j]);
        while (j > 1) {
            j /= 2;
            printf(" %d", heap[j]);
        }
        printf("\n");
    }
    return 0;
}
