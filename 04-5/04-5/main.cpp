//
//  main.cpp
//  04-5
//
//  Created by Qian Hu on 2017/10/30.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>
#define ElemType int

using namespace std;
typedef struct AVLNode {
    ElemType data;
    AVLNode *left;
    AVLNode *right;
    int height;
} AVLNode, *AVLTree;

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(AVLTree tree) {
    if (tree == NULL) {
        return -1;
    }
    return max(getHeight(tree->left), getHeight(tree->right)) + 1;
}

AVLTree singleLeftRotation(AVLTree atree) {
    AVLTree btree = atree->left;
    atree->left = btree->right;
    btree->right = atree;
    atree->height = max(getHeight(atree->left), getHeight(atree->right)) + 1;
    btree->height = max(getHeight(btree->left), getHeight(btree->right)) + 1;
    return btree;
}

AVLTree singleRightRotation(AVLTree atree) {
    AVLTree btree = atree->right;
    atree->right = btree->left;
    btree->left = atree;
    atree->height = max(getHeight(atree->left), getHeight(atree->right)) + 1;
    btree->height = max(getHeight(btree->left), getHeight(btree->right)) + 1;
    return btree;
}

AVLTree doubleLeftRightRotation(AVLTree tree) {
    tree->left = singleRightRotation(tree->left);
    return singleLeftRotation(tree);
}

AVLTree doubleRightLeftRotation(AVLTree tree) {
    tree->right = singleLeftRotation(tree->right);
    return singleRightRotation(tree);
}

AVLTree insert(AVLTree tree, ElemType x) {
    if (!tree) {
        tree = (AVLTree)malloc(sizeof(AVLNode));
        tree->data = x;
        tree->left = tree->right = NULL;
        tree->height = 0;
    } else if (x < tree->data) {
        tree->left = insert(tree->left, x);
        if (getHeight(tree->left) - getHeight(tree->right) == 2) {
            if (x < tree->left->data) {
                tree = singleLeftRotation(tree);
            } else {
                tree = doubleLeftRightRotation(tree);
            }
        }
    } else if (x > tree->data) {
        tree->right = insert(tree->right, x);
        if (getHeight(tree->right) - getHeight(tree->left) == 2) {
            if (x > tree->right->data) {
                tree = singleRightRotation(tree);
            } else {
                tree = doubleRightLeftRotation(tree);
            }
        }
    }
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
    return tree;
}

int main(int argc, const char * argv[]) {
    int n;
    AVLTree tree;
    ElemType e;
    cin >> n;
    while(n--) {
        cin >> e;
        tree = insert(tree, e);
    }
    cout << tree->data << endl;
    return 0;
}
