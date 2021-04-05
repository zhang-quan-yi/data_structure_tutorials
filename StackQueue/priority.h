#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"
#include <string.h>
#define N_OPTR 9

typedef enum
{
  ADD,
  SUB,
  MUL,
  DIV,
  POW,
  FAC,
  L_P,
  R_P,
  EOE
} Operator;

/**
 *       |-------------------- 当前运算符 --------------------|
 * ^      +     -     *     /     ^     !     (     )     \0
 * |  +  'g',  'g',  'l',  'l',  'l',  'l',  'l',  'g',  'g',
 * |  -  'g',  'g',  'l',  'l',  'l',  'l',  'l',  'g',  'g',
 * t  *  'g',  'g',  'g',  'g',  'l',  'l',  'l',  'g',  'g',
 * o  /  'g',  'g',  'g',  'g',  'l',  'l',  'l',  'g',  'g',
 * p  ^  'g',  'g',  'g',  'g',  'g',  'l',  'l',  'g',  'g',
 * |  !  'g',  'g',  'g',  'g',  'g',  'g',  ' ',  'g',  'g',
 * |  (  'l',  'l',  'l',  'l',  'l',  'l',  'l',  '=',  ' ',
 * |  )  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',  ' ',
 * | \0  'l',  'l',  'l',  'l',  'l',  'l',  'l',  ' ',  '=',
*/
const char pri[N_OPTR][N_OPTR] = {
    /** + */
    'g', 'g', 'l', 'l', 'l', 'l', 'l', 'g', 'g',
    /** - */
    'g', 'g', 'l', 'l', 'l', 'l', 'l', 'g', 'g',
    /** * */
    'g', 'g', 'g', 'g', 'l', 'l', 'l', 'g', 'g',
    /** / */
    'g', 'g', 'g', 'g', 'l', 'l', 'l', 'g', 'g',
    /** ^ */
    'g', 'g', 'g', 'g', 'g', 'l', 'l', 'g', 'g',
    /** ! */
    'g', 'g', 'g', 'g', 'g', 'g', ' ', 'g', 'g',
    /** ( */
    'l', 'l', 'l', 'l', 'l', 'l', 'l', '=', ' ',
    /** ) */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /**\0 */
    'l', 'l', 'l', 'l', 'l', 'l', 'l', ' ', '=',
    /** */
};

void readNumber(char *&p, Stack<float> &stk)
{
  stk.push((float)(*p - '0'));
  while (isdigit(*(++p)))
  {
    stk.push(stk.pop() * 10 + (*p - '0'));
  }
  if ('.' != *p)
  {
    return;
  }
  float fraction = 1;
  while (isdigit(*(++p)))
  {
    stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
  }
}

Operator optr2rank(char op)
{
  switch (op)
  {
  case '+':
    return ADD;
  case '-':
    return SUB;
  case '*':
    return MUL;
  case '/':
    return DIV;
  case '^':
    return POW;
  case '!':
    return FAC;
  case '(':
    return L_P;
  case ')':
    return R_P;
  case '\0':
    return EOE;
  default:
    exit(-1);
  }
}

char orderBetween(char pre, char curr)
{
  return pri[optr2rank(pre)][optr2rank(curr)];
}

float calcu(char optr, float opnd)
{
  if (optr == '!')
  {
    int i = opnd;
    int r = 1;
    while (i > 1)
    {
      r *= i;
      i--;
    }
    return r;
  }
}

float calcu(float opnd1, char optr, float opnd2)
{
  if (optr == '+')
  {
    return opnd1 + opnd2;
  }
  if (optr == '-')
  {
    return opnd1 - opnd2;
  }
  if (optr == '*')
  {
    return opnd1 * opnd2;
  }
  if (optr == '/')
  {
    return opnd1 / opnd2;
  }
  if (optr == '^')
  {
    float r = 1;
    for (int i = 0; i < opnd2; i++)
    {
      r *= r;
    }
    return r;
  }
}

void append(char *&rpn, float opnd)
{
  int n = strlen(rpn);
  char buf[64];
  if (opnd != (float)(int)opnd)
  {
    sprintf(buf, "%.2f \0", opnd); // 浮点格式
  }
  else
  {
    sprintf(buf, "%d \0", (int)opnd); // 整数格式
  }
  rpn = (char *)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));
  strcat(rpn, buf);
}

void append(char *&rpn, char optr)
{
  int n = strlen(rpn);
  rpn = (char *)realloc(rpn, sizeof(char) * (n + 3));
  sprintf(rpn + n, "%c ", optr);
  rpn[n + 2] = '\0';
}

float evaluate(char *S, char *&RPN)
{
  Stack<float> opnd;
  Stack<char> optr;
  optr.push('\0');
  while (!optr.empty())
  {
    if (isdigit(*S))
    {
      readNumber(S, opnd);
      append(RPN, opnd.top());
    }
    else
    {
      switch (orderBetween(optr.top(), *S))
      {
      case 'l':
        optr.push(*S);
        S++;
        break;
      case '=':
        optr.pop();
        S++;
        break;
      case 'g':
      {
        char op = optr.pop();
        append(RPN, op);
        if ('!' == op)
        {
          float pOpnd = opnd.pop();
          opnd.push(calcu(op, pOpnd));
        }
        else
        {
          float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
          opnd.push(calcu(pOpnd1, op, pOpnd2));
        }
        break;
      }
      default:
        exit(-1);
      }
    }
  }
  return opnd.pop();
}
