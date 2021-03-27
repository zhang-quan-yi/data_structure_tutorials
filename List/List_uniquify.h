#pragma once
#include "List.h"

template <typename T>
int List<T>::uniquify()
{
  if (_size < 2)
  {
    return 0;
  }
  int oldSize = _size;
  ListNodePosition(T) p = first();
  ListNodePosition(T) q;
  while ((q = p->succ) != trailer)
  {
    if (p->data == q->data)
    {
      remove(q);
    }
    else
    {
      p = q;
    }
  }
  return oldSize - _size;
}