#include <iostream>
#include <stdlib.h>
#include "Stack.h"
#include "priority.h"
#include "queen.h"
#include "labyrinth.h"
#include "Queue.h"

using namespace std;

// ======== 逆序输出
// 十进制到其他进制的转换： 递归版
void convert(Stack<char> &s, int n, int base)
{
  static char digit[] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  if (0 < n)
  {
    s.push(digit[n % base]);
    convert(s, n / base, base);
  }
}

// 十进制到其他进制的转换： 循环版
void convert_loop(Stack<char> &s, int n, int base)
{
  static char digit[] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  while (n > 0)
  {
    int remainder = n % base;
    s.push(digit[remainder]);
    n /= base;
  }
}

// ======== 括号匹配
// 删除 exp[lo,hi] 不含括号的最长前缀
void trim(const char exp[], int &lo, int &hi)
{
  while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))
    lo++;
  while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))
    hi--;
}

int divide(const char exp[], int lo, int hi)
{
  int mi = lo;
  int crc = 1;
  while ((crc > 0) && (++mi < hi))
  {
    if (exp[mi] == ')')
    {
      crc--;
    }
    if (exp[mi] == '(')
    {
      crc++;
    }
  }
  return mi;
}
bool paren(const char exp[], int lo, int hi)
{
  trim(exp, lo, hi);
  if (lo > hi)
  {
    return true;
  }
  if (exp[lo] != '(')
  {
    return false;
  }
  if (exp[hi] != ')')
  {
    return false;
  }
  int mi = divide(exp, lo, hi);
  if (mi > hi)
  {
    return false;
  }
  return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
}

bool paren_stack(const char exp[], int lo, int hi)
{
  Stack<char> s;
  for (int i = lo; i <= hi; i++)
  {
    switch (exp[i])
    {
    case '(':
    case '[':
    case '{':
      s.push(exp[i]);
      break;
    case ')':
      if (s.empty() || '(' != s.pop())
      {
        return false;
      }
      break;
    case ']':
      if (s.empty() || '[' != s.pop())
      {
        return false;
      }
    case '}':
      if (s.empty() || '{' != s.pop())
      {
        return false;
      }
    default:
      break;
    }
  }
  return s.empty();
}

// ======== 延迟缓冲
// 四则运算
void testEvaluate()
{
  char *rpn = (char *)malloc(sizeof(char) * 1);
  rpn[0] = '\0';
  float r = evaluate("1+2*3-4", rpn);
  printf("%s", rpn);
  printf("\n");
}

// ======= 八皇后
void testQueue()
{
  placeQueens(8);
}

// ======== 迷宫
void testLaby()
{
  srand((unsigned int)time(NULL));
  randLaby();
  displayLaby();
  labyrinth(startCell, goalCell);
  displayLaby();
}

int main(int argc, char *argv[])
{
  // testEvaluate();
  // testQueue();
  // testLaby();
  Queue<int>* q = new Queue<int>();
}