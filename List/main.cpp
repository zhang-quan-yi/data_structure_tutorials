#include <iostream>
using namespace std;

#include "List.h"
#include "../Vector/Vector.h"

int main(int argc, char *agrv[])
{
  Vector<int> * v = new Vector<int>();
  List<int> *l = new List<int>();
  l->insertAsFirst(2);
  l->insertAsFirst(1);
  printf("first is %d", l->first()->data);
}