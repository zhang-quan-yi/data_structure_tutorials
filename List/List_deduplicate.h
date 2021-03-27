#pragma once
#include "List.h"

template <typename T>
int List<T>::deduplicate()
{
  if (_size < 2)
  {
    return 0;
  }
  int oldSize = _size;
  ListNodePosition(T) p = header;
  Rank r = 0;
  while (trailer != (p = p->succ))
  {
    ListNodePosition(T) target = find(p->data, r, p);
    if (target)
    {
      remove(target);
    }
    else
    {
      r++;
    }
  }
  return oldSize - _size;
}