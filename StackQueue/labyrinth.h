#pragma once
#include <iostream>
#include <stdlib.h>
#include "Stack.h"

typedef enum
{
  AVAILABLE,
  ROUTE,
  BACKTRACKED,
  WALL
} Status;

typedef enum
{
  UNKNOWN,
  EAST,
  SOUTH,
  WEST,
  NORTH,
  NO_WAY
} ESWN;

inline ESWN nextESWN(ESWN eswn)
{
  return ESWN(eswn + 1);
}

struct Cell
{
  int x, y;
  Status status;
  ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];
int labySize;
Cell *startCell;
Cell *goalCell;

// 查询当前位置的相邻格点
inline Cell *neighbor(Cell *cell)
{
  switch (cell->outgoing)
  {
  case EAST:
    return cell + LABY_MAX;
  case SOUTH:
    return cell + 1;
  case WEST:
    return cell - LABY_MAX;
  case NORTH:
    return cell - 1;
  default:
    exit(-1);
  }
}

// 从当前位置转入相邻格点
inline Cell *advance(Cell *cell)
{
  Cell *next;
  switch (cell->outgoing)
  {
  case EAST:
    next = cell + LABY_MAX;
    next->incoming = WEST;
    break;
  case SOUTH:
    next = cell + 1;
    next->incoming = NORTH;
    break;
  case WEST:
    next = cell - LABY_MAX;
    next->incoming = EAST;
    break;
  case NORTH:
    next = cell - 1;
    next->incoming = SOUTH;
    break;
  default:
    exit(-1);
  }
  return next;
}

bool labyrinth(Cell *s, Cell *t)
{
  if ((s->status != AVAILABLE) || (t->status != AVAILABLE))
  {
    return false;
  }
  Stack<Cell *> path;
  s->incoming = UNKNOWN;
  s->status = ROUTE;
  path.push(s);
  do
  {
    Cell *c = path.top();
    if (c == t)
    {
      return true;
    }
    while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
    {
      if (AVAILABLE == neighbor(c)->status)
      {
        break;
      }
    }
    if (NO_WAY <= c->outgoing)
    {
      c->status = BACKTRACKED;
      c = path.pop();
    }
    else
    {
      path.push(c = advance(c));
      c->outgoing = UNKNOWN;
      c->status = ROUTE;
    }
  } while (!path.empty());
  return false;
}

//生成随机的迷宫
void randLaby()
{
  labySize = LABY_MAX / 2 + rand() % (LABY_MAX / 2); /*DSA*/
  printf("Using a laby of size %d ...\n", labySize);
  // getchar();
  for (int i = 0; i < labySize; i++)
    for (int j = 0; j < labySize; j++)
    {
      laby[i][j].x = i;
      laby[i][j].y = j;
      laby[i][j].incoming = laby[i][j].outgoing = UNKNOWN;
      laby[i][j].status = WALL; //边界格点必须是墙
    }
  for (int i = 1; i < labySize - 1; i++)
    for (int j = 1; j < labySize - 1; j++)
      if (rand() % 4)
        laby[i][j].status = AVAILABLE; //75%的格点为空可用
  startCell = &laby[rand() % (labySize - 2) + 1][rand() % (labySize - 2) + 1];
  goalCell = &laby[rand() % (labySize - 2) + 1][rand() % (labySize - 2) + 1];
  startCell->status = goalCell->status = AVAILABLE; //起始格点必须可用
}

/******************************************************************************************
 * 显示迷宫
 ******************************************************************************************/
void displayLaby()
{ //┘└┐┌│─
  static char *pattern[5][5] = {
      //U     E     S     W     N
      "─┼", "─┼", "─┼", "─┼", "─┼", // U
      // row
      "─┼", "  ", " ┌", "──", " └", // E
      // row
      "─┼", " ┌", "  ", "─┐", " │", // S
      // row
      "─┼", "──", "─┐", "  ", "─┘", // W
      // row
      "─┼", " └", " │", "─┘", "  " // N
  };

  system("clear");
  printf("  ");
  for (int j = 0; j < labySize; j++)
    (j < 10) ? printf("%2X", j) : printf(" %c", 'A' - 10 + j);
  printf("\n");
  for (int j = 0; j < labySize; j++)
  {
    (j < 10) ? printf("%2X", j) : printf(" %c", 'A' - 10 + j);
    for (int i = 0; i < labySize; i++)
      if (goalCell == &laby[i][j])
        printf("﹩");
      else
        switch (laby[i][j].status)
        {
        case WALL:
          printf(" █");
          break;
        case BACKTRACKED:
          printf(" ○");
          break;
        case AVAILABLE:
          printf("  ");
          break;
        default:
          printf("%s", pattern[laby[i][j].outgoing][laby[i][j].incoming]);
          // printf("\n");
          // printf("i: %d, j:%d, out: %d, in: %d", i, j, laby[i][j].outgoing, laby[i][j].incoming);
          // printf("\n");
          break;
        }
    printf("\n");
  } //for
} //displayLaby