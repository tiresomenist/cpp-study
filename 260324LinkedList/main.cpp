#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;	
	Node* next;
	Node(int val):data(val),next(nullptr){}
};

struct Node_Smart {
	int data;
	unique_ptr<Node_Smart> next;
	Node_Smart(int val):data(val),next(nullptr){}
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList():head(nullptr){}

	void Append(int val) {
		if (!head) {
			head = new Node(val);
			return;
		}
		Node* cur = head;
		while (cur->next)cur = cur->next;
		cur->next = new Node(val);
	}

	void Display() {
		Node* cur = head;
		while (cur) {
			cout << cur->data << "->";
			cur = cur->next;
		}
		cout << "NULL\n";
	}

	~LinkedList() {
		Node* cur = head;
		while (cur) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}
	}
};

//스마트포인터 사용버전
class LinkedList_Smart {
private:
	unique_ptr<Node_Smart> head;
public:
	LinkedList_Smart() :head(nullptr) {}

	void Append(int val) {
		if (!head) {
			head = make_unique<Node_Smart>(val);
			return;
		}
		Node_Smart* cur = head.get();	//unique_ptr의 소유권을 뺏지않고, 주소값만 빌려온다.
		while (cur->next) {
			cur = cur->next.get();
		}
		cur->next = make_unique<Node_Smart>(val);
	}

	void Display() {
		Node_Smart* cur = head.get();
		while (cur) {
			cout << cur->data << "->";
			cur = cur->next.get();
		}
		cout << "NULL\n";
	}

	~LinkedList_Smart() {
		//스마트 포인터에 의해 자동으로 메모리 해제됨.
	}
};

int main() {
	LinkedList list;
	list.Append(10);
	list.Append(20);
	list.Append(30);
	list.Display();

	LinkedList_Smart list_S;
	list_S.Append(40);
	list_S.Append(50);
	list_S.Append(60);
	list_S.Display();

	return 0;
}