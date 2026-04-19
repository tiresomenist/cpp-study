#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class MyHashTable
{
public:
	MyHashTable();
	~MyHashTable();

	void insert(string key, int value) {
		int index = hashFunction(key);
		for (auto& pair : table[index]) {
			if (pair.first == key) {
				pair.second = value;
				return;
				//이미 있는 키값이면 업데이트
			}
		}
		table[index].push_back({ key,value });
		//새로운 키값이면 푸시
	}

	int get(string key) {
		int index = hashFunction(key);
		for (auto& pair : table[index]) {
			if (pair.first == key) return pair.second;
		}
		return -1;
	}


private:
	static const int TABLE_SIZE = 10;
	vector<list<pair<string, int>>> table;

	int hashFunction(string key) {
		int hash = 0;
		for (char c : key)hash += c;
		return hash % TABLE_SIZE;
	}

};

MyHashTable::MyHashTable()
{
	table.resize(TABLE_SIZE);
}

MyHashTable::~MyHashTable()
{
}

int main() {
	MyHashTable mh;

	mh.insert("Apple", 100);
	mh.insert("Banana", 200);
	mh.insert("Cherry", 300);

	mh.insert("ABC", 1);
	mh.insert("CBA", 2);
	mh.insert("BAC", 3);

	cout << mh.get("Apple") << '\n';
	cout << mh.get("Banana") << '\n';
	cout << mh.get("Cherry") << '\n';
	cout << mh.get("Mango") << '\n';
	cout << mh.get("ABC") << '\n';
	cout << mh.get("CBA") << '\n';
	cout << mh.get("BAC") << '\n';
	return 0;
}