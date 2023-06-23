#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H
#include <vector>
#include <iostream>

using namespace std;

typedef void(*PROC_OUT)(void); //���庯��PROC_OUTָ��
typedef void(*PROC_HELP)(void);//���庯��PROC_HELP��ָ��
typedef int(*PROC_GETNUM)(void);//���庯��PROC_GETNUM��ָ��

class CPluginController//����CPluginController��
{
public:
	CPluginController(void);//���캯��
	virtual ~CPluginController(void);//��������

	bool InitializeController(void);//�����ʼ��controller����
	bool UnintializeController(void);//����ǳ�ʼ������

	bool ProcessHelp(void);//�������help����
	bool ProcessRequest(int FunctionNUM);//����������

private:
	vector <void *>m_vForPlugin; //��type
	vector <PROC_OUT>m_vPrintFunc; //�洢Out������ַ
	vector <PROC_GETNUM> m_vGetNUMFunc; //�洢GetNum������ַ
};

#endif

