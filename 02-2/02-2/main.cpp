//
//  main.cpp
//  02-2
//
//  Created by Qian Hu on 2017/10/9.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <iostream>
using namespace std;

typedef struct PolyNode {
    int coef;
    int expon;
    PolyNode *link;
} PolyNode, *Polynomial;

void attach(int c, int e, Polynomial *pRear) {
    Polynomial p;
    p = (Polynomial) malloc(sizeof(PolyNode));
    p->coef = c;
    p->expon = e;
    p->link = NULL;
    (*pRear)->link = p;
    *pRear = p;
}

Polynomial readPoly() {
    int n, c, e;
    Polynomial p, rear, temp;
    
    cin >> n;
    p = (Polynomial)malloc(sizeof(PolyNode));
    p->link = NULL;
    rear = p;
    while(n--) {
        cin >> c >> e;
        attach(c, e, &rear);
    }
    temp = p;
    p = p->link;
    free(temp);
    return p;
}

Polynomial calculateSum(Polynomial p1, Polynomial p2) {
    Polynomial p, t1, t2, rear, temp;
    t1 = p1;
    t2 = p2;
    p = (Polynomial)malloc(sizeof(PolyNode));
    p->link = NULL;
    rear = p;
    while (t1 && t2) {
        if (t1->expon == t2->expon) {
            if (t1->coef + t2->coef != 0) {
                attach(t1->coef + t2->coef, t1->expon, &rear);
            }
            t1 = t1->link;
            t2 = t2->link;
        } else if (t1->expon > t2->expon) {
            attach(t1->coef, t1->expon, &rear);
            t1 = t1->link;
        } else {
            attach(t2->coef, t2->expon, &rear);
            t2 = t2->link;
        }
    }
    
    while(t1) {
        attach(t1->coef, t1->expon, &rear);
        t1 = t1->link;
    }
    
    while(t2) {
        attach(t2->coef, t2->expon, &rear);
        t2 = t2->link;
    }
    
    temp = p;
    p = p->link;
    free(temp);
    return p;
}

Polynomial calculateMulti(Polynomial p1, Polynomial p2) {
    Polynomial p, t1, t2, rear, t;
    int c, e;
    
    if (!p1 || !p2) {
        return NULL;
    }
    
    t1 = p1;
    t2 = p2;
    p = (Polynomial)malloc(sizeof(PolyNode));
    p->link = NULL;
    rear = p;
    while (t2) {
        attach(t1->coef * t2->coef, t1->expon + t2->expon, &rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while (t1) {
        t2 = p2;
        rear = p;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (rear->link && rear->link->expon > e) {
                rear = rear->link;
            }
            if (rear->link && rear->link->expon == e) {
                if (rear->link->coef + c) {
                    rear->link->coef += c;
                } else {
                    t = rear->link;
                    rear->link = t->link;
                    free(t);
                }
            } else {
                t = (Polynomial)malloc(sizeof(PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = rear->link;
                rear->link = t;
                rear = rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = p;
    p = p->link;
    free(t2);
    
    return p;
}

void printPoly(Polynomial p) {
    Polynomial rear;
    bool flag = false;
    if (!p) {
        cout << "0 0" << endl;
        return;
    }
    rear = p;
    while (rear) {
        if (!flag) {
            flag = true;
        } else {
            cout << " ";
        }
        cout << rear->coef << " " << rear->expon;
        rear = rear->link;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Polynomial polyA, polyB, polyMulti, polySum;
    
    polyA = readPoly();
    polyB = readPoly();
    
    polyMulti = calculateMulti(polyA, polyB);
    printPoly(polyMulti);
    
    polySum = calculateSum(polyA, polyB);
    printPoly(polySum);
    
    
    return 0;
}
