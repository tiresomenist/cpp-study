#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <queue>

#define INF 2147483000

using namespace std;


vector<int>generateRandomVector(int size, int min, int max) {
	vector<int> res;
	res.reserve(size);

	mt19937 gen(static_cast<unsigned int>(time(NULL)));
	uniform_int_distribution<int> dis(min, max);

	for (int i = 0; i < size; i++) {
		res.push_back(dis(gen));
	}
	return res;
}

int partition(vector<int>& arr, int low, int high) {
	int pivot = arr[high];//피벗, 기준점
	int i = low - 1;	//피벗보다 작은값의 갯수
	for (int j = low; j < high; j++) {
		if (pivot >= arr[j]) {	//피벗보다 지금 보는 값이 작거나 같으면
			i++;	//i값을 늘리고
			swap(arr[i], arr[j]);	//그 공간에 작은 값을 넣는다.
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);	//피벗의 최종위치
}

void quickSort(vector<int>&arr,int low,int high) {
	if (low < high) {
		int pivot = partition(arr, low, high);
		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}


void merge(vector<int>&arr, int l, int m, int r) {
	int i = l;
	int j = m + 1;
	vector<int>temp;
	for (int k = 0; k < r - l + 1; k++) {
		if (arr[i] <= arr[j]) {
			temp.push_back(arr[i]);
			i++;
			if (i == m + 1) {
				//i쪽 다넣었으니 j쪽 전부 푸시
				for (int n = j; n < r + 1; n++) {
					temp.push_back(arr[n]);
				}
				break;
			}
		}
		else {
			temp.push_back(arr[j]);
			j++;
			if (j == r + 1) {
				//j쪽 다넣었으니 i쪽 전부 푸시
				for (int n = i; n < m + 1; n++) {
					temp.push_back(arr[n]);
				}
				break;
			}
		}
	}
	for (int k = 0; k < temp.size(); k++) {
		arr[l + k] = temp[k];
	}
}

void mergeSort(vector<int>&arr,int l,int r) {
	if (l >= r)return;
	int mid = l + (r - l) / 2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid + 1, r);

	merge(arr, l, mid, r);
}

struct Node {
	int id;
	int x, y;
	int g, h, f;
	int parentId;
	Node(int id, int x, int y) :id(id), x(x), y(y), g(INF), h(0), f(INF), parentId(-1) {}

	bool operator>(const Node& other)const {
		return f > other.f;
	}
	bool operator==(const Node& other)const {
		return x == other.x && y == other.y;
	}
};

//노드 리스트
vector<Node*> nodeList;
//인접 리스트
vector<vector<pair<int, int>>> adj;

struct compare {
	bool operator()(Node* a, Node* b) {
		return a->f > b->f;
	}
};

void AStar (int s,int t) {
	priority_queue<Node*, vector<Node*>, compare> openList;
	Node* sNode = nodeList[s];
	Node* tNode = nodeList[t];

	sNode->g = 0;
	sNode->h = abs(tNode->x - sNode->x) + abs(tNode->y - sNode->y);
	//맨하탄 거리.
	sNode->f = sNode->g + sNode->h;
	openList.push(sNode);

	while (!openList.empty()) {
		Node* cur = openList.top();
		openList.pop();
		if (cur->id == t) break;
		for (auto& edge : adj[cur->id]) {
			int nextId = edge.first;
			int weight = edge.second;
			Node* nextNode = nodeList[nextId];

			int newG = cur->g + weight;
			if (newG < nextNode->g) {
				nextNode->g = newG;
				nextNode->h = abs(tNode->x - nextNode->x) + abs(tNode->y - nextNode->y);
				nextNode->f = nextNode->g + nextNode->h;
				nextNode->parentId = cur->id;

				openList.push(nextNode);
			}
		}
	}
}

void printPath(int t) {
	int cur = t;
	while (cur != -1) {
		cout << cur << "<-";
		cur = nodeList[cur]->parentId;

	}
	cout << "START\n";
}


//다익스트라 알고리즘의 인풋, 각 정점의 거리를 저장하는 배열
vector<pair<int,int>> dInput[10001];

void dijkstra(int start,int size) {
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,start });
	vector<int> dist;
	dist.resize(size + 1);
	fill(dist.begin(),dist.end(),INF);
	dist[start] = 0;
	while (!pq.empty()) {
		int distance = -pq.top().first;	//최소힙
		int cur = pq.top().second;
		pq.pop();

		if (dist[cur] < distance) continue;
		for (auto& edge : dInput[cur]) {
			int cost = distance + edge.second;
			if (cost < dist[edge.first]) {
				dist[edge.first] = cost;
				pq.push({ -cost,edge.first });
			}
		}
	}
	for (auto& t : dist) {
		cout << t << '\n';
	}
}

int fwGraph[101][101]; //노드i에서j까지의 거리.

