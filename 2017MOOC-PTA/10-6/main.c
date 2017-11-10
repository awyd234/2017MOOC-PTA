//
//  main.c
//  10-排序6 Sort with Swap(0, i)  https://pintia.cn/problem-sets/900290821590183936/problems/926663572338114560
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100010

typedef struct Node {
    int num;
    int flag;
} Node;

int main(int argc, const char * argv[]) {
    int n, num, count;
    int first, this_first;
    Node data[MAX_SIZE];
    int table[MAX_SIZE];
    int s = 0, k = 0;
    Node tmp;
    int another_flag = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        data[i].num = num;
        data[i].flag = 0;
        table[data[i].num] = i;
    }
    if (data[0].num == 0) {
        another_flag = 1;
    }
    for (first = 0; first < n; first++) {
        if (data[first].flag == 1) {
            continue;
        }
        count = 1;
        this_first = first;
        tmp = data[this_first];
        while (tmp.num != this_first) {
            data[this_first] = data[table[this_first]];
            data[this_first].flag = 1;
            //table[data[this_first].num] = this_first;
            this_first = table[this_first];
            count++;
        }
        if (count == 1) {
            s++;
        } else if (count > 1) {
            k++;
        }
        data[this_first] = tmp;
        data[this_first].flag = 1;
    }
    if (another_flag) {
        printf("%d\n", n - s + k);
    } else if (k == 0) {
        printf("0\n");
    } else {
        printf("%d\n", n - s + k - 2);
    }
    
    return 0;
}
