#include <iostream>
#include <cstdio>
#include<cstring>
#include<string>
#include <string.h>
#include <stdlib.h>
#include "CPluginController.h"

#define MAX 80
using namespace std;

int main()
{
	char enter;
	cout << "*****************Welcome to the plugin system!*****************" << endl;//欢迎语和提示语
	cout << "enter '0' to see the help info" << endl;
	cout << "enter 's' to know some file info " << endl;
	cout << "enter 'p' to know the specific file info " << endl;
	cout << "enter 'o' to exit the plugin system. " << endl;

	for (;;)//用户需要无条件循环遍历，这里可以使用while(1),for(),do-while，但是一定要Break跳出循环，否则就是死循环
	{
		cin>> enter;
		getchar();//吸收一个字符的输入
	   
	   if (enter == '0')//打印帮助信息
		{
			CPluginController pt;
			pt.ProcessHelp();//每次都会创建新进程，让此进程去运行插件
		}
		if (enter == 's')//输入s，进入某个文件信息界面
		{
			CPluginController ptr;
			cout << "Please enter the file name:" << endl;//输入想要了解的文件名
			char File[MAX];
			cin >> File;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the number of the plugin to know the info:(1357)" << endl;//输入对应的功能ID
			char enter1;
			cin >> enter1;
			if (enter1 == '1')//功能ID打印字符，1是统计行数功能
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(1);   //需求函数，输出字符提示
					pt.UninitializeController();
				}
				if (enter1 == '3')//3是统计单词数
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(3);   //需求函数，输出字符提示
					pt.UninitializeController();
				}
				if (enter1 == '5')//5是统计字节数，即文件大小
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(5);   //需求函数，输出字符提示
					pt.UninitializeController();
				}
				if (enter1 == '7')//功能ID打印字符，1是统计最大行长度的功能
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(7);   //需求函数，输出字符提示
					pt.UninitializeController();
				}
				if (enter == 'o')//退出
				{
					cout << "Thanks for your use!" << endl;
					exit(0);
					break;
				}
			cout << "Please enter the word of the plugin that you want to know:" << endl;//输入之前提示的字符
			char Function[MAX];
			cin >> Function;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			ptr.InitializeController();
			if (ptr.Process(Function) == 0)//打开错误
			{
				cout << "Plugin not exist" << endl;//输出错误提示

			}
			else
			{
				ptr.ProcessFunc(Function, File);//遍历文件相关信息
			}
			ptr.UninitializeController();//调用CPluginController.cpp中的函数，实现遍历
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
		}

		if (enter == 'p')//p能统计指定目录下特定后缀名的所有文件信息
		{
			CPluginController ptr;
			cout << "Please enter the specific dir name:" << endl;//输入特定目录名
			char dir[MAX];
			cin >> dir;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the specific aftername of the files:" << endl;//输入后缀名
			char aftername[MAX];
			cin >> aftername;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the number of the plugin to know the info:(246)" << endl;//输入你想知道的信息对应的功能ID
			char enter2;
			cin >> enter2;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			if (enter2 == '2')//功能ID，2是统计行数
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(2);
				pt.UninitializeController();
			}

			if (enter2 == '4')//4是统计单词数
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(4);
				pt.UninitializeController();
			}

			if (enter2 == '6')//6是统计字节数即文件大小
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(6);
				pt.UninitializeController();
			}
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the word of the plugin that you want to use:" << endl;//输入功能ID提示的字符
			char Function[MAX];
			cin >> Function;
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			ptr.InitializeController();
			if (ptr.Process(Function) == 0)//输入错误
			{
				cout << "Plugin not exist" << endl;

			}
			else
			{
				ptr.ProcessFunc(Function, dir, aftername);//遍历文件名
			}
			ptr.UninitializeController();//调用CPluginController.cpp中的函数，实现遍历
			if (enter == 'o')//退出
			{
				cout << "Thanks for your use!" << endl;//输出感谢使用字符
				exit(0);
				break;
			}
		}
		if (enter == 'o')//直接输出o，则直接退出程序
		{
			cout << "Thanks for your use!" << endl;
			exit(0);
			break;
		}
	}
}

