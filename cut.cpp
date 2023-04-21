#include <bits-stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

const int V = 7;

int f(int another_graph[V][V], int e, int b, int p[])
{
    bool vis[V];
    for (int i = 0; i < V; i++)
        vis[i] = 0;

    queue <int> c;
    c.push(e);
    vis[e] = 1;
    p[e] = -1;
    int s;
    while (!c.empty())
    {
        int y = c.front();
        c.pop();
        for (s = 0; s < V; s++)
        {
            if (vis[s] == 0 && another_graph[y][s] > 0)
            {
                c.push(s);
                p[s] = y;
                vis[s] = 1;
            }
        }
    }
    return (vis[b] == 1);
}

void f2(int another_graph[V][V], int a, bool vis[])
{
    vis[a] = 1;
    for (int i = 0; i < V; i++)
        if (another_graph[a][i] && !vis[i])
            f2(another_graph, i, vis);
}

void mincut(int G[V][V], int a, int b)
{
    int i, j;
    int another_graph[V][V];
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            another_graph[i][j] = G[i][j];

    int p[V];
    while (f(another_graph, a, b, p))
    {
        int ss = INT_MAX;
        for (j = b; j != a; j = p[j])
        {
            i = p[j];
            ss = min(ss, another_graph[i][j]);
        }

        for (j = b; j != a; j = p[j])
        {
            i = p[j];
            another_graph[i][j] = another_graph[j][i] - ss;
            another_graph[j][i] = another_graph[i][j] + ss;
        }
    }

    bool vis[V];
    for (int u = 0; u < V; u++)
        vis[u] = 0;

    f2(another_graph, a, vis);

    for (int u = 0; u < V; u++)
        for (int l = 0; l < V; l++)
            if (vis[u] && vis[l] == 0 && G[u][l] != 0)
                cout << u << " -> " << l << endl;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int start;
    cout << "Введите начальную вершину: " << endl;
    cin >> start;

    int end;
    cout << "Введите конечную вершину: " << endl;
    cin >> end;

    int G[V][V] = { {0, 1, 2, 5, 7, 0, 0},
                        {1, 0, 0, 0, 0, 5, 0},
                        {2, 0, 0, 1, 0, 0, 0},
                        {5, 0, 1, 0, 1, 0, 0},
                        {7, 0, 0, 1, 0, 1, 1},
                        {0, 5, 0, 0, 1, 0, 3}, 
                        {0, 0, 0, 0, 1, 3, 0} };

    cout << "Минимальный разрез: " << endl;

    mincut(G, start, end);

    return 0;
}