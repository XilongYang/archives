#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

char b[100][41];	//定义一个二维数组作为背景
int flag = 1;		//游戏存活判定开关
int number = 5;		//蛇的身体节数
int locnum = 0;		//转折的地点数
int timer = 100;	//食物刷新间隔
int score = 0;		//得分

struct location {	//定义一个类用来标记蛇的转折点，拥有转向数据，横纵坐标和开关四个参数
	int sta;
	int x1;
	int y1;
	int flag;
};

struct bodys {	//定义一个类用来存放蛇的身体，拥有转向数据和横纵坐标三个参数
	int statu;
	int x2;
	int y2;
};

struct bodys body[1000];	//声明类
struct location loc[10000];

void init();		//声明自定义函数
void move(int bo);
void play();
void food();
void eatfood();
void getxy(int x, int y);

int main()
{
	printf("简易的贪吃蛇，方向键控制，按回车键开始。\n");	//开始界面
	getchar();	//用以捕捉回车
	init();	//游戏初始化
	play();	//游戏操作函数
	system("cls");	//清空屏幕
	printf("You die!\n""Your score is: %d\n", score * 10);	//结束界面
	getchar();	//用以使界面暂停
	return 0;
}

void init()		//初始化函数
{
	int x , y , j , k;	//定义for循环需要使用的函数
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	//隐藏光标
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	system("mode con cols=100 lines=42");	//设置窗口大小
	for (y = 0; y <= 40; y++)	//调用两个for循环打印游戏背景界面
	{
		for (x = 0; x <= 99; x++)
		{
			b[x][y] = ' ';
			if (x == 0 || x == 99 || y == 0 || y == 40)
			{
				b[x][y] = '#';
			}
			printf("%c", b[x][y]);
		}
		printf("\n");
	}
	for (j = 0; j < number; j++)	//打印初始蛇身
	{
		body[j].statu = 1;
		body[j].x2 = 40 - j * 2;
		body[j].y2 = 20;
		if (j == 0)
		{
			b[body[j].x2][body[j].y2] = '@';
		}
		else
		{
			b[body[j].x2][body[j].y2] = '0';
		}
	}	
	for (k = 0; k < 10000; k++)	//转折点初始化
	{
		loc[k].flag = 0;
	}
	food();
	body[0].statu = 1;	//初始方向初始化，向右运动
}

void move(int bo)	//移动函数，有一个参数用以选择第几节身体
{
	switch(body[bo].statu)	//判定方向
	{
	case 1:		//向右的情况
		if (b[body[bo].x2 + 2][body[bo].y2] != ' ' && b[body[bo].x2 + 2][body[bo].y2] != '$')	//判定前方障碍，有蛇身或墙壁则游戏失败。
		{
			flag = 0;
			break;
		}  
		b[body[bo].x2 + 2][body[bo].y2] = b[body[bo].x2][body[bo].y2];	//设置前面一格字符为待移动字符
		b[body[bo].x2][body[bo].y2] = ' ';//删除残留字符
		getxy(body[bo].x2 + 2, body[bo].y2);
		putchar('0');
		getxy(body[bo].x2, body[bo].y2);
		putchar(' ');
		body[bo].x2 += 2;	//更新身体数据
		break;
	case 2:	//向下
		if (b[body[bo].x2][body[bo].y2 +1] != ' ' && b[body[bo].x2][body[bo].y2 + 1] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2][body[bo].y2 + 1] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		getxy(body[bo].x2, body[bo].y2 + 1);
		putchar('0');
		getxy(body[bo].x2, body[bo].y2);
		putchar(' ');
		body[bo].y2++;
		break;
	case 3:	//向左
		if (b[body[bo].x2 - 2][body[bo].y2] != ' ' && b[body[bo].x2 - 2][body[bo].y2] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2 - 2][body[bo].y2] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		getxy(body[bo].x2 - 2, body[bo].y2);
		putchar('0');
		getxy(body[bo].x2, body[bo].y2);
		putchar(' ');
		body[bo].x2--;
		body[bo].x2--;
		break;
	case 4:	//向上
		if (b[body[bo].x2][body[bo].y2 -1] != ' ' && b[body[bo].x2][body[bo].y2 - 1] != '$')
		{
			flag = 0;
			break;
		}
		b[body[bo].x2][body[bo].y2 - 1] = b[body[bo].x2][body[bo].y2];
		b[body[bo].x2][body[bo].y2] = ' ';
		getxy(body[bo].x2, body[bo].y2 - 1);
		putchar('0');
		getxy(body[bo].x2, body[bo].y2);
		putchar(' ');
		body[bo].y2--;
		break;
	}
}

