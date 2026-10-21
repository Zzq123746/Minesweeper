#include "game.h"


void menu()
{
	printf("---------------\n");
	printf("-----1、play---\n");
	printf("-----0、exit---\n");
	printf("---------------\n");

}
int main()
{
	srand((uint)time(NULL));	//设置一个随机数种子

	int input = 0;
	menu();
	printf("请输入:> ");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
		game();
		break;
	case 0:
		break;
	default:
		printf("非法输入\n");
		break;
	}
	return 0;
}
