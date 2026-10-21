#include "game.h"

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
//封装一个game函数
void game()
{
	char mine[ROWS][COLS] = { 0 };//设置的扫雷模型
	char show[ROWS][COLS] = { 0 };//显示的扫雷模型
	char revealed[ROWS][COLS] = { 0 };//记录被解开的格子
	//定义对应的坐标：前后左右 8个方向


	//初始化扫雷
	Init_broad(mine, ROWS, COLS, '0');
	Init_broad(show, ROWS, COLS, '*');
	Init_broad(revealed, ROWS, COLS, '0');

	//显示模型
	//Display_broad(mine, ROW, COL);
	Display_broad(show, ROW, COL);
	//设置雷
	Set_Mine(mine, ROW, COL);
	//查找雷
	Find_mine(mine, show, revealed, ROW, COL);
	
}

void Init_broad(char broad[][COLS], int row, int col, char c)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			broad[i][j] = c;
		}
	}
}

void Display_broad(char broad[][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (j = 0; j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);


		for (j = 1; j <= col; j++)
		{
			printf("%c ", broad[i][j]);
		}

		printf("\n");
	}

}

void Set_Mine(char broad[][COLS], int row, int col)
{
	int count = MINE_NUMS;

	while (count)
	{
		int i = rand() % row + 1;
		int j = rand() % col + 1;
		if (broad[i][j] != '1')
		{
			broad[i][j] = '1';
			count--;
		}
	}
}

void Find_mine(char mine[][COLS], char show[][COLS], char revealed[][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int win = 0;
	while (win < MINE_NUMS)	//在没有找完所有雷之前一直找
	{
		printf("请输入坐标\n");
		scanf("%d %d", &i, &j);
		Cancel_Flag_Mine(show, i, j);	//输入已被标记的坐标
		if ('!' == Flag_Mine(show, i, j))
		{
			if ('!' == show[i][j] && mine[i][j] == '1')
				win++;
			Display_broad(show, ROW, COL);
		}
		else
		{
			if (i > 0 && i <= row && j > 0 && j <= col)
			{
				if (mine[i][j] == '0')		//找到的坐标没有雷
				{
					show[i][j] = Get_mine_count(mine, i, j) + '0';	//这种写法可以将字符和数字转换
					Check_Around_Mine(mine, show, revealed, i, j);
					Display_broad(show, ROW, COL);
				}
				else
				{
					printf("你被炸死了\n");
					Display_broad(mine, ROW, COL);
					break;
				}
			}
			else
				printf("查找越界，请重新查找\n");
		}
		if (win == MINE_NUMS)
		{
			printf("排雷成功\n");
			Display_broad(mine, ROW, COL);
		}
	}
}

int Get_mine_count(char mine[][COLS], int x, int y)
{
	return (mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] - 8 * '0');
}

char Flag_Mine(char show[ROWS][COLS], int x, int y)
{
	int input = 0;
	printf("是否标记旗帜\n");
	printf("---1.YES----\n");
	printf("---0.NO---\n");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		if (x > 0 && x <= ROW && y > 0 && y <= COL)
		{
			show[x][y] = '!';	//标记为'!'
		}
	}
	case 0:
		break;
	}
	return show[x][y];
}

void Cancel_Flag_Mine(char show[][COLS], int x, int y)
{

	if (show[x][y] == '!')
	{
		int input = 0;
		printf("是否取消旗帜\n");
		printf("---1.YES----\n");
		printf("---0.NO---\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			show[x][y] = '*';
			Display_broad(show, ROW, COL);

		}
		case 0:
			break;
		}
	}
}

void Check_Around_Mine(char mine[][COLS], char show[][COLS], char revealed[][COLS], int x, int y)
{
	show[x][y] = Get_mine_count(mine, x, y) + '0';

	if (!(x > 0 && x <= ROW && y > 0 && y <= COL))	//越界
		return;
	if (mine[x][y] == '1')
		return;
	if (revealed[x][y] == '1')
		return;
		
	revealed[x][y] = '1';

	if (show[x][y] != '0')
		return;

	if (show[x][y] == '0')	//如果这个坐标周围没有雷，去遍历周围的8个坐标
	{
		int i = 0;
		for (i = 0; i < 8; i++)
		{
			int ni = x + dx[i];
			int nj = y + dy[i];
			Check_Around_Mine(mine, show, revealed, ni, nj);
			//Display_broad(show, ROW, COL);

		}
	}
}