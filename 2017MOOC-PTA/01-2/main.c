//
//  main.c
//  01-复杂度2 Maximum Subsequence Sum  https://pintia.cn/problem-sets/900290821590183936/problems/900291257604861953
//  这题是要输出数字，而非索引
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>

#define MAX_SIZE 10010

void maxSubSequence(int data[], int n) {
    int thisSum, maxSum;
    int i;
    int begin = 0, end = 0;
    int this_begin = 0;
    thisSum = maxSum = 0;
    int flag = 1;
    for (i = 0; i < n; i++) {
        thisSum += data[i];
        if (thisSum > maxSum) {
            flag = 0;
            maxSum = thisSum;
            begin = this_begin;
            end = i;
        } else if (thisSum < 0) {
            thisSum = 0;
            this_begin = i + 1;
        } else if (thisSum == 0 && begin == 0) {
            flag = 0;
            end = begin = i;
        }
    }
    if (flag) {
        end = n - 1;
    }
    printf("%d %d %d\n", maxSum, data[begin], data[end]);
}

int main(int argc, const char * argv[]) {
    int n;
    int data[MAX_SIZE];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }
    
    maxSubSequence(data, n);
    
    return 0;
}
