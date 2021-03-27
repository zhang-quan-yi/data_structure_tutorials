#pragma once
#include "List.h"

template <typename T>
ListNodePosition(T) List<T>::insertAsFirst(T const &e)
{
  _size++;
  return header->insertAsSucc(e);
}

template <typename T>
ListNodePosition(T) List<T>::insertAsLast(T const &e)
{
  _size++;
  return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosition(T) List<T>::insertA(ListNodePosition(T) p, T const &e)
{
  +_size++;
  return p->insertAsSucc(e);
}

template <typename T>
ListNodePosition(T) List<T>::insertB(ListNodePosition(T) p, T const &e)
{
  +_size++;
  return p->insertAsPred(e);
}