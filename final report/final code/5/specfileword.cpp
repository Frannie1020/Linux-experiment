#include <map>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "IPrintPlugin.h"

using namespace std;

char BYTE[] = "SFB"; //ͳ��ĳ���ļ��ĵ�����


class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 4;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ4
	}
	virtual ~CPlugin()//��������
	{
	}
	virtual void Print()//��ӡ���������ݣ���ʾ�û�����SFB���Ի�ȡ�ļ�������
	{
		cout << "Want to know the specific filewords? Enter'SFB'" << endl;

	}
	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the specific doc's words" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ4
	{
		return 4;
	}

	virtual char *GetNames()//��ȡ����ļ���������SFB�Ժ󼴿�
	{
		return BYTE;
	}

	int Fileline(const char *sfline)
	{
		int sbyte = 0;
		int i = 0;
		for (; i < strlen(sfline); i++)//����ĳ���ļ�ÿһ�е��ֽ�������ʼѭ��������
		{
			if (*(sfline + i) != ' ' || *(sfline + i) != '/t' || *(sfline + i) != '\n')
			{
				sbyte++;//����������
				while ((*(sfline + i) != ' ') && (*(sfline + i) != '\0'))//��������
				{
					i++;
				}
			}
		}
		return sbyte;//����ͳ�Ƶĵ�����
	}

	void Function(char *File)//���ִ�к�����ʵ��ͳ�������Ĺ��ܣ�������
	{
		int sbyte = 0;
		FILE *fp; //����һ���ļ�����ָ��fp
		char pBuffer[4094];//����ÿ��������ַ��������Ϊ4*1024-2=4094���ַ�
		if ((fp = fopen(File, "r")) == NULL)//���ļ�ʧ�ܵĴ���
		{
			cout << "open failed" << endl;
			exit(-1);
		}
		while (!feof(fp))//���ļ���ѭ����ֱ��eof����
		{
			//��ȡÿ�еĵ�����
			if (fgets(pBuffer, sizeof(pBuffer), fp) != NULL)
				
				sbyte += Fileline(pBuffer);
		}
		fclose(fp);//�ر��ļ�
		cout << File << " total bytes : " << sbyte << endl;//��ӡ���
	}

	virtual void Function(string path, string aftername)
	{//����Ҫͳ���ض�Ŀ¼�ض���׺���������ļ�������������Ҫ����Ŀ¼�жϺ�����������CPluginEnumerator.cpp�Ĳ��ö����
		DIR *dir;
		struct dirent *pentry;//��Ų�����ļ���,�ṹָ��
		if ((dir = opendir(path.c_str())) == nullptr) {//��ָ�룬��ʧ�ܣ�����ʧ����ʾ
			perror("opendir failed");
			exit(1);
		}
		while ((pentry = readdir(dir)) != nullptr) {//�����ǿ�ָ�������ѭ������
			if (strcmp(pentry->d_name, ".") == 0 || strcmp(pentry->d_name, "..") == 0)
				continue;//�ļ���׺��Ϊ.xx�������������..xx
			else if (pentry->d_type == 8) {
				string filename = pentry->d_name;//�ļ���׺Ϊ8���ֽڵ����
				string afternamestr = filename.substr(filename.find_last_of('.') + 1);//��ȡ�ļ���׺����·��+��ʽ
				if (afternamestr == aftername) {//�ļ���׺���붨�����ȣ�����п���
					
					char p[100];
					strcpy(p, (path + "/" + pentry->d_name).c_str());//������0���ַ���
					Function(p);
				}
			}
			else if (pentry->d_type == 4) //��׺Ϊ4�ֽڵ����
			{
				Function(path + "/" + pentry->d_name, aftername); //����function��������
			}
		}
		closedir(dir);//�ر�Ŀ¼
	}
private:
	int FUNC_NUM;
};
extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //��������
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}
