#include <iostream>
#include<cstring>
#include<string.h>
#include<string>
#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "IPrintPlugin.h"
#include "dlfcn.h"

using namespace std;

CPluginController::CPluginController(void)   //���캯��
{
}

CPluginController::~CPluginController(void)  //��������
{
}

bool CPluginController::InitializeController(void)   // ��ʼ��������
{
	vector<string> vPluginNames;      // �������

	CPluginEnumerator enumerator;        // ʵ�������ö����������Ѱ�Ҳ���ļ���

	if (!enumerator.GetPluginNames(vPluginNames))  // ע��Ŀ¼��Ĳ��
	{
		cout << "GetPluginNames error" << endl;
		return false;
	}

	for (unsigned int i = 0; i < vPluginNames.size(); i++) //�������ҵ��Ķ�̬�⣬�����������ҵ�������
	{

		typedef int(*PLUGIN_CREATE)(IPrintPlugin**);
		PLUGIN_CREATE CreateProc;

		IPrintPlugin *pPlugin = NULL;// �򿪶�̬���ӿ⡣RTLD_LAZY ��̬���붯̬���ӿ��еĺ���

		void* htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);

		if (htype != NULL)
		{
			m_vForPlugin.push_back(htype);  // ���붯̬���ӿ������� ӳ�䶯̬���ӿ����е� CreateObj()����������

			CreateProc = (PLUGIN_CREATE)dlsym(htype, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);  // CreateObj()����������

				if (pPlugin != NULL)
				{
					m_vpPlugin.push_back(pPlugin);  // ������������
				}
			}
		}
	}

	return true;
}
bool CPluginController::UninitializeController()     // ж�ز��
{
	for (unsigned int i = 0; i < m_vForPlugin.size(); i++)   // ����ж�ز�����
	{
		dlclose(m_vForPlugin[i]);
	}

	return true;
}

bool CPluginController::ProcessRequest(int FunctionNUM)   // ����NUM�����������
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)
	{
		if (m_vpPlugin[i]->GetID() == FunctionNUM)   // �ڹ���NUM�����бȶ�
		{
			m_vpPlugin[i]->Print();    // �������Print()���������
			break;
		}
	}

	return true;
}


bool CPluginController::ProcessHelp(void)   // Help��������
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

		IPrintPlugin *pPlugin = NULL;// �򿪶�̬���ӿ� RTLD_LAZY ��̬���붯̬���ӿ��еĺ���

		void* htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);

		if (htype != NULL)
		{
			// ӳ�䶯̬���ӿ����е� CreateObj()����������
			CreateProc = (PLUGIN_CREATE)dlsym(htype, "CreateObj");

			if (NULL != CreateProc)
			{
				(CreateProc)(&pPlugin);

				if (pPlugin != NULL)
				{
					pPlugin->Help();  // ������Help()���������
				}
			}

			dlclose(htype);    // ж�ؾ��
		}
	}

	return true;
}

bool CPluginController::Process(char *Function)//������ڵ��жϱ�־
{
	unsigned int i;
	for ( i = 0; i < m_vpPlugin.size(); i++)//��������ļ���
	{
		if (strcmp(Function,m_vpPlugin[i]->GetNames())==0)//��ȡ�ļ�������ʧ�ܣ�ֱ���˳�
			break;
	}
	if(i<m_vpPlugin.size())//�ļ�����С�����򷵻�true
		return true;
	else 
		return false;
}

bool CPluginController::ProcessFunc(char *Function, char *File) //���ͳ��ĳ���ļ��Ĳ������
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)//��������ļ���
	{
		if (strcmp(Function, m_vpPlugin[i]->GetNames()) == 0)
		{
			m_vpPlugin[i]->Function(File);//��ȡ�ļ�������ʧ�ܣ�ֱ���˳�
			break;
		}
	}
	return true;
}

bool CPluginController::ProcessFunc(char *Function, char *dir, char *aftername)//ִ��ͳ��ָ��Ŀ¼���к�׺���ļ��Ĳ������
{
	for (unsigned int i = 0; i < m_vpPlugin.size(); i++)//�����ض�Ŀ¼��ָ����׺�����ļ�
	{
		if (strcmp(Function, m_vpPlugin[i]->GetNames()) == 0)
		{
			m_vpPlugin[i]->Function(dir, aftername);//����ȡ�ļ�������ʧ�����˳�
			break;
		}
	}
	return true;
}


