#include <dlfcn.h> //����linux�е�dl����
#include <iostream>
#include "CPluginEnumerator.h"

using namespace std;

int main()
{
	vector<string>vPluginNames; //��ʼ���ļ�������

	CPluginEnumerator enumerator;//����CPluginEnumerator����
	if (!enumerator.GetPluginNames(vPluginNames))//δ�����ļ���
	{
		cout << "��ȡplugin�ļ���ʧ��" << endl;
		return 0;
	}
	for (int i = 0; i < vPluginNames.size(); i++)//����plugin�ļ����е��ļ���
	{
		void *type = dlopen(vPluginNames[i].c_str(),RTLD_LAZY);//�򿪷�ʽλRTLD_LAZY
			if (type == 0)
			{
				cout << "��Ŀ¼����" << endl;
				return 0;
			}
		typedef void(*FUNC_OUT)();//���庯������FUNC_OUT
		FUNC_OUT dl_print = (FUNC_OUT)dlsym(type, "Out");//����Out������ӡ
		if (dl_print == 0)
		{
			cout << "ϵͳ����" << endl;
			return 0;
		}
		(dl_print)();//��ӡĿ¼
		dlclose(type);//�ر�Ŀ¼
	}
	return 0;
}