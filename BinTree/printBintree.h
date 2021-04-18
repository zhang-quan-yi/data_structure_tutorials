#pragma once
#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1 * L_CHILD

template <typename T> //元素类型
static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap *bType)
{
  if (!bt)
    return;
  if (-1 < depth) //设置当前层的拐向标志
    R_CHILD == type ? bType->set(depth) : bType->clear(depth);
  printBinTree(bt->rc, depth + 1, R_CHILD, bType); //右子树（在上）
  printf("%c", bt->data);
  printf(" *");
  for (int i = -1; i < depth; i++)                       //根据相邻各层
    if ((0 > i) || bType->test(i) == bType->test(i + 1)) //的拐向是否一致，即可确定
      printf("      ");                                  //是否应该
    else
      printf("│    "); //打印横线
  switch (type)
  {
  case R_CHILD:
    printf("┌─");
    break;
  case L_CHILD:
    printf("└─");
    break;
  default:
    printf("──");
    break; //root
  }
  printf("%c", bt->data);
  printf("\n");
  printBinTree(bt->lc, depth + 1, L_CHILD, bType); //左子树（在下）
}