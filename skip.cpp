#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
struct SkipNode {
  K key;
  V value;
  vector<SkipNode*> next;
  SkipNode(K key, V value, int level) : key{key}, value{value} {
    next.resize(level + 1, nullptr);
  }
};

template <typename K, typename V>
class SkipList {
  vector<SkipNode<K, V>*> head;
  size_t _size;

 public:
  SkipList() : _size(0) { head.resize(1, nullptr); }
  int search(K key) {
    int N = head.size();
    auto node = head[N - 1];
    for (int i = N - 1; i >= 0; i--) {
      while (node && node->key < key) {
        node = node->next[i];
      }
    }
    if (!node) {
      return -1;
    } else {
      return node->value;
    }
  }
  size_t size() { return _size; }
  void insert(K key, V value) {
    int N = head.size();
    vector<SkipNode<K, V>*>* nodes = &head;
    vector<SkipNode<K, V>**> update(N);
    for (int i = N - 1; i >= 0; i--) {
      while ((*nodes)[i] && (*nodes)[i]->key < key) {
        nodes = &(*nodes)[i]->next;
      }
      update[i] = &(*nodes)[i];
    }
    if (*update[0] && (*update[0])->key == key) {
      (*update[0])->value = value;
      return;
    }
    int new_level = 0;
    while (_size && new_level < N + 1 && rand() & 1) {  // coin choice
      new_level++;
    }
    _size++;
    auto new_node = new SkipNode<K, V>(key, value, new_level);
    for (int i = N - 1; i >= 0; i--) {
      new_node->next[i] = *update[i];
      *update[i] = new_node;
    }
    if (new_level == N) {
      head.push_back(
          new_node);  // the HEAD COULD REALLOCATE, better doing the everything
                      // is done, it TOOK ME SOMETIME DO DISCOVER THIS
    }
  }
  void remove(K key) {
    int N = head.size();
    vector<SkipNode<K, V>*>* nodes = &head;
    vector<SkipNode<K, V>**> update(N);
    for (int i = N - 1; i >= 0; i--) {
      while ((*nodes)[i] && (*nodes)[i]->key < key) {
        nodes = &(*nodes)[i]->next;
      }
      update[i] = &(*nodes)[i];
    }
    if (!*update[0] || (*update[0])->key != key) {  // value doesn't exist
      return;
    }
    auto node = *update[0];
    for (int i = node->next.size() - 1; i >= 0; i--) {
      *update[i] = node->next[i];
      node->next[i] = nullptr;
      if (!head[i] && _size > 1) {
        head.pop_back();
      }
    }
    delete node;
    _size--;
  }
  friend ostream& operator<<(ostream& os, const SkipList& skip) {
    // O(n^2)
    for (int level = skip.head.size() - 1; level > 0; level--) {
      for (auto node = skip.head[0]; node; node = node->next[0]) {
        if (node->next.size() > level) {
          os << node->key << ' ';
        } else {
          os << "  ";
        }
      }
      os << '\n';
    }
    for (auto node = skip.head[0]; node; node = node->next[0]) {
      os << node->key << ' ';
    }
    return os;
  }
};
int main() {
  // cout << time(0) << '\n';
  srand(time(0));
  SkipList<int, int> skip;
  skip.insert(7, 3);
  skip.insert(8, 1);
  skip.insert(2, 1);
  skip.insert(4, 1);
  cout << "size " << skip.size() << '\n';
  skip.remove(8);
  cout << "size " << skip.size() << '\n';
  skip.insert(9, 1231);
  cout << skip << '\n';
  cout << skip.search(9) << '\n';
  cout << skip.search(13) << '\n';
  return 0;
}

