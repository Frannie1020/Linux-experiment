#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H

#include <vector>
#include <string.h>
#include <string>
#include<cstring>
#include <iostream>
using namespace std;

class IPrintPlugin;//虚基类

class CPluginController
{
public:
	CPluginController(void);//构造函数
	virtual ~CPluginController(void);//析构函数

	bool InitializeController(void);//初始化插件句柄
	bool UninitializeController(void);//卸载插件

	bool ProcessHelp(void);//打开所有动态库，实现help
	bool ProcessRequest(int FunctionNUM);// 功能ID输出命令处理进程
	bool Process(char *Function);//判断插件函数
	bool ProcessFunc(char *Function, char *File);//实现打印行数和字节数的函数
	bool ProcessFunc(char *Function, char *dir, char *aftername);//统计特定后缀名的所有文件信息

private:
	vector<void *> m_vForPlugin; // htype动态链接库句柄容器
	vector<IPrintPlugin*> m_vpPlugin;  // 插件类容器
};

#endif
