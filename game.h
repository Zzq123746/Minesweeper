#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//宏定义一个游戏数组的大小
typedef unsigned int uint;
#define	ROW 9
#define	COL 9

#define	ROWS ROW+2
#define	COLS COL+2

#define MINE_NUMS 10

extern int dx[8];
extern int dy[8];

//封装一个game函数
void game();
//初始化游戏数组
void Init_broad(char broad[][COLS], int row, int col, char c);
//显示游戏数组
void Display_broad(char broad[][COLS], int row, int col);
//设置雷
void Set_Mine(char broad[][COLS], int row, int col);
//排查雷
void Find_mine(char mine[][COLS], char show[][COLS], char revealed[][COLS], int row, int col);
//标记雷
char Flag_Mine(char show[ROWS][COLS], int x, int y);
//取消标记雷
void Cancel_Flag_Mine(char show[][COLS], int x, int y);
//递归揭开格子
void Check_Around_Mine(char mine[][COLS], char show[][COLS], char revealed[][COLS], int x, int y);	//难点，待优化把推出来的格子改为’_‘
//查找（x,y）周围有几个雷
int Get_mine_count(char mine[][COLS], int x, int y);
