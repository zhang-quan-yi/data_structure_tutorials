#pragma once
#include "ListNode.h"

template <typename T>
ListNodePosition(T) ListNode<T>::insertAsPred(T const &e)
{
  ListNodePosition(T) node = new ListNode(e, pred, this);
  pred->succ = node;
  pred = node;
  return node;
}

template <typename T>
ListNodePosition(T) ListNode<T>::insertAsSucc(T const &e)
{
  ListNodePosition(T) node = new ListNode(e, this, succ);
  succ->pred = node;
  succ = node;
  return node;
}