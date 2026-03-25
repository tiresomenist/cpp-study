#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int val): data(val),left(nullptr),right(nullptr){}
};

class BST {	//이진 탐색 트리의 구현
private:
	Node* root;

	Node* insert(Node* node, int val) {
		if (!node)return new Node(val);
		if (val < node->data)
			node->left = insert(node->left, val);
		//들어온 값이 현재 노드보다 작으면 노드의 왼쪽 자식으로 배치
		else if (val > node->data)
			node->right = insert(node->right, val);
		//들어온 값이 현재 노드보다 크면 노드의 오른쪽 자식으로 배치
		return node;
	}

	bool search(Node* node, int val) {
		if (!node)return false;
		else if (node->data == val) return true;
		else if (val < node->data)return search(node->left, val);
		else return search(node->right, val);
	}
	void clear(Node* node) {
		if (!node)return;
		clear(node->left);
		clear(node->right);
		delete node;
		//후위순회를 통해 메모리누수없이 안전하게 delete함.
		//스마트 포인터를 이용하면 이런 방식을 사용하지않아도 안전하게 삭제가능.
	}
	Node* findMin(Node* node) {
		while (node && node->left) node = node->left;
		return node;
	}
	Node* remove(Node* node, int target) {
		if (!node) return nullptr;
		if (target < node->data)
			node->left = remove(node->left, target);
		else if (target > node->data)
			node->right = remove(node->right, target);
		else {
			if (!node->left) {
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right) {
				Node* temp = node->left;
				delete node;
				return temp;
			}
			Node* temp = findMin(node->right);
			node->data = temp->data;
			node->right = remove(node->right, temp->data);
		}
		return node;
	}

public:
	BST() :root(nullptr) {}
	~BST() { clear(root); }
	void Insert(int val) { root = insert(root, val); }
	bool Search(int val) { return search(root, val); }
	void Remove(int val) { root = remove(root, val); }
};

int main() {
	BST tree;
	tree.Insert(50);
	tree.Insert(20); 
	tree.Insert(10);
	tree.Insert(40);
	tree.Insert(30);
	//이진 탐색 트리에서 최악의 경우인 데이터 쏠린 경우. 탐색 O(N)이 걸림.

	cout << (tree.Search(30) ? "데이터 있음\n" : "데이터 없음\n");
	tree.Remove(30);
	cout << "타겟 데이터 삭제\n";
	cout << (tree.Search(30) ? "데이터 있음\n" : "데이터 없음\n");
	return 0;
}