#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct point {
    int x, y, dist;
};

int maze[5][5] = {
    {1, 0, 1, 1, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1}
};
bool visited[5][5] = { false, };

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int BFS() {
    memset(visited, false, sizeof(visited));
    queue<point> q;
    q.push({ 0,0,1 });
    visited[0][0] = true;
    while (!q.empty()) {
        point cur = q.front();
        q.pop();
        if (cur.x == 4 && cur.y == 4)return cur.dist;

        for (int i = 0; i < 4; i++) {
            int curX = cur.x + dx[i];
            int curY = cur.y + dy[i];

            if (curX >= 0 && curX < 5 && curY >= 0 && curY < 5) {
                if (!visited[curX][curY]&&maze[curX][curY]==1) {
                    visited[curX][curY] = true;
                    q.push({ curX,curY, cur.dist + 1 });
                }
            }
        }
    }
    return -1;
}

int main() {
    int result = BFS();

    if (result != -1) {
        cout << "최단 거리: " << result << endl;
    }
    else {
        cout << "목적지에 도달할 수 없습니다." << endl;
    }

    return 0;
}