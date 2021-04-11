#pragma once
#include "BinNode.h"

// BinNode 状态与性质的判断
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

// 与 BinNode 具有特定关系的节点及指针
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? ((x)->parent->lc) : ((x)->parent->rc)))

//统计当前节点后代总数，即以其为根的子树规模
template <typename T>
int BinNode<T>::size()
{
  int s = 1; //计入本身
  if (lc)
    s += lc->size(); //递归计入左子树规模
  if (rc)
    s += rc->size(); //递归计入右子树规模
  return s;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
  return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
  return rc = new BinNode(e, this);
}

// 中序遍历
template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit)
{
  switch (rand() % 5)
  {
  case 1:
    travIn_I1(this, visit); // 迭代版1
    break;
  case 2:
    travIn_I2(this, visit); // 迭代版1
    break;
  case 3:
    travIn_I3(this, visit); // 迭代版1
    break;
  case 4:
    travIn_I4(this, visit); // 迭代版1
    break;
  default:
    travIn_IR(this, visit); // 递归版
    break;
  }
}