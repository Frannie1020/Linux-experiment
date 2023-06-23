#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H
#include <vector>
#include <iostream>

using namespace std;

typedef void(*PROC_OUT)(void); //定义函数PROC_OUT指针
typedef void(*PROC_HELP)(void);//定义函数PROC_HELP的指针
typedef int(*PROC_GETNUM)(void);//定义函数PROC_GETNUM的指针

class CPluginController//定义CPluginController类
{
public:
	CPluginController(void);//构造函数
	virtual ~CPluginController(void);//析构函数

	bool InitializeController(void);//定义初始化controller函数
	bool UnintializeController(void);//定义非初始化函数

	bool ProcessHelp(void);//定义过程help函数
	bool ProcessRequest(int FunctionNUM);//定义需求函数

private:
	vector <void *>m_vForPlugin; //存type
	vector <PROC_OUT>m_vPrintFunc; //存储Out函数地址
	vector <PROC_GETNUM> m_vGetNUMFunc; //存储GetNum函数地址
};

#endif

