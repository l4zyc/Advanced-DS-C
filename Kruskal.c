#include <stdio.h>
#include <stdlib.h>

typedef struct Edge Edge;

struct Edge{
    int src, dst, cost;
};

int compareQsort(const void *a, const void *b) {
    return ((Edge*)a)->cost > ((Edge*)b)->cost;
}

int findParents(int *listD, int index) {
    if(listD[index] == index) {
        return index;
    } else {
        return findParents(listD, listD[index]);
    }
}

void unionD(int *listD, int p1, int p2) {
    listD[findParents(listD, p1)] = findParents(listD, p2);
}

void solve(Edge *edge, int e, int v) {
    qsort(edge, e, sizeof(Edge), compareQsort);

    int listD[v];

    for(int i = 0 ; i < v; i++) {
        listD[i] = i;
    }

    int indexEdgeProblem = 0, indexResult = 0;
    Edge result[v-1];
    while(indexResult < v-1) {
        Edge currEdge = edge[indexEdgeProblem];
        indexEdgeProblem++;

        int p1 = findParents(listD, currEdge.src);
        int p2 = findParents(listD, currEdge.dst);

        if(p1 != p2) {
            result[indexResult] = currEdge;
            indexResult++;
            unionD(listD, p1, p2);
        }
    }

    for(int i = 0; i < v-1; i++) {
        Edge curr = result[i];
        printf("%d -> %d : %d\n", curr.src, curr.dst, curr.cost);
    }
}

int main() {
    int v = 4;
    int e = 5;

    Edge edge[e];

    edge[0] = (Edge) {0,1,10};
    edge[1] = (Edge) {0,2,6};
    edge[2] = (Edge) {2,3,4};
    edge[3] = (Edge) {1,3,15};
    edge[4] = (Edge) {3,0,5};

    solve(edge, e ,v);

    return 0;
}