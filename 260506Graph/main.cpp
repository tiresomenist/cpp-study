#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>

using namespace std;

using namespace std;

vector<int> adj[101];
int visited[101]; // 0: 미방문 1: 탐색 중 2: 탐색 완료
int color[101];   // 이분 그래프 판별용 (0: 무색, 1: 빨강, -1: 파랑)
int N, M;

// 1. 연결 요소 세기
// 3. 이분 그래프 판별
bool isBipartite = true;
void dfs_components(int now, int c) {
    visited[now] = 2;
    color[now] = c;

    for (int next : adj[now]) {
        if (color[next] == 0) {
            dfs_components(next, -c);   //인접 칸을 다른 색으로 색칠
        }
        else if (color[next] == color[now]) {
            isBipartite = false; // 인접 노드가 같은 색이면 이분 그래프 아님
        }
    }
}

// 2. 방향 그래프 사이클 감지
bool hasCycle = false;
void dfs_cycle(int now) {
    visited[now] = 1; // 탐색중

    for (int next : adj[now]) {
        if (visited[next] == 0) {
            dfs_cycle(next);
        }
        else if (visited[next] == 1) {
            hasCycle = true; // 탐색 중인 노드를 다시 만나면 사이클
        }
    }
    visited[now] = 2; // 탐색 완료
}

int main() {
    N = 6; M = 5;

    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);
    adj[4].push_back(5); adj[5].push_back(4);

    // 연결 요소 개수, 이분 그래프 판별
    int components = 0;
    for (int i = 1; i <= N; i++) {
        if (color[i] == 0) {
            components++;   //dfs를 호출한 횟수
            dfs_components(i, 1);   //dfs
        }
    }

    cout << "1. 연결 요소 개수: " << components << "\n";
    cout << "2. 이분 그래프 : " << (isBipartite ? "Yes" : "No") << "\n";

    // [실행 2] 방향 사이클 감지
    for (int i = 1; i <= N; i++) visited[i] = 0; // 방문 기록 초기화
    adj[3].push_back(1);

    for (int i = 1; i <= N; i++) {
        if (visited[i] == 0) dfs_cycle(i);
    }
    cout << "3. 방향 사이클 : " << (hasCycle ? "Yes" : "No") << "\n";

    return 0;
}