#include <iostream>
#include "CPluginController.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		if(strcmp(argv[1], "help") == 0)    //help参数检查，不是两个为错误
		{
			CPluginController pc;  // 实例化一个插件控制器
			pc.ProcessHelp();      // 调用Help命令处理进程
			return 0;              // 结束
		}else
		{
			int FunctionNUM = atoi(argv[1]); // 功能ID参数
			CPluginController pc;           // 实例化一个插件控制器
			pc.InitializeController();      // 初始化插件句柄
			pc.ProcessRequest(FunctionNUM);  // 调用功能ID输出命令处理进程
			pc.UninitializeController();    // 卸载插件
		}
		break;
	default:
		cout << "参数有误" << endl;
		return 0;
		break;
	}

	return 0;
}