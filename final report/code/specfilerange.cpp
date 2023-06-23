#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "IPrintPlugin.h"

using namespace std;

char SRANGE[] = "SR";//统计某个文件的大小，借鉴了linux中的wc命令，所以添加此功能

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 6;//和之前版本一样，默认FUNC_NUM为6
	}

	virtual ~CPlugin()//析构函数
	{
	}
	virtual void Print()//打印函数的内容，提示用户输入SR可以获取文件大小
	{
		cout << "Want to know the specfic file range? Enter'SR'" << endl;

	}
	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the specific doc's range" << endl;
	}

	virtual int GetID()//返回GetID接口的值为6
	{
		return 6;
	}

	virtual char *GetNames()//获取插件文件名，输SR以后即可
	{
		return SRANGE;
	}
	virtual void Function(char* FileNames)//插件执行函数，实现统计行数的功能，并计算
	{
		int fd, num = 0;
		char tmp;
		while ((fd = open(FileNames, O_RDONLY)) == -1)//打开文件失败
		{
			cout << "open failed" << FileNames << endl;//产生失败提示
			return;
		}
		while (read(fd, &tmp, 1) == 1)//循环遍历文件行数
		{
				num++;
		}
		close(fd);
		if (num==0)//空文件
		{
			cout << FileNames << " is empty!" << endl;
		}
		cout << FileNames << " range: " << num << endl;//打印输出
	}

	virtual void Function(string path, string aftername)//由于要统计特定目录特定后缀名的所有文件的行数，所以要加入目录判断函数，类似于CPluginEnumerator.cpp的插件枚举器
	{
		DIR *dir;
		struct dirent *pentry;//存放插件的文件夹,结构指针
		if ((dir = opendir(path.c_str())) == nullptr)//空指针，打开失败，返回失败提示
		{
			perror("opendir failed");
			exit(1);
		}
		while ((pentry = readdir(dir)) != nullptr)//若不是空指针则进行循环遍历
		{
			if (strcmp(pentry->d_name, ".") == 0 || strcmp(pentry->d_name, "..") == 0)
				continue;//文件后缀名为.xx，或者特殊情况..xx，这在之前插件枚举器中有写过
			else if (pentry->d_type == 8)//文件后缀为8个字节的情况
			{
				string filename = pentry->d_name;
				string afternamestr = filename.substr(filename.find_last_of('.') + 1);//获取文件后缀名，路径+形式
				if (afternamestr == aftername)//文件后缀名与定义的相等，则进行拷贝
				{
					char p[80];
					strcpy(p, (path + "/" + pentry->d_name).c_str());//拷贝到0的字符串
					Function(p);
				}
			}
			else if (pentry->d_type == 4)//后缀为4字节的情况
			{
				Function(path + "/" + pentry->d_name, aftername);//调用function函数遍历相应的
			}
		}
		closedir(dir);//关闭目录
	}
private:
	int FUNC_NUM;    //功能ID
};

extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //创建对象
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}
