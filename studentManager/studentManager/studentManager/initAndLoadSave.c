/*
	功能性模块，包括用以初始化结构体，读取数据和储存数据的函数
	作者：杨熙龙
	版本：1.0
*/

#include "studentManagerData.h"

void initInfo(studInfo *tmpStudent, courInfo *headCourse, resuInfo *tmpResult)
{
	// 用以初始化结构体的函数
	int i;
	// 将所有学生信息初始化
	for (i = 0; i < N; i++)
	{
		tmpStudent[i].sNo = 0;
		tmpStudent[i].sName[0] = '\0';
		tmpStudent[i].sSex = '\0';
		tmpStudent[i].sAddress[0] = '\0';
	}
	// 初始化链表头节点
	headCourse->cNo = 0;
	headCourse->cName[0] = '\0';
	headCourse->cCredit = 0;
	headCourse->cTime = 0;
	headCourse->next = NULL;
	// 将所有成绩信息初始化
	for (i = 0; i < S; i++)
	{
		tmpResult[i].sNo = 0;
		tmpResult[i].sName[0] = '\0';
		tmpResult[i].cNo = 0;
		tmpResult[i].cName[0] = '\0';
		tmpResult[i].sTerm = 0;
		tmpResult[i].score = 0;

	}
}

void loadData(studInfo *tmpStudent, courInfo *tmpHeadCourse, resuInfo *tmpResult)
{
	// 用以从文件中读取数据的函数
	int i;
	courInfo *tmpCurrentCourse, *tmpEndCourse;
	FILE *tmpStudentData, *tmpCourseData, *tmpResultData;
	// 用ab+打开文件， 若文件不存在则新建
	// 学生信息读取
	if ((tmpStudentData = fopen("student.dat", "ab+")) == NULL)
	{
		printf("Open file \"student.dat\" failed!");
		exit(0);
	}
	for (i = 0; i < N; i++)
	{
		if (0 == fread(&tmpStudent[i], sizeof(studInfo), 1, tmpStudentData))
		{
			break;
		}
	}
	fclose(tmpStudentData);
	// 课程信息读取
	if ((tmpCourseData = fopen("course.dat", "ab+")) == NULL)
	{
		printf("Open file \"course.dat\" failed!");
		exit(0);
	}
	tmpEndCourse = tmpHeadCourse;
	while (1 == fread(tmpEndCourse, sizeof(courInfo), 1, tmpCourseData) && tmpEndCourse->next != NULL)
	{
		tmpCurrentCourse = (courInfo*)malloc(sizeof(courInfo));
		tmpEndCourse->next = tmpCurrentCourse;
		tmpEndCourse = tmpCurrentCourse;
	}
	tmpEndCourse->next = NULL;
	fclose(tmpCourseData);
	// 成绩信息读取
	if ((tmpResultData = fopen("result.dat", "ab+")) == NULL)
	{
		printf("Open file \"result.dat\" failed!");
		exit(0);
	}
	for (i = 0; i < S; i++)
	{
		if (0 == fread(&tmpResult[i], sizeof(resuInfo), 1, tmpResultData))
		{
			break;
		}
	}
	fclose(tmpResultData);
}

void saveData(studInfo *tmpStudent, courInfo *tmpHeadCourse, resuInfo *tmpResult)
{
	// 用以向文件中保存数据的函数
	FILE *tmpStudentData, *tmpCourseData, *tmpResultData;
	// 使用wb进行覆盖写入
	// 学生信息存储
	if ((tmpStudentData = fopen("student.dat", "wb")) == NULL)
	{
		printf("Open file \"student.dat\" failed!");
		exit(0);
	}
	fwrite(tmpStudent, sizeof(studInfo), N, tmpStudentData);
	fclose(tmpStudentData);
	// 课程信息写入
	if ((tmpCourseData = fopen("Course.dat", "wb")) == NULL)
	{
		printf("Open file \"course.dat\" failed!");
		exit(0);
	}
	while (tmpHeadCourse != NULL)
	{
		fwrite(tmpHeadCourse, sizeof(courInfo), 1, tmpCourseData);
		tmpHeadCourse = tmpHeadCourse->next;
	}
	fclose(tmpStudentData);
	// 成绩信息写入
	if ((tmpResultData = fopen("result.dat", "wb")) == NULL)
	{
		printf("Open file \"result.dat\" failed!");
		exit(0);
	}
	fwrite(tmpResult, sizeof(resuInfo), S, tmpResultData);
	fclose(tmpResultData);
}