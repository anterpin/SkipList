#include <bits/stdc++.h>
#include <algorithm>
#include <cstdlib>
using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& arr) {
  if (arr.empty())
    return os << "{}";
  os << '{';
  for (int i = 0; i < (int)arr.size() - 1; i++) {
    os << arr[i] << ", ";
  }
  return os << arr.back() << '}';
}

template <typename Iterator>
void merge_sort(Iterator begin, Iterator end) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  int N = distance(begin, end);
  if (N <= 1) {
    return;
  }
  auto middle = begin + (N >> 1);
  merge_sort(begin, middle);
  merge_sort(middle, end);
  T* tmp = new T[N];
  auto a = begin;
  auto b = middle;
  int i = 0;
  while (a != middle && b != end) {
    if (*a < *b) {
      tmp[i++] = *a++;
    } else {
      tmp[i++] = *b++;
    }
  }
  auto c = b == end ? a : b;
  for (; i < N; i++) {
    tmp[i++] = *c++;
  }
  memcpy(&*begin, tmp, N * sizeof(T));
  delete[] tmp;
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  int N = distance(begin, end);
  if (N <= 1) {
    return;
  }
  // srand(*begin);
  int chosen = rand() % N;
  auto pos = begin;
  auto pivot = end - 1;
  swap(*(begin + chosen), *pivot);
  for (auto iter = begin; iter != pivot; iter++) {
    if (*iter < *pivot) {
      swap(*pos, *iter);
      pos++;
    }
  }
  swap(*pivot, *pos);
  quick_sort(begin, pos);
  quick_sort(pos + 1, end);
}

template <typename Iterator>
void _heapify_linear(Iterator current, Iterator begin, Iterator end) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  for (auto iter = begin; iter < end;) {
    int i = distance(begin, current);
    auto left = begin + (i << 1) + 1;
    auto right = begin + (i << 1) + 2;
    auto ma = current;
    if (left<end&& * left> * ma) {
      ma = left;
    }
    if (right<end&& * right> * ma) {
      ma = right;
    }
    if (ma == current) {
      break;
    }
    swap(*ma, *current);
    iter = ma;
  }
}

template <typename Iterator>
void _heapify(Iterator current, Iterator begin, Iterator end) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  int i = distance(begin, current);
  auto left = begin + (i << 1) + 1;
  auto right = begin + (i << 1) + 2;
  auto ma = current;
  if (left<end&& * left> * ma) {
    ma = left;
  }
  if (right<end&& * right> * ma) {
    ma = right;
  }
  if (ma != current) {
    swap(*ma, *current);
    _heapify(ma, begin, end);
  }
}
template <typename Iterator>
void heap_sort(Iterator begin, Iterator end) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  // make_heap(begin, end);
  int N = distance(begin, end);
  for (int i = N >> 1; i >= 0; i--) {
    _heapify_linear(begin + i, begin, end);
  }
  for (int i = N - 1; i >= 1; i--) {
    swap(*begin, *(begin + i));
    // pop_heap(begin, begin + i);
    _heapify_linear(begin, begin, begin + i);
  }
}
template <typename Iterator>
typename std::iterator_traits<Iterator>::value_type quick_select(Iterator begin,
                                                                 Iterator end,
                                                                 int k) {
  using T = typename std::iterator_traits<Iterator>::value_type;
  int N = distance(begin, end);
  assert(0 < N);
  assert(k < N);
  assert(0 <= k);
  if (N == 1) {
    return *begin;
  }
  int chosen = rand() % N;
  auto pos = begin;
  auto pivot = end - 1;
  swap(*(begin + chosen), *pivot);
  for (auto iter = begin; iter != end; iter++) {
    if (*iter < *pivot) {
      swap(*pos, *iter);
      pos++;
    }
  }
  swap(*pivot, *pos);
  int i = distance(begin, pos);
  if (i == k) {
    return *pos;
  } else if (i < k) {
    return quick_select(pos + 1, end, k - i - 1);
  } else {
    return quick_select(begin, pos, k);
  }
}
int main() {
  srand(time(0));
  vector<int> arr{3, 2, 4, 1, 5, 0};
  heap_sort(arr.begin(), arr.end());
  cout << arr << '\n';
  // cout << quick_select(arr.begin(), arr.end(), 4) << '\n';
  return 0;
}
