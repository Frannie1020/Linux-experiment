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

char BYTE[] = "B"; //统计某个文件的单词数

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 3;//和之前版本一样，默认FUNC_NUM为3
	}

	virtual ~CPlugin()//析构函数
	{
	}

	virtual void Print()//打印函数的内容，提示用户输入B可以获取文件单词数
	{
		cout << "Want to know the words? Enter'B'" << endl;

	}

	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM "<<FUNC_NUM << ":this function will know the doc's words" << endl;
	}

	virtual int GetID()//返回GetID接口的值为3
	{
		return 3;
	}

	virtual char *GetNames()//获取插件文件名，输入B即可
	{
		return BYTE;
	}
	int Fileline(const char *sfline)
	{
		int sbyte = 0;
		int i = 0;
		for(; i < strlen(sfline);i++)//遍历某个文件每一行的字节数，初始循环无条件
		{
			if (*(sfline + i) != ' '|| *(sfline + i) != '/t'|| *(sfline + i) != '\n')
			{
				sbyte++;//单词数增加
				while ((*(sfline + i) != ' ') && (*(sfline + i) != '\0'))//行数增加
				{
					i++;
				}
			}
		} 
		return sbyte;//返回统计的单词数
	}

	void Function(char *File)//插件执行函数，实现统计行数的功能，并计算
	{
		int sbyte = 0;
		FILE *fp; //定义一个文件类型指针fp
		char pBuffer[4094];//定义每行输入的字符缓冲最多为4*1024-2=4094个字符
		if ((fp = fopen(File, "r")) == NULL)//打开文件失败的处理
		{
			cout << "open failed" << endl;
			exit(-1);
		}
		while (!feof(fp))//读文件的循环，直到eof结束
		{
			//获取每行的单词数
			if (fgets(pBuffer, sizeof(pBuffer), fp) != NULL)

				sbyte += Fileline(pBuffer);
		}
		fclose(fp);//关闭文件
		cout << File << " total bytes : " << sbyte << endl;//打印输出
	}

	virtual void Function(string path, string aftername)
	{

	}
private:
	int FUNC_NUM;    //功能ID
};


extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //创建对象
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}