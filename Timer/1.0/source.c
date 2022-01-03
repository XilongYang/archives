#include<stdio.h>
#include<windows.h>

int main()
{
	int min = 0;
	int sec = 59;
	char flag = 'y';

	while (flag == 'y')
	{
		printf("Enter a number: ");
		scanf("%d", &min);
		for (min = min - 1; min >= 0; min--)
		{
			for (sec = 59; sec >= 0; sec--)
			{
				system("cls");
				printf("%2.2d:%2.2d\n", min, sec);
				Sleep(1000);
			}
		}
		printf("\a");
		printf("Continue?(y/n): ");
		getchar();
		scanf("%c", &flag);
		system("cls");
	}
	return 0;
}
