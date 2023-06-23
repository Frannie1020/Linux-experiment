#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include <dlfcn.h>//linux下dl函数的库
#include<iostream>

using namespace std;

CPluginController::CPluginController(void)//构造函数
{

}
CPluginController::~CPluginController(void)//析构函数
{

}

bool CPluginController::InitializeController(void)//初始化ctroller函数
{
	vector<string>vPluginNames; //获取plugin目录下的文件名

	CPluginEnumerator enumerator;
	if (!enumerator.GetPluginNames(vPluginNames))//获取Plugin目录下文件名失败
		return false;//返回错误

	for (unsigned int i = 0; i < vPluginNames.size(); i++)//遍历动态链接库
	{
		void *htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY); //RTLD_LAZY模式打开
			if (htype != NULL)//打开成功，开始执行
			{
				m_vForPlugin.push_back(htype); //htype放入plugin变量里

				PROC_OUT DLLPrint = (PROC_OUT)dlsym(htype, "Out");//htype打开系统文件进行输出
				PROC_GETNUM DLLGetNUM = (PROC_GETNUM)dlsym(htype, "GetNUM");//获取文件数字函数的打印
				if ((NULL != DLLPrint) && (NULL != DLLGetNUM))//若都获取成功
				{
					m_vPrintFunc.push_back(DLLPrint);//逐个打印
					m_vGetNUMFunc.push_back(DLLGetNUM);//保证位置在同一个索引下
				}

			}

	}

	return true;//返回成功
}

bool CPluginController::ProcessRequest(int FunctionNUM)//需求函数
{
	for (unsigned int i = 0; i < m_vGetNUMFunc.size(); i++) //遍历三个变量
	{
		if ((m_vGetNUMFunc[i])() == FunctionNUM)//变量的数目和指针相同
		{
			(m_vPrintFunc[i])();//则可以进行打印
			break;
		}
	}
	return true;//返回成功
}

bool CPluginController::ProcessHelp(void)//help函数的实现
{
	vector<string>vPluginNames;//初始化变量vPluginNames
	CPluginEnumerator enumerator;//初始化enumerator

	if (!enumerator.GetPluginNames(vPluginNames)//获取plugin目录下文件名失败
		return false;//返回错误

	for (unsigned int i = 0; i < vPluginNames.size(); i++)//逐个遍历目录下文件名
	{
		PROC_HELP DLLProc;

		void *htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);//打开文件名
		if (htype != NULL)//若指针非空
		{
			DLLProc = (PROC_HELP)dlsym(htype,"Help");//调用help函数并打印
			if (NULL != DLLProc)//逐个打印
			{
				(DLLProc)();

			}
			dlclose(htype);//关闭
		}
	}
	return true;//返回成功
}

bool CPluginController::UnintializeController()//未初始化的函数
{
	for (unsigned int i = 0; i < m_vForPlugin.size(); i++) //遍历plugin的htype
	{
		dlclose(m_vForPlugin[i]);//关闭函数指针

	}
	return true;
}