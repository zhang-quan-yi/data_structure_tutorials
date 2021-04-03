#pragma once
#include <algorithm>
#include "List.h"

template <typename T>
void List<T>::reverse()
{
  if (_size < 2)
  {
    return;
  }
  ListNodePosition(T) current;
  ListNodePosition(T) next;
  for (current = header, next = current->succ; current != trailer; current = next, next = current->succ)
  {
    current->pred = next;
  }
  ListNodePosition(T) pred;
  for (current = header, pred = current->pred; current != trailer; current = pred; pred = current->pred)
  {
    pred->succ = current;
  }
  header->succ = null;
  trailer->pred = null;
  std::swap(header, trailer);
}