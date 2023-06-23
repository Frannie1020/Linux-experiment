#include <iostream>
#include "CPluginController.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2) //检查参数
	{
		cout << "Invaild parameter" << endl; //参数错误
		return 0;
	}

	if (strcmp(argv[1], "help") == 0)//help函数的功能
	{
		CPluginController pt;//初始化PluginController
		pt.ProcessHelp();//help成员引用

		return 0;
	}

	int FunctionNUM = atoi(argv[1]); //转化成Num
	CPluginController pt;//定义类型指针pt

	pt.InitializeController();//定义初始化接口变量
	pt.ProcessRequest(FunctionNUM);//定义函数FunctionNUM接口变量
	pt.UnintializeController();//定义未初始化接口变量

	return 0;
}