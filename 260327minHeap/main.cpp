#include <iostream>
#include <vector>

using namespace std;

class minHeap {
private:
	vector<int>heap;
public:
	minHeap() {

	}
	void push(int value) {
		heap.push_back(value);
		int cur = heap.size() - 1;
		while (cur > 0) {
			if (heap[(cur - 1) / 2] > heap[cur]) {
				int temp = heap[(cur - 1) / 2];
				heap[(cur - 1) / 2] = heap[cur];
				heap[cur] = temp;
				cur = (cur - 1) / 2;
			}
			else break;
		}
	}
	int pop() {
		if (heap.empty()) return -1;
		//비어있을때 예외처리
		int temp = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		int cur = 0;
		while (cur * 2 + 1 < heap.size()) {
			int right = cur * 2 + 2;
			int left = cur * 2 + 1;
			int smaller = left;
			if (right < heap.size() && heap[right] < heap[left]) smaller = right;
			if (heap[cur] < heap[smaller])break;
			int temp2 = heap[cur];
			heap[cur] = heap[smaller];
			heap[smaller] = temp2;
			cur = smaller;
		}
		return temp;
	}
	bool empty() { return heap.empty(); }
};


int main() {

	return 0;
}