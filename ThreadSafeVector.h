#pragma once
#pragma once
#include <vector>
#include <mutex>
#include <iostream>
using namespace std;
template<typename T>
class ThreadSafeVector {

	vector<T> vec;
	mutex update_mutex;
public:
	ThreadSafeVector() {

	}
	void add(T x) {
		lock_guard<mutex> lg(update_mutex);
		vec.push_back(x);
		cout << "Added : " << x << endl;
	}

	void remove(T x) {
		lock_guard<mutex> lg(update_mutex);
		int pos = find(x);
		if (pos >= 0) {
			auto it = vec.begin();
			vec.erase(it+pos);
			cout << "Removed : " << x << endl;
		}
		else{
			cout << "Not found\n";
		}
		
	}
	void show() {
		lock_guard<mutex> lg(update_mutex);
		for (auto x : vec) {
			cout << x << " ";
		}
		cout << endl;
	}
	int find(T x) {
		int pos = 0;
		for (auto y : vec) {
			if (x == y) {
				return pos;
			}
			pos++;
		}
		return -1;
	}
	T at(int pos) {
		lock_guard<mutex> lg(update_mutex);
		return vec.at(pos);
	}

	//friend ostream& operator << (ostream&, ThreadSafeMap<Key, Value>&);
	template <typename T>
	friend ostream& operator <<(ostream& os, const ThreadSafeVector<T>& t)
	{
		for (auto x : t.vec) {
			cout << x << " " << endl;
		}
		cout << endl;

		return os;
	}
};
