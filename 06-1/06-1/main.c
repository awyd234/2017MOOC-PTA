//
//  main.c
//  06-图1 列出连通集   https://pintia.cn/problem-sets/900290821590183936/problems/916508799760003072
//
//  Created by Qian Hu on 2017/11/2.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 10

typedef int WeightType;
typedef char DataType;
typedef int Vertex;

typedef struct GNode {
    int nv;
    int ne;
    WeightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    DataType data[MAX_VERTEX_NUM];
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
            graph->g[v][w] = 0;
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
    Edge e;
    int nv;
    
    scanf("%d", &nv);
    graph = createGraph(nv);
    scanf("%d", &graph->ne);
    
    if (graph->ne != 0) {
        e = (Edge)malloc(sizeof(ENode));
        for ( int i = 0; i < graph->ne; i++) {
            //scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
            scanf("%d %d", &e->v1, &e->v2);
            e->weight = 1;
            insertEdge(graph, e);
        }
    }
    /*
         for (Vertex v = 0; v < graph->nv; v++) {
            scanf("%c", &(graph->data[v]));
         }
     */
    return graph;
}

void DFS(MGraph graph, int visited[], Vertex v) {
    visited[v] = 1;
    printf("%d ", v);
    for (Vertex w = 0; w < graph->nv; w++) {
        if (graph->g[v][w] == 1 && visited[w] == 0) {
            DFS(graph, visited, w);
        }
    }
}

Vertex queue[MAX_VERTEX_NUM];
int front = 0;
int tail = 0;
void BFS(MGraph graph, int visited[], Vertex v) {
    visited[v] = 1;
    //printf("%d ", v);
    queue[tail++] = v;
    while(tail - front != 0) {
        v = queue[front++];
        printf("%d ", v);
        for (Vertex w = 0; w < graph->nv; w++) {
            if (graph->g[v][w] == 1 && visited[w] == 0) {
                visited[w] = 1;
                queue[tail++] = w;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    MGraph graph;
    int visited[MAX_VERTEX_NUM];
    graph = buildGraph();
    for (Vertex v = 0; v < graph->nv; v++) {
        visited[v] = 0;
    }
    for (Vertex v = 0; v < graph->nv; v++) {
        if (visited[v] != 1) {
            printf("{ ");
            DFS(graph, visited, v);
            printf("}\n");
        }
    }
    for (Vertex v = 0; v < graph->nv; v++) {
        visited[v] = 0;
    }
    for (Vertex v = 0; v < graph->nv; v++) {
        if (visited[v] != 1) {
            printf("{ ");
            BFS(graph, visited, v);
            printf("}\n");
        }
    }
    return 0;
}
