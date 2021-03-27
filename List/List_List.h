#pragma once
#include "List.h"

template <typename T>
void List<T>::copyNodes(ListNodePosition(T) p, int n)
{
  init();
  while (n--)
  {
    insertAsLast(p->data);
    p = p->succ;
  }
}

template <typename T>
List<T>::List(ListNodePosition(T) p, int n)
{
  copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const &l)
{
  copyNodes(l.first(), l.size());
}

template <typename T>
List<T>::List(List<T> const &L)
{
  copyNodes(L.first(), L.size());
}

template <typename T>
List<T>::List(List<T> const &L, Rank r, int n)
{
  copyNodes(L[r], n);
}

template <typename T>
List<T>::~List()
{
  clear();
  delete header;
  delete trailer;
}

template <typename T>
int List<T>::clear()
{
  int oldSize = _size;
  while (0 < _size)
  {
    remove(header->succ);
  }
  return oldSize;
}