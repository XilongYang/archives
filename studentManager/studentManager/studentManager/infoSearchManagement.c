/*
	信息查询模块
	作者：杨熙龙
	版本 1.0
*/

#include "studentManagerData.h"

void infoSearchManager(studInfo* tmpStudent, courInfo* tmpCourse, resuInfo *tmpResult)
{
	// 声明部分
	void infoSearchMenu();
	void studentInfoSearch(studInfo *, int);
	void courseInfoSearch(courInfo *, int);
	void enrolInfoSearch(resuInfo *, int);
	void scoreInfoSearch(resuInfo *, int);
	int infoSearchMenuChoice = 1;
	// 主要功能部分
	while (infoSearchMenuChoice)
	{
		infoSearchMenu();
		printf("Enter your choice:");
		scanf("%d", &infoSearchMenuChoice);
		fflush(stdin);
		switch (infoSearchMenuChoice)
		{
		case 11:
			studentInfoSearch(tmpStudent, 0);
			break;
		case 12:
			studentInfoSearch(tmpStudent, 1);
			break;
		case 13:
			studentInfoSearch(tmpStudent, 2);
			break;
		case 21:
			courseInfoSearch(tmpCourse, 0);
			break;
		case 22:
			courseInfoSearch(tmpCourse, 1);
			break;
		case 31:
			enrolInfoSearch(tmpResult, 0);
			break;
		case 32:
			enrolInfoSearch(tmpResult, 1);
			break;
		case 33:
			enrolInfoSearch(tmpResult, 2);
			break;
		case 41:
			scoreInfoSearch(tmpResult, 0);
			break;
		case 42:
			scoreInfoSearch(tmpResult, 1);
			break;
		case 43:
			scoreInfoSearch(tmpResult, 2);
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

void infoSearchMenu()
{
	// 打印模块菜单
	system("CLS");
	printf("\n%40s\n", "信 息 查 询 系 统");
	printf("%50s\n", "------------------------------------");
	printf("%39s\n", "*学生信息查询    ");
	printf("%39s\n", "11.按 学 号 查 询");
	printf("%39s\n", "12.按 姓 名 查 询");
	printf("%39s\n", "13.按 地 址 查 询");
	printf("%39s\n", "*课程信息查询    ");
	printf("%39s\n", "21.按 课 号 查 询");
	printf("%39s\n", "22.按 课 名 查 询");
	printf("%39s\n", "*选课信息查询    ");
	printf("%39s\n", "31.按 学 号 查 询");
	printf("%39s\n", "32.按 课 号 查 询");
	printf("%39s\n", "33.显示 所有 信息");
	printf("%39s\n", "*成绩信息查询    ");
	printf("%39s\n", "41.按 学 号 查 询");
	printf("%39s\n", "42.按 课 号 查 询");
	printf("%39s\n", "43.按 排 名 显 示");
	printf("%39s\n", "0.回  主  菜  单 ");
	printf("%50s\n", "------------------------------------");
}

void studentInfoSearch(studInfo *inStudent, int mode)
{
	// 查询学生信息，功能与学生信息管理模块近似
	if (mode == 0)
	{
		system("CLS");
		int tmpSID, flg = 1, i;
		printf("Enter a student ID:");
		scanf("%d", &tmpSID);
		printf("%-4s %-10s %3s %-15s\n", "ID", "Name", "Sex", "Address");
		printf("------------------------------------\n");
		for (i = 0; i < N; i++)
		{
			if (inStudent[i].sNo == tmpSID && inStudent[i].sNo != 0)
			{
				printf("%4d %-10s %3c %-15s\n", inStudent[i].sNo, inStudent[i].sName,
					inStudent[i].sSex, inStudent[i].sAddress);
				flg = 0;
			}
		}
		if (flg)
		{
			printf("No data found!\n");
		}
		printf("\nPress <Enter> to continue.");
		getchar();
		getchar();
	}
	else if (mode == 1)
	{
		system("CLS");
		int flg = 1, i;
		char tmpName[40];
		printf("Enter a Name:");
		scanf("%s", &tmpName);
		printf("%-4s %-10s %3s %-15s\n", "ID", "Name", "Sex", "Address");
		printf("------------------------------------\n");
		for (i = 0; i < N; i++)
		{
			if (!(strcmp(inStudent[i].sName, tmpName)) && inStudent[i].sNo != 0)
			{
				printf("%4d %-10s %3c %-15s\n", inStudent[i].sNo, inStudent[i].sName,
					inStudent[i].sSex, inStudent[i].sAddress);
				flg = 0;
			}
		}
		if (flg)
		{
			printf("No data found!\n");
		}
		printf("\nPress <Enter> to continue.");
		getchar();
		getchar();
	}
	else
	{
		system("CLS");
		int flg = 1, i;
		char tmpAddress[40];
		printf("Enter a address:");
		scanf("%s", &tmpAddress);
		printf("%-4s %-10s %3s %-15s\n", "ID", "Name", "Sex", "Address");
		printf("------------------------------------\n");
		for (i = 0; i < N; i++)
		{
			if (!(strcmp(inStudent[i].sAddress, tmpAddress)) && inStudent[i].sNo != 0)
			{
				printf("%4d %-10s %3c %-15s\n", inStudent[i].sNo, inStudent[i].sName,
					inStudent[i].sSex, inStudent[i].sAddress);
				flg = 0;
			}
		}
		if (flg)
		{
			printf("No data found!\n");
		}
		printf("\nPress <Enter> to continue.");
		getchar();
		getchar();
	}
}

void courseInfoSearch(courInfo *headCourse, int mode)
{
	// 查询课程信息，功能与课程信息管理模块近似
	int flg = 1;
	if (mode == 0)
	{
		int tmpCID;
		courInfo *currentCourse;
		system("CLS");
		printf("Enter a course ID:");
		scanf("%d", &tmpCID);
		printf("%-4s %-20s %6s %6s\n", "ID", "Name", "Credit", "Period");
		printf("---------------------------------------\n");
		for (currentCourse = headCourse; currentCourse != NULL && currentCourse->cNo != 0;
			currentCourse = currentCourse->next)
		{
			if (currentCourse->cNo == tmpCID && currentCourse->cNo != 0)
			{
				flg = 0;
				printf("%4d %-20s %6d %6d\n", currentCourse->cNo, currentCourse->cName,
					currentCourse->cCredit, currentCourse->cTime);
			}
		}
		getchar();
	}
	else
	{
		char tmpName[80];
		courInfo *currentCourse;
		system("CLS");
		getchar();
		printf("Enter course name:");
		fgets(tmpName, 80, stdin);
		char *p = tmpName;
		for (; *p != '\0'; p++)
		{
			if (*p == '\n') *p = '\0';
		}
		printf("%-4s %-20s %6s %6s\n", "ID", "Name", "Credit", "Period");
		printf("---------------------------------------\n");
		for (currentCourse = headCourse; currentCourse != NULL && currentCourse->cNo != 0;
			currentCourse = currentCourse->next)
		{
			if (!(strcmp(currentCourse->cName, tmpName)) && currentCourse->cNo != 0)
			{
				flg = 0;
				printf("%4d %-20s %6d %6d\n", currentCourse->cNo, currentCourse->cName,
					currentCourse->cCredit, currentCourse->cTime);
			}
		}
	}
	if (flg) printf("No data!\n");
	printf("\nPress <Enter> to continue.\n");
	getchar();
}

void enrolInfoSearch(resuInfo *tmpResult, int mode)
{
	// 查询选课信息，功能与选课信息管理模块近似
	system("ClS");
	int i, j, flg = 1, inID;
	resultStudnumInfoSort(tmpResult);
	if (mode == 0)
	{
		printf("Enter student ID: ");
		scanf("%d", &inID);
		printf("%-4s %-10s %-4s %-15s %4s\n", "S.ID", "Name", "C.ID", "Course", "Term");
		printf("------------------------------------\n");
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			if (tmpResult[i].sNo == inID)
			{
				printf("%-4d %-10s %-4d %-15s %4d\n", tmpResult[i].sNo, tmpResult[i].sName,
					tmpResult[i].cNo, tmpResult[i].cName, tmpResult[i].sTerm);
				flg = 0;
			}
		}
		if (flg) printf("No data!\n");
	}
	else if (mode == 2)
	{
		printf("%-4s %-10s %-4s %-15s %4s\n", "S.ID", "Name", "C.ID", "Course", "Term");
		printf("------------------------------------\n");
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			printf("%-4d %-10s %-4d %-15s %4d\n", tmpResult[i].sNo, tmpResult[i].sName,
				tmpResult[i].cNo, tmpResult[i].cName, tmpResult[i].sTerm);
			flg = 0;
		}
		if (flg) printf("No data!\n");
	}
	else
	{
		printf("Enter course ID: ");
		scanf("%d", &inID);
		printf("%-4s %-10s %-4s %-15s %4s\n", "S.ID", "Name", "C.ID", "Course", "Term");
		printf("------------------------------------\n");
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			if (tmpResult[i].cNo == inID)
			{
				printf("%-4d %-10s %-4d %-15s %4d\n", tmpResult[i].sNo, tmpResult[i].sName,
					tmpResult[i].cNo, tmpResult[i].cName, tmpResult[i].sTerm);
				flg = 0;
			}
		}
		if (flg) printf("No data!\n");
	}
	printf("\nPress <Enter> to continue.");
	getchar();
	getchar();
}

