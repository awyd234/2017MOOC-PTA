//
//  main.cpp
//  04-4
//
//  Created by Qian Hu on 2017/10/30.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left, *right;
    bool flag;
} TreeNode, *Tree;

Tree newNode(int v) {
    Tree tree = (Tree)malloc(sizeof(TreeNode));
    tree->val = v;
    tree->left = tree->right = NULL;
    tree->flag = false;
    return tree;
}

Tree insert(Tree tree, int v) {
    if(!tree) {
        tree = newNode(v);
    } else {
        if (v > tree->val) {
            tree->right = insert(tree->right, v);
        } else {
            tree->left = insert(tree->left, v);
        }
    }
    return tree;
}

Tree makeTree(int n) {
    Tree tree;
    int v;
    cin >> v;
    tree = newNode(v);
    for (int i = 1; i < n; i++) {
        cin >> v;
        tree = insert(tree, v);
    }
    return tree;
}

bool check(Tree tree, int v) {
    if (tree->flag) {
        if (v < tree->val) {
            return check(tree->left, v);
        } else if (v > tree->val) {
            return check(tree->right, v);
        } else {
            return false;
        }
    } else {
        if (v == tree->val) {
            tree->flag = true;
            return true;
        } else {
            return false;
        }
    }
}

bool judge(Tree tree, int n) {
    int v, this_flag =  false;
    cin >> v;
    if (v != tree->val) {
        this_flag = true;
    } else {
        tree->flag = true;
    }
    for (int i = 1; i < n; i++) {
        cin >> v;
        if ((!this_flag) && (!check(tree, v))) {
            this_flag = true;
        }
    }
    if (this_flag) {
        return false;
    } else {
        return true;
    }
}

void reset(Tree tree) {
    if (tree->left) {
        reset(tree->left);
    }
    if (tree->right) {
        reset(tree->right);
    }
    tree->flag = false;
}

void freeTree(Tree tree) {
    if (tree->left) {
        freeTree(tree->left);
    }
    if (tree->right) {
        freeTree(tree->right);
    }
    free(tree);
}

int main(int argc, const char * argv[]) {
    int n, l;
    Tree tree;
    cin >> n;
    while (n) {
        cin >> l;
        tree = makeTree(n);
        for (int i = 0; i < l; i++) {
            if (judge(tree, n)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
            reset(tree);
        }
        freeTree(tree);
        cin >> n;
    }
    return 0;
}
