#pragma once

#include <stdlib.h>
#include <algorithm>
#include "Vector.h"

/**
 * 向量空间不足时扩容
*/
template <typename T>
void Vector<T>::expand()
{
  if (_size < _capacity)
  {
    return;
  }
  if (_capacity < DEFAULT_CAPACITY)
  {
    _capacity = DEFAULT_CAPACITY;
  }
  T *oldElem = _elem;
  _elem = new T[_capacity <<= 1];
  for (int i = 0; i < _size; i++)
  {
    _elem[i] = oldElem[i];
  }
  delete[] oldElem;
}

/** 
 * 填装因子过小时，压缩向量所占空间
*/
template <typename T>
void Vector<T>::shrink()
{
  if (_capacity < DEFAULT_CAPACITY << 1)
  {
    return;
  }

  if (_capacity < _size << 2)
  {
    return;
  }

  T *oldElem = _elem;
  // TODO: new T 是啥操作
  _elem = new T[_capacity >>= 1];

  for (int i = 0; i < _size; i++)
  {
    _elem[i] = oldElem[i];
  }
  // TODO: delete[] 是什么操作
  delete[] oldElem;
}

template <typename T> //元素类型
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{                                           //以数组区间A[lo, hi)为蓝本复制向量
  _elem = new T[_capacity = 2 * (hi - lo)]; //分配空间
  for (_size = 0; lo < hi; _size++, lo++)   //A[lo, hi)内的元素逐一
    _elem[_size] = A[lo];                   //复制至_elem[0, hi - lo)
}

/** 
 * 重载 [] 操作符，通过秩直接引用元素
*/
template <typename T>
T &Vector<T>::operator[](Rank r) const
{
  return _elem[r];
}

/**
 * 区间置乱接口
*/
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
  T *V = _elem + lo;
  for (Rank i = hi - lo; i > 0; i--)
  {
    swap(V[i - 1], V[rand() % i]);
  }
}

/**
 * 判等器与比较器
 * 
*/
template <typename T>
static bool lt(T *a, T *b)
{
  return lt(*a, *b);
}

template <typename T>
static bool lt(T &a, T &b)
{
  return a < b;
}

template <typename T>
static bool eq(T *a, T *b)
{
  return eq(*a, *b);
}

template <typename T>
static bool eq(T &a, T &b)
{
  return a == b;
}

/**
 * 无序查找
 * 复杂度：O(n)
 * 
*/
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
  while ((lo < hi--) && (e != _elem[hi]))
    ;
  return hi;
}

/**
 * 插入
 * 复杂度：O(n)
*/
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
  expand(); //若有必要，扩容
  for (int i = _size; i > r; i--)
  {
    _elem[i] = _elem[i - 1];
  }
  _elem[r] = e;
  _size++;
  return r;
}

/**
 * 删除
 * 区间删除 remove(lo, hi)
 * 单个删除 remove(r)
 * 
 * 乍看起来，利用后者即可实现前者:令r从hi - 1到lo递减，反复 调用remove(r)。
 * 因数组中元素的地址必须连续，故每删除一个元素，所有后继元素都需向前移动一个单元。 
 * 若后继元素共有m = _size - hi个，则对remove(r)的每次调用都需移动m次;对于整个区间，
 * 元素移动的次数累计将达到m*(hi - lo)
 * 
 * 实际可行的思路恰好相反，应将单元素删除视作区间删除的特例，并基于后者来实现前者。
*/
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
  if (lo == hi)
    return 0;
  while (hi < _size)
  {
    _elem[lo++] = _elem[hi++];
  }
  _size = lo;
  shrink();
  return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
  T e = _elem[r];
  remove(r, r + 1);
  return e;
}

/**
 * 唯一化
 * 复杂度：O(n^2)
 * TOJS
*/
template <typename T>
int Vector<T>::deduplicate()
{
  int oldSize = _size;
  Rank i = 1;
  while (i < _size)
  {
    int target = find(_elem[i], 0, i);
    if (target < 0)
    {
      i++;
    }
    else
    {
      remove(i);
    }
  }
  return oldSize - _size;
}

/**
 * 遍历
 * 
*/
template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) // 函数指针
{
  for (int i = 0; i < _size; i++)
  {
    visit(_elem[i]);
  }
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
  for (int i = 0; i < _size; i++)
  {
    visit(_elem[i]);
  }
}
/**
 * 返回向量中逆序相邻元素对的总数
 * 复杂度： O(n)
*/
template <typename T>
int Vector<T>::disordered() const
{
  int n = 0;
  for (int i = 1; i < _size; i++)
  {
    if (_elem[i - 1] > _elem[i])
    {
      n++;
    }
  }
  return n;
}

