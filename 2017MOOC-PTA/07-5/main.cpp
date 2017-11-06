//
//  main.cpp
//  07-图5 Saving James Bond - Hard Version  https://pintia.cn/problem-sets/900290821590183936/problems/919158261277134848
//
//  Created by Qian Hu on 2017/11/6.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 120
#define THIS_INFINITY 65535

typedef int WeightType;
typedef char DataType;
typedef int Vertex;

typedef struct GNode {
    float x;
    float y;
} GNode, *PtrToGNode;

typedef struct MGNode {
    int nv;
    int ne;
    float length;
    int dist[MAX_VERTEX_NUM];
    int available[MAX_VERTEX_NUM];
    float sequence[MAX_VERTEX_NUM];
    Vertex path[MAX_VERTEX_NUM];
    GNode node[MAX_VERTEX_NUM];
    WeightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} MGNode, *MGraph;

typedef struct ENode {
    Vertex v1, v2;
    WeightType weight;
} ENode, *PtrToENode;

typedef PtrToENode Edge;

MGraph createGraph(int vertexNum) {
    MGraph graph;
    Vertex v, w;
    
    graph = (MGraph)malloc(sizeof(MGNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    
    for (v = 0; v < graph->nv; v++) {
        for(w = 0; w < graph->nv; w++) {
            graph->g[v][w] = THIS_INFINITY;
        }
    }
    
    for (v = 0; v < graph->nv; v++) {
        graph->available[v] = 0;
        graph->dist[v] = THIS_INFINITY;
        graph->path[v] = -1;
    }
    graph->dist[0] = 0;
    return graph;
}

void insertEdge(MGraph graph, Edge e) {
    graph->g[e->v1][e->v2] = e->weight;
    graph->g[e->v2][e->v1] = e->weight;
}

int isAvailable(GNode v, GNode w, float length) {
    if (pow(v.x - w.x, 2) + pow(v.y - w.y, 2) <= pow(length, 2)) {
        return 1;
    } else {
        return 0;
    }
}

MGraph buildGraph() {
    MGraph graph;
    Edge e;
    int nv;
    float length;
    
    scanf("%d", &nv);
    graph = createGraph(nv + 1);
    scanf("%f", &length);
    graph->length = length;
    
    graph->node[0].x = 0;
    graph->node[0].y = 0;
    
    for (Vertex v = 1; v < graph->nv; v++) {
        scanf("%f %f", &graph->node[v].x, &graph->node[v].y);
    }
    
    for (Vertex v = 1; v < graph->nv; v++) {
        graph->sequence[v] = -1;
        if (isAvailable(graph->node[0], graph->node[v], graph->length + 15/2.0)) {
            e = (Edge)malloc(sizeof(ENode));
            e->v1 = 0;
            e->v2 = v;
            e->weight = 1;
            insertEdge(graph, e);
        }
    }
    
    for (Vertex v = 1; v < graph->nv; v++) {
        for (Vertex w = 1; w < graph->nv; w++) {
            if (isAvailable(graph->node[v], graph->node[w], graph->length) == 1) {
                e = (Edge)malloc(sizeof(ENode));
                e->v1 = v;
                e->v2 = w;
                e->weight = 1;
                insertEdge(graph, e);
            }
        }
    }
    
    return graph;
}

int isSafe(GNode v, float length) {
    if ((v.x + length >= 50) || (v.x - length <= -50) || (v.y + length) >= 50 || (v.y - length <= -50) ) {
        return 1;
    } else {
        return 0;
    }
}

Vertex queue[MAX_VERTEX_NUM];
int front = 0;
int tail = 0;

void bfs(MGraph graph, Vertex source) {
    //printf("#####################################\n");
    int visited[MAX_VERTEX_NUM] = {0};
    queue[tail++] = source;
    while (tail != front) {
        Vertex v = queue[front++];
        for (Vertex w = 1; w < graph->nv; w++) {
            if (graph->g[v][w] < THIS_INFINITY && !visited[w]) {
                visited[w] = 1;
                if (isSafe(graph->node[w], graph->length)) {
                    graph->available[w] = 1;
                }
                graph->dist[w] = graph->dist[v] + 1;
                graph->path[w] = v;
                if (graph->path[w] == 0) {
                    graph->sequence[w] = pow(graph->node[w].x, 2) + pow(graph->node[w].y, 2);
                } else {
                    graph->sequence[w] = graph->sequence[v];
                }
                //printf("%d %.0f %.0f %d %d %d\n", w, graph->node[w].x, graph->node[w].y, graph->dist[w],graph->sequence[w], graph->available[w]);
                queue[tail++] = w;
            }
        }
    }
}

void save007(MGraph graph) {
    Vertex minV = -1;
    float minSequence = -1;
    int minDist = THIS_INFINITY;
    if (graph->length + 15.0/2 >= 50) {
        printf("1\n");
        return;
    }
    bfs(graph, 0);
    for (Vertex v = 1; v < graph->nv; v++) {
        if (graph->available[v]) {
            if (graph->dist[v] < minDist) {
                minV = v;
                minDist = graph->dist[v];
                minSequence = graph->sequence[v];
            } else if (graph->dist[v] == minDist && graph->sequence[v] < minSequence) {
                minSequence = graph->sequence[v];
                minV = v;
            }
        }
    }
    if (minV != -1) {
        int stack[MAX_VERTEX_NUM];
        int index = 0;
        int this_v = minV;
        while (graph->path[this_v] != -1) {
            stack[index++] = this_v;
            this_v = graph->path[this_v];
        }
        printf("%d\n", minDist + 1);
        while (index-- > 0) {
            printf("%.0f %.0f\n", graph->node[stack[index]].x, graph->node[stack[index]].y);
        }
    } else {
        printf("0\n");
    }
}

int main(int argc, const char * argv[]) {
    MGraph graph;
    graph = buildGraph();
    save007(graph);
    return 0;
}
