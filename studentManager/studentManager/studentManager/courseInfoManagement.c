/*
	课程信息管理模块
	作者：杨熙龙
	版本：1.0
*/

#include "studentManagerData.h"

void courseInfoManager(courInfo **headCourseInfo)
{
	// 声明部分
	void courseInfoMenu();
	void courseInfoInput(courInfo*);
	void courseInfoEdit(courInfo**);
	void courseInfoDelete(courInfo**);
	void courseInfoLook(courInfo*);
	void courseInfoSort(courInfo**);
	int courseInfoMenuChoice = 1;
	// 主要功能部分
	while (courseInfoMenuChoice)
	{
		courseInfoMenu();
		printf("Enter your choice<0-5>:");
		scanf("%d", &courseInfoMenuChoice);
		switch (courseInfoMenuChoice)
		{
		case 1:
			courseInfoInput(*headCourseInfo);
			break;
		case 2:
			courseInfoEdit(headCourseInfo);
			break;
		case 3:
			courseInfoDelete(headCourseInfo);
			break;
		case 4:
			courseInfoLook(*headCourseInfo);
			break;
		case 5:
			courseInfoSort(headCourseInfo);
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

void courseInfoMenu()
{
	// 用以打印课程信息管理模块菜单的函数
	system("CLS");
	printf("\n%40s\n", "课程信息管理系统");
	printf("%50s\n", "------------------------------------");
	printf("%39s\n", "1.新        增");
	printf("\n%39s\n", "2.修        改");
	printf("\n%39s\n", "3.删        除");
	printf("\n%39s\n", "4.查        看");
	printf("\n%39s\n", "5.根据课号排序");
	printf("\n%39s\n", "0.回 主  菜 单");
	printf("%50s\n", "------------------------------------");
}

void courseInfoInput(courInfo *headCourse)
{
	// 用以新建课程信息的函数
	int courseID;
	courInfo *endCourse;
	// 找到信息尾部
	for (endCourse = headCourse; endCourse->next != NULL; endCourse = endCourse->next);
	system("CLS");
	// 输入信息
	printf("Enter a course ID: ");
	scanf("%d",&courseID);
	getchar();
	while (courseID)
	{
		if (0 != endCourse->cNo)
		{
			endCourse->next = (courInfo*)malloc(sizeof(courInfo));
			endCourse = endCourse->next;
			endCourse->next = NULL;
		}
		endCourse->cNo = courseID;
		printf("Enter course name:");
		fgets(endCourse->cName, 80, stdin);
		char *p = endCourse->cName;
		for (; *p != '\0'; p++)
		{
			if (*p == '\n') *p = '\0';
		}
		printf("Enter course credit:");
		scanf("%d", &endCourse->cCredit);
		printf("Enter course period:");
		scanf("%d", &endCourse->cTime);
		system("CLS");
		printf("Enter course ID:");
		scanf("%d", &courseID);
		getchar();
	}
}

void courseInfoEdit(courInfo **headCourse)
{
	// 用以编辑课程信息的函数
	int courseID;
	char saveChangeChoice;
	courInfo *currentCourse, *tmpCourse;
	system("CLS");
	// 输入课程号并判定课程是否存在
	printf("Enter a course ID:");
	scanf("%d", &courseID);
	getchar();
	for (currentCourse = *headCourse;currentCourse != NULL && currentCourse->cNo != courseID;
		currentCourse = currentCourse->next);
	if (currentCourse != NULL)
	{
		// 将数据输入临时变量中
		tmpCourse = (courInfo*)malloc(sizeof(courInfo));
		tmpCourse->cNo = courseID;
		printf("Enter course name:");
		fgets(tmpCourse->cName, 80, stdin);
		char *p = tmpCourse->cName;
		for (; *p != '\0'; p++)
		{
			if (*p == '\n') *p = '\0';
		}
		printf("Enter course credit:");
		scanf("%d", &tmpCourse->cCredit);
		printf("Enter course period:");
		scanf("%d", &tmpCourse->cTime);
		getchar();
		// 确认输入，将数据从临时变量取出
		printf("Save changes <y/n>?");
		scanf("%c", &saveChangeChoice);
		if (saveChangeChoice == 'Y' || saveChangeChoice == 'y')
		{
			tmpCourse->next = currentCourse->next;
			if (currentCourse->cNo == (*headCourse)->cNo)
			{
				*headCourse = tmpCourse;
			}
			else
			{
				for (currentCourse = *headCourse; currentCourse->next != NULL && (currentCourse->next)->cNo != courseID;
					currentCourse = currentCourse->next);
				currentCourse->next = tmpCourse;
			}
			printf("Edit complete!\n");
			getchar();
		}
	}
	else
	{
		printf("No course found!\n");
	}
	printf("\nPress <Enter> to continue.");
	getchar();
}

void courseInfoDelete(courInfo **headCourse)
{
	// 用以删除课程信息的函数
	int courseID;
	char deleteChangeChoice;
	courInfo *currentCourse;
	system("CLS");
	// 输入课号，判定课程是否存在
	printf("Enter a course ID:");
	scanf("%d", &courseID);
	getchar();
	for (currentCourse = *headCourse; currentCourse != NULL && currentCourse->cNo != courseID;
		currentCourse = currentCourse->next);
	if (currentCourse != NULL)
	{
		// 确认删除
		printf("Delete course <y/n>?");
		scanf("%c", &deleteChangeChoice);
		if (deleteChangeChoice == 'Y' || deleteChangeChoice == 'y')
		{
			// 分情况进行删除，由于未使用头节点这一步显得很复杂
			if (currentCourse->next == NULL)
			{
				if (currentCourse->cNo == (*headCourse)->cNo)
				{
					(*headCourse)->next = NULL;
					(*headCourse)->cNo = 0;
				}
				else
				{
					for (currentCourse = *headCourse; currentCourse->next != NULL && (currentCourse->next)->cNo != courseID;
						currentCourse = currentCourse->next);
					currentCourse->next = NULL;
				}
			}
			else
			{
				if (currentCourse->cNo == (*headCourse)->cNo)
				{
					*headCourse = currentCourse->next;
				}
				else
				{
					for (currentCourse = *headCourse; currentCourse->next != NULL && (currentCourse->next)->cNo != courseID;
						currentCourse = currentCourse->next);
					currentCourse->next = (currentCourse->next)->next;
				}
			}
			printf("Delete complete!\n");
			getchar();
		}
	}
	else
	{
		printf("No course found!\n");
	}
	printf("\nPress <Enter> to continue.");
	getchar();
}

void courseInfoLook(courInfo *headCourse)
{
	// 用以查看课程信息的函数
	int flg = 1;
	courInfo *currentCourse;
	// 清屏并打印表头
	system("CLS");
	printf("%-4s %-20s %6s %6s\n", "ID", "Name", "Credit", "Period");
	printf("---------------------------------------\n");
	// 打印课程信息
	for (currentCourse = headCourse; currentCourse != NULL && currentCourse->cNo != 0; currentCourse = currentCourse->next)
	{
		flg = 0;
		printf("%4d %-20s %6d %6d\n", currentCourse->cNo, currentCourse->cName, currentCourse->cCredit, currentCourse->cTime);
	}
	if (flg) printf("No data!\n");
	printf("\nPress <Enter> to continue.\n");
	getchar();
	getchar();
}

void courseInfoSwap(courInfo *alphaCourse, courInfo *betaCourse)
{
	// 用以在不破坏链表的情况下交换两节点的数据
	courInfo tmpCourse;
	courInfo *tmpNextAlpha, *tmpNextBeta;
	// 保存节点指向信息
	tmpNextAlpha = alphaCourse->next;
	tmpNextBeta = betaCourse->next;
	// 数据交换
	tmpCourse = *alphaCourse;
	*alphaCourse = *betaCourse;
	*betaCourse = tmpCourse;
	// 指向恢复
	alphaCourse->next = tmpNextAlpha;
	betaCourse->next = tmpNextBeta;
}

void courseInfoSort(courInfo **headCourse)
{
	// 用以对课程信息进行排序的函数
	int courseSum, i, j;
	courInfo *tmpCourse;
	// 求出课程信息数量
	for (tmpCourse = *headCourse, courseSum = 0; tmpCourse != NULL; tmpCourse = tmpCourse->next, courseSum++);
	// 冒泡排序
	for (i = 0; i < courseSum - 1; i++)
	{
		for (j = 0, tmpCourse = *headCourse; j < courseSum - i - 1 && tmpCourse->next != NULL;
			j++, tmpCourse = tmpCourse->next)
		{
			if (tmpCourse->cNo > (tmpCourse->next)->cNo)
			{
				courseInfoSwap(tmpCourse, tmpCourse->next);
			}
		}
	}
	printf("Sort complete.");
	getchar();
	getchar();
}