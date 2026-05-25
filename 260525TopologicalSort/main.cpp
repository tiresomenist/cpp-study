#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void topologicalSort(int V, vector<vector<int>>& adj, vector<int>& indegree) {
    queue<int> q;
    vector<int> result;
    for (int i = 1; i <= V; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        result.push_back(curr);

        for (int next : adj[curr]) {
            indegree[next]--; // 진입차수 감소
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    //정렬된 정점의 개수가 전체 정점 개수보다 적으면 사이클이 존재함
    if (result.size() < V) {
        cout << "오류: 사이클 존재.\n";
        return;
    }

    for (int node : result) cout << node << " ";
    cout << "\n";
}

int main() {
    int V1 = 5;
    vector<vector<int>> adj1(V1 + 1);
    vector<int> indegree1(V1 + 1, 0);

    adj1[1].push_back(2); indegree1[2]++;
    adj1[2].push_back(3); indegree1[3]++;
    adj1[1].push_back(4); indegree1[4]++;
    adj1[2].push_back(5); indegree1[5]++;
    adj1[4].push_back(5); indegree1[5]++;

    topologicalSort(V1, adj1, indegree1);


    int V2 = 3;
    vector<vector<int>> adj2(V2 + 1);
    vector<int> indegree2(V2 + 1, 0);

    adj2[1].push_back(2); indegree2[2]++;
    adj2[2].push_back(3); indegree2[3]++;
    adj2[3].push_back(1); indegree2[1]++;

    topologicalSort(V2, adj2, indegree2);

    return 0;
}