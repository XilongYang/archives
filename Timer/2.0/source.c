#include<stdio.h>
#include<windows.h>

char bg[65][11];
char  in[10];
int sum[8];
int hour, min, sec;

void init();
void draw();
void refresh();

int main()
{
	int con = 1;
	int con1 = 1;
	int con2 = 1;
	int loop;
	char conc;
	while (con)
	{
		con2 = 1;
		con1 = 1;
		init();
		while (con2)
		{
			printf("Time(**h**m**s): ");
			scanf("%s", in);
			getchar();
			if (in[0] < 58 && in[0] > 47)
			{
				if ((in[1] == 'H' || in[1] == 'h' || in[1] == 'M' || in[1] == 'm' || in[1] == 'S' || in[1] == 's') && in[2] == '\0' )
				{
					break;
				}
				if ((in[1] < 58 && in[1] > 47) && (in[2] == 'H' || in[2] == 'h' || in[2] == 'M' || in[2] == 'm' || in[2] == 'S' || in[2] == 's') && in[3] == '\0')
				{
					break;
				}
				if ((in[1] < 58 && in[1] > 47) && (in[2] == 'H' || in[2] == 'h') && (in[3] < 58 && in[3] > 47) && (in[4] < 58 && in[4] > 47) && (in[5] == 'M' || in[5] == 'm') && (in[6] < 58 && in[6] > 47) && (in[7] < 58 && in[7] > 47) && (in[8] == 'S' || in[8] == 's'))
				{
					break;
				}
				if ((in[1] < 58 && in[1] > 47) && (in[2] < 58 && in[2] > 47) && (in[3] < 58 && in[3] > 47) && in[4] == '\0')
				{
					if(in[0] < 54)
					break;
				}
				if (((in[1] < 58 && in[1] > 47) && (in[2] < 58 && in[2] > 47) && (in[3] == '\0')) || ((in[1] < 58 && in[1] > 47) && (in[2] == '\0')) || (in[1] == '\0'))
				{
						break;
				}
			}
			if (in[0] == 'h' && in[1] == 'e' && in[2] == 'l' && in[3] == 'p')
			{
				printf("Enable input:\n xxHxxMxxS\n xxx(min)\n xxH/M/S\n");
			}
			else
			{
				printf("Error!\n");
			}
		}
		for (loop = 0; loop < 10; loop++)
		{
			if (in[loop] != '\0')
			{
				if (in[loop] == 'h' || in[loop] == 'H')
				{
					if (loop == 1)
					{
						hour = in[loop - 1] - 48;
					}
					else
					{
						hour = (in[loop - 2] - 48) * 10 + (in[loop - 1] - 48);
					}
				}
				if (in[loop] == 'm' || in[loop] == 'M')
				{
					if (loop == 1)
					{
						min = in[loop - 1] - 48;
					}
					else
					{
						min = (in[loop - 2] - 48) * 10 + (in[loop - 1] - 48);
					}
				}
				if (in[loop] == 's' || in[loop] == 'S')
				{
					if (loop == 1)
					{
						sec = in[loop - 1] - 48;
					}
					else
					{
						sec = (in[loop - 2] - 48) * 10 + (in[loop - 1] - 48);
					}
				}
			}
			else
			{
				int loop1, flag, loop2;
				flag = 1;
				for (loop1 = 0; loop1 < loop; loop1++)
				{
					if (in[loop1] < 48 || in[loop1] > 57)
					{
						flag = 0;
						break;
					}
				}
				if (flag)
				{
					for (loop1 = 0; loop1 < loop; loop1++)
					{
						sum[loop1] = in[loop1] - 48;
						for (loop2 = 0; loop2 < loop - loop1 - 1; loop2++)
						{
							sum[loop1] = sum[loop1] * 10;
						}
					}
					for (loop2 = 0; loop2 < 7; loop2++)
					{
						sum[7] += sum[loop2];
					}
					hour = sum[7] / 60;
					min = sum[7] - hour * 60;
				}
			}
		}
		for (hour = hour; hour >= 0; hour--)
		{
			draw(1, hour / 10);
			draw(2, hour % 10);
			for (min; min >= 0; min--)
			{
				draw(3, min / 10);
				draw(4, min % 10);
				for (sec; sec >= 0; sec--)
				{
					draw(5, sec / 10);
					draw(6, sec % 10);
					refresh();
					Sleep(1000);
				}
				sec = 59;
			}
			min = 59;
		}
		while (con1)
		{
			printf("\aContinue(y/n)?: ");
			scanf("%c", &conc);
			getchar();
			if (conc == 'n' || conc == 'N' || conc == 'y' || conc == 'Y')
			{
				if (conc == 'n' || conc == 'N')
				{
					con = 0;
					printf("%c", conc);
				}
				con1 = 0;
			}
			else
			{
				printf("Error!\n");
				con1 = 1;
			}
		}
	}
	return 0;
}

