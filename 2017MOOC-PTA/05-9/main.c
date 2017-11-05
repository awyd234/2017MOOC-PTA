//
//  main.c
//  05-树9 Huffman Codes  https://pintia.cn/problem-sets/900290821590183936/problems/914044227287445504
//
//  Created by Qian Hu on 2017/11/4.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 70
char letter[MAX_SIZE];
int weightList[MAX_SIZE];

typedef struct TreeNode {
    int weight;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Tree;

typedef struct MinHeapNode {
    TreeNode *data;
    int size;
    int capacity;
} MinHeapNode, *MinHeap;

MinHeap createMinHeap(int n) {
    MinHeap heap = (MinHeap)malloc(sizeof(MinHeapNode));
    heap->data = (Tree)malloc(sizeof(TreeNode) * (n + 1));
    for (int i = 0; i < n + 1; i ++) {
        heap->data[i].left = NULL;
        heap->data[i].right = NULL;
        heap->data[i].weight = 0;
    }
    heap->size = 0;
    heap->capacity = n + 1;
    heap->data[0].weight = 0;
    return heap;
}

MinHeap readData(MinHeap heap, int n, int weightList[]) {
    int position;
    int weight;
    char ele;
    for (int i = 1; i < n + 1; i++) {
        getchar();
        scanf("%c %d", &ele, &weight);
        weightList[i - 1] = weight;
        letter[i - 1] = ele;
        position = ++heap->size;
        for (; heap->data[position / 2].weight > weight; position /= 2) {
            heap->data[i] = heap->data[i / 2];
        }
        heap->data[position].weight = weight;
    }
    return heap;
}

TreeNode *delMin(MinHeap heap) {
    int parent, child;
    TreeNode x;
    TreeNode *minNode = (TreeNode *)malloc(sizeof(TreeNode));
    *minNode = heap->data[1];
    x = heap->data[heap->size--];
    for (parent = 1; parent * 2 <= heap->size; parent = child) {
        child = parent * 2;
        if ((child < heap->size) && (heap->data[child].weight > heap->data[child + 1].weight)) {
            child++;
        }
        if (x.weight <= heap->data[child].weight) {
            break;
        } else {
            heap->data[parent] = heap->data[child];
        }
    }
    heap->data[parent] = x;
    return minNode;
}

MinHeap insert(MinHeap heap, Tree Tree) {
    int i;
    i = ++heap->size;
    for (; heap->data[i/2].weight > Tree->weight; i/=2) {
        heap->data[i] = heap->data[i / 2];
    }
    heap->data[i] = *Tree;
    return heap;
}

Tree createTree(MinHeap heap) {
    int num = heap->size;
    Tree tree = NULL;
    for (int i = 0; i < num - 1; i++) {
        tree = (Tree)malloc(sizeof(TreeNode));
        tree->left = delMin(heap);
        tree->right = delMin(heap);
        tree->weight = tree->left->weight + tree->right->weight;
        heap = insert(heap, tree);
        
    }
    return tree;
}

int wpl(Tree tree, int depth) {
    if (!tree->left && !tree->right) {
        return depth * tree->weight;
    } else {
        return wpl(tree->left, depth + 1) + wpl(tree->right, depth + 1);
    }
}

int getStrLength(char str[]) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

int count1, count2;
void traverseTree(Tree tree) {
    if (tree) {
        if (tree->left && tree->right) {
            count2++;
        } else if (!tree->left && !tree->right) {
            count1++;
        } else {
            count1 = 0;
        }
        traverseTree(tree->left);
        traverseTree(tree->right);
    }
}

int judge(int n, int codeLen) {
    int this_weight, k;
    int flag = 1;
    char ele;
    char temp[MAX_SIZE];
    Tree judgeNode = (Tree)malloc(sizeof(TreeNode));
    judgeNode->left = NULL;
    judgeNode->right = NULL;
    judgeNode->weight = 0;
    for(int i = 0; i < n; i++) {
        Tree anotherJudgeNode = judgeNode;
        getchar();
        scanf("%c %s", &ele, temp);
        if (getStrLength(temp) > n) {
            flag = 0;
        }
        for(k = 0; ele != letter[k]; k++) {}
        this_weight = weightList[k];
        for (int j = 0; temp[j]; j++) {
            if (temp[j] == '0') {
                if (!anotherJudgeNode->left) {
                    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
                    newNode->left = NULL;
                    newNode->right = NULL;
                    newNode->weight = 0;
                    anotherJudgeNode->left = newNode;
                }
                anotherJudgeNode = anotherJudgeNode->left;
            } else if (temp[j] == '1') {
                if (!anotherJudgeNode->right) {
                    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
                    newNode->left = NULL;
                    newNode->right = NULL;
                    newNode->weight = 0;
                    anotherJudgeNode->right = newNode;
                }
                anotherJudgeNode = anotherJudgeNode->right;
            }
            if(!temp[j + 1]) {
                if (anotherJudgeNode->left || anotherJudgeNode->right) {
                    flag = 0;
                }
                anotherJudgeNode->weight = this_weight;
            }
        }
    }
    if (!flag) {
        return 0;
    }
    count1 = count2 = 0;
    traverseTree(judgeNode);
    if(count1 != count2 + 1) return 0;
    if (wpl(judgeNode, 0) == codeLen) {
        return 1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int m, n;
    scanf("%d", &n);
    Tree tree;
    MinHeap heap = createMinHeap(n);
    heap = readData(heap, n, weightList);
    tree = createTree(heap);
    int codeLen = wpl(tree, 0);
    
    scanf("%d", &m);
    while (m--) {
        if (judge(n, codeLen)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}

