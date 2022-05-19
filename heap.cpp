#include <bits/stdc++.h>
using namespace std;

class Heap {
  vector<int> arr;
  function<bool(int, int)> comparison = less<int>();
  void _reverse_heapify(int i) {
    int parent = i >> 1;
    if (comparison(arr[i], arr[parent])) {
      swap(arr[i], arr[parent]);
      _reverse_heapify(parent);
    }
  }
  void _reverse_heapify_linear() {
    for (int i = arr.size() - 1; i > 0 && comparison(arr[i], arr[i >> 1]);
         i >>= 1) {
      swap(arr[i], arr[i >> 1]);
    }
  }
  void _heapify_linear() {
    int N = arr.size();
    for (int i = 0; i < N;) {
      int left = (i << 1) + 1;
      int right = (i << 1) + 2;
      int mi = i;
      if (left < N && comparison(arr[left], arr[mi])) {
        mi = left;
      }
      if (right < N && comparison(arr[right], arr[mi])) {
        mi = right;
      }
      if (mi == i) {
        break;
      }
      swap(arr[i], arr[mi]);
      i = mi;
    }
  }
  void _heapify(int i) {  // top to bottom
    int left = (i << 1) + 1;
    int right = (i << 1) + 2;
    int mi = i;
    int N = arr.size();
    if (left < N && comparison(arr[left], arr[mi])) {
      mi = left;
    }
    if (right < N && comparison(arr[right], arr[mi])) {
      mi = right;
    }
    if (mi != i) {
      swap(arr[i], arr[mi]);
      _heapify(mi);
    }
  }

 public:
  Heap(){};
  Heap(function<bool(int, int)> comp) : comparison(comp){};
  void insert(int e) {
    arr.push_back(e);
    _reverse_heapify_linear();
  }
  int peek() { return arr.front(); }
  void remove() {
    arr[0] = arr.back();
    arr.pop_back();
    _heapify_linear();
  }
  size_t size() { return arr.size(); }
};
int main() {
  // auto comp = [](int a, int b) { return a * a < b * b; };
  Heap h;
  h.insert(-2);
  h.insert(4);
  h.insert(2);
  h.insert(1);
  h.insert(5);
  while (h.size()) {
    cout << h.peek() << '\n';
    h.remove();
  }

  return 0;
}