void play()	//游戏操作函数，用以判断玩家按键与计时刷新
{
	int x,y,m, flag1;	//定义for循环需要用的变量
	while (flag)	//游戏进行开关，关闭flag则结束游戏
	{
		if (9999 == locnum)
			locnum = 1;
		if (GetAsyncKeyState(VK_UP) && body[0].statu != 2)	//判断是否按下上方向键
		{
			body[0].statu = 4;	//设置蛇头的方向参数为上
			loc[locnum].flag = 1;	//打开转向点开关
			loc[locnum].sta = body[0].statu;	//设置转向点的方向参数
			loc[locnum].x1 = body[0].x2;	//设置转向点横坐标
			loc[locnum].y1 = body[0].y2;	//设置转向点纵坐标
			locnum++;	//下一个转向点序号加一
		}
		else if (GetAsyncKeyState(VK_DOWN) && body[0].statu != 4)	//判断下方向键
		{
			body[0].statu = 2;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		else if (GetAsyncKeyState(VK_LEFT) && body[0].statu != 1)	//判断左方向键
		{
			body[0].statu = 3;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && body[0].statu != 3)	//判断右方向键
		{
			body[0].statu = 1;
			loc[locnum].flag = 1;
			loc[locnum].sta = body[0].statu;
			loc[locnum].x1 = body[0].x2;
			loc[locnum].y1 = body[0].y2;
			locnum++;
		}
		for (x = 1; x < number; x++)	//判定已打开转向点上是否有字符，如果有就改变字符的方向参数，蛇尾通过时则关闭该转向点。
		{
			for (y = 0; y < 10000; y++)
			{
				if (loc[y].flag)
				{
					if (loc[y].x1 == body[x].x2 && loc[y].y1 == body[x].y2) //判定蛇身与转向点坐标是否重合
					{
						body[x].statu = loc[y].sta;	//改变蛇身方向参数
						if (x == number - 1)	//判定是否为蛇尾
						{
							loc[y].flag = 0;	//关闭转向点
						}
					}
				}
			}
		}
		Sleep(200);	//刷新频率
		for (m = 0; m < number; m++)	//循环选择所有蛇身，并且移动它们。
		{
			move(m);
		}
		if (timer == 200)	//根据间隔刷新食物
		{
			food();
			timer = 0;
		}
		else
		{
			timer++;
		}
		flag1 = 1;
		for (y = 0; y <= 40; y++)	//吃掉食物后加分
		{
			for (x = 0; x <= 99; x++)
			{
				if (b[x][y] == '$')
				{
					flag1 = 0;
				}
			}
		}
		if (flag1) eatfood();
		getxy(0, 41);
		printf("Score: %d", score * 10);
	}
}

void food()	//生成食物函数
{
	int x,y;	//定义for循环需要的变量
	int flag = 1;	//定义食物生成条件变量
	srand(time(NULL));	//用系统时间作为随机数种子
	for (y = 0; y <= 40; y++)	//遍历所有字符删除已存在食物
	{
		for (x = 0; x <= 99; x++)
		{
			if (b[x][y] == '$')
			{
				b[x][y] = ' ';
				getxy(x, y);
				putchar(b[x][y]);
			}
		}
	}
	while (flag)
	{
		int x3 = (rand() % 98) + 1;	//生成1-99范围内的随机数作为食物横坐标
		int y3 = (rand() % 39) + 1;	//生成1-40范围内的随机数作为食物纵坐标
		if ((b[x3][y3] == ' ' || b[x3][y3] == '$') && x3%2 == 0)	//判定食物坐标点是否可以使用，如无法使用则重新生成
		{
			b[x3][y3] = '$';
			getxy(x3, y3);
			putchar(b[x3][y3]);
			flag = 0;	//关闭循环
		}
	}
}

void eatfood()	//进食函数
{
	switch (body[number - 1].statu)	//判定蛇尾前进方向
	{
	case 1:	//向右运动时的情况
		body[number].statu = body[number - 1].statu;	//定义新生身体的方向参数
		body[number].x2 = body[number - 1].x2 - 2;		//定义新生身体的横坐标，为蛇尾运动方向的反向+1格
		body[number].y2 = body[number - 1].y2;			//定义新生身体的纵坐标
		b[body[number].x2][body[number].y2] = '0';		//生成新身体
		getxy(body[number].x2, body[number].y2);
		putchar('0');
		number++;										//总身体数加一
		break;
	case 2:	//向下运动时的情况
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2;
		body[number].y2 = body[number - 1].y2 - 1;
		b[body[number].x2][body[number].y2] = '0';
		getxy(body[number].x2, body[number].y2);
		putchar('0');
		number++;
		break;
	case 3:	//向左
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2 + 2;
		body[number].y2 = body[number - 1].y2;
		b[body[number].x2][body[number].y2] = '0';
		getxy(body[number].x2, body[number].y2);
		putchar('0');
		number++;
		break;
	case 4:	//向上
		body[number].statu = body[number - 1].statu;
		body[number].x2 = body[number - 1].x2;
		body[number].y2 = body[number - 1].y2 + 1;
		b[body[number].x2][body[number].y2] = '0';
		getxy(body[number].x2, body[number].y2);
		putchar('0');
		number++;
		break;
	}
	food();	//生成新的食物
	score++;	//分数加一
	timer = 0;
}

void getxy(int x, int y) //移动光标函数，用以实现字符的变化
{
	COORD cor;
	HANDLE hout;
	cor.X = x;
	cor.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, cor);
}