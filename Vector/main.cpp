#include <iostream>
#include <stdlib.h>
#include "../common/common.h"
#include "Vector.h"
#include "permute.h"

using namespace std;

template <typename T>
void testVector(int testSize)
{
  printf("\n  ==== 00. Generate a  random vector\n");
  Vector<T> V;
  for (int i = 0; i < testSize; i++)
    V.insert(i, dice((T)testSize * 3)); //在[0, 3n)中选择n个数，随机插入向量
  permute<T>(V);
  for (int i = 0; i < testSize; i++)
  {
    printf(" %d", V[i]);
  }
  printf("\n");
  V.sort();
  for (int i = 0; i < testSize; i++)
  {
    printf(" %d", V[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (2 > argc)
  {
    printf("Usage: %s <size of test>\a\a\n", argv[0]);
    return 1;
  }
  printf("size of test: %d \n", atoi(argv[1]));
  srand((unsigned int)time(NULL));
  testVector<int>(atoi(argv[1]));
}
