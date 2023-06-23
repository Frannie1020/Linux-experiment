#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "CPluginController.h"


using namespace std;

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "help") == 0) //help参数检查，不是两个为错误
		{
			CPluginController pt;// 实例化一个插件控制器
			pt.ProcessHelp();// 调用Help命令处理进程
			return 0;// 结束
		}
		else
		{
			int FunctionNUM = atoi(argv[1]);// 功能ID参数
			CPluginController pt;// 实例化一个插件控制器
			pt.InitializeController();// 初始化插件句柄
			pt.ProcessRequest(FunctionNUM);// 调用功能ID输出命令处理进程
			pt.UninitializeController();// 卸载插件
			return 0;
		}
	}
	else if (argc == 3)  //插件执行参数
	{
		CPluginController ptr; //实例化一个插件控制器指针
		char *Function = argv[1];//定义文件名类型
		char *FileNames = argv[2];
		ptr.InitializeController();//继承一个成员变量
		if (ptr.Process(Function) == false)//插件名寻找失败
		{
			cout << "Plugin not exist" << endl;//输出相应提示
		}
		else
		{
			ptr.ProcessFunc(Function,FileNames);//插件名寻找成功则打印相关内容
		};
		ptr.UninitializeController();
		return 0;
	}
	else
	{
		cout << "Invaild Parameters" << endl;//其余情况均失败，返回空
		return 0;
	}
}