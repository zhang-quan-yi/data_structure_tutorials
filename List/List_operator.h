#pragma once
#include "List.h"

template <typename T>
T &List<T>::operator[](Rank r) const
{
  ListNodePosition(T) p = first();
  while (r-- > 0)
  {
    p = p->succ;
  }
  return p->data;
}