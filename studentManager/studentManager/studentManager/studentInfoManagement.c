/*
	学生信息管理模块，定义了相关函数，在主函数中声明并调用studentInfoManager函数来使用这个模块。
	作者：杨熙龙
	版本：1.0
*/

#include "studentManagerData.h"

void studentInfoManager(studInfo *tmpStudent)
{
	// 声明部分
	void studentInfoMenu();
	void studentInfoInput(studInfo*);
	void studentInfoLook(studInfo*);
	void studentInfoDelete(studInfo*);
	void studentInfoEdit(studInfo*);
	void studentInfoSort(studInfo*);
	int studentInfoMenuChoice = 1;
	// 主要功能
	while (studentInfoMenuChoice)
	{
		studentInfoMenu();
		printf("Enter your choice<0-5>:");
		scanf("%d", &studentInfoMenuChoice);
		fflush(stdin);
		switch (studentInfoMenuChoice)
		{
		case 1:
			studentInfoInput(tmpStudent);
			break;
		case 2:
			studentInfoEdit(tmpStudent);
			break;
		case 3:
			studentInfoDelete(tmpStudent);
			break;
		case 4:
			studentInfoLook(tmpStudent);
			break;
		case 5:
			studentInfoSort(tmpStudent);
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

void studentInfoMenu()
{
	//用以打印学生管理模块的菜单
	system("CLS");
	printf("\n%40s\n", "学生信息管理系统");
	printf("%50s\n", "------------------------------------");
	printf("%39s\n", "1.新        增");
	printf("\n%39s\n", "2.修        改");
	printf("\n%39s\n", "3.删        除");
	printf("\n%39s\n", "4.查        看");
	printf("\n%39s\n", "5.根据学号排序");
	printf("\n%39s\n", "0.回 主  菜 单");
	printf("%50s\n", "------------------------------------");
}

void studentInfoInput(studInfo *inStudent, int n)
{
	// 用以新建学生信息函数
	// 用循环找到学生类型的尾部并清屏
	int i;
	for (i = 0; i < N && inStudent[i].sNo != 0; i++);
	system("CLS");
	// 输入数据， 学号为零时结束
	printf("Enter student ID(0 to exit): ");
	scanf("%d", &inStudent[i].sNo);
	while (inStudent[i].sNo != 0)
	{
		printf("Enter name: ");
		scanf("%s", inStudent[i].sName);
		printf("Enter sex: ");
		getchar();
		scanf("%c", &inStudent[i].sSex);
		printf("Enter address: ");
		scanf("%s", inStudent[i].sAddress);
		i++;
		system("CLS");
		printf("Enter student ID(0 to exit): ");
		scanf("%d", &inStudent[i].sNo);
	}
}

void studentInfoLook(studInfo *tmpStudent)
{
	// 用以查看全部学生信息的函数
	// 清屏并打印表头，定义开关flg用来判断是否有学生信息，初始打开
	system("ClS");
	int i, flg = 1;
	printf("%-4s %-10s %3s %-15s\n", "ID", "Name", "Sex", "Address");
	printf("------------------------------------\n");
	//遍历学生信息数组，若有信息则关闭开关flg
	for (i = 0; i < N && tmpStudent[i].sNo != 0; i++)
	{
		printf("%4d %-10s %3c %-15s\n", tmpStudent[i].sNo, tmpStudent[i].sName,
			tmpStudent[i].sSex, tmpStudent[i].sAddress);
		flg = 0;
	}
	//若flg是打开状态，显示没有信息
	if (flg)
	{
		printf("No data!\n");
	}
	printf("\nPress <Enter> to continue.");
	getchar();
	getchar();
}

void studentInfoDelete(studInfo *tmpStud)
{
	// 用以删除学生数据的函数
	// 清屏，输入要删除的学生信息的学号
	system("CLS");
	int i = 0, delID;
	char delChoice;
	printf("Enter a student ID: ");
	scanf("%d", &delID);
	getchar();
	// 遍历学生信息寻找该学号
	for (i = 0; i < N && tmpStud[i].sNo != delID; i++);
	// 判断是否找到该学号
	if (tmpStud[i].sNo == delID)
	{
		// 确认删除信息
		printf("Delete the data of student:%d <y/n>?", delID);
		scanf("%c", &delChoice);
		if (delChoice == 'Y' || delChoice == 'y')
		{
			// 使被删除信息之后的信息依次向前覆盖， 再将尾部清空
			while (++i < N)
			{
				tmpStud[i - 1] = tmpStud[i];
			}
			tmpStud[i - 1].sNo = 0;
			tmpStud[i - 1].sName[0] = '\0';
			tmpStud[i - 1].sSex = '\0';
			tmpStud[i - 1].sAddress[0] = '\0';
			printf("Complete!");
			getchar();
		}
	}
	else
	{
		// 找不到学号， 打印提示信息
		printf("No data found!");
	}
	getchar();
}

void studentInfoEdit(studInfo *tmpStud)
{
	// 用以编辑学生信息的函数
	// 清屏并且定义相关变量
	system("CLS");
	int i, editID;
	char editChoice;
	studInfo tmpData;
	// 输入学号
	printf("Enter a student ID: ");
	scanf("%d", &editID);
	// 遍历查找学号
	for (i = 0; i < N && tmpStud[i].sNo != editID; i++);
	// 判断是否存在该学号
	if (tmpStud[i].sNo == editID)
	{
		// 将数据输入到临时变量里
		tmpData.sNo = editID;
		printf("Enter name: ");
		scanf("%s", tmpData.sName);
		printf("Enter sex: ");
		getchar();
		scanf("%c", &tmpData.sSex);
		printf("Enter address: ");
		scanf("%s", tmpData.sAddress);
		// 确认修改信息
		printf("Save changes <y/n>?");
		getchar();
		scanf("%c", &editChoice);
		if (editChoice == 'Y' || editChoice == 'y')
		{
			// 将数据从临时变量中取出
			tmpStud[i] = tmpData;
			printf("Edit complete!");
		}
		else
		{
			printf("Press <Enter> to continue.");
		}
	}
	else
	{
		printf("No data found!");
	}
	getchar();
	getchar();
}

void studentInfoSort(studInfo *tmpStud)
{
	// 用以排序的函数
	// 冒泡排序法
	int i, j;
	studInfo tmpData;
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < N - i - 1; j++)
		{
			if (tmpStud[j].sNo > tmpStud[j + 1].sNo && tmpStud[j + 1].sNo != 0)
			{
				tmpData = tmpStud[j];
				tmpStud[j] = tmpStud[j + 1];
				tmpStud[j + 1] = tmpData;
			}
		}
	}
	printf("Sort complete!");
	getchar();
	getchar();
}
