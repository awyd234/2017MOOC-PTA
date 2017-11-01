//
//  main.cpp
//  03-2
//
//  Created by Qian Hu on 2017/10/23.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>

using namespace std;

#define ElementType char
#define MaxTree 10
#define Tree int
#define Null -1

typedef struct TreeNode {
    Tree left;
    Tree right;
} TreeNode;

Tree buildTree(TreeNode t[]) {
    int i, n;
    Tree root;
    int check[MaxTree];
    ElementType cl, cr;
    cin >> n;
    if (n) {
        for (i = 0; i < n; i++) {
            check[i] = 0;
        }
        
        for (i = 0; i < n; i++) {
            cin >> cl >> cr;
            if (cl != '-') {
                t[i].left = cl - '0';
                check[t[i].left] = 1;
            } else {
                t[i].left = Null;
            }
            if (cr != '-') {
                t[i].right = cr - '0';
                check[t[i].right] = 1;
            } else {
                t[i].right = Null;
            }
        }
        
        for (i = 0; i < n; i++) {
            if (!check[i]) {
                break;
            }
        }
        root = i;
    } else {
        root = Null;
    }
    return root;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    TreeNode tree[MaxTree];
    int queue[MaxTree];
    int head = 0, rear = -1;
    int p;
    bool flag = false;
    Tree root;
    root = buildTree(tree);
    queue[++rear] = root;
    while (rear - head != -1) {
        p = queue[head++];
        if (tree[p].left == Null && tree[p].right == Null) {
            if (flag) {
                cout << " ";
            } else {
                flag = true;
            }
            cout << p;
            continue;
        }
        if (tree[p].left != Null) {
            queue[++rear] = tree[p].left;
        }
        if (tree[p].right != Null) {
            queue[++rear] = tree[p].right;
        }
    }
    return 0;
}
