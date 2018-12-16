#include "stdafx.h"
#include "cstdio"
#include "iostream"
#include "cstring"
#include "cstdlib"
#include<fstream>
using namespace std;
FILE *fp1, *fp2;
errno_t err1 = fopen_s(&fp1, "sudoku.txt", "w");//sudoku.txt 存放数独终局
errno_t err2 = fopen_s(&fp2, "solve.txt", "w");//solve.txt 存放数独的解
int sudo_solve[9][9];
int Displacement[9] = { 3,6,1,4,7,2,5,8 };//位移量
struct NODE1
{
	int n, m;
}node1[4] = { { 0,0 },{ 2,3 },{ 2,4 },{ 3,4 } };//交换数独的中间三行的位置
struct NODE2
{
	int n, m;
}node2[4] = { { 0,0 },{ 5,6 },{ 5,7 },{ 6,7 } };//交换数独后三行的位置
//在数独模板1的基础上对数独进行与行之间的交换（4~6,7~9行之间任意两行的交换）
int exchange(char sudo_1[10][10], int Count, int N)
{
	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 6; x++)
		{
			if (!x && !y);
			else if (Count < N)
			{
				swap(Displacement[node1[x].n], Displacement[node1[x].m]);
				swap(Displacement[node2[y].n], Displacement[node1[y].m]);
				int k = 0;
				for (int i = 0; i < 9; i++)
				{
					if (k)
					{
						for (int j = 0; j < 9; j++)
						{
							sudo_1[k][(j + Displacement[i - 1]) % 9] = sudo_1[0][j];
						}
					}
					for (int z = 0; z < 9; z++)
					{
						if (z) fputc(' ', fp1);
						fputc(sudo_1[k][z], fp1);
					}
					fputc('\n', fp1);
					k++;
				}
				fputc('\n', fp1);
				swap(Displacement[node1[x].n], Displacement[node1[x].m]);
				swap(Displacement[node2[y].n], Displacement[node1[y].m]);
				Count++;
			}
		}
	}
	return Count;
}
//对数独第一行进行全排列，共有8！种，生成数独模板1
void permutation(int *a, int k, int m, int *Count, int N)
{
	char sudo[10][10];
	memset(sudo, 0, sizeof(sudo));
	int b[8], i, j;
	if (k == m)
	{
		if (*Count < N)
		{
			for (i = 0; i <= m; i++)
			{
				b[i] = a[i];
			}
			*Count += 1;
			int k = 0, l = 0;
			sudo[0][0] = '5';//学号1120161822,（2+2）% 9 + 1 = 5
			for (i = 0; i < 8; i++)
			{
				sudo[0][i + 1] = b[i] + '0';
			}
			//分别将数独第一行右移3、6、1、4、7、2、5、8列得到第二到九行
			for (i = 0; i < 9; i++)
			{
				if (k)
				{
					for (l = 0; l < 9; l++)
					{
						sudo[k][(l + Displacement[i - 1]) % 9] = sudo[0][l];
					}
				}
				for (j = 0; j < 9; j++)
				{
					if (j) fputc(' ', fp1);
					fputc(sudo[k][j], fp1);
				}
				fputc('\n', fp1);
				k++;
			}
			fputc('\n', fp1);
			char sudo_1[10][10];
			strncpy_s(sudo_1[0], sizeof(sudo_1), sudo[0], sizeof(sudo));
			*Count = exchange(sudo_1, *Count, N);
		}
	}
	else
	{
		for (j = k; j <= m; j++)
		{
			swap(a[j], a[k]);
			permutation(a, k + 1, m, Count, N);
			swap(a[j], a[k]);
		}
	}
}
//创建数独终局的函数sudo_create，N为待创建的终局数
void sudo_create(int N)
{
	int a[] = { 1,2,3,4,6,7,8,9 }, len = 8;
	int Count = 0;
	permutation(a, 0, len - 1, &Count, N);
	fclose(fp1);
}

//解决数独模块里的行列以及九宫格检测，判断是否合法
bool check(int Count)
{
	int x = Count / 9;//当前行位置
	int y = Count % 9;//当前列位置
	int i;
	//每行都要有1~9且每一个数字只能存在一个
	for (i = 0; i < 9; i++)
	{
		if (sudo_solve[x][y] == sudo_solve[x][i] && i != y) return false;
	}
	//每列都要有1~9且每一个数字只能存在一个
	for (i = 0; i < 9; i++)
	{
		if (sudo_solve[x][y] == sudo_solve[i][y] && i != x) return false;
	}
	//每个九宫格都要有1~9且每一个数字只能存在一个
	int xx = x / 3 * 3, yy = y / 3 * 3;
	for (i = xx; i < xx + 3; ++i)
	{
		for (int j = yy; j < yy + 3; ++j)
		{
			if (sudo_solve[i][j] == sudo_solve[x][y] && i != x&&j != y) return false;
		}
	}
	return true;
}
//通过回溯法求解数独
void backtrace(int Count)
{
	if (Count == 81)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				fputc((char)(sudo_solve[i][j] + '0'), fp2);
				fputc(' ', fp2);
			}
			fputc('\n', fp2);
		}
		fputc('\n', fp2);
		return;
	}
	int x = Count / 9, y = Count % 9;
	if (sudo_solve[x][y] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			sudo_solve[x][y] = i;
			if (check(Count))
				backtrace(Count + 1);
		}
		sudo_solve[x][y] = 0;
	}
	else
		backtrace(Count + 1);
}

void sudo_Solve(char *c)
{
	FILE *fp3;
	errno_t err3 = fopen_s(&fp3, c, "r");//待求解的数独
	if (fp3 == NULL)
		cout << "Path is error";
	else
	{
		int i, j;
		while (fscanf_s(fp3, "%d", &sudo_solve[0][0]) != EOF)
		{
			for (i = 0; i < 9; i++)
			{
				for (j = 0; j < 9; j++)
				{
					if (i == 0 && j == 0)
						continue;
					else
						fscanf_s(fp3, "%d", &sudo_solve[i][j]);
				}
			}
			backtrace(0);
			memset(sudo_solve, 0, sizeof(sudo_solve));
		}
	}
}
//参数检测
int ArgCheck(char *argv)
{
	int num = 0;
	int len = strlen(argv);
	for (int i = 0; i < len; i++)
	{
		if (!(argv[i] >= '0'&&argv[i] <= '9'))
			return -1;
		else
			num = num * 10 + (int)(argv[i] - '0');
	}

	return num;
}

int main(int argc, char *argv[])
{

	argc = 2;
	char c[3] = { 0 }, s[3] = { 0 };
	c[0] = '-', c[1] = 'c';
	s[0] = '-', s[1] = 's';
	if (argc > 3) {
	cout << "Input is error!";
	}
	else if (argc == 2)
	{
	if (!strcmp(argv[1], "-c"))
	{
	int num = ArgCheck(argv[2]);
	if (num == -1)
	cout << "Input is error";
	else
	sudo_create(num);
	}
	else if (!strcmp(argv[1], s))
	sudo_Solve(argv[2]);
	}
	return 0;
}


