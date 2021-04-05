#pragma once
#include "../Vector/Vector.h"

template <typename T>
class Stack : public Vector<T>
{
public:
  void push(T const &e)
  {
    Rank i = this->size();
    this->insert(i, e);
  }

  T pop()
  {
    return this->remove(this->size() - 1);
  }

  T &top()
  {
    return (*this)[this->size() - 1];
  }
};
