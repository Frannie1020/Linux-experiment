#include<iostream>
#include <stdio.h>
#include <unistd.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <string>
#include"IPrintPlugin.h"

#define N 80

using namespace std;

char LENGTH[] = "ML"; //ͳ��ĳ���ļ�������

class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 7;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ7
	}

	virtual ~CPlugin()//��������
	{
	}

	virtual void Print()//��ӡ���������ݣ���ʾ�û�����ML���Ի�ȡ�ļ�����г���
	{
		cout << "Want to know the length of the max line? Enter'ML'" << endl;

	}

	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's length of the max line" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ7
	{
		return 7;
	}

	virtual char *GetNames()//��ȡ����ļ���������ML����
	{
		return LENGTH;
	}

	virtual void Function(char* FileNames)
	{
		FILE *fp;
		char h[N], zc[N], zd[N];
		int n = 0, len, maxno, minno;
		if (fp == NULL)
		printf("�ļ���ʧ��!\n");
		else
		{
			while (!feof(fp))
			{
				fgets(h, N, fp);
				if (n == 1)
				{
					maxno = 1;
					//minno = 1;
					strcpy(zc, h);
					//strcpy(zd, h);
				}
				else
				{
					if (strlen(zc) <= strlen(h))
					{
						maxno = n;
						strcpy(zc, h);
					}
					/*if (strlen(zd) >= strlen(h))
					{
						minno = n;
						strcpy(zd, h);
					}*/
				}
				n++;
			}
			fclose(fp);
			n--;
		//	printf("˵�����ļ��й��У�%d��!\n", n);
			printf("��%d�������%d���ַ�", maxno, strlen(zc));
		//	printf("��%d����̣���%d���ַ�������Ϊ��\n%s\n", minno, strlen(zd), zd);
		}

	}
	virtual void Function(string path, string aftername)
	{

	}
private:
	int FUNC_NUM;    //����ID
};


extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //��������
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}
