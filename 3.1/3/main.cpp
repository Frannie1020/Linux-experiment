#include <dlfcn.h>
#include <iostream>
#include "CPluginEnumerator.h"
#include <string.h>

using namespace std;

int main(int argc, char **argv) 
{
	if (argc != 2)//���argc/argv
		return 0;

	if (strcmp(argv[1], "help") == 0)//help����������
	{
		vector<string>vPluginNames;//����Vectorָ������ΪvPluginNames
		CPluginEnumerator enumerator; //����CPluginEnumerator����

		if (!enumerator.GetPluginNames(vPluginNames))//��ȡplugin�ļ��ڵĶ�̬�ļ�.so������
		{
			cout << "��ȡplugin�ļ���ʧ��" << endl;//��ȡʧ��
			return 0;//���ؿ�
		}

		for (int i = 0; i < vPluginNames.size(); i++)//����plugin�ļ����е��ļ���
		{
			void *type = dlopen(vPluginNames[i].c_str(), RTLD_LAZY);//�򿪷�ʽλRTLD_LAZY
			if (type == 0)//Ŀ¼����ȡ����
			{
				cout << "��Ŀ¼����" << endl;//�����Ŀ¼����
				return 0;//���ؿ�
			}

			typedef void(*FUNC_HELP)();//���庯������FUNC_HELP
			FUNC_HELP dl_help = (FUNC_HELP)dlsym(type, "Help");//����Help������ӡ
			if (dl_help == 0)//help������ӡ����
			{
				cout << "ϵͳ����" << endl;//���ϵͳ����
				return 0;
			}
			(dl_help)();

			dlclose(type);//�ر��ļ���
		}
	}
}