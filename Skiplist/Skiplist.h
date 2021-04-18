#pragma once
#include <cstdlib>
#include <stddef.h>
#include "../List/List.h"
#include "../Entry/Entry.h"
#include "Quadlist.h"
#include "../Dictionary/Dictionary.h"

template <typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>> *>
{
protected:
  bool skipSearch(ListNode<Quadlist<Entry<K, V>> *> *&qlist, QuadlistNode<Entry<K, V>> *&p, K &k);

public:
  int size() const { return this->isEmpty() ? 0 : this->last()->data->size(); }
  int level()
  {
    return List<Quadlist<Entry<K, V>> *>::size();
  }
  bool put(K, V);
  V *get(K k);
  bool remove(K k);
};

template <typename K, typename V>
V *Skiplist<K, V>::get(K k)
{
  if (this->isEmpty())
  {
    return NULL;
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL;
}

template <typename K, typename V>
bool Skiplist<K, V>::skipSearch(ListNode<Quadlist<Entry<K, V>> *> *&qlist, QuadlistNode<Entry<K, V>> *&p, K &k)
{
  while (true)
  {
    while (p->succ && p->entry.key <= k)
    {
      p = p->succ;
    }
    p = p->pred;
    if (p->pred && (k == p->entry.key))
    {
      return true;
    }
    qlist = qlist->succ;
    if (!qlist->succ)
    {
      return false;
    }
    p = (p->pred) ? p->below : qlist->data->first();
  }
}

template <typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
  Entry<K, V> e = Entry<K, V>(k, v);
  if (this->isEmpty())
  {
    this->insertAsFirst(new Quadlist<Entry<K, V>>);
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  if (skipSearch(qlist, p, k))
  {
    while (p->below)
    {
      p = p->below;
    }
  }
  qlist = this->last();
  QuadlistNode<Entry<K, V>> *b = qlist->data->insertAfterAbove(e, p);
  while (rand() & 1)
  {
    while (qlist->data->valid(p) && !p->above)
    {
      p = p->pred;
    }
    if (!qlist->data->valid(p))
    {
      if (qlist == this->first())
      {
        this->insertAsFirst(new Quadlist<Entry<K, V>>);
      }
      p = qlist->pred->data->first()->pred;
    }
    else
    {
      p = p->above;
    }
    qlist = qlist->pred;
    b = qlist->data->insertAfterAbove(e, p, b);
  }
  return true;
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
  if (this->isEmpty())
  {
    return false;
  }
  ListNode<Quadlist<Entry<K, V>> *> *qlist = this->first();
  QuadlistNode<Entry<K, V>> *p = qlist->data->first();
  if (!skipSearch(qlist, p, k))
  {
    return false;
  }
  do
  {
    QuadlistNode<Entry<K, V>> *lower = p->below;
    qlist->data->remove(p);
    p = lower;
    qlist = qlist->succ;
  } while (qlist->succ);
  while (!this->isEmpty() && this->first()->data->empty())
  {
    List<Quadlist<Entry<K, V>> *>::remove(this->first());
  }
  return true;
}