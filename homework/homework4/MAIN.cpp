#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph {//图数据结构
private:
    int V; // 顶点数
    vector<int>* adj; // 邻接表

public:
    Graph(int V); // 构造函数
    void addEdge(int v, int w); // 添加边
    void BFS(int s); // 广度优先搜索
    void DFS(int s); // 深度优先搜索
    void Dijkstra(int s); // 最短路径算法
    void Prim(); // 最小支撑树算法
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::BFS(int s) {//BFS
    vector<bool> visited(V, false); // 记录是否访问过
    queue<int> q;

    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        s = q.front();
        cout << s << " ";
        q.pop();

        for (auto i = adj[s].begin(); i != adj[s].end(); i++) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
}

void Graph::DFS(int s) {//DFS
    vector<bool> visited(V, false); // 记录是否访问过
    stack<int> st;

    visited[s] = true;
    st.push(s);

    while (!st.empty()) {
        s = st.top();
        cout << s << " ";
        st.pop();

        for (auto i = adj[s].begin(); i != adj[s].end(); i++) {
            if (!visited[*i]) {
                visited[*i] = true;
                st.push(*i);
            }
        }
    }
}

void Graph::Dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 小顶堆
    vector<int> dist(V, INT_MAX); // 记录到起点的距离

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            int v = *i;
            int weight = 1; // 边权重为1

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "最短路径：\n";
    for (int i = 0; i < V; i++) {
        cout << s << " 到 " << i << " 的距离为 " << dist[i] << endl;
    }
}

void Graph::Prim() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 小顶堆
    vector<int> key(V, INT_MAX); // 记录到MST的最小权重
    vector<int> parent(V, -1); // 记录MST中每个节点的父节点
    vector<bool> inMST(V, false); // 记录是否在MST中

    pq.push(make_pair(0, 0)); // 第一个节点入队
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            int v = *i;
            int weight = 1; // 边权重为1

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    cout << "最小支撑树：\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << endl;
    }
}

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "BFS: ";
    g.BFS(0);
    cout << endl;

    cout << "DFS: ";
    g.DFS(0);
    cout << endl;

    Graph g1(9);

    g1.addEdge(0, 1);
    g1.addEdge(0, 7);
    g1.addEdge(1, 2);
    g1.addEdge(1, 7);
    g1.addEdge(2, 3);
    g1.addEdge(2, 8);
    g1.addEdge(2, 5);
    g1.addEdge(3, 4);
    g1.addEdge(3, 5);
    g1.addEdge(4, 5);
    g1.addEdge(5, 6);
    g1.addEdge(6, 7);
    g1.addEdge(6, 8);
    g1.addEdge(7, 8);

    g1.Dijkstra(0);
    g1.Prim();

    return 0;
}
