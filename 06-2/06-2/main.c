//
//  main.c
//  06-图2 Saving James Bond - Easy Version   https://pintia.cn/problem-sets/900290821590183936/problems/916508881217581056
//
//  Created by Qian Hu on 2017/11/2.
//  Copyright © 2017年 Qian Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 100

typedef int WeightType;
typedef char DataType;
typedef int Vertex;

typedef struct GNode {
    int x;
    int y;
} GNode, *PtrToGNode;

typedef struct MGNode {
    int nv;
    int ne;
    int length;
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
            graph->g[v][w] = 0;
        }
    }
    return graph;
}

void insertEdge(MGraph graph, Edge e) {
    graph->g[e->v1][e->v2] = e->weight;
    graph->g[e->v2][e->v1] = e->weight;
}

int isAvailable(GNode v, GNode w, int length) {
    if ((v.x - w.x) * (v.x - w.x) + (v.y - w.y) * (v.y - w.y) <= length * length) {
        return 1;
    } else {
        return 0;
    }
}

MGraph buildGraph() {
    MGraph graph;
    Edge e;
    int nv;
    int length;
    
    scanf("%d", &nv);
    graph = createGraph(nv);
    scanf("%d", &length);
    
    graph->length = length;
    for (Vertex v = 0; v < graph->nv; v++) {
        scanf("%d %d", &graph->node[v].x, &graph->node[v].y);
    }
    
    for (Vertex v = 0; v < graph->nv; v++) {
        for (Vertex w = v + 1; w < graph->nv; w++) {
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

int isSafe(GNode v, int length) {
    if ((v.x + length >= 50) || (v.x - length <= -50) || (v.y + length) >= 50 || (v.y - length <= -50) ) {
        return 1;
    } else {
        return 0;
    }
}

int DFS(MGraph graph, int visited[], Vertex v) {
    int answer = 0;
    visited[v] = 1;
    if (isSafe(graph->node[v], graph->length)) {
        answer = 1;
    } else {
        for (Vertex w = 0; w < graph->nv; w++) {
            if (!visited[w] && graph->g[v][w] == 1) {
                answer = DFS(graph, visited, w);
                if (answer == 1) {
                    break;
                }
            }
        }
    }
    return answer;
}

void save007(MGraph graph, int visited[]) {
    int answer = 0;
    PtrToGNode originNode = (PtrToGNode)malloc(sizeof(GNode));
    originNode->x = 0;
    originNode->y = 0;
    for (Vertex v = 0; v < graph->nv; v ++) {
        if (visited[v] != 1 && isAvailable(graph->node[v], *originNode, graph->length + 15)) {
            answer = DFS(graph, visited, v);
            if (answer == 1) {
                break;
            }
        }
    }
    if (answer == 1) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main(int argc, const char * argv[]) {
    MGraph graph;
    int visited[MAX_VERTEX_NUM];
    graph = buildGraph();
    for (Vertex v = 0; v < graph->nv; v++) {
        visited[v] = 0;
    }
    save007(graph, visited);
    return 0;
}
