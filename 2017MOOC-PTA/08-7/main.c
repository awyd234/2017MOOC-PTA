//
//  main.c
//  08-图7 公路村村通  https://pintia.cn/problem-sets/900290821590183936/problems/921717857800011776
//
//  Created by Qian Hu on 2017/11/7.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1010
#define INFINITY 65535
#define ERROR -1

typedef int WeightType;
typedef char DataType;
typedef int Vertex;

typedef struct GNode {
    int nv;
    int ne;
    WeightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} GNode, *MGraph;

typedef struct ENode {
    Vertex v1, v2;
    WeightType weight;
} ENode, *Edge;

typedef struct AdjVNode {
    Vertex adjV;
    WeightType weight;
    struct AdjVNode *next;
} AdjVNode, *PtrToAdjVNode;

typedef struct VNode {
    PtrToAdjVNode firstEdge;
    DataType data;
} AdjList[MAX_VERTEX_NUM];

typedef struct LGNode {
    int nv;
    int ne;
    AdjList g;
} LGNode, *LGraph;

MGraph createGraph(int vertexNum) {
    MGraph graph;
    Vertex v, w;
    
    graph = (MGraph)malloc(sizeof(GNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    
    for (v = 0; v < graph->nv; v++) {
        for(w = 0; w < graph->nv; w++) {
            graph->g[v][w] = INFINITY;
        }
    }
    return graph;
}

void insertEdge(MGraph graph, Edge e) {
    graph->g[e->v1 - 1][e->v2 - 1] = e->weight;
    graph->g[e->v2 - 1][e->v1 - 1] = e->weight;
}

MGraph buildGraph() {
    MGraph graph;
    Edge e;
    int nv;
    
    scanf("%d", &nv);
    graph = createGraph(nv);
    scanf("%d", &graph->ne);
    
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        for ( int i = 0; i < graph->ne; i++) {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            insertEdge(graph, e);
        }
    }
    return graph;
}

Vertex findMinDist(MGraph graph, WeightType dist[]) {
    Vertex minV, v;
    WeightType minDist = INFINITY;
    
    for (v = 0; v < graph->nv; v++) {
        if (dist[v] != 0 && dist[v] < minDist) {
            minDist = dist[v];
            minV = v;
        }
    }
    if (minDist < INFINITY) {
        return minV;
    } else {
        return ERROR;
    }
}

int prim(MGraph graph) {
    WeightType dist[MAX_VERTEX_NUM], totalWeight;
    Vertex parent[MAX_VERTEX_NUM], v, w;
    int vCount;
    for (v = 0; v < graph->nv; v++) {
        dist[v] = graph->g[0][v];
        parent[v] = 0;
    }
    totalWeight = 0;
    vCount = 0;
    
    dist[0] = 0;
    vCount++;
    parent[0] = -1;
    
    while (1) {
        v = findMinDist(graph, dist);
        if (v == ERROR) {
            break;
        }
        totalWeight += dist[v];
        //printf("%d %d\n", v + 1, dist[v]);
        dist[v] = 0;
        vCount++;
        
        for (w = 0; w < graph->nv; w++) {
            if (dist[w] != 0 && graph->g[v][w] < INFINITY) {
                if (graph->g[v][w] < dist[w]) {
                    dist[w] = graph->g[v][w];
                    parent[w] = v;
                }
            }
        }
    }
    if (vCount < graph->nv) {
        totalWeight = ERROR;
    }
    return totalWeight;
}

int main(int argc, const char * argv[]) {
    MGraph graph;
    graph = buildGraph();
    int totalWeight = prim(graph);
    printf("%d\n", totalWeight);
    return 0;
}

