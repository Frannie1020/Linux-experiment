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
	cout << "*****************Welcome to the plugin system!*****************" << endl;//��ӭ�����ʾ��
	cout << "enter '0' to see the help info" << endl;
	cout << "enter 's' to know some file info " << endl;
	cout << "enter 'p' to know the specific file info " << endl;
	cout << "enter 'o' to exit the plugin system. " << endl;

	for (;;)//�û���Ҫ������ѭ���������������ʹ��while(1),for(),do-while������һ��ҪBreak����ѭ�������������ѭ��
	{
		cin>> enter;
		getchar();//����һ���ַ�������
	   
	   if (enter == '0')//��ӡ������Ϣ
		{
			CPluginController pt;
			pt.ProcessHelp();//ÿ�ζ��ᴴ���½��̣��ô˽���ȥ���в��
		}
		if (enter == 's')//����s������ĳ���ļ���Ϣ����
		{
			CPluginController ptr;
			cout << "Please enter the file name:" << endl;//������Ҫ�˽���ļ���
			char File[MAX];
			cin >> File;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the number of the plugin to know the info:(1357)" << endl;//�����Ӧ�Ĺ���ID
			char enter1;
			cin >> enter1;
			if (enter1 == '1')//����ID��ӡ�ַ���1��ͳ����������
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(1);   //������������ַ���ʾ
					pt.UninitializeController();
				}
				if (enter1 == '3')//3��ͳ�Ƶ�����
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(3);   //������������ַ���ʾ
					pt.UninitializeController();
				}
				if (enter1 == '5')//5��ͳ���ֽ��������ļ���С
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(5);   //������������ַ���ʾ
					pt.UninitializeController();
				}
				if (enter1 == '7')//����ID��ӡ�ַ���1��ͳ������г��ȵĹ���
				{
					CPluginController pt;
					pt.InitializeController();
					pt.ProcessRequest(7);   //������������ַ���ʾ
					pt.UninitializeController();
				}
				if (enter == 'o')//�˳�
				{
					cout << "Thanks for your use!" << endl;
					exit(0);
					break;
				}
			cout << "Please enter the word of the plugin that you want to know:" << endl;//����֮ǰ��ʾ���ַ�
			char Function[MAX];
			cin >> Function;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			ptr.InitializeController();
			if (ptr.Process(Function) == 0)//�򿪴���
			{
				cout << "Plugin not exist" << endl;//���������ʾ

			}
			else
			{
				ptr.ProcessFunc(Function, File);//�����ļ������Ϣ
			}
			ptr.UninitializeController();//����CPluginController.cpp�еĺ�����ʵ�ֱ���
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
		}

		if (enter == 'p')//p��ͳ��ָ��Ŀ¼���ض���׺���������ļ���Ϣ
		{
			CPluginController ptr;
			cout << "Please enter the specific dir name:" << endl;//�����ض�Ŀ¼��
			char dir[MAX];
			cin >> dir;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the specific aftername of the files:" << endl;//�����׺��
			char aftername[MAX];
			cin >> aftername;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the number of the plugin to know the info:(246)" << endl;//��������֪������Ϣ��Ӧ�Ĺ���ID
			char enter2;
			cin >> enter2;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			if (enter2 == '2')//����ID��2��ͳ������
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(2);
				pt.UninitializeController();
			}

			if (enter2 == '4')//4��ͳ�Ƶ�����
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(4);
				pt.UninitializeController();
			}

			if (enter2 == '6')//6��ͳ���ֽ������ļ���С
			{
				CPluginController pt;
				pt.InitializeController();
				pt.ProcessRequest(6);
				pt.UninitializeController();
			}
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			cout << "Please enter the word of the plugin that you want to use:" << endl;//���빦��ID��ʾ���ַ�
			char Function[MAX];
			cin >> Function;
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;
				exit(0);
				break;
			}
			ptr.InitializeController();
			if (ptr.Process(Function) == 0)//�������
			{
				cout << "Plugin not exist" << endl;

			}
			else
			{
				ptr.ProcessFunc(Function, dir, aftername);//�����ļ���
			}
			ptr.UninitializeController();//����CPluginController.cpp�еĺ�����ʵ�ֱ���
			if (enter == 'o')//�˳�
			{
				cout << "Thanks for your use!" << endl;//�����лʹ���ַ�
				exit(0);
				break;
			}
		}
		if (enter == 'o')//ֱ�����o����ֱ���˳�����
		{
			cout << "Thanks for your use!" << endl;
			exit(0);
			break;
		}
	}
}

