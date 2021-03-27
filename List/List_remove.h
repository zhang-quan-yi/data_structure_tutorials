#pragma once
#include "List.h"

template <typename T>
T List<T>::remove(ListNodePosition(T) p)
{
  T d = p->data;
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  delete p;
  _size--;
  return d;
}