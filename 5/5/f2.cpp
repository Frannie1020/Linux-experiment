#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include"IPrintPlugin.h"

using namespace std;

char BYTE[] = "B"; //ͳ��ĳ���ļ����ֽ���

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

	virtual void Print()//��ӡ���������ݣ���ʾ�û�����B+�ļ������Ի�ȡ�ļ��ֽ���
	{
		cout << "Want to know the bytes? Enter'B'" << endl;

	}

	virtual void Help()//��ȡhelp�ӿڵ��������ݲ���ӡ
	{
		cout << "Func NUM "<<FUNC_NUM << ":this function will knows the doc's bytes" << endl;
	}

	virtual int GetID()//����GetID�ӿڵ�ֵΪ2
	{
		return 2;
	}

	virtual char *GetPluginNames()//��ȡ����ļ���������B�ӿո��Ժ󼴿�
	{
		return BYTE;
	}

	virtual void Function(char* FileNames)//���ִ�к�����ʵ��ͳ�������Ĺ��ܣ�������
	{
		int fd,num = 0;
		char tmp;
		while ((fd = open(FileNames,O_RDONLY)) == -1)//���ļ�ʧ��
		{
			cout << "open failed" << FileNames << endl;//����ʧ����ʾ
			return;
		}
		while (read(fd, &tmp, 1)==1)//ѭ�������ļ�����
		{
				num++;
	
		}
		close(fd);
		cout << FileNames << " total bytes: " << num << endl;//��ӡ���
	}
private:
	int FUNC_NUM;    //����ID
};


extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //��������
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}