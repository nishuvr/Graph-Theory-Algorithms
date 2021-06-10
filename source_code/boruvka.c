#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     int first;
     int second;
     int weight;
}weighted_edge;

int edge_compare(const weighted_edge *edge1, const weighted_edge *edge2)
{
    return (edge1->weight - edge2->weight);
}
int triangular_number(int n)
{
    return (n * (n + 1)) / 2;
}
void print(const weighted_edge *edges, int n)
{
    for (int i = 0; i < n; i++)
        printf("(%d, %d, %d) ", edges[i].first, edges[i].second, edges[i].weight);
    printf("\n");
}

int complete_graph(int v, weighted_edge **edges)
{
    int n = triangular_number(v - 1);
    int i, j, k;
    *edges = malloc(n * sizeof(weighted_edge));
    if(edges != NULL) {
        for (i = 0, k = 0; i < v - 1; i++) {
            for (j = i + 1; j < v; j++)
            {
                (*edges)[k].first = i;
                (*edges)[k].second = j;
                (*edges)[k].weight = k + 1;
                k++;
            }
        }
    }
    return n;
}

/* the cheapest edge with one endpoint in tree and one not */
int cheapest_edge(const weighted_edge *edges,  int size, int *vertices,  int tree)
{
    int cheapest = -1;
    for (int i = 0; i < size && cheapest == -1; i++)
    {
        if((vertices[edges[i].first] == tree && vertices[edges[i].second] != tree) || (vertices[edges[i].first] != tree && vertices[edges[i].second] == tree))
            cheapest = i;
    }
    return cheapest;
}

/* Merge trees for all of the edges in mst from mst_prev to mst_edges */
void merge_trees(const weighted_edge *mst,  int mst_prev, int mst_edges, int *vertices, int order, int *trees)
{
    for(int i = mst_prev; i < mst_edges; i++)
    {
        for (int j = 0; j < order; j++)
        {
            if (vertices[j] == mst[i].second)
                vertices[j] = mst[i].first;
        }
        (*trees)--;
    }
}
 int boruvka(weighted_edge *edges, int size, int order, weighted_edge **mst)
{
    *mst = malloc((order - 1)* sizeof(weighted_edge));
    int *vertices = malloc(order * sizeof( int));
    int trees = order;
    int *links = malloc(size * sizeof(int));
    int i, cost = 0, mst_edges = 0;
    for (i = 0; i < order; i++)
        vertices[i] = i;
    qsort(edges, size, sizeof(weighted_edge),(int(*)(const void *, const void *))edge_compare);
    while (trees > 1) {
        unsigned int t, mst_prev = mst_edges;
        memset(links, 0, size * sizeof(int));
        for (t = 0; t < trees ; t++) {
            int cheapest = cheapest_edge(edges, size, vertices, t);
            if (links[cheapest] != 1) {
                (*mst)[mst_edges++] = edges[cheapest];
                links[cheapest] = 1;
                cost += edges[cheapest].weight;
            }
        }
        merge_trees(*mst, mst_prev, mst_edges, vertices, order, &trees);
    }
    return cost;
}
int main()
{
    int num;
    scanf("%d",&num);
    int n=0;
    while(n<num)
    {
        weighted_edge *edges;
        int order;
        scanf("%d",&order);
        int size = complete_graph(order, &edges);
        weighted_edge *mst;
        int cost = boruvka(edges, size, order, &mst);
        printf("Total Cost : %d\n", cost);
        print(mst, order - 1);
        n++;
    }
}

