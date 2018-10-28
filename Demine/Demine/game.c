#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	memset(board, set, rows*cols*sizeof(board[0][0]));
}
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("----------------------------\n");
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("----------------------------\n");
}
void SetMine(char borad[ROWS][COLS], int row, int col)
{
	int count = COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (borad[x][y] = '0')
		{
			borad[x][y] = '1';
			count--;
		}
	}
}
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int k = 0;
	int l = 0;
	int win = 0;
	while (win < row*col - COUNT)
	{
		printf("请输入要排查的坐标：");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (win == 0)
			{
				if (mine[x][y] == '1')
				{
					mine[x][y] = '0';
					k = rand() % row + 1;
					l = rand() % col + 1;
					if (mine[k][l] == '0')
					{
						mine[k][l] = '1';
					}
				}
				win++;
				/*DisplayBoard(mine, ROW, COL);*/
			}
			if (mine[x][y] == '1')
			{
				printf("你被炸死了！\n");
				DisplayBoard(mine, row, col);
				break;
			}
			else
			{
				int count = GetMineCount(mine, x, y);
				show[x][y] = count + '0';
				if (count == 0)
				{
					OpenBoard(mine, show, x, y);
				}
				DisplayBoard(show, row, col);
				win = 0;
				for (x = 1; x <= row; x++)
				{
					for (y = 1; y <= col; y++)
					{
						if (show[x][y] != '*')
							win++;
					}
				}
			}
		}
		else
		{
			printf("坐标非法，请重新输入！\n");
		}
	}
	if (win == row*col - COUNT)
	{
		printf("排雷成功！\n");
		DisplayBoard(mine, row, col);
	}
}
int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y + 1] +
		mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y + 1] +
		mine[x][y - 1] +
		mine[x + 1][y + 1] +
		mine[x + 1][y] +
		mine[x + 1][y - 1] - 8 * '0';
}
void OpenBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	show[x][y] = ' ';
	if (mine[x - 1][y] == '0'&&x - 1 > 0 && y  > 0 && show[x - 1][y] == '*')
	{
		x = x - 1;
		show[x][y] = GetMineCount(mine, x, y) + '0';
		if (GetMineCount(mine, x, y) == 0)
		{
			OpenBoard(mine, show, x, y);
		}
		x = x + 1;
	}

	if (mine[x][y + 1] == '0'&&x  > 0 && y + 1 > 0 && show[x][y + 1] == '*')
	{
		y = y + 1;
		show[x][y] = GetMineCount(mine, x, y) + '0';
		if (GetMineCount(mine, x, y) == 0)
		{
			OpenBoard(mine, show, x, y);
		}
		y = y - 1;
	}
	if (mine[x][y - 1] == '0'&&x  > 0 && y - 1 > 0 && show[x][y - 1] == '*')
	{
		y = y - 1;
		show[x][y] = GetMineCount(mine, x, y) + '0';
		if (GetMineCount(mine, x, y) == 0)
		{
			OpenBoard(mine, show, x, y);
		}
		y = y + 1;
	}

	if (mine[x + 1][y] == '0'&&x + 1 > 0 && y  > 0 && show[x + 1][y] == '*')
	{
		x = x + 1;
		show[x][y] = GetMineCount(mine, x, y) + '0';
		if (GetMineCount(mine, x, y) == 0)
		{
			OpenBoard(mine, show, x, y);
		}
		x = x - 1;
	}
}