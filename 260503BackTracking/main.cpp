#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>

using namespace std;

void randomInput(int n, vector<int>&input) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 100);
	for (int i = 0; i < n; i++) {
		input[i] = distribution(generator);
	}
}

void backTracking(const vector<int>&input,vector<int>&picked,int index,int m) {
	if (picked.size() == m) {
		for (int id : picked)cout << id << " ";
		cout << '\n';
		return;
	}
	for (int i = index; i < input.size(); i++) {
		picked.push_back(input[i]);
		backTracking(input, picked, (i + 1), m);
		picked.pop_back();
	}
}

int main() {
	int n, m;
	cout << "총 개수:";
	cin >> n;
	cout << "선택 개수:";
	cin >> m;
	vector<int> input;
	input.resize(n);
	randomInput(n, input);
	cout << "현재 배열: ";
	for (auto& e : input) {
		cout << e << " ";
	}
	cout << '\n';

	cout << "경우의 수\n";
	vector<int> picked;
	backTracking(input, picked, 0, m);
	return 0;

}