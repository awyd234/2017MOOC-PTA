//
//  main.c
//  07-图4 哈利·波特的考试  https://pintia.cn/problem-sets/900290821590183936/problems/919158178544488448
//
//  Created by Qian Hu on 2017/11/5.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 110
#define MAX_LENGTH 65535

typedef int WeightType;
typedef int Vertex;

typedef struct GNode {
    int nv;
    int ne;
    WeightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} GNode, *PtrToGNode;

typedef struct ENode {
    Vertex v1, v2;
    WeightType weight;
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
            graph->g[v][w] = MAX_LENGTH;
        }
    }
    return graph;
}

void insertEdge(MGraph graph, Edge e) {
    graph->g[e->v1][e->v2] = e->weight;
    graph->g[e->v2][e->v1] = e->weight;
}

MGraph buildGraph() {
    MGraph graph;
    int n, i;
    Edge e;
    
    scanf("%d", &n);
    graph = createGraph(n);
    scanf("%d", &graph->ne);
    
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        for (i = 0; i < graph->ne; i++) {
            scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            e->v1--;
            e->v2--;
            insertEdge(graph, e);
        }
    }
    
    return graph;
}

void floyd(MGraph graph, WeightType d[][MAX_VERTEX_NUM]) {
    Vertex i, j, k;
    for (i = 0; i < graph->nv; i++) {
        for (j = 0; j < graph->nv; j++) {
            d[i][j] = graph->g[i][j];
        }
    }
    for (k = 0; k < graph->nv; k++) {
        for (i = 0; i < graph->nv; i++) {
            for (j = 0; j < graph->nv; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

WeightType findMaxDist(WeightType d[][MAX_VERTEX_NUM], Vertex i, int n) {
    WeightType maxDist;
    Vertex j;
    
    maxDist = 0;
    for (j = 0; j < n; j++) {
        if (i != j && d[i][j] > maxDist) {
            maxDist = d[i][j];
        }
    }
    return maxDist;
}

void findAnimal(MGraph graph) {
    Vertex i, animal;
    WeightType d[MAX_VERTEX_NUM][MAX_VERTEX_NUM], maxDist, minDist;
    
    floyd(graph, d);
    
    minDist = MAX_LENGTH;
    for (i = 0; i < graph->nv; i++) {
        maxDist = findMaxDist(d, i, graph->nv);
        if (maxDist == MAX_LENGTH) {
            printf("0\n");
            return;
        }
        if (minDist > maxDist) {
            minDist = maxDist;
            animal = i + 1;
        }
    }
    printf("%d %d\n", animal, minDist);
}

int main(int argc, const char * argv[]) {
    MGraph graph = buildGraph();
    findAnimal(graph);
    return 0;
}
