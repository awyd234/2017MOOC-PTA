//
//  main.c
//  08-图8 How Long Does It Take  https://pintia.cn/problem-sets/900290821590183936/problems/921717982744133632
//
//  Created by Qian Hu on 2017/11/7.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 110
#define INFINITY 65535

typedef int Vetex;
typedef int WeightType;
typedef char DataType;

typedef struct ENode {
    Vetex v1, v2;
    WeightType weight;
} ENode, *Edge, *PtrToENode;

typedef struct AdjVNode {
    Vetex adjV;
    WeightType weight;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjVNode;

typedef struct VNode {
    PtrToAdjVNode firstEdge;
    DataType data;
    int earlist;
} AdjList[MAX_VERTEX_NUM];

typedef struct GNode {
    int nv;
    int ne;
    AdjList g;
} GNode, *LGraph;

LGraph createGraph(int vertexNum) {
    Vetex v;
    LGraph graph;
    
    graph = (LGraph)malloc(sizeof(GNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    
    for (v = 0; v < graph->nv; v++) {
        graph->g[v].firstEdge = NULL;
        graph->g[v].earlist = INFINITY;
    }
    
    return graph;
}

void insertEdge(LGraph graph, Edge e) {
    PtrToAdjVNode newNode;
    
    newNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
    newNode->adjV = e->v2;
    newNode->weight = e->weight;
    newNode->next = graph->g[e->v1].firstEdge;
    graph->g[e->v1].firstEdge = newNode;
    
    /*newNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
    newNode->adjV = e->v1;
    newNode->weight = e->weight;
    newNode->next = graph->g[e->v2].firstEdge;
    graph->g[e->v2].firstEdge = newNode;*/
}

LGraph buildGraph() {
    LGraph graph;
    Edge e;
    Vetex v;
    int nv, i;
    
    scanf("%d", &nv);
    graph = createGraph(nv);
    
    scanf("%d", &graph->ne);
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        for (i = 0; i < graph->ne; i++) {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            insertEdge(graph, e);
        }
    }
    
    /*for (v = 0; v < graph->nv; v++) {
        scanf("%c", &graph->g[v].data);
    }*/
    
    return graph;
}

int topSort(LGraph graph, Vetex topOrder[]) {
    int indegree[MAX_VERTEX_NUM], count;
    Vetex v;
    PtrToAdjVNode w;
    
    int queue[MAX_VERTEX_NUM];
    int front = 0;
    int tail = 0;
    
    for (v = 0; v < graph->nv; v++) {
        indegree[v] = 0;
    }
    
    for (v = 0; v < graph->nv; v++) {
        for (w = graph->g[v].firstEdge; w; w = w->next) {
            indegree[w->adjV]++;
        }
    }
    
    for (v = 0; v < graph->nv; v++) {
        if (indegree[v] == 0) {
            queue[tail++] = v;
            graph->g[v].earlist = 0;
        }
    }
    
    count = 0;
    while (front != tail) {
        v = queue[front++];
        topOrder[count++] = v;
        for (w = graph->g[v].firstEdge; w; w = w->next) {
            if (--indegree[w->adjV] == 0) {
                queue[tail++] = w->adjV;
                if (graph->g[v].earlist + w->weight < graph->g[w->adjV].earlist) {
                    graph->g[w->adjV].earlist = graph->g[v].earlist + w->weight;
                }
            }
        }
    }
    
    if (count != graph->nv) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, const char * argv[]) {
    LGraph graph;
    int topOrder[MAX_VERTEX_NUM];
    graph = buildGraph();
    if (topSort(graph, topOrder)) {
        int maxEarlist = -1;
        for (Vetex v = 0; v < graph->nv; v++) {
            if (graph->g[v].earlist > maxEarlist) {
                maxEarlist = graph->g[v].earlist;
            }
        }
        printf("%d\n", maxEarlist);
    } else {
        printf("Impossible\n");
    }
    
    return 0;
}
