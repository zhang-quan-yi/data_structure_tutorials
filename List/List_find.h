#pragma once
#include "List.h"

template <typename T>
ListNodePosition(T) List<T>::find(T const &e, int n, ListNodePosition(T) p) const
{
  while (0 < n--)
  {
    if (e == (p = p->pred)->data)
    {
      return p;
    }
  }
  return NULL;
}