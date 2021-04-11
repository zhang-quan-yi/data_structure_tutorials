#pragma once
#include "../common/common.h"
#include "BinNode.h"
#include "../StackQueue/Stack.h"
#include "../StackQueue/Queue.h"

template <typename T>
class BinTree
{
protected:
  int _size;
  BinNodePosi(T) _root;
  virtual int updateHeight(BinNodePosi(T) x); // 更新节点的高度
  void updateHeightAbove(BinNodePosi(T) x);   // 更新节点 x 及其祖先的高度

public:
  BinTree() : _size(0), _root(NULL) {}
  ~BinTree()
  {
    if (0 < _size)
    {
      remove(_root);
    }
  }
  bool empty() const { return !_root; }
  BinNodePosi(T) root() const { return _root; }
  BinNodePosi(T) insertAsRoot(T const &e);
  BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
  BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
  BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *&t);
  BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *&t);
  int remove(BinNodePosi(T) x);
  BinTree<T> *secede(BinNodePosi(T) x); // 将子树 x 从当前树中摘除

  template <typename VST>
  void travLevel(VST &visit)
  {
    if (_root)
    {
      _root->travLevel(visit);
    }
  }

  template <typename VST>
  void travIn(VST &visit)
  {
    if (_root)
    {
      _root->travIn(visit);
    }
  }

  template <typename VST>
  void travPost(VST &visit)
  {
    if (_root)
    {
      _root->travPost(visit);
    }
  }

  bool operator<(BinTree<T> const &t)
  {
    return _root && t._root && lt(_root, t._root);
  }

  bool operator==(BinTree<T> const &t)
  {
    return _root && t._root && (_root == t._root);
  }
};