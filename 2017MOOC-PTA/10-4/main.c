//
//  main.c
//  10-排序4 统计工龄  https://pintia.cn/problem-sets/900290821590183936/problems/926663413340438528
//  这题没啥好说的，就是简单的桶排序
//
//  Created by Qian Hu on 2017/11/9.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int array[51] = {0};
    int n, input;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &input);
        array[input] ++;
    }
    
    for (int i = 0 ; i <= 50; i++) {
        if (array[i] > 0) {
            printf("%d:%d\n", i, array[i]);
        }
    }
    return 0;
}
