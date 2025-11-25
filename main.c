#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 101
#define INF 100000000

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int dist[MAX_VERTICES];
int parent[MAX_VERTICES]; 
int n;
int first_print;

int queue[MAX_VERTICES];
int front = 0, rear = 0;

void initQueue() {
    front = 0;
    rear = 0;
}

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

int isQueueEmpty() {
    return front == rear;
}


void dfs(int v) {
    visited[v] = 1;
    
    if (!first_print)
        printf(" - ");
    printf("%d", v);
    first_print = 0;

    for (int i = 1; i <= n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}


void bfs(int start) {
    initQueue();
    for (int i = 1; i <= n; i++)
        visited[i] = 0;

    visited[start] = 1;
    enqueue(start);
    
    first_print = 1;

    while (!isQueueEmpty()) {
        int v = dequeue();

        if (!first_print)
            printf(" - ");
        printf("%d", v);
        first_print = 0;

        for (int i = 1; i <= n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
            }
        } //인접 노드 큐에 추가
    }
}

void processInput1() {
    FILE *fp = fopen("input1.txt", "r");
    if (fp == NULL) {
        printf("input1.txt 파일없음\n");
        return;
    }

    int graph_count = 1;
    char line[1024];

    while (fscanf(fp, "%d", &n) != EOF) {
        for (int i = 1; i <= 100; i++) {
            for (int j = 1; j <= 100; j++) {
                adj[i][j] = 0;
            }
        }

        fgets(line, sizeof(line), fp); // \n제거용

        for (int i = 0; i < n; i++) {
            if (fgets(line, sizeof(line), fp) == NULL)
                break;
            char *ptr = strtok(line, " ");
            int u = atoi(ptr);
            
            while ((ptr = strtok(NULL, " ")) != NULL) {
                int v = atoi(ptr);
                adj[u][v] = 1;
            }
        }

        printf("그래프 [%d]\n", graph_count);
        printf("----------------------------\n");
        printf("깊이 우선 탐색\n");
        for (int i = 1; i <= n; i++)
            visited[i] = 0;
        first_print = 1;
        dfs(1);
        printf("\n");

        printf("너비 우선 탐색\n");
        bfs(1);
        printf("\n");
        printf("============================\n\n");

        graph_count++;
    }
    fclose(fp);
}

void printPath(int v) {
    if (v == 1) {
        printf("1");
        return;
    }
    printPath(parent[v]);
    printf(" - %d", v);
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = 0;
    } //초기화
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        int minVal = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minVal) {
                minVal = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break; // 더 이상 갈 곳 없음
        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != INF) {
                if (!visited[v] && dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

void processInput2() {
    FILE *fp = fopen("input2.txt", "r");
    if (fp == NULL) {
        printf("input2.txt 파일없음\n");
        return;
    }

    int graph_count = 1;
    char line[1024];
    
    while (fscanf(fp, "%d", &n) != EOF) {
        for (int i = 1; i <= 100; i++) {
            for (int j = 1; j <= 100; j++) {
                adj[i][j] = INF;
            }
        }

        fgets(line, sizeof(line), fp); // \n제거용

        for (int i = 0; i < n; i++) {
            if (fgets(line, sizeof(line), fp) == NULL)
                break;

            char *ptr = strtok(line, " ");
            int u = atoi(ptr);

            while ((ptr = strtok(NULL, " ")) != NULL) {
                int v = atoi(ptr);
                ptr = strtok(NULL, " ");
                if (ptr == NULL)
                    break; 
                int w = atoi(ptr);
                adj[u][v] = w;
            }
        }

        printf("그래프 [%d]\n", graph_count);
        printf("----------------------------\n");
        printf("시작점: 1\n");

        dijkstra(1);

        for (int i = 2; i <= n; i++) {
            if (dist[i] == INF) {
                printf("정점 [%d]: 경로 없음\n", i);
            } else {
                printf("정점 [%d]: ", i);
                printPath(i);
                printf(", 길이: %d\n", dist[i]);
            }
        }
        printf("============================\n\n");
        graph_count++;
    }
    fclose(fp);
}

int main() {
    printf("1. 그래프 탐방 수행 결과\n\n");
    processInput1();
    printf("\n");

    printf("2. 최단 경로 구하기 수행 결과\n\n");
    processInput2();

    return 0;
}