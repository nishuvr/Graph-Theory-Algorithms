#include<stdio.h>
#include<stdlib.h>
#define INT_MAX 2147483647

typedef struct node {
    int id;
    int cost;
    struct node* next;
}node;

typedef struct list {
    node* head;
    node* tail;
    int count;
}list;

node* create_node(int id, int cost) {
    node* Node = malloc(sizeof(node));
    Node -> id = id;
    Node -> cost = cost;
    Node -> next = NULL;
    return Node;
}

int min(int a, int b) {
    return a < b ? a: b;
}

//insert at end
void insert(list* list, int id, int cost) {
    node* newNode = create_node(id,cost);
    if(list -> head == NULL) {
        list -> head = newNode;
        list -> count++;
    }
    else {
        list -> tail -> next = newNode;
        list -> count++;
    }
    list -> tail = newNode;
}


void dijkstra(int source, int n, int** minCost, list* graph) {

    int* costs = minCost[source];
    for(int i = 0; i <= n; ++i) costs[i] = 1e9;
    costs[source] = 0;
    int* visited = calloc(n + 1, sizeof(int));
    int cur = source;
    int costs_found = 0;
    while(costs_found < n) {
        ++costs_found;
        visited[cur] = 1;
        node* cur_node = graph[cur].head;
        while(cur_node) {
            costs[cur_node -> id] = min (
                costs[cur_node -> id],
                costs[cur] + cur_node -> cost
            );
            cur_node = cur_node -> next;
        }
        int next_node = cur;
        for(int i=1; i<=n; ++i)
            if(visited[i] == 0 && ( costs[i] < costs[next_node] || next_node == cur ))
                next_node = i;
        cur = next_node;
    }
}

void min_pair_cost(int* odd_nodes, int odd_nodes_count, int** costs, int* visited, int cost, int* min_pairs_cost, int cur) {
    if(cur == odd_nodes_count)
        *min_pairs_cost = min(*min_pairs_cost, cost);
    else {
        if(visited[cur] == 1)
            min_pair_cost(odd_nodes, odd_nodes_count, costs, visited, cost, min_pairs_cost, cur + 1);
        else {
            visited[cur] = 1;
            for(int i = cur + 1; i < odd_nodes_count; ++i) {
                if(visited[i] == 0) {
                    visited[i] = 1;
                    min_pair_cost(odd_nodes, odd_nodes_count, costs, visited, cost + costs[odd_nodes[cur]][odd_nodes[i]], min_pairs_cost, cur + 1);
                    visited[i] = 0;
                }
            }
            visited[cur] = 1;
        }
    }
}

int main() {
    int n, e;
    int num;
    scanf("%d",&num);
    for(int i=0;i<num;i++){
    scanf("%d %d", &n, &e);
    list* graph = malloc((n + 1) * sizeof(list));
    int** mincost = malloc((n + 1) * sizeof(int*));
    for(int i = 0; i <= n; ++i)
        mincost[i] = malloc((n + 1) * sizeof(int));
    int total_cost = 0;
    for(int i = 0; i < e; ++i) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        insert(&graph[u], v, cost);
        insert(&graph[v], u, cost);
        total_cost += cost;
    }
    for(int i = 1; i <= n; ++i)
        dijkstra(i, n, mincost, graph);
    int* odd_nodes = malloc(n * sizeof(int));
    int odd_nodes_count = 0;
    for(int i = 1; i <= n; ++i)
        if(graph[i].count % 2)
            odd_nodes[odd_nodes_count++] = i;
    int* visited = malloc(n * sizeof(int));
    int min_pairs_cost = INT_MAX;
    min_pair_cost(odd_nodes, odd_nodes_count, mincost, visited, 0, &min_pairs_cost, 0);
    printf("Minimum cost of the path: %d\n", min_pairs_cost + total_cost );}

}
