#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <string>
#include"IPrintPlugin.h"

using namespace std;

char LINE[] = "L"; //ͳ��ĳ���ļ�������

class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 1;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ1
	}

	virtual ~CPlugin()//��������
	{
	}

	virtual void Print()//��ӡ���������ݣ���ʾ�û�����L���Ի�ȡ�ļ�����
	{
		cout << "Want to know the lines? Enter'L'" << endl;

	}

	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's lines" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ1
	{
		return 1;
	}

	virtual char *GetNames()//��ȡ����ļ���������L����
	{
		return LINE;
	}

	virtual void Function(char* FileNames)//���ִ�к�����ʵ��ͳ�������Ĺ��ܣ�������
	{
		int fd, num = 0;
		char tmp;
		while((fd = open(FileNames, O_RDONLY)) == -1)//���ļ�ʧ��
		{
			cout << "open failed" << FileNames<< endl;//����ʧ����ʾ
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
		cout << FileNames << " total lines: " << num+1 << endl;//ĩβ��û��\n�����Ի���ͳ��һ�У���+1
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