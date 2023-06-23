#include <dlfcn.h>
#include <iostream>
#include "CPluginEnumerator.h"
#include <string.h>

using namespace std;

int main(int argc, char **argv) 
{
	if (argc != 2)//检查argc/argv
		return 0;

	if (strcmp(argv[1], "help") == 0)//help函数的作用
	{
		vector<string>vPluginNames;//变量Vector指针命名为vPluginNames
		CPluginEnumerator enumerator; //变量CPluginEnumerator命名

		if (!enumerator.GetPluginNames(vPluginNames))//读取plugin文件内的动态文件.so的内容
		{
			cout << "读取plugin文件名失败" << endl;//读取失败
			return 0;//返回空
		}

		for (int i = 0; i < vPluginNames.size(); i++)//遍历plugin文件夹中的文件名
		{
			void *type = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);//打开方式位RTLD_LAZY
			if (type == 0)//目录名读取错误
			{
				cout << "打开目录错误" << endl;//输出打开目录错误
				return 0;//返回空
			}

			typedef void(*FUNC_HELP)();//定义函数类型FUNC_HELP
			FUNC_HELP dl_help = (FUNC_HELP)dlsym(type, "Help");//调用Help函数打印
			if (dl_help == 0)//help函数打印错误
			{
				cout << "系统错误" << endl;//输出系统错误
				return 0;
			}
			(dl_help)();

			dlclose(type);//关闭文件名
		}
	}
}