/*
	用以声明函数的头文件，保持主函数文件简洁
	作者：杨熙龙
	版本：1.1
*/

#ifndef STUDENTMANAGERTOOLS_H
#define STUDENTMANAGERTOOLS_H
// 打印主菜单
extern void mainMenu();
// 实现初始化以及数据读写功能， 来自文件initAndLoadSave.c
extern void initInfo(studInfo*, courInfo*, resuInfo*);
extern void loadData(studInfo*, courInfo*, resuInfo*);
extern void saveData(studInfo*, courInfo*, resuInfo*);
//五个功能模块
extern void studentInfoManager(studInfo *);
extern void courseInfoManager(courInfo **);
extern void resultInfoManager(studInfo *, courInfo*, resuInfo*);
extern void scoreInfoManager(resuInfo *);
extern void infoSearchManager(studInfo*, courInfo*, resuInfo*);

#endif