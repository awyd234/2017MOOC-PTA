//
//  main.c
//  08-图9 关键活动  https://pintia.cn/problem-sets/900290821590183936/problems/921718060988874752
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
    int earlist;
    int latest;
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
    
    for (v = 1; v < graph->nv + 1; v++) {
        graph->g[v].firstEdge = NULL;
        graph->g[v].latest = INFINITY;
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

LGraph reverseGraph;
LGraph buildGraph() {
    LGraph graph;
    Edge e, reverseE;
    int nv, i;
    
    scanf("%d", &nv);
    graph = createGraph(nv);
    reverseGraph = createGraph(nv);
    
    scanf("%d", &graph->ne);
    reverseGraph->ne = graph->ne;
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        reverseE = (Edge)malloc(sizeof(ENode));
        for (i = 0; i < graph->ne; i++) {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            insertEdge(graph, e);
            
            reverseE->v1 = e->v2;
            reverseE->v2 = e->v1;
            reverseE->weight = e->weight;
            insertEdge(reverseGraph, reverseE);
        }
    }
    
    /*for (v = 0; v < graph->nv; v++) {
     scanf("%c", &graph->g[v].data);
     }*/
    
    return graph;
}

void topSort(LGraph graph, Vetex topOrder[]) {
    int indegree[MAX_VERTEX_NUM], count;
    int outdegree[MAX_VERTEX_NUM];
    Vetex v;
    PtrToAdjVNode w;
    
    int queue[MAX_VERTEX_NUM];
    int front = 0;
    int tail = 0;
    
    for (v = 1; v < graph->nv + 1; v++) {
        indegree[v] = 0;
        outdegree[v] = 0;
        graph->g[v].earlist = 0;
    }
    
    for (v = 1; v < graph->nv + 1; v++) {
        for (w = graph->g[v].firstEdge; w; w = w->next) {
            indegree[w->adjV]++;
        }
    }
    
    for (v = 1; v < graph->nv + 1; v++) {
        if (indegree[v] == 0) {
            queue[tail++] = v;
        }
    }
    
    count = 0;
    while (front != tail) {
        v = queue[front++];
        topOrder[count++] = v;
        for (w = graph->g[v].firstEdge; w; w = w->next) {
            if (--indegree[w->adjV] == 0) {
                queue[tail++] = w->adjV;
            }
            if (graph->g[v].earlist + w->weight > graph->g[w->adjV].earlist) {
                graph->g[w->adjV].earlist = graph->g[v].earlist + w->weight;
            }
        }
    }
    
    if (count != graph->nv) {
        printf("0\n");
        return;
    }
    
    int maxEarlist = -1;
    for (v = 1; v <= graph->nv; v++) {
        if (graph->g[v].earlist > maxEarlist) {
            maxEarlist = graph->g[v].earlist;
        }
    }
    printf("%d\n", maxEarlist);
    front = tail = 0;
    
    for (v = 1; v < reverseGraph->nv + 1; v++) {
        for (w = reverseGraph->g[v].firstEdge; w; w = w->next) {
            ++outdegree[w->adjV];
        }
    }
    
    for (v = 1; v < reverseGraph->nv + 1; v++) {
        if (!outdegree[v]) {
            reverseGraph->g[v].latest = maxEarlist;
            queue[tail++] = v;
        }
    }
    
    while (front != tail) {
        v = queue[front++];
        for (w = reverseGraph->g[v].firstEdge; w; w = w->next) {
            if (--outdegree[w->adjV] == 0) {
                queue[tail++] = w->adjV;
            }
            if (reverseGraph->g[w->adjV].latest > reverseGraph->g[v].latest - w->weight) {
                reverseGraph->g[w->adjV].latest = reverseGraph->g[v].latest - w->weight;
            }
        }
    }
    
    for (v = 1; v < count; v++) {
        for (w = graph->g[v].firstEdge; w; w = w->next) {
            if (reverseGraph->g[w->adjV].latest - w->weight == graph->g[v].earlist) {
                printf("%d->%d\n", v, w->adjV);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    LGraph graph;
    int topOrder[MAX_VERTEX_NUM];
    
    graph = buildGraph();
    topSort(graph, topOrder);
    
    return 0;
}

