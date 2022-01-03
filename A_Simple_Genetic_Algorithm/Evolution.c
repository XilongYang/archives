#include<stdio.h>
#include<time.h>	//使用其中的time作为随机数种子
#include<windows.h>	//调用其中的Sleep来延时
#include<stdlib.h>	//调用其中的rand来生成随机数

#define  NUM 1000	//定义一个预处理常量用来调整生物的数量
#define GEN 30 //循环选择代数

char bg[40][20];	//定义一个二维数组提供字符界面
int generation = 0;	//当前遗传的代数
int live;		//存活生物数量
int s = 0;	 //用作记录路径

struct creature		//定义一个类表示生物
{
	char gene[9];	//九位字符串表示基因
	int x;		//生物位置横坐标
	int y;		//生物位置纵坐标
	char step[61];	//生物在这代选择中的路径记录
	int alive;	//判定生物是否存活
}; 

struct creature cre[NUM];	//定义生物数量

void init();	//声明函数：初始化
int sum(int a, int b);		//声明函数：统计基因频率
int randmove(int c);		//声明函数：随机取得移动趋势
void refresh();		//声明函数：刷新屏幕
void move(int c);	//声明函数： 移动生物
void run();	//声明函数： 选择过程
void swap(int a, int b);		//声明函数： 交换生物位置（排序的辅助函数）
void rank();	//声明函数： 对生物排序
void dieout();	//声明函数：自然选择（杀死一部分生物）
void reproduce();		//声明函数：繁衍（让选择下存活的生物进行繁衍，补足生物数量）

int main()
{
	int a, b;		//循环用局部变量
	init();	//初始化
	for (a = 0; a < GEN; a++)		//循环选择
	{
		run();	//运行选择过程
		rank();	//第一次排序，为淘汰做准备
		dieout(); //淘汰掉部分生物
		rank();	//第二次排序 ，为繁衍做准备
		reproduce(); //运行繁衍函数
		refresh();
	}
	getchar(); 
	return 0;
}

void init()
{
	int x, y, c, g;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	system("mode con cols=40 lines=21"); //以上为隐藏光标和调整窗口大小
	srand(time(NULL)); // 定义随机数种子
	for (y = 0; y < 20; y++) //嵌套循环打印字符界面
	{
		for (x = 0; x < 34; x++)
		{
			if (y == 0 || y == 19 || x == 0 || x == 39)
			{
				bg[x][y] = '#';
			}
			else
			{
				bg[x][y] = ' ';
			}
			printf("%c", bg[x][y]);
		}
		printf("\n");
	}
	for (c = 0; c < NUM; c++)	//批量初始化生物属性
	{
		cre[c].alive = 1;
		cre[c].x = 4;
		cre[c].y = 10;
		for (g = 0; g < 8; g++)
		{
			cre[c].gene[g] = rand() % 4 + 48;
		}
		for (g = 0; g < 60; g++)
		{
			cre[c].step[g] = '0';
		}
	}
}

int sum(int a, int b)
{
	int i, sum;
	sum = 0;
	for (i = 0; i < 8; i++)
	{
		sum = ((cre[a].gene[i] - 48) == b) ? (sum + 1) : sum;
	}	//统计生物a的基因b频率并返回
	return sum;
}

void refresh()
{
	int x, y, c; //循环用局部变量
	y = 0;
	system("cls");
	live = 0;
	while (y < NUM)	//检测存活生物数量
	{
		if (cre[y].alive == 1 || cre[y].alive == 2)
		{
			live++;
		}
		y++;
	}
	for (y = 0; y < 20; y++)	//重新打印当前屏幕
	{
		for (x = 0; x < 40; x++)
		{
			bg[x][y] = ' ';
			for (c = 0; c < NUM; c++)
			{
				if (cre[c].x == x && cre[c].y == y)
				{
					bg[x][y] = 's';
				}
				else if (x == 0 || y == 0 || x == 39 || y == 19)
				{
					bg[x][y] = '#';
				}
				bg[39][10] = '$';
				bg[39][9] = '$';
				bg[39][11] = '$';
			}
			printf("%c", bg[x][y]);
		}
		printf("\n");
	}
	printf("Alive: %d  Generation: %d", live, generation);	//实时显示存活生物数量，当前代数
}

