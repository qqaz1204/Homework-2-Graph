#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

// 定義無窮大，用於 Dijkstra 演算法
const int INF = 1e9;

class Graph {
private:
    int numV; // 頂點數量
    vector<vector<pair<int, int>>> adj; // 鄰接串列：adj[u] 存儲 {v, weight}

public:
    // 建構函數
    Graph(int vertices) {
        numV = vertices;
        adj.resize(vertices);
    }

    // 新增邊 (預設為無向圖，帶權重)
    void addEdge(int u, int v, int weight = 1, bool bidirectional = true) {
        adj[u].push_back({v, weight});
        if (bidirectional) {
            adj[v].push_back({u, weight});
        }
    }

    // 1. 深度優先搜尋 (DFS)
    void DFS(int start) {
        vector<bool> visited(numV, false);
        cout << "DFS 遍歷順序 (自節點 " << start << " 開始): ";
        DFS_Recursive(start, visited);
        cout << endl;
    }

    void DFS_Recursive(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (auto& edge : adj[u]) {
            int v = edge.first;
            if (!visited[v]) {
                DFS_Recursive(v, visited);
            }
        }
    }

    // 2. 廣度優先搜尋 (BFS)
    void BFS(int start) {
        vector<bool> visited(numV, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS 遍歷順序 (自節點 " << start << " 開始): ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (auto& edge : adj[u]) {
                int v = edge.first;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    // 3. Dijkstra 最短路徑演算法
    void Dijkstra(int start) {
        vector<int> dist(numV, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start}); // {距離, 節點}

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // 輸出結果
        cout << "\nDijkstra 從節點 " << start << " 到各點的最短路徑:\n";
        cout << "節點\t最短距離\n";
        for (int i = 0; i < numV; i++) {
            cout << i << "\t";
            if (dist[i] == INF) cout << "不可達" << endl;
            else cout << dist[i] << endl;
        }
    }

    // 4. 計算連通分量 (Connected Components)
    int countConnectedComponents() {
        vector<bool> visited(numV, false);
        int count = 0;
        for (int i = 0; i < numV; i++) {
            if (!visited[i]) {
                count++;
                // 使用內部的 DFS 來遍歷整個連通塊
                stack<int> s;
                s.push(i);
                visited[i] = true;
                while (!s.empty()) {
                    int u = s.top(); s.pop();
                    for (auto& edge : adj[u]) {
                        if (!visited[edge.first]) {
                            visited[edge.first] = true;
                            s.push(edge.first);
                        }
                    }
                }
            }
        }
        return count;
    }
};

int main() {
    // 建立一個有 6 個節點的圖 (0 到 5)
    Graph g(6);

    // 新增邊 (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 3, 4);
    g.addEdge(3, 5, 11);

    cout << "=== 圖論演算法實作展示 ===\n" << endl;

    // 1. 執行 DFS
    g.DFS(0);

    // 2. 執行 BFS
    g.BFS(0);

    // 3. 執行 Dijkstra
    g.Dijkstra(0);

    // 4. 連通分量
    cout << "\n圖中的連通分量數量: " << g.countConnectedComponents() << endl;

    return 0;
}
