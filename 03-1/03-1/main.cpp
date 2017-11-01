//
//  main.cpp
//  03-1
//
//  Created by Qian Hu on 2017/10/23.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>

using namespace std;

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

typedef struct TreeNode {
    ElementType element;
    Tree left;
    Tree right;
} TreeNode;

TreeNode t1[MaxTree], t2[MaxTree];


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
            cin >> t[i].element >> cl >> cr;
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


int isomorphic(Tree r1, Tree r2) {
    if ((r1 == Null) && r2 == Null) {
        return 1;
    }
    if (((r1 == Null) && (r2 != Null)) || ((r1 != Null) && (r2 == Null))) {
        return 0;
    }
    if (t1[r1].element != t2[r2].element) {
        return 0;
    }
    if ((t1[r1].left == Null) && (t2[r2].left == Null)) {
        return isomorphic(t1[r1].right, t2[r2].right);
    }
    if (((t1[r1].left != Null) && (t2[r2].left != Null)) && ((t1[t1[r1].left].element) == (t2[t2[r2].left].element))) {
        return (isomorphic(t1[r1].left, t2[r2].left) && isomorphic(t1[r1].right, t2[r2].right));
    } else {
        return (isomorphic(t1[r1].left, t2[r2].right) && isomorphic(t1[r1].right, t2[r2].left));
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    Tree r1, r2;
    r1 = buildTree(t1);
    r2 = buildTree(t2);
    
    if (isomorphic(r1, r2)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
