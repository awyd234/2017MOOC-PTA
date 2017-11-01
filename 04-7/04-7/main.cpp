#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;
    
    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    //printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    //printf("Inorder:"); InorderTraversal(BST); printf("\n");
    
    return 0;
}

BinTree Insert( BinTree BST, ElementType X ) {
    Position position = BST;
    BinTree node = (BinTree)malloc(sizeof(struct TNode));
    node->Data = X;
    node->Left = node->Right = NULL;
    if (!position) {
        BST = node;
        return BST;
    }
    while (position) {
        if (X < position->Data) {
            if (position->Left) {
                position = position->Left;
            } else {
                position->Left = node;
                break;
            }
        } else if (X > position->Data) {
            if (position->Right) {
                position = position->Right;
            } else {
                position->Right = node;
                break;
            }
        }
    }
    return BST;
}

BinTree Delete( BinTree BST, ElementType X ) {
    Position position = Find(BST, X);
    Position another_position;
    if (!position) {
        printf("Not Found\n");
        return BST;
    }
    if (position->Left) {
        another_position = FindMax(position->Left);
        position->Data = another_position->Data;
        free(another_position);
    } else if (position->Right) {
        another_position = FindMin(position->Right);
        position->Data = another_position->Data;
        free(another_position);
    } else {
        free(position);
    }
    
    return BST;
}

Position Find( BinTree BST, ElementType X ) {
    Position position = BST;
    while(position) {
        if (X < position->Data) {
            position = position->Left;
        } else if (X > position->Data) {
            position = position->Right;
        } else {
            break;
        }
    }
    return position;
}

Position FindMin( BinTree BST ) {
    Position position = BST;
    if(!position) {
        return position;
    }
    while(position->Left) {
        position = position->Left;
    }
    return position;
}

Position FindMax( BinTree BST ) {
    Position position = BST;
    if(!position) {
        return position;
    }
    while(position->Right) {
        position = position->Right;
    }
    return position;
}
/* 你的代码将被嵌在这里 */
