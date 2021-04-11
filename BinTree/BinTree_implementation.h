#pragma once
#include "BinTree.h"

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
  return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
  while (x)
  {
    updateHeight(x);
    x = x->parent;
  }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e)
{
  _size = 1;
  return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e)
{
  _size++;
  x->insertAsLC(e);
  updateHeightAbove(x);
  return x->lc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e)
{
  _size++;
  x->insertAsRC(e);
  updateHeightAbove(x);
  return x->rc;
}

// 子树接入
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> *&S)
{
  if (x->lc = S->_root)
  {
    x->lc->parent = x;
  }
  _size += S->_size;
  updateHeightAbove(x);
  S->root = NULL;
  S->_size = 0;
  release(S);
  S = NULL;
  return x;
}

// 子树接入
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> *&S)
{
  if (x->rc = S->_root)
  {
    x->rc->parent = x;
  }
  _size += S->_size;
  updateHeightAbove(x);
  S->root = NULL;
  S->_size = 0;
  release(S);
  S = NULL;
  return x;
}

// 子树删除
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
  FromParentTo(*x) = NULL;
  updateHeightAbove(x->parent);
  int n = removeAt(x);
  _size -= n;
  return n;
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
  if (!x)
  {
    return 0;
  }
  int n = 1 + removeAt(x->lc) + removeAt(x->rc);
  release(x->data);
  release(x);
  return n;
}

// 子树分离
template <typename T>
BinTree<T> *BinTree<T>::secede(BinNodePosi(T) x)
{
  FromParentTo(*x) = NULL;
  updateHeightAbove(x->parent);
  BinTree<T> *S = new BinTree<T>;
  S->_root = x;
  x->parent - NULL;
  S->_size = x->size();
  _size -= S->_size;
  return S;
}

/* =========================================================================================================
 * 遍历
 * ========================================================================================================= */

// 先序遍历 -- 递归
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit)
{
  if (!x)
  {
    return
  }
  visit(x->data);
  travPre_R(x->lc);
  travPre_R(x->rc);
}

// 后序遍历 -- 递归
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit)
{
  if (!x)
  {
    return;
  }
  travPost_R(x->lc, visit);
  travPost_R(x->rc, visit);
  visit(x->data)
}

// 中序遍历 -- 递归
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit)
{
  if (!x)
  {
    return;
  }
  travPost_R(x->lc, visit);
  visit(x->data);
  travPost_R(x->rc, visit);
}

// 先序遍历 -- 循环 2
template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S)
{
  while (x)
  {
    visit(x->data);
    S.push(x->rc);
    x = x->lc;
  }
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit)
{
  Stack<BinNodePosi(T)> S;
  while (true)
  {
    visitAlongLeftBranch(x, visit, S);
    if (S.empty())
    {
      break;
    }
    x = S.pop();
  }
}

// 中序遍历 -- 循环 1
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S)
{
  while (x)
  {
    S.push(x);
    x = x->lc;
  }
}
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
  Stack<BinNodePosi(T)> S;
  while (true)
  {
    goAlongLeftBranchs(x, visit, S);
    if (S.empty())
    {
      break;
    }
    x = S.pop();
    visit(x->data);
    x = x->rc;
  }
}

// 中序遍历 -- 循环 2
template <typename T>
BinNodePosi(T) BinNode<T>::succ() // 定位节点的直接后继
{
  BinNodePosi(T) s = this;
  if (rc) // 若有右孩子，则直接后继比在右子树中
  {
    s = rc;
    while (HasLChild(*s))
    {
      s = s->lc;
    }
  }
  else
  {
    while (IsRChild(*s)) // 逆向沿右分支，不断朝左上方移动。
    {
      s = s->parent;
    }
    s = s->parent;
  }
  return s;
}

template <typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST &visit)
{
  Stack<T> S;
  while (true)
  {
    if (x)
    {
      S.push(x);
      x = x->lc;
    }
    else if (!S.empty())
    {
      x = S.pop();
      visit(x->data);
      x = x->rc;
    }
    else
    {
      break;
    }
  }
}

// 中序遍历 -- 循环 3
template <typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST &visit)
{
  bool backtrack = false;
  while (true)
  {
    if (!backtrack && HasLChild(*x))
    {
      x = x->lc;
    }
    else
    {
      visit(x->data); // 沿着左子树到了最底端
      if (HasRChild(*x))
      {
        x = x->rc;
        backtrack = false;
      }
      else
      {
        if (!(x = x->succ()))
        {
          break;
        }
        backtrack = true; // 当前节点的左子树已经遍历完毕
      }
    }
  }
}

// 后序遍历 -- 循环
template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)> &S)
{
  while (BinNodePosi(T) x = S.top())
  {
    if (HasLChild(*x))
    {
      if (HasRChild(*x))
      {
        S.push(x->rc); // 该节点之后需要 gotoHLVFL
      }
      S.push(x->lc);
    }
    else
    {
      S.push(x->rc);
    }
  }
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit)
{
  Stack<BinNodePosi(T)> S;
  if (x)
  {
    S.push(x);
  }
  while (!S.empty())
  {
    if (S.top() != x->parent) // 如果是右子树的话，需要 gotoHLVFL
    {
      gotoHLVFL(S);
    }
    x = S.pop();
    visit(x->data);
  }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit)
{
  Queue<BinNodePosi(T)> Q;
  Q.enqueue(this);
  while (!Q.empty())
  {
    BinNodePosi(T) x = Q.dequeue();
    visit(x->data);
    if (HasLChild(*x))
    {
      Q.enqueue(x->lc);
    }
    if (HasRChild(*x))
    {
      Q.enqueue(x->rc);
    }
  }
}
