#pragma once
#include "QuadlistNode.h"

template <typename T>
class Quadlist
{
private:
  int _size;
  QListNodePosi(T) header;
  QListNodePosi(T) trailer;

protected:
  void init();
  int clear();

public:
  Quadlist() { init(); }
  ~Quadlist()
  {
    clear();
    delete header;
    delete trailer;
  }
  // 只读访问接口
  int size() const { return _size; }
  bool empty() const { return _size < 0; }
  QListNodePosi(T) first() const { return header->succ; }
  QListNodePosi(T) last() const { return trailer->pred; }
  bool valid(QListNodePosi(T) p)
  {
    return p && (trailer != p) && (header != p);
  }
  // 可写访问接口
  T remove(QListNodePosi(T) p);
  QListNodePosi(T) insertAfterAbove(T const &e, QListNodePosi(T) p, QListNodePosi(T) b = NULL);

  // 遍历
  void traverse(void (*)(T &));
  template <typename VST>
  void traverse(VST &);
};

template <typename T>
void Quadlist<T>::init()
{                                //Quadlist初始化，创建Quadlist对象时统一调用
  header = new QuadlistNode<T>;  //创建头哨兵节点
  trailer = new QuadlistNode<T>; //创建尾哨兵节点
  header->succ = trailer;
  header->pred = NULL; //沿横向联接哨兵
  trailer->pred = header;
  trailer->succ = NULL;                  //沿横向联接哨兵
  header->above = trailer->above = NULL; //纵向的后继置空
  header->below = trailer->below = NULL; //纵向的前驱置空
  _size = 0;                             //记录规模
}

template <typename T>
QListNodePosi(T) Quadlist<T>::insertAfterAbove(T const &e, QListNodePosi(T) p, QListNodePosi(T) b)
{
  _size++;
  return p->insertAsSuccAbove(e, b);
}

template <typename T>
T Quadlist<T>::remove(QListNodePosi(T) p)
{
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  _size--;
  T e = p->entry;
  delete p;
  return e;
}

template <typename T>
int Quadlist<T>::clear()
{
  int oldSize = _size;
  while (0 < _size)
  {
    remove(header->succ);
  }
  return oldSize;
}