float scoreAverage(resuInfo *tmpResult, int SID)
{
	// 用以求平均分的函数，返回平均分
	int sumResult = 0, i;
	float averScore = 0.0, sumScore = 0.0;
	for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
	{
		if (tmpResult[i].sNo == SID)
		{
			sumResult++;
			sumScore += tmpResult[i].score;
		}
	}
	averScore = sumScore / sumResult;
	return averScore;
}

void sortScoreAverage(rankInfo *inrank)
{
	// 对学生成绩信息按平均分排序
	int i, j;
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < N - i - 1; j++)
		{
			if (inrank[j].averScore < inrank[j + 1].averScore && inrank[j].sNo != 0 && inrank[j + 1].sNo != 0)
			{
				rankInfo tmprank;
				tmprank = inrank[j];
				inrank[j] = inrank[j + 1];
				inrank[j + 1] = tmprank;
			}
		}
	}
}

void scoreInfoSearch(resuInfo *tmpResult, int mode)
{
	// 查询成绩信息
	system("ClS");
	int i, j, flg = 1, inID;
	// 对课程信息进行排序
	resultStudnumInfoSort(tmpResult);
	if (mode == 0)
	{
		// 按学号查询
		int sumResult = 0;
		float averScore = 0.0, sumScore = 0.0;
		printf("Enter student ID: ");
		scanf("%d", &inID);
		printf("%-4s %-10s %-4s %-15s %4s %5s\n", "S.ID", "Name", "C.ID", "Course", "Term", "Score");
		printf("------------------------------------\n");
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			if (tmpResult[i].sNo == inID)
			{
				printf("%-4d %-10s %-4d %-15s %4d %5d\n", tmpResult[i].sNo, tmpResult[i].sName,
					tmpResult[i].cNo, tmpResult[i].cName, tmpResult[i].sTerm, tmpResult[i].score);
				sumResult++;
				sumScore += tmpResult[i].score;
				flg = 0;
			}
		}
		if (flg)
		{
			printf("No data!\n");
		}
		else
		{
			averScore = sumScore / sumResult;
			printf("Average score: %.2f\n", averScore);
		}
	}
	else if (mode == 1)
	{
		// 按课号查询
		int sumResult = 0, tmpTerm;
		float averScore = 0.0, sumScore = 0.0;
		printf("Enter course ID: ");
		scanf("%d", &inID);
		printf("Enter term info: ");
		scanf("%d", &tmpTerm);
		printf("%-4s %-10s %-4s %-15s %4s %5s\n", "S.ID", "Name", "C.ID", "Course", "Term", "Score");
		printf("------------------------------------\n");
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			if (tmpResult[i].cNo == inID && tmpResult[i].sTerm == tmpTerm)
			{
				printf("%-4d %-10s %-4d %-15s %4d %5d\n", tmpResult[i].sNo, tmpResult[i].sName,
					tmpResult[i].cNo, tmpResult[i].cName, tmpResult[i].sTerm, tmpResult[i].score);
				sumResult++;
				sumScore += tmpResult[i].score;
				flg = 0;
			}
		}
		if (flg)
		{
			printf("No data!\n");
		}
		else
		{
			averScore = sumScore / sumResult;
			printf("Average score: %.2f\n", averScore);
		} 		
	}
	else
	{
		// 按排名显示
		rankInfo tmprank[N];
		int k = 0;
		for (i = 0; i < N; i++)
		{
			tmprank[i].sNo = 0;
			tmprank[i].averScore = 0;
			tmprank[i].sName[0] = '\0';
		}
		for (i = 0; i < S && tmpResult[i].sNo != 0; i++)
		{
			int flg1 = 1;
			for (j = 0; j < N; j++)
			{
				if (tmprank[j].sNo == tmpResult[i].sNo)
				{
					flg1 = 0;
				}
			}
			if(flg1)
			{
				tmprank[k].sNo = tmpResult[i].sNo;
				strcpy(&tmprank[k].sName, &tmpResult[i].sName);
				tmprank[k].averScore = scoreAverage(tmpResult, tmpResult[i].sNo);
				k++;
			}
		}
		sortScoreAverage(tmprank);
		printf("%-4s %-10s %5s\n", "S.ID", "Name", "Score");
		printf("------------------------------------\n");
		for (i = 0; i < N && tmprank[i].sNo != 0; i++)
		{
			printf("%-4d %-10s %5.2f\n", tmprank[i].sNo, tmprank[i].sName,
				tmprank[i].averScore);
			flg = 0;
		}
		if (flg) printf("No data!\n");
	}
	printf("\nPress <Enter> to continue.");
	getchar();
	getchar();
}