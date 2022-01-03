/*
	程序中需要使用的数据结构定义
	作者：杨熙龙
	版本：1.0
*/

#ifndef STUDENTMANAGERDATA_H
#define STUDENTMANAGERDATA_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 定义两个宏作为分别作为学生与选课信息的数量
#define N 100
#define S 300

typedef struct studentInfo
{
	int sNo;
	char sName[40];
	char sSex;
	char sAddress[100];
}studInfo;

typedef struct courseInfo
{
	int cNo;
	char cName[80];
	int cCredit;
	int cTime;
	struct courseInfo *next;

}courInfo;

typedef struct resultInfo
{
	int sNo;
	char sName[40];
	int cNo;
	char cName[80];
	int sTerm;
	int score;
}resuInfo;

// 为排名专门创建的类型
typedef struct rankInfo
{
	int sNo;
	char sName[40];
	float averScore;
}rankInfo;

#endif
