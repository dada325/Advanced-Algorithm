#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int NMAX = 11000;

vector<vector<int>> graph, reversedGraph;
vector<int> order, componentID, componentSize, outDegree;
vector<bool> visited;
int n, m, sccCount;

void dfs(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
    order.push_back(node);
}

void reverseDfs(int node, int component) {
    visited[node] = true;
    componentID[node] = component;
    componentSize[component]++;
    for (int neighbor : reversedGraph[node]) {
        if (!visited[neighbor]) {
            reverseDfs(neighbor, component);
        }
    }
}

void Kosaraju() {
    order.clear();
    componentID.assign(n + 1, 0);
    componentSize.assign(sccCount, 0);
    visited.assign(n + 1, false);

    // Step 1: DFS on the original graph to fill the order vector
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Step 2: DFS on the reversed graph to find SCCs
    visited.assign(n + 1, false);
    sccCount = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (!visited[order[i]]) {
            reverseDfs(order[i], sccCount);
            sccCount++;
        }
    }

    // Calculate out-degrees of SCCs
    outDegree.assign(sccCount, 0);
    for (int i = 1; i <= n; i++) {
        for (int neighbor : graph[i]) {
            if (componentID[i] != componentID[neighbor]) {
                outDegree[componentID[i]]++;
            }
        }
    }

    // Check if the contracted graph is a DAG and print the result
    int zeroOutDegreeCount = 0, ansID = 0;
    for (int i = 1; i < sccCount; i++) {
        if (outDegree[i] == 0) {
            zeroOutDegreeCount++;
            ansID = i;
        }
    }

    if (zeroOutDegreeCount > 1) {
        printf("0\n");
    } else {
        printf("%d\n", componentSize[ansID]);
    }
}

int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        graph.assign(n + 1, vector<int>());
        reversedGraph.assign(n + 1, vector<int>());
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            reversedGraph[y].push_back(x);
        }
        Kosaraju();
    }
    return 0;
}
