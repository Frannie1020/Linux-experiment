#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "IPrintPlugin.h"

using namespace std;

char SLINE[] = "SL"; //ͳ��ĳ���ļ�������

class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 2;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ2
	}

	virtual ~CPlugin()//��������
	{
	}

	virtual void Print()//��ӡ���������ݣ���ʾ�û�����SL���Ի�ȡ�ļ�����
	{
		cout << "Want to know the specific filelines? Enter'SL'" << endl;

	}

	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the specific doc's lines" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ2
	{
		return 2;
	}

	virtual char *GetNames()//��ȡ����ļ���������SL�Ժ󼴿�
	{
		return SLINE;
	}
	virtual void Function(char* FileNames)//���ִ�к�����ʵ��ͳ�������Ĺ��ܣ�������
	{
		int fd, num = 0;
		char tmp;
		while ((fd = open(FileNames, O_RDONLY)) == -1)//���ļ�ʧ��
		{
			cout << "open failed" << FileNames << endl;//����ʧ����ʾ
			return;
		}
		while (read(fd, &tmp, 1))//ѭ�������ļ�����
		{
			if (tmp == '\n')
			{
				num++;
			}
		}
		close(fd);
		cout << FileNames << " total lines: " << num + 1 << endl;//ĩβ��û��\n�����Ի���ͳ��һ�У���+1
	}

	virtual void Function(string path, string aftername)//����Ҫͳ���ض�Ŀ¼�ض���׺���������ļ�������������Ҫ����Ŀ¼�жϺ�����������CPluginEnumerator.cpp�Ĳ��ö����
	{
		DIR *dir;
		struct dirent *pentry;//��Ų�����ļ���,�ṹָ��
		if ((dir = opendir(path.c_str())) == nullptr)//��ָ�룬��ʧ�ܣ�����ʧ����ʾ
		{
			perror("opendir failed");
			exit(-1);
		}
		while ((pentry = readdir(dir)) != nullptr)//�����ǿ�ָ�������ѭ������
		{
			if (strcmp(pentry->d_name, ".") == 0 || strcmp(pentry->d_name, "..") == 0)
				continue;//�ļ���׺��Ϊ.xx�������������..xx������֮ǰ���ö��������д��
			else if (pentry->d_type == 8)//�ļ���׺Ϊ8���ֽڵ����
			{
				string filename = pentry->d_name;
				string afternamestr = filename.substr(filename.find_last_of('.') + 1);//��ȡ�ļ���׺����·��+��ʽ
				if (afternamestr == aftername)//�ļ���׺���붨�����ȣ�����п���
				{
					char p[80];
					strcpy(p, (path + "/" + pentry->d_name).c_str());//������0���ַ���
					Function(p);
				}
			}
			else if (pentry->d_type == 4)//��׺Ϊ4�ֽڵ����
			{
				Function(path + "/" + pentry->d_name, aftername);//����function����������Ӧ��
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
