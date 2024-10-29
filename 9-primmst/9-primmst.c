#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// 그래프 구조체
typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 거리 정점 찾음
int FindPrimMST(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;
        }
    }
    return v;
}

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
        selected[i] = FALSE;
        distance[i] = INF;
    }
}

// 최소 신장 트리 생성
void prim(GraphType* g, int s) {
    int u, v;

    // 거리 배열 초기화
    for (u = 0; u < g->n; u++)
        distance[u] = INF;
    distance[s] = 0;

    printf("Prim MST Algorithm\n");

    for (int i = 0; i < g->n; i++) {
        u = FindPrimMST(g->n);
        if (u == -1 || distance[u] == INF) return;

        selected[u] = TRUE;
        printf("정점 %d 추가\n", u + 1);  // 정점 번호 1부터 시작하도록 출력

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

// 그래프 간선 가중치 초기화
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 그래프 정점 수

    // 간선 가중치 배열 정의
    int weights[10][10] = {
        // 1    2    3    4    5    6    7    8    9    10
        {  0,   3, INF, INF, INF,  11,  12, INF, INF, INF }, // 1
        {  3,   0,   5,   4,   1,   7,   8, INF, INF, INF }, // 2
        {INF,   5,   0,   2, INF, INF,   6,   5, INF, INF }, // 3
        {INF,   4,   2,   0,   5, INF, INF,  14, INF,  16 }, // 4
        {INF,   1, INF,   5,   0,   9, INF, INF,  18,  17 }, // 5
        { 11,   7, INF, INF,   9,   0, INF, INF, INF, INF }, // 6
        { 12,   8,   6, INF, INF, INF,   0,  13, INF, INF }, // 7
        {INF, INF,   5,  14, INF, INF,  13,   0, INF,  15 }, // 8
        {INF, INF, INF, INF,  18, INF, INF, INF,   0,  10 }, // 9
        {INF, INF, INF,  16,  17, INF, INF,  15,  10,   0 }  // 10
    };

    // 가중치 배열 그래프에 복사
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            g->weight[i][j] = weights[i][j];
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);  // 그래프 초기화

    GenerateGraph(g);  // 그래프 생성

    prim(g, 0);  // Prim 알고리즘 실행, 시작 정점은 0 (정점 1에 해당)

    free(g);  // 메모리 해제
    return 0;
}
