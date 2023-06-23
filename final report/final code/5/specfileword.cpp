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

char BYTE[] = "SFB"; //统计某个文件的单词数


class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 4;//和之前版本一样，默认FUNC_NUM为4
	}
	virtual ~CPlugin()//析构函数
	{
	}
	virtual void Print()//打印函数的内容，提示用户输入SFB可以获取文件单词数
	{
		cout << "Want to know the specific filewords? Enter'SFB'" << endl;

	}
	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the specific doc's words" << endl;
	}

	virtual int GetID()//返回GetID接口的值为4
	{
		return 4;
	}

	virtual char *GetNames()//获取插件文件名，输入SFB以后即可
	{
		return BYTE;
	}

	int Fileline(const char *sfline)
	{
		int sbyte = 0;
		int i = 0;
		for (; i < strlen(sfline); i++)//遍历某个文件每一行的字节数，初始循环无条件
		{
			if (*(sfline + i) != ' ' || *(sfline + i) != '/t' || *(sfline + i) != '\n')
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
	{//由于要统计特定目录特定后缀名的所有文件的行数，所以要加入目录判断函数，类似于CPluginEnumerator.cpp的插件枚举器
		DIR *dir;
		struct dirent *pentry;//存放插件的文件夹,结构指针
		if ((dir = opendir(path.c_str())) == nullptr) {//空指针，打开失败，返回失败提示
			perror("opendir failed");
			exit(1);
		}
		while ((pentry = readdir(dir)) != nullptr) {//若不是空指针则进行循环遍历
			if (strcmp(pentry->d_name, ".") == 0 || strcmp(pentry->d_name, "..") == 0)
				continue;//文件后缀名为.xx，或者特殊情况..xx
			else if (pentry->d_type == 8) {
				string filename = pentry->d_name;//文件后缀为8个字节的情况
				string afternamestr = filename.substr(filename.find_last_of('.') + 1);//获取文件后缀名，路径+形式
				if (afternamestr == aftername) {//文件后缀名与定义的相等，则进行拷贝
					
					char p[100];
					strcpy(p, (path + "/" + pentry->d_name).c_str());//拷贝到0的字符串
					Function(p);
				}
			}
			else if (pentry->d_type == 4) //后缀为4字节的情况
			{
				Function(path + "/" + pentry->d_name, aftername); //调用function函数遍历
			}
		}
		closedir(dir);//关闭目录
	}
private:
	int FUNC_NUM;
};
extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //创建对象
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}
