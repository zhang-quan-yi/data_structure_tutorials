#pragma once
#define ListNodePosition(T) ListNode<T> *

typedef int Rank;

template <typename T>
struct ListNode
{
  // 成员
  T data;
  ListNodePosition(T) pred;
  ListNodePosition(T) succ;

  ListNode() {}
  ListNode(T e, ListNodePosition(T) p = NULL, ListNodePosition(T) s = NULL)
      : data(e), pred(p), succ(s) {}
  ListNodePosition(T) insertAsPred(T const &e);
  ListNodePosition(T) insertAsSucc(T const &e);
};

#include "ListNode_inplementation.h"