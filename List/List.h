#pragma once
#include "ListNode.h"

template <typename T>
class List
{
private:
  int _size;
  ListNodePosition(T) header;  // 头哨兵
  ListNodePosition(T) trailer; // 尾哨兵

protected:
  void init();
  int clear(); // 清除所有节点
  void copyNodes(ListNodePosition(T) p, int n);
  void merge(ListNodePosition(T), int, List<T> &, ListNodePosition(T), int);
  void mergeSort(ListNodePosition(T), int);
  void selectionSort(ListNodePosition(T), int);
  void insertionSort(ListNodePosition(T), int);

public:
  // 构造函数
  List() { init(); };
  List(List<T> const &L); // 复制列表
  List(List<T> const &L, Rank s, int n);
  List(ListNodePosition(T) p, int n);

  ~List();

  // 只读访问接口
  Rank size() const { return _size; }
  bool isEmpty() const { return _size <= 0; }
  T &operator[](Rank r) const; // 重载，支持循秩讵问(效率低)
  ListNodePosition(T) first() const { return header->succ; }
  ListNodePosition(T) last() const { return trailer->pred; }
  bool isValid(ListNodePosition(T) p)
  {
    return p && p != header && p != trailer;
  }
  int disordered() const;
  ListNodePosition(T) find(T const &e) const
  {
    return find(e, _size, trailer);
  }
  ListNodePosition(T) find(T const &e, int n, ListNodePosition(T) p) const;
  ListNodePosition(T) search(T const &e)
  {
    return search(e, _size, trailer);
  };
  ListNodePosition(T) search(T const &e, int n, ListNodePosition(T) p) const;
  ListNodePosition(T) selectMax()
  {
    return selectMax(header->succ, _size);
  }
  ListNodePosition(T) selectMax(ListNodePosition(T) p, int n);
  // 可写访问接口
  ListNodePosition(T) insertAsFirst(T const &e);
  ListNodePosition(T) insertAsLast(T const &e);
  ListNodePosition(T) insertA(ListNodePosition(T) p, T const &e);
  ListNodePosition(T) insertB(ListNodePosition(T) p, T const &e);
  T remove(ListNodePosition(T) p);
  void merge(List<T> &L)
  {
    merge(first(), _size, L, L.first(), L.size());
  }
  void sort(ListNodePosition(T) p, int n);
  void sort()
  {
    sort(first(), _size);
  }
  int deduplicate();
  int uniquify();
  void reverse();
  // 遍历
  void traverse(void (*)(T &));
  template <typename VST>
  void traverse(VST &);
};

#include "List_implementation.h"