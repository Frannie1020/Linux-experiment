#include <iostream>
#include "CPluginController.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2) //������
	{
		cout << "Invaild parameter" << endl; //��������
		return 0;
	}

	if (strcmp(argv[1], "help") == 0)//help�����Ĺ���
	{
		CPluginController pt;//��ʼ��PluginController
		pt.ProcessHelp();//help��Ա����

		return 0;
	}

	int FunctionNUM = atoi(argv[1]); //ת����Num
	CPluginController pt;//��������ָ��pt

	pt.InitializeController();//�����ʼ���ӿڱ���
	pt.ProcessRequest(FunctionNUM);//���庯��FunctionNUM�ӿڱ���
	pt.UnintializeController();//����δ��ʼ���ӿڱ���

	return 0;
}