void FloydInit(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j) fwGraph[i][j] = INF;
			else fwGraph[i][j] = 0;
		}
	}
}
void FloydWarshall(int n) {	
	vector<vector<int>> root(n + 1, vector<int>(n + 1, INF));
	for (int k = 1; k <= n; k++) { // 중간 거쳐가는 점
		for (int a = 1; a <= n; a++) { // 출발점
			for (int b = 1; b <= n; b++) { // 도착점
				if (fwGraph[a][k] == INF || fwGraph[k][b] == INF)continue;
				if (fwGraph[a][b] > fwGraph[a][k] + fwGraph[k][b]) {
					fwGraph[a][b] = fwGraph[a][k] + fwGraph[k][b];
					//경로는 k.임을 표시할수있다.
					root[a][b] = k;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << fwGraph[i][j] << " ";
		}
		cout << '\n';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << root[i][j] << " ";
		}
		cout << '\n';
	}

}

//5. Union-Find 구조 
struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n, 1);
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]); // 경로 압축 (Path Compression)
	}

	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;

		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v; // rank가 더 작은 u를 v 밑에 붙임
		if (rank[u] == rank[v]) rank[v]++;
	}
};

//크루스칼용 간선 구조체
struct Edge {
	int u, v, weight;
	bool operator<(const Edge& o) const {
		return weight < o.weight;
	}
};


//6.MST
void kruskal(int V, vector<Edge>& edges) {
	
	DisjointSet temp(V + 1);
	sort(edges.begin(), edges.end());
	int weightSum = 0;
	int count = 0;
	for (const auto& edge : edges) {
		if (temp.find(edge.v) != temp.find(edge.u)) {
			temp.merge(edge.u, edge.v);
			weightSum += edge.weight;
			count++;
			if (count == V - 1) break;
		}
	}
	cout << "Kruskal Weight Sum: " << weightSum << '\n';
}

void prim(int V, int startNode, vector<vector<pair<int, int>>>& adjList) {
	
	vector<bool> visited(V + 1, false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({ 0,startNode });
	//가중치,정점번호를 push.
	int weightSum = 0;
	int count = 0;
	while (!q.empty()) {
		pair<int, int> target = q.top();
		q.pop();
		int weight = target.first;
		int curNode = target.second;
		if (visited[curNode]) continue;
		visited[curNode] = true;
		weightSum += weight;
		count++;
		if (count == V)break;

		for (const auto& edge : adjList[curNode]) {
			int nextNode = edge.first;
			int nextWeight = edge.second;
			if (!visited[nextNode]) {
				q.push({ nextWeight,nextNode });
			}
		}
	}
}

int main() {

	//1.퀵소트/머지소트
	/*
	vector<int> data = generateRandomVector(15, 0, 1050);
	cout << "퀵 소트 정렬 전: ";
	for (int n : data) cout << n << " ";
	cout << "\n";

	quickSort(data, 0, data.size() - 1);

	cout << "정렬 후: ";
	for (int n : data) cout << n << " ";
	cout << "\n";
	vector<int> data2 = generateRandomVector(15, 0, 1050);
	cout << "머지 소트 정렬 전: ";
	for (int n : data2) cout << n << " ";
	cout << "\n";

	mergeSort(data2, 0, data2.size() - 1);

	cout << "정렬 후: ";
	for (int n : data2) cout << n << " ";
	cout << "\n";
	*/

	//2.A*알고리즘
	/*
	priority_queue<Node> input;
	nodeList.push_back(new Node(0, 0, 0));
	nodeList.push_back(new Node(1, 2, 0));
	nodeList.push_back(new Node(2, 1, 2));
	nodeList.push_back(new Node(3, 3, 2));
	nodeList.push_back(new Node(4, 4, 0));
	
	adj.resize(nodeList.size());

	adj[0].push_back({ 1,2 });
	adj[0].push_back({ 2,3 });
	adj[2].push_back({ 3,2 });
	adj[3].push_back({ 4,2 });

	AStar(0, 4);
	printPath(4);
	for (auto node : nodeList)delete node;
	*/

	//3.Dijkstar 알고리즘
	// 정점 6개, 간선 8개 구성
	/*
	dInput[1].push_back({ 2, 2 });
	dInput[1].push_back({ 3, 5 });
	dInput[1].push_back({ 4, 1 });
	dInput[4].push_back({ 3, 3 });
	dInput[2].push_back({ 3, 3 });
	dInput[3].push_back({ 6, 5 });
	dInput[4].push_back({ 5, 1 });
	dInput[5].push_back({ 6, 2 });

	dijkstra(1,6); // 1번 노드 출발
	*/
	//4.플로이드-워셜 알고리즘
	/*
	FloydInit(4);
	fwGraph[1][2] = 5;
	fwGraph[1][4] = 9;
	fwGraph[2][3] = 2;
	fwGraph[3][1] = 3;
	fwGraph[3][4] = 1;
	fwGraph[4][1] = 1;
	FloydWarshall(4);
	*/



	return 0;
}