void init()
{
	int x, y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	system("mode con cols=66 lines=12");
	for (y = 0; y < 11; y++)
	{
		for (x = 0; x < 65; x++)
		{
			bg[x][y] = ' ';
			if(((y == 4 || y == 6) && (x == 21 || x == 22 || x == 43 || x == 44)))
			bg[x][y] = '#';
			printf("%c", bg[x][y]);
		}
		printf("\n");
	}
	for (y = 1; y < 7; y++)
	{
		draw(y, 0);
	}
	for (y = 0; y < 8; y++)
	{
		in[y] = '#';
		sum[y] = 0;
	}
	hour = 0;
	min = 0;
	sec = 0;
	refresh();
}

void draw(int place, int number)
{
	int px,  n1, x, y;
	switch (place)
	{
	case 1:
		px = 3;
		break;
	case 2:
		px = 12;
		break;
	case 3:
		px = 25;
		break;
	case 4:
		px = 34;
		break;
	case 5:
		px = 47;
		break;
	case 6:
		px = 56;
		break;
	}
	for (y = 2; y< 9; y++)
	{
		for (x = px; x < px + 7; x++)
		{
			bg[x][y] = ' ';
			switch (number)
			{
			case 0:
				if (x == px || x == px + 6 || y == 2 || y == 8)
				{
					bg[x][y] = '#';
				}
				break;
			case 1:
				if (x == px + 6)
				{
					bg[x][y] = '#';
				}
				break;
			case 2:
				if ( y == 5 || y == 2 || y == 8 || (x == px + 6 && y < 5) || (x == px && y > 5))
				{
					bg[x][y] = '#';
				}
				break;
			case 3:
				if (y == 5 || y == 2 || y == 8 || x == px + 6)
				{
					bg[x][y] = '#';
				}
				break;
			case 4:
				if (y == 5 || x == px + 6 || (x == px && y < 5))
				{
					bg[x][y] = '#';
				}
				break;
			case 5:
				if (y == 5 || y == 2 || y == 8 || (x == px + 6 && y > 5) || (x == px && y < 5))
				{
					bg[x][y] = '#';
				}
				break;
			case 6:
				if (y == 5 || y == 2 || y == 8 || (x == px + 6 && y > 5) || x == px )
				{
					bg[x][y] = '#';
				}
				break;
			case 7:
				if (y == 2 || x == px + 6 )
				{
					bg[x][y] = '#';
				}
				break;
			case 8:
				if (x == px || x == px + 6 || y == 2 || y == 8 || y == 5)
				{
					bg[x][y] = '#';
				}
				break;
			case 9:
				if ((x == px && y < 5) || x == px + 6 || y == 2 || y == 8 || y == 5)
				{
					bg[x][y] = '#';
				}
				break;
			}
		}
	}
}

void refresh()
{
	int x, y;
	system("cls");
	for (y = 0; y < 11; y++)
	{
		for (x = 0; x < 65; x++)
		{
			printf("%c", bg[x][y]);
		}
		printf("\n");
	}
}
