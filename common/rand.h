#pragma once

#include <cstdlib>
#include <ctime> //通常用当前时刻设置随机种子

static int dice(int range)
{
  return rand() % range;
}