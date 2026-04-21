#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
	int to;
	int weight;

	bool operator==(const Edge& other)const {
		return this->to == other.to;
	}
};

template<typename T,bool IsDirected=true>
class MyGraph {
private:
	int V;
	vector<vector<T>> adj;
	void addReverseEdge(int u, int v) {
		for (const auto& e : adj[v])if (e == u)return;
		adj[v].push_back(u);
	}
public:
	MyGraph(int V) :V(V) {
		adj.resize(V);
	}
	void addEdge(int vertex, T edge) {
		if (vertex < 0 || vertex >= V) {
			cout << "Error:Out of Range to input Graph\n";
			return;
		}
		for (const auto& e : adj[vertex]) {
			if (e == edge) {
				cout << "Error: duplicate edges(" << vertex << ", " << edge << ")\n";
				return;
			}
		}
		adj[vertex].push_back(edge);
		if (!IsDirected) {
			addReverseEdge(vertex, edge);
		}
	}
	void printGraph() {
		for (int i = 0; i < V; i++) {
			for (const auto& neigh : adj[i]) {
				cout << i << "번 정점 - " << neigh << "번 정점\n";
			}
		}
	}
};

template<bool IsDirected>
class MyGraph<Edge,IsDirected> {
private:
	int V;
	vector<vector<Edge>> adj;
	void addReverseEdge(int u, Edge e) {
		int v = e.to;
		for (const auto& e : adj[v])if (e.to == u)return;
		adj[v].push_back({ u,e.weight });

	}
public:
	MyGraph(int V) :V(V) {
		adj.resize(V);
	}
	void addEdge(int vertex, Edge edge) {
		if (vertex < 0 || vertex >= V) {
			cout << "Error:Out of Range to input Graph\n";
			return;
		}
		for (const auto& e : adj[vertex]) {
			if (e == edge) {
				cout << "Error: duplicate edges(" << vertex << ", " << edge.to << ")\n";
				return;
			}
		}
		adj[vertex].push_back(edge);
		if (!IsDirected) {
			addReverseEdge(vertex, edge);
		}
	}
	void printGraph() {
		for (int i = 0; i < V; i++) {
			for (const auto& neigh : adj[i]) {
				cout << i << "번 정점 - " << neigh.to << "번 정점 (거리:" << neigh.weight << ")\n";
			}
		}
	}
};


int main() {

	MyGraph<int> simpleG(5);
	simpleG.addEdge(0, 1);
	simpleG.addEdge(0, 1); // 중복 테스트
	simpleG.addEdge(0, 2);
	simpleG.printGraph();

	MyGraph<Edge> weightG(5);
	weightG.addEdge(0, { 1, 10 });
	weightG.addEdge(0, { 1, 20 }); 
	weightG.addEdge(1, { 2, 5 });
	weightG.printGraph();

	return 0;
}