#pragma once
#include "List.h"

template <typename T>
ListNodePosition(T) List<T>::search(T const &e, int n, ListNodePosition(T) p) const
{
  while (0 <= n--)
  {
    if ((p = p->pred)->data <= e)
    {
      break;
    }
  }
  return p;
}

/**
 * 最好情况下：O(1)
 * 最坏情况下：O(n)
*/