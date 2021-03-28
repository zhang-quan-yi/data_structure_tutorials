#pragma once
#include "List.h"
#include <stdlib.h>

template <typename T>
void List<T>::sort(ListNodePosition(T) p, int n)
{
  switch (rand() % 3)
  {
  case 1:
    insertionSort(p, n);
    break;
  case 2:
    selectionSort(p, n);
  default:
    mergeSort(p, n);
    break;
  }
}

template <typename T>
void List<T>::insertionSort(ListNodePosition(T) p, int n)
{
  for (int i = 0; i < n; i++)
  {
    insertA(search(p->data, i, p), p->data);
    p = p->succ;
    remove(p->pred);
  }
}

template <typename T>
void List<T>::selectionSort(ListNodePosition(T) p, int n)
{
  ListNodePosition(T) header = p->pred;
  ListNodePosition(T) tail = p;
  for (i = 0; i < n; i++)
    tail = tail->succ;
  while (1 < n--)
  {
    ListNodePosition(T) max = selectMax(header->succ, n);
    insertB(tail, max->data);
    remove(max);
  }
}

template <typename T>
ListNodePosition(T) List<T>::selectMax(ListNodePosition(T) p, int n)
{
  ListNodePosition(T) max = p;
  for (ListNodePosition(T) cur = p; 1 < n; n--)
  {
    if (lt(max->data, (cur = cur->succ)->data))
    {
      max = cur;
    }
  }
  return max;
}

template <typename T>
void List<T>::mergeSort(ListNodePosition(T) p, int n)
{
  if (n < 2)
    return;
  // 先找中点；分而治之；
  int mid = n >> 1;
  ListNodePosition(T) q = p;
  for (int i = 0; i < mid; i++)
    q = q->succ;
  mergeSort(p, mid);
  mergeSort(q, n - mid);
  // [p, m)
  // [m, n]
  merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::merge(ListNodePosition(T) p, int n, List<T> &L, ListNodePosition(T) q, int m)
{
  ListNodePosition(T) pp = p->pred;
  while (0 < m)
  {
    if (0 < n && p->data <= q->data)
    {
      p = p->succ;
      if (q == p)
      {
        break;
      }
      n--;
    }
    else
    {
      // p 已超出右界或者 v(q) < v(p)
      insertB(p, L.remove((q = q->succ)->pred));
      m--;
    }
  }
  p = pp->succ;
}