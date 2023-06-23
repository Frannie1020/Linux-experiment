#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H

#include <vector>
#include <string.h>
#include <string>
#include<cstring>
#include <iostream>
using namespace std;

class IPrintPlugin;//�����

class CPluginController
{
public:
	CPluginController(void);//���캯��
	virtual ~CPluginController(void);//��������

	bool InitializeController(void);//��ʼ��������
	bool UninitializeController(void);//ж�ز��

	bool ProcessHelp(void);//�����ж�̬�⣬ʵ��help
	bool ProcessRequest(int FunctionNUM);// ����ID�����������
	bool Process(char *Function);//�жϲ������
	bool ProcessFunc(char *Function, char *File);//ʵ�ִ�ӡ�������ֽ����ĺ���
	bool ProcessFunc(char *Function, char *dir, char *aftername);//ͳ���ض���׺���������ļ���Ϣ

private:
	vector<void *> m_vForPlugin; // htype��̬���ӿ�������
	vector<IPrintPlugin*> m_vpPlugin;  // ���������
};

#endif
