#pragma once
#include <stddef.h>
#include "../Entry/Entry.h"
#define QListNodePosi(T) QuadlistNode<T> *

template <typename T>
struct QuadlistNode
{
  T entry;
  QListNodePosi(T) pred;
  QListNodePosi(T) succ;
  QListNodePosi(T) above;
  QListNodePosi(T) below;
  QuadlistNode(T e = T(), QListNodePosi(T) p = NULL, QListNodePosi(T) s = NULL, QListNodePosi(T) a = NULL, QListNodePosi(T) b = NULL) : entry(e), pred(p), succ(s), above(a), below(b)
  {
  }
  QListNodePosi(T) insertAsSuccAbove(T const &e, QListNodePosi(T) b = NULL);
};

template <typename T>
QListNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const &e, QListNodePosi(T) b)
{
  QListNodePosi(T) x = new QuadlistNode<T>(e, this, succ, NULL, b);
  succ->pred = x;
  succ = x; //设置水平逆向链接
  if (b)
  {
    b->above = x; //设置垂直逆向链接
  }
  return x; //返回新节点的位置s
};
