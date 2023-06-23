#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include <dlfcn.h>//linux��dl�����Ŀ�
#include<iostream>

using namespace std;

CPluginController::CPluginController(void)//���캯��
{

}
CPluginController::~CPluginController(void)//��������
{

}

bool CPluginController::InitializeController(void)//��ʼ��ctroller����
{
	vector<string>vPluginNames; //��ȡpluginĿ¼�µ��ļ���

	CPluginEnumerator enumerator;
	if (!enumerator.GetPluginNames(vPluginNames))//��ȡPluginĿ¼���ļ���ʧ��
		return false;//���ش���

	for (unsigned int i = 0; i < vPluginNames.size(); i++)//������̬���ӿ�
	{
		void *htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY); //RTLD_LAZYģʽ��
			if (htype != NULL)//�򿪳ɹ�����ʼִ��
			{
				m_vForPlugin.push_back(htype); //htype����plugin������

				PROC_OUT DLLPrint = (PROC_OUT)dlsym(htype, "Out");//htype��ϵͳ�ļ��������
				PROC_GETNUM DLLGetNUM = (PROC_GETNUM)dlsym(htype, "GetNUM");//��ȡ�ļ����ֺ����Ĵ�ӡ
				if ((NULL != DLLPrint) && (NULL != DLLGetNUM))//������ȡ�ɹ�
				{
					m_vPrintFunc.push_back(DLLPrint);//�����ӡ
					m_vGetNUMFunc.push_back(DLLGetNUM);//��֤λ����ͬһ��������
				}

			}

	}

	return true;//���سɹ�
}

bool CPluginController::ProcessRequest(int FunctionNUM)//������
{
	for (unsigned int i = 0; i < m_vGetNUMFunc.size(); i++) //������������
	{
		if ((m_vGetNUMFunc[i])() == FunctionNUM)//��������Ŀ��ָ����ͬ
		{
			(m_vPrintFunc[i])();//����Խ��д�ӡ
			break;
		}
	}
	return true;//���سɹ�
}

bool CPluginController::ProcessHelp(void)//help������ʵ��
{
	vector<string>vPluginNames;//��ʼ������vPluginNames
	CPluginEnumerator enumerator;//��ʼ��enumerator

	if (!enumerator.GetPluginNames(vPluginNames)//��ȡpluginĿ¼���ļ���ʧ��
		return false;//���ش���

	for (unsigned int i = 0; i < vPluginNames.size(); i++)//�������Ŀ¼���ļ���
	{
		PROC_HELP DLLProc;

		void *htype = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);//���ļ���
		if (htype != NULL)//��ָ��ǿ�
		{
			DLLProc = (PROC_HELP)dlsym(htype,"Help");//����help��������ӡ
			if (NULL != DLLProc)//�����ӡ
			{
				(DLLProc)();

			}
			dlclose(htype);//�ر�
		}
	}
	return true;//���سɹ�
}

bool CPluginController::UnintializeController()//δ��ʼ���ĺ���
{
	for (unsigned int i = 0; i < m_vForPlugin.size(); i++) //����plugin��htype
	{
		dlclose(m_vForPlugin[i]);//�رպ���ָ��

	}
	return true;
}