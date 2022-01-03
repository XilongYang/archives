/*
	成绩管理模块
	作者：杨熙龙
	版本：v1.0
*/

#include "studentManagerData.h"

void scoreInfoManager(resuInfo *tmpResult)
{
	// 声明部分
	void scoreInfoMenu();
	void scoreInfoInput(resuInfo *);
	void scoreInfoEdit(resuInfo *);
	int resultInfoMenuChoice = 1;
	// 主要功能部分
	while (resultInfoMenuChoice)
	{
		scoreInfoMenu();
		printf("Enter your choice<0-2>:");
		scanf("%d", &resultInfoMenuChoice);
		fflush(stdin);
		switch (resultInfoMenuChoice)
		{
		case 1:
			scoreInfoInput(tmpResult);
			break;
		case 2:
			scoreInfoEdit(tmpResult);
			break;
		case 0:
			break;
		default:
			printf("Worng choice!");
			getchar();
			getchar();
			break;
		}
	}
}

void scoreInfoMenu()
{
	// 打印成绩管理模块主菜单
	system("CLS");
	printf("\n%40s\n", "成绩信息管理系统");
	printf("%50s\n", "------------------------------------");
	printf("%39s\n", "1.成  绩  录  入");
	printf("\n%39s\n", "2.成  绩  修  改");
	printf("\n%39s\n", "0.回  主  菜  单");
	printf("%50s\n", "------------------------------------");
}

void scoreInfoInputMenu()
{
	// 打印成绩输入部分菜单
	int i;
	system("CLS");
	printf("%-4s %-10s %-4s %-15s %4s %5s\n", "S.ID", "Name", "C.ID", "Course", "Term", "Score");
	printf("------------------------------------\n");
}

void scoreInfoInput(resuInfo *inResult)
{
	// 用以输入成绩的函数
	int i, flg =1, scoreCID, scoreTerm, tmpScore[S];
	char scoreSaveChoice;
	courInfo *tmpCurrentCourse;
	// 输入课程信息
	system("CLS");
	printf("Enter course ID: ");
	scanf("%d", &scoreCID);
	getchar();
	printf("Enter term info: ");
	scanf("%d", &scoreTerm);
	resultInfoInputMenu();
	// 对查找到的选课信息进行成绩输入
	for (i = 0; i < S; i++)
	{
		tmpScore[i] = 0;
		if (inResult[i].cNo == scoreCID && inResult[i].sTerm == scoreTerm &&inResult[i].cNo != 0)
		{
			printf("%-4d %-10s %-4d %-15s %4d    ", inResult[i].sNo, inResult[i].sName,
				inResult[i].cNo, inResult[i].cName, inResult[i].sTerm);
			scanf("%d", &tmpScore[i]);
			flg = 0;
		}
	}
	fflush(stdin);
	if (flg)
	{
		printf("No result data found!\n");
	}
	else
	{
		// 确认改动
		printf("Save changes? <y/n>\n");
		getchar();
		scanf("%c", &scoreSaveChoice);
		if (scoreSaveChoice == 'Y' || scoreSaveChoice == 'y')
		{
			for (i = 0; i < S; i++)
			{
				if (inResult[i].cNo == scoreCID && inResult[i].sTerm == scoreTerm && inResult[i].cNo != 0)
				{
					inResult[i].score = tmpScore[i];
				}
			}
			printf("Complete!\n");
		}
	}
	printf("\nPress <Enter> to continue.\n");
	getchar();
	getchar();
}

void scoreInfoEdit(resuInfo *inResult)
{
	// 用以编辑成绩信息的函数
	int i, flg = 1, scoreSID, scoreCID, scoreTerm, tmpScore[S];
	char scoreSaveChoice;
	courInfo *tmpCurrentCourse;
	system("CLS");
	// 输入学号课号等信息
	printf("Enter student ID: ");
	scanf("%d", &scoreSID);
	printf("Enter course ID: ");
	scanf("%d", &scoreCID);
	printf("Enter term info: ");
	scanf("%d", &scoreTerm);
	resultInfoInputMenu();
	// 改变所属信息
	for (i = 0; i < S; i++)
	{
		tmpScore[i] = 0;
		if (inResult[i].sNo == scoreSID && inResult[i].cNo == scoreCID 
			&& inResult[i].sTerm == scoreTerm && inResult[i].cNo != 0)
		{
			printf("%-4d %-10s %-4d %-15s %4d %5d\n", inResult[i].sNo, inResult[i].sName,
				inResult[i].cNo, inResult[i].cName, inResult[i].sTerm, inResult[i].score);
			printf("Enter new score: ");
			scanf("%d", &tmpScore[i]);
			flg = 0;
		}
	}
	fflush(stdin);
	if (flg)
	{
		printf("No result data found!\n");
	}
	else
	{
		// 确认改动
		printf("Save changes? <y/n>\n");
		getchar();
		scanf("%c", &scoreSaveChoice);
		if (scoreSaveChoice == 'Y' || scoreSaveChoice == 'y')
		{
			for (i = 0; i < S; i++)
			{
				if (inResult[i].sNo == scoreSID && inResult[i].cNo == scoreCID
					&& inResult[i].sTerm == scoreTerm && inResult[i].cNo != 0)
				{
					inResult[i].score = tmpScore[i];
				}
			}
			printf("Complete!\n");
		}
	}
	printf("\nPress <Enter> to continue.\n");
	getchar();
	getchar();
}