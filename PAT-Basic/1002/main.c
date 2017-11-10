//
//  main.c
//  1002. 写出这个数  https://www.patest.cn/contests/pat-b-practise/1002
//
//  Created by Qian Hu on 2017/11/10.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int total = 0;
    int result[3];
    int count = 0;
    char chinese[10][20] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    char c;
    while ((c = getchar()) != '\n') {
        total += c - '0';
    }
    while (total > 0) {
        result[count++] = total % 10;
        total /= 10;
    }
    for (int i = count - 1; i > 0; i--) {
        printf("%s ", chinese[result[i]]);
    }
    printf("%s\n", chinese[result[0]]);
    return 0;
}
