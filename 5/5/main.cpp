#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "CPluginController.h"


using namespace std;

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "help") == 0) //help������飬��������Ϊ����
		{
			CPluginController pt;// ʵ����һ�����������
			pt.ProcessHelp();// ����Help��������
			return 0;// ����
		}
		else
		{
			int FunctionNUM = atoi(argv[1]);// ����ID����
			CPluginController pt;// ʵ����һ�����������
			pt.InitializeController();// ��ʼ��������
			pt.ProcessRequest(FunctionNUM);// ���ù���ID�����������
			pt.UninitializeController();// ж�ز��
			return 0;
		}
	}
	else if (argc == 3)  //���ִ�в���
	{
		CPluginController ptr; //ʵ����һ�����������ָ��
		char *Function = argv[1];//�����ļ�������
		char *FileNames = argv[2];
		ptr.InitializeController();//�̳�һ����Ա����
		if (ptr.Process(Function) == false)//�����Ѱ��ʧ��
		{
			cout << "Plugin not exist" << endl;//�����Ӧ��ʾ
		}
		else
		{
			ptr.ProcessFunc(Function,FileNames);//�����Ѱ�ҳɹ����ӡ�������
		};
		ptr.UninitializeController();
		return 0;
	}
	else
	{
		cout << "Invaild Parameters" << endl;//���������ʧ�ܣ����ؿ�
		return 0;
	}
}