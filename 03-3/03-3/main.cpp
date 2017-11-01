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
    int n;
    string action;
    cin >> n;
    while (n--) {
        cin >> action;
        if action
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

