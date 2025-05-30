#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> convertMatrixToList(const string& filename)
{
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fin >> matrix[i][j];

    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (matrix[i][j])
                adjList[i].push_back(j);
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{
    ifstream fin(filename);
    int n;
    fin >> n;
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; ++i)
    {
        int size, v;
        fin >> size;
        while (size-- && fin >> v)
            adjList[i].push_back(v);
    }

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j : adjList[i])
            matrix[i][j] = 1;
    return matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] != adjMatrix[j][i])
                return true;
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
    int edges = 0;
    for (auto& row : adjMatrix)
        for (int val : row)
            edges += val;
    return isDirected(adjMatrix) ? edges : edges / 2;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
{
    vector<int> isolated;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
    {
        bool hasEdge = false;
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] || adjMatrix[j][i])
                hasEdge = true;
        if (!hasEdge) isolated.push_back(i);
    }
    return isolated;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && adjMatrix[i][j] != 1)
                return false;
    return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    for (int start = 0; start < n; ++start)
    {
        if (color[start] != -1) continue;
        color[start] = 0;
        q.push(start);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; ++v)
            {
                if (adjMatrix[u][v])
                {
                    if (color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if (color[v] == color[u])
                        return false;
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix)
{
    if (!isBipartite(adjMatrix)) return false;
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    vector<int> part[2];
    for (int start = 0; start < n; ++start)
    {
        if (color[start] != -1) continue;
        color[start] = 0;
        q.push(start);
        part[0].push_back(start);
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; ++v)
                if (adjMatrix[u][v])
                    if (color[v] == -1)
                    {
                        color[v] = 1 - color[u];
                        q.push(v);
                        part[color[v]].push_back(v);
                    }
        }
    }
    for (int u : part[0])
        for (int v : part[1])
            if (!adjMatrix[u][v])
                return false;
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<int>> undirected(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adjMatrix[i][j] || adjMatrix[j][i])
                undirected[i][j] = undirected[j][i] = 1;
    return undirected;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<int>> complement(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && adjMatrix[i][j] == 0)
                complement[i][j] = 1;
    return complement;
}

vector<int> findEulerCycle(vector<vector<int>> adjMatrix)
{
    int n = adjMatrix.size();
    stack<int> st;
    vector<int> circuit;
    vector<vector<int>> graph = adjMatrix;
    st.push(0);
    while (!st.empty())
    {
        int u = st.top();
        bool found = false;
        for (int v = 0; v < n; ++v)
        {
            if (graph[u][v])
            {
                graph[u][v]--;
                graph[v][u]--; // for undirected graph
                st.push(v);
                found = true;
                break;
            }
        }
        if (!found)
        {
            circuit.push_back(u);
            st.pop();
        }
    }
    reverse(circuit.begin(), circuit.end());
    return circuit;
}

void dfss(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& tree)
{
    visited[u] = true;
    int n = adjMatrix.size();
    for (int v = 0; v < n; ++v) {
        if (adjMatrix[u][v] && !visited[v])
        {
            tree[u][v] = tree[v][u] = 1;
            dfss(v, adjMatrix, visited, tree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> tree(n, vector<int>(n, 0));
    dfss(start, adjMatrix, visited, tree);
    return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> tree(n, vector<int>(n, 0));
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[u][v] && !visited[v])
            {
                visited[v] = true;
                tree[u][v] = tree[v][u] = 1;
                q.push(v);
            }
        }
    }
    return tree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty())
    {
        int curr = q.front(); q.pop();
        if (curr == v) return true;
        for (int i = 0; i < n; ++i)
            if (adjMatrix[curr][i] && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && dist[v] > dist[u] + adjMatrix[u][v])
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    dist[start] = 0;
    for (int i = 1; i < n; ++i)
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v)
                if (adjMatrix[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + adjMatrix[u][v])
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

