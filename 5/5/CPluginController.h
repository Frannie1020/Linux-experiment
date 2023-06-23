#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H

#include <vector>
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
	bool Process(char *Function);//�жϲ������
	bool ProcessFunc(char *Function, char *FileNames);//ʵ�ִ�ӡ�������ֽ����ĺ���
	bool ProcessRequest(int FunctionNUM);// ����ID�����������

private:
	vector<void *> m_vForPlugin; // htype��̬���ӿ�������
	vector<IPrintPlugin*> m_vpPlugin;  // ���������
};

#endif
