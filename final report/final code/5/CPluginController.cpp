#include <iostream>
#include<cstring>
#include<string.h>
#include<string>
#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "IPrintPlugin.h"
#include "dlfcn.h"

using namespace std;

CPluginController::CPluginController(void)   //构造函数
{
}

CPluginController::~CPluginController(void)  //析构函数
{
}

bool CPluginController::InitializeController(void)   // 初始化插件句柄
{
	vector<string> vPluginNames;      // 插件容器

	CPluginEnumerator enumerator;        // 实例化插件枚举器，用于寻找插件文件名

	if (!enumerator.GetPluginNames(vPluginNames))  // 注册目录里的插件
	{
		cout << "GetPluginNames error" << endl;
		return false;
	}

	for (unsigned int i = 0; i < vPluginNames.size(); i++) //遍历能找到的动态库，挨个遍历能找到的类型
	{

		typedef int(*PLUGIN_CREATE)(IPrintPlugin**);
		PLUGIN_CREATE CreateProc;

		IPrintPlugin *pPlugin = NULL;// 打开动态链接库。RTLD_LAZY 动态加入动态链接库中的函数

		void* htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);

		if (htype != NULL)
		{
			m_vForPlugin.push_back(htype);  // 放入动态链接库句柄容器 映射动态链接库类中的 CreateObj()创建对象函数

			CreateProc = (PLUGIN_CREATE)dlsym(htype, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);  // CreateObj()创建对象函数

				if (pPlugin != NULL)
				{
					m_vpPlugin.push_back(pPlugin);  // 放入插件类容器
				}
			}
		}
	}

	return true;
}
bool CPluginController::UninitializeController()     // 卸载插件
{
	for (unsigned int i = 0; i < m_vForPlugin.size(); i++)   // 遍历卸载插件句柄
	{
		dlclose(m_vForPlugin[i]);
	}

	return true;
}

bool CPluginController::ProcessRequest(int FunctionNUM)   // 功能NUM输出命令处理进程
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)
	{
		if (m_vpPlugin[i]->GetID() == FunctionNUM)   // 在功能NUM集合中比对
		{
			m_vpPlugin[i]->Print();    // 调用类的Print()函数，输出
			break;
		}
	}

	return true;
}


bool CPluginController::ProcessHelp(void)   // Help命令处理进程
{
	vector<string> vPluginNames;
	CPluginEnumerator enumerator;

	if (!enumerator.GetPluginNames(vPluginNames)) {

		cout << "GetPluginNames error" << endl;
		return false;
	}

	for (unsigned int i = 0; i < vPluginNames.size(); i++)
	{
		typedef int(*PLUGIN_CREATE)(IPrintPlugin**);
		PLUGIN_CREATE CreateProc;

		IPrintPlugin *pPlugin = NULL;// 打开动态链接库 RTLD_LAZY 动态加入动态链接库中的函数

		void* htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);

		if (htype != NULL)
		{
			// 映射动态链接库类中的 CreateObj()创建对象函数
			CreateProc = (PLUGIN_CREATE)dlsym(htype, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);

				if (pPlugin != NULL)
				{
					pPlugin->Help();  // 调用类Help()函数，输出
				}
			}

			dlclose(htype);    // 卸载句柄
		}
	}

	return true;
}

bool CPluginController::Process(char *Function)//插件存在的判断标志
{
	unsigned int i;
	for ( i = 0; i < m_vpPlugin.size(); i++)//遍历插件文件名
	{
		if (strcmp(Function,m_vpPlugin[i]->GetNames())==0)//获取文件名意外失败，直接退出
			break;
	}
	if(i<m_vpPlugin.size())//文件名大小正常则返回true
		return true;
	else 
		return false;
}

bool CPluginController::ProcessFunc(char *Function, char *File) //插件统计某个文件的插件内容
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)//遍历插件文件名
	{
		if (strcmp(Function, m_vpPlugin[i]->GetNames()) == 0)
		{
			m_vpPlugin[i]->Function(File);//获取文件名意外失败，直接退出
			break;
		}
	}
	return true;
}

bool CPluginController::ProcessFunc(char *Function, char *dir, char *aftername)//执行统计指定目录所有后缀名文件的插件内容
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)//遍历特定目录下指定后缀名的文件
	{
		if (strcmp(Function, m_vpPlugin[i]->GetNames()) == 0)
		{
			m_vpPlugin[i]->Function(dir, aftername);//若获取文件名意外失败则退出
			break;
		}
	}
	return true;
}