int randmove(int c)
{
	float ra, r, u, d, l;	//定义变量用以计算概率
	int re;	//定义变量用以返回计算结果
	ra = rand() % 100;	//生成一个100以内随机数
	u = sum(c, 0)  * 100/ 8;	//取基因‘0’的频率作为向上运动的概率
	d = sum(c, 1) * 100/ 8;		//取基因‘1’的频率作为向下移动的概率
	l = sum(c, 2)  * 100/ 8;		//取基因‘2’的频率作为向左移动的概率
	r =100 -u -d -l;	//由于机器运算的不准确性，为防止出现概率漏洞，取1 - 其他概率的值为向右移动的概率
	if (ra < u) re = 1;
	else if(ra < (u + d)) re = 2;
	else if (ra < (u + d + l)) re = 3;
	else re = 4;	//根据随机数与概率取一个返回值
	return re;	//返回结果，上，下，左，右分别为 1，2，3，4
}

void move(int c)
{
	cre[c].step[s] = '0';	//为生物当前移动情况定一个默认值
	if (cre[c].alive == 1)	//判定生物是否存活且未到达出口
	{
		switch (randmove(c))	//根据随机移动函数的返回值选择移动方向
		{
		case 1:
			if (bg[cre[c].x][cre[c].y - 1] != '#')		//判定前方是否为空，若不为空则进一步判定是墙壁还是出口，是墙壁则碰壁死亡，是出口则赋予生存状态2以暂停单位并提供更高的排序优先级。
			{
				if (bg[cre[c].x][cre[c].y - 1] == '$')
				{
					cre[c].alive = 2;
				}
				else
				{
					cre[c].y--;
					cre[c].step[s] = '1';
				}
			}
			else
			{
				cre[c].alive = 0;
			}
			break;
		case 2:
			if (bg[cre[c].x][cre[c].y + 1] != '#')
			{
				if (bg[cre[c].x][cre[c].y + 1] == '$')
				{
					cre[c].alive = 2;
				}
				else
				{
					cre[c].y++;
					cre[c].step[s] = '2';
				}
			}
			else
			{
				cre[c].alive = 0;
			}
			break;
		case 3:
			if (bg[cre[c].x - 1][cre[c].y] != '#')
			{
				if (bg[cre[c].x - 1][cre[c].y] == '$')
				{
					cre[c].alive = 2;
				}
				else
				{
					cre[c].x--;
					cre[c].step[s] = '3';
				}
			}
			else
			{
				cre[c].alive = 0;
			}
			break;
		case 4:
			if (bg[cre[c].x + 1][cre[c].y] != '#')
			{
				if (bg[cre[c].x + 1][cre[c].y] == '$')
				{
					cre[c].alive = 2;
				}
				else
				{
					cre[c].x++;
					cre[c].step[s] = '4';
				}
			}
			else
			{
				cre[c].alive = 0;
			}
			break;
		}
	}
}

void run()
{
	int a, b; //定义循环用变量
	generation++; //选择代数+1
	s = 0;	//初始化路径记录起点，很重要，如不初始化会导致数组溢出造成程序崩溃
	for (b = 0; b < NUM; b++)	// 初始化生物生存状态，恢复被暂停单位，清空上一轮路径
	{
		cre[b].alive = 1;
		for (a = 0; a < 60; a++)
		{
			cre[b].step[a] = '0';
		}
	}
	for(a = 0; a < 50; a = (live <= NUM / 2) ? 50 : a)	//使生物随即移动，循环50次或生物数量小于最大值一半时终止循环
	{
		for (b = 0; b < NUM; b++) move(b);
		refresh();
		Sleep(50);
		a++;
		s++;	//路径记录步数+1
	}
}

