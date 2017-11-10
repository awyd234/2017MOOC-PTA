//
//  main.c
//  1001. 害死人不偿命的(3n+1)猜想  https://www.patest.cn/contests/pat-b-practise/1001
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int n;
    int count = 0;
    scanf("%d", &n);
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = (3 * n + 1)/2;
        }
        count++;
    }
    printf("%d\n", count);
    return 0;
}
