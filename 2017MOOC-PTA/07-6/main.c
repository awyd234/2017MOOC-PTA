//
//  main.c
//  07-图6 旅游规划  https://pintia.cn/problem-sets/900290821590183936/problems/919158334576791552
//
//  Created by Qian Hu on 2017/11/8.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 600
#define INFINITY 65535
#define ERROR -1

typedef int WeightType;
typedef int Vertex;

typedef struct GNode {
    int nv;
    int ne;
    WeightType gCost[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    WeightType gLength[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} GNode, *PtrToGNode;

typedef struct ENode {
    Vertex v1, v2;
    WeightType cost;
    WeightType length;
} ENode, *PtrToENode;

typedef PtrToGNode MGraph;
typedef PtrToENode Edge;

MGraph createGraph(int vertexNum) {
    MGraph graph;
    Vertex v, w;
    
    graph = (MGraph)malloc(sizeof(GNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    
    for (v = 0; v < graph->nv; v++) {
        for(w = 0; w < graph->nv; w++) {
            graph->gCost[v][w] = INFINITY;
            graph->gLength[v][w] = INFINITY;
        }
    }
    return graph;
}

void insertEdge(MGraph graph, Edge e) {
    graph->gCost[e->v1][e->v2] = e->cost;
    graph->gCost[e->v2][e->v1] = e->cost;
    graph->gLength[e->v1][e->v2] = e->length;
    graph->gLength[e->v2][e->v1] = e->length;
}

MGraph buildGraph(Vertex *source, Vertex *target) {
    MGraph graph;
    int n, i;
    Edge e;
    
    scanf("%d", &n);
    graph = createGraph(n);
    scanf("%d", &graph->ne);
    scanf("%d %d", source, target);
    
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        for (i = 0; i < graph->ne; i++) {
            scanf("%d %d %d %d", &e->v1, &e->v2, &e->length, &e->cost);
            insertEdge(graph, e);
        }
    }
    
    return graph;
}

Vertex findMinDist(MGraph graph, WeightType length[], WeightType cost[], int collected[]) {
    Vertex minV, v;
    int minLength = INFINITY;
    int minCost = INFINITY;
    
    for (v = 0; v < graph->nv; v++) {
        if (collected[v] == 0) {
            if (length[v] < minLength) {
                minLength = length[v];
                minCost = cost[v];
                minV = v;
            } else if (length[v] == minLength && cost[v] < minCost) {
                minLength = length[v];
                minCost = cost[v];
                minV = v;
            }
        }
    }
    
    if (minLength < INFINITY && minCost < INFINITY) {
        return minV;
    } else {
        return ERROR;
    }
}

int dijkstra(MGraph graph, Vertex source, Vertex target) {
    int collected[MAX_VERTEX_NUM];
    WeightType cost[MAX_VERTEX_NUM];
    WeightType length[MAX_VERTEX_NUM];
    Vertex v, w;
    Vertex path[MAX_VERTEX_NUM];
    
    for (v = 0; v < graph->nv; v++) {
        length[v] = graph->gLength[source][v];
        cost[v] = graph->gCost[source][v];
        if (length[v] < INFINITY) {
            path[v] = source;
        } else {
            path[v] = -1;
        }
        collected[v] = 0;
    }
    
    cost[source] = 0;
    length[source] = 0;
    collected[source] = 1;
    
    while (1) {
        v = findMinDist(graph, length, cost, collected);
        if (v == ERROR) {
            break;
        }
        collected[v] = 1;
        for (w = 0; w < graph->nv; w++) {
            if (collected[w] == 0 && graph->gCost[v][w] < INFINITY && graph->gLength[v][w] < INFINITY) {
                if (graph->gLength[v][w] < 0 || graph->gCost[v][w] < 0) {
                    return 0;
                }
                if ( length[v] + graph->gLength[v][w] < length[w]) {
                    length[w] = length[v] + graph->gLength[v][w];
                    cost[w] = cost[v] + graph->gCost[v][w];
                    path[w] = v;
                } else if (length[v] + graph->gLength[v][w] == length[w]){
                    if (cost[v] + graph->gCost[v][w] < cost[w]) {
                        cost[w] = cost[v] + graph->gCost[v][w];
                    }
                }
            }
        }
    }
    printf("%d %d\n", length[target], cost[target]);
    return 1;
}

int main(int argc, const char * argv[]) {
    Vertex source, target;
    MGraph graph = buildGraph(&source, &target);
    dijkstra(graph, source, target);
    return 0;
}