void swap(int a, int b)
{
	int v;
	char tgene[9];
	int tx;
	int ty;
	char tstep[61];
	int talive;
	//---------------------
	for (v = 0; v < 9; v++) //将生物a的各项数据记录在临时变量中
	{
		tgene[v] = cre[a].gene[v];
	}
	tx = cre[a].x;
	ty = cre[a].y;
	for (v = 0; v < 61; v++)
	{
		tstep[v] = cre[a].step[v];
	}
	talive = cre[a].alive;
	//---------------------
	for (v = 0; v < 9; v++)	//将生物b的数据赋给生物a
	{
		cre[a].gene[v] = cre[b].gene[v];
	}
	cre[a].x = cre[b].x;
	cre[a].y = cre[b].y;
	for (v = 0; v < 61; v++)
	{
		cre[a].step[v] = cre[b].step[v];
	}
	cre[a].alive = cre[b].alive;
	//-------------------------
	for (v = 0; v < 9; v++)	//从临时变量中取出生物a的数据赋给生物b
	{
		cre[b].gene[v] = tgene[v];
	}
	cre[b].x =tx;
	cre[b].y = ty;
	for (v = 0; v < 61; v++)
	{
		cre[b].step[v] = tstep[v];
	}
	cre[b].alive = talive;
}

void dieout()
{
	int a;
	for (a = NUM / 2; a < NUM; a++) cre[a].alive = 0;
	for (a = 0; a <NUM / 20; a++)
	{
		cre[rand() % (NUM / 3) + NUM / 5].alive = 0;
		cre[rand() % (NUM / 3) + NUM / 2].alive = 1;
	}
}

void rank()
{
	int a,b, n1, n2, n3;
	n1 = 0;
	n2 = 0;
	n3 = 0;
	for (a = 0; a < NUM - 1 ; a++)	//根据生存状态进行初步排序
	{
		for (b = 0; b < NUM  - a - 1; b++)
		{
			if (cre[b].alive < cre[b + 1].alive)
			{
				swap(b, b + 1);
			}
		}
	}
	for (a = 0; a <NUM; a++)	//统计各个状态中的生物数目
	{
		n1 += (cre[a].alive == 2) ? 1 : 0;
		n2 += (cre[a].alive == 1) ? 1 : 0;
		n3 += (cre[a].alive == 0) ? 1 : 0;
	}
	for (a = 0; a < n1 - 1; a++)	//对抵达终点的生物进行排序，依据为所用步数，越小越靠前
	{
		for (b = 0; b < n1 - a - 1; b++)
		{
			int s1, s2, i;
			s1 = 0;
			s2 = 0;
			for (i = 0; i < 60; i++) if (cre[b].step[i] == '0') s1++;
			for (i = 0; i < 60; i++) if (cre[b + 1].step[i] == '0') s2++;
			if (s1 < s2) swap(b, b + 1);
		}
	}
	for (a = n1; a < n1 + n2 - 1; a++)	//对未抵达终点但是存活的单位进行排序， 依据是x值，越靠近右边越靠前
	{
		for (b = n1; b < n1 + n2 - a - 1; b++) if (cre[b].x < cre[b + 1].x) swap(b, b + 1);
	}
	for (a = n1+n2; a <NUM - 1 ; a++)		//对死亡单位进行排序，依据同上。
	{
		for (b = n1 + n2; b < NUM - 1 ; b++) if (cre[b].x < cre[b + 1].x) swap(b, b + 1);
	}
}

void reproduce()
{
	int a, b, t;		//定义循环变量和存储临时数据的变量
	live = 0;	//初始化存活生物数量
	for (b = 0; b < NUM; b++) if (cre[b].alive != 0) live++;	//统计存活生物数量
	while (live < NUM)	//为死亡生物赋予新生，直到所有生物的状态都为存活
	{
		for (a = 0; a < NUM; a++)	//遍历所有生物
		{
			cre[a].x = 4;	//初始化所有生物的位置
			cre[a].y = 10;
			if (cre[a].alive == 0)		//判定生物是否死亡
			{
				for (b = 0; b < 8; b++)		//对死亡单位的每一位基因进行操作
				{
					t = rand() % NUM;	//随机取一个生物
					while (cre[t].alive == 0)
					{
						t = rand() % NUM;	//判定选取生物的存活状态，直到选取到存活的生物
					}
					cre[a].gene[b] = (rand() % 1000 == 122)? rand()%3 + 48 : cre[t].gene[b];	//设置死亡单位的基因，有千分之一的概率发生随机变异
				}
				cre[a].alive = 1;	//将死亡单位的存活状态设为存活
				for (b = 0; b < NUM; b++) if (cre[b].alive != 0) live++;	//统计存活单位总数目
			}
		}
	}
}