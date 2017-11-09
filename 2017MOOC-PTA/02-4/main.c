//
//  main.c
//  02-线性结构4 Pop Sequence  https://pintia.cn/problem-sets/900290821590183936/problems/906377222682353664
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>

#define MAX_SIZE 1010

int main(int argc, const char * argv[]) {
    int capacity, n, k, num;
    int stack[MAX_SIZE];
    int top;
    scanf("%d %d %d", &capacity, &n, &k);
    for (int iIndex = 0; iIndex < k; iIndex++) {
        top = 0;
        int flag = 1;
        int normal = 1;
        for (int j = 0; j < n; j++) {
            scanf("%d", &num);
            //printf("%d ---- %d\n", iIndex, num);
            if (flag) {
                while (top == 0 || stack[top - 1] != num) {
                    stack[top++] = normal;
                    if (top > capacity) {
                        flag = 0;
                        break;
                    }
                    normal++;
                }
                if (flag) {
                    top--;
                }
            }
        }
        if (flag) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
