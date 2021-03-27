#pragma once
#include "List.h"

template <typename T>
void List<T>::traverse(void (*visit)(T &e))
{
  for (ListNodePosition(T) p = header->succ; p != trailer; p = p->succ)
  {
    visit(p->data);
  }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
  for (ListNodePosition(T) p = header->succ; p != trailer; p = p->succ)
  {
    visit(p->data);
  }
}