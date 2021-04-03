#pragma once
#include <cstdio> //采用C风格精细控制输出格式

static void print(char *x) { printf(" %s", x ? x : "<NULL>"); }       //字符串特别处理
static void print(const char *x) { printf(" %s", x ? x : "<NULL>"); } //字符串特别处理
