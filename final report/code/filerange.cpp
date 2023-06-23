#include <unistd.h>
#include <fcntl.h>
#include<cstring>
#include<string.h>
#include<string>
#include<iostream>
#include "IPrintPlugin.h"

using namespace std;

char RANGE[] = "R";//ͳ��ĳ���ļ��Ĵ�С�������linux�е�wc���������Ӵ˹���

class CPlugin :
	public IPrintPlugin//�̳������IPrintPlugin������
{
public:
	CPlugin()
	{
		FUNC_NUM = 5;//��֮ǰ�汾һ����Ĭ��FUNC_NUMΪ5
	}

	virtual ~CPlugin()//��������
	{
	}
	virtual void Print()//��ӡ���������ݣ���ʾ�û�����R���Ի�ȡ�ļ���С
	{
		cout << "Want to know the file range? Enter'R'" << endl;

	}
	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's range" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ5
	{
		return 5;
	}

	virtual char *GetNames()//��ȡ����ļ�������R�Ժ󼴿�
	{
		return RANGE;
	}
	virtual void Function(char* FileNames)//���ִ�к�����ʵ��ͳ�������Ĺ��ܣ�������
	{
		int fd, num = 0;
		char tmp;
		while((fd = open(FileNames, O_RDONLY)) == -1)//���ļ�ʧ��
		{
			cout << "open failed" << FileNames << endl;//����ʧ����ʾ
			return;
		}
		while (read(fd, &tmp, 1) == 1)//ѭ�������ļ�����
		{
				num++;
		}
		close(fd);
		if (num==0)//���ļ�
		{
			cout << FileNames << " is empty!" << endl;
		}
		cout << FileNames << " range: " << num << endl;//��ӡ���
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