/**
 * 有序向量重复元素剔除算法 低效版
 * 复杂度：O(n^2)
*/
template <typename T>
int Vector<T>::uniquify_n2()
{
  int oldSize = _size;
  int i = 1;
  while (i < _size)
  {
    _elem[-i] == _elem[i] ? remove(i) : i++;
  }
  return oldSize - _size;
}

/**
 * 有序向量重复元素剔除算法 高效版
 * 复杂度：O(n)
*/
template <typename T>
int Vector<T>::uniquify()
{
  Rank i = 0, j = 0;
  while (++j < _size)
  {
    if (_elem[i] != _elem[j])
    {
      _elem[++i] = _elem[j];
    }
  }
  _size = ++i;
  shrink();
  return j - i;
}

/**
 * 在有序向量的区间[lo, hi)內，确定不大于 e 的最后一个节点的秩
 * 复杂度： O(logn)
*/
template <typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const
{
  return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi)
{
  while (lo < hi)
  {
    Rank mi = (lo + hi) >> 1;
    if (e < A[mi])
    {
      hi = mi;
    }
    else if (e > A[mi])
    {
      lo = mi + 1;
    }
    else
    {
      return mi;
    }
  }
  return -1;
}

template <typename T>
static Rank binSearch_B(T *A, T const &e, Rank lo, Rank hi)
{
  while (1 < hi - lo) // 循环结束时，区间中必须留有一个元素。
  {
    Rank mi = (hi - lo) >> 1;
    (e < A[mi]) ? hi = mi : lo = mi;
  }
  return (e == A[lo]) ? lo : -1;
}

template <typename T>
static Rank binSearch_C(T *A, T const &e, Rank lo, Rank hi)
{
  while (lo < hi)
  {
    Rank mi = (lo + hi) >> 1;
    (e < A[mi]) ? hi = mi : lo = mi + 1;
  }
  return --lo;
}

template <typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi)
{
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
  insertionSort(lo, hi);
  // int s = 2; // rand() % 5
  // switch (s)
  // {
  // case 1:
  //   bubbleSort(lo, hi);
  //   break;
  // case 2:
  //   selectionSort(lo, hi);
  //   break;
  // case 3:
  //   mergeSort(lo, hi);
  //   break;
  // case 4:
  //   heapSort(lo, hi);
  //   break;
  // default:
  //   quickSort(lo, hi);
  //   break;
  // }
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
  while (!bubble(lo, hi--))
    ;
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
  bool sorted = true;
  while (++lo < hi)
  {
    if (_elem[lo - 1] > _elem[lo])
    {
      sorted = false;
      swap(_elem[lo - 1], _elem[lo]);
    }
  }
  return sorted;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
  if (hi - lo < 2)
  {
    return;
  }
  int mi = (lo + hi) / 2;
  mergeSort(lo, mi);
  mergeSort(mi, hi);
  merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
  T *Current = _elem + lo; // 待排序待数组
  int size_for_one = mi - lo;
  T *One = new T[size_for_one]; // 数组1
  for (Rank i = 0; i < size_for_one; One[i] = Current[i++])
    ;
  int size_for_two = hi - mi;
  T *Two = _elem + mi; // 数组2
  // 对于数组2来说，实质上是一种置换
  for (Rank one = 0, two = 0, i = 0; (one < size_for_one) || (two < size_for_two);)
  {
    if ((one < size_for_one) && ((two >= size_for_two) || (One[one] <= Two[two])))
    {
      Current[i++] = One[one++]; // 取数组1中的值；
    }
    if ((two < size_for_two) && ((one >= size_for_one) || (One[one] > Two[two])))
    {
      Current[i++] = Two[two++];
    }
  }
  delete[] One;
}

template <typename T>
void Vector<T>::insertionSort(Rank lo, Rank hi)
{
  // 不变性：[lo, i) 均为以排序列表
  T *oldElem = _elem;
  copyFrom(oldElem, 0, lo);
  Rank curr = 0;
  while (lo + curr < hi)
  {
    Rank target = search(oldElem[lo + curr], 0, curr);
    if (target == -1)
    {
      insert(0, oldElem[lo + curr]);
    }
    else
    {
      insert(target + 1, oldElem[lo + curr]);
    }
    curr++;
  }
  for (Rank i = hi; i < _size; i++)
  {
    insert(i, oldElem[i]);
  }
  delete[] oldElem;
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{
  Rank maxRank = lo;
  for (Rank i = lo + 1; i < hi; i++)
  {
    if (_elem[maxRank] < _elem[i])
    {
      maxRank = i;
    }
  }
  return maxRank;
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
  // 不变性：[low, i) 均不大于 [i, hi)，且  [i, hi) 是有序的
  Rank i = hi;
  while (i > lo)
  {
    Rank maxRank = max(lo, i);
    std::swap(_elem[maxRank], _elem[i - 1]);
    i--;
  }
}