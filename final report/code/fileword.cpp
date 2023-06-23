#include<iostream>
#include <map>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include<cstring>
#include<string>
#include <string.h>
#include"IPrintPlugin.h"

using namespace std;

char BYTE[] = "B"; //ͳ��ĳ���ļ��ĵ�����

class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 3;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ3
	}

	virtual ~CPlugin()//��������
	{
	}

	virtual void Print()//��ӡ���������ݣ���ʾ�û�����B���Ի�ȡ�ļ�������
	{
		cout << "Want to know the words? Enter'B'" << endl;

	}

	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM "<<FUNC_NUM << ":this function will know the doc's words" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ3
	{
		return 3;
	}

	virtual char *GetNames()//��ȡ����ļ���������B����
	{
		return BYTE;
	}
	int Fileline(const char *sfline)
	{
		int sbyte = 0;
		int i = 0;
		for(; i < strlen(sfline);i++)//����ĳ���ļ�ÿһ�е��ֽ�������ʼѭ��������
		{
			if (*(sfline + i) != ' '|| *(sfline + i) != '/t'|| *(sfline + i) != '\n')
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