#include <iostream>
using namespace std;

#include <stdlib.h>
#include "Huffman.h"

int main(int argc, char *argv[])
{
  char content[] = {'r', 'a', 'y', '\0'};
  PFCForest *forest = initForest();
  PFCTree *tree = generateTree(forest);
  release(forest);
  PFCTable *table = generateTable(tree);
  Bitmap *codeString = new Bitmap();
  int n = encode(table, codeString, content);
  decode(tree, codeString, n);
  release(table);
  release(tree);
  return 0;
}