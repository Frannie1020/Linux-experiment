#include <dlfcn.h> //调用linux中的dl命令
#include <iostream>
#include "CPluginEnumerator.h"

using namespace std;

int main()
{
	vector<string>vPluginNames; //初始化文件名变量

	CPluginEnumerator enumerator;//调用CPluginEnumerator参数
	if (!enumerator.GetPluginNames(vPluginNames))//未读到文件名
	{
		cout << "读取plugin文件名失败" << endl;
		return 0;
	}
	for (int i = 0; i < vPluginNames.size(); i++)//遍历plugin文件夹中的文件名
	{
		void *type = dlopen(vPluginNames[i].c_str(),RTLD_LAZY);//打开方式位RTLD_LAZY
			if (type == 0)
			{
				cout << "打开目录错误" << endl;
				return 0;
			}
		typedef void(*FUNC_OUT)();//定义函数类型FUNC_OUT
		FUNC_OUT dl_print = (FUNC_OUT)dlsym(type, "Out");//调用Out函数打印
		if (dl_print == 0)
		{
			cout << "系统错误" << endl;
			return 0;
		}
		(dl_print)();//打印目录
		dlclose(type);//关闭目录
	}
	return 0;
}