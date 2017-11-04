//
//  main.c
//  03-树3 Tree Traversals Again https://pintia.cn/problem-sets/900290821590183936/problems/909063377378181120
//
//  Created by Qian Hu on 2017/11/4.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 32

void buildTree(int pre[], int in[], int n) {
    int stack[MAX_SIZE];
    int top = 0;
    char action[6];
    int num;
    int preIndex = 0;
    for (int i = 0; i < n; ){
        scanf("%s %d", action, &num);
        if (strcmp(action, "Push") == 0) {
            pre[preIndex++] = num;
            stack[top++] = num;
        } else if (strcmp(action, "Pop") == 0) {
            top--;
            in[i] = stack[top];
            i++;
        }
    }
}

void solve(int preL, int inL, int postL, int n, int pre[], int in[], int post[]) {
    if (n == 0) {
        return;
    } else if (n == 1) {
        post[postL] = pre[preL];
        return;
    }
    int root = pre[preL];
    int i;
    int l, r;
    post[postL + n - 1] = root;
    for (i = 0; i < n; i++) {
        if ( in[inL + i] == root ) {
            break;
        }
    }
    l = i;
    r = n - l - 1;
    solve(preL + 1, inL, postL, l, pre, in, post);
    solve(preL + l + 1, inL + l + 1, postL + l, r, pre, in, post);
    
}

int main(int argc, const char * argv[]) {
    int in[MAX_SIZE];
    int pre[MAX_SIZE];
    int post[MAX_SIZE];
    int n, i;
    scanf("%d", &n);
    buildTree(pre, in, n);
    solve(0, 0, 0, n, pre, in, post);
    for (i = 0; i < n - 1; i++) {
        printf("%d ", post[i]);
    }
    printf("%d\n", post[i]);
    
    return 0;
}
