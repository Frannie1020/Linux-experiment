#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <string>
#include"IPrintPlugin.h"

using namespace std;

char LINE[] = "L"; //统计某个文件的行数

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 1;//和之前版本一样，默认FUNC_NUM为1
	}

	virtual ~CPlugin()//析构函数
	{
	}

	virtual void Print()//打印函数的内容，提示用户输入L可以获取文件行数
	{
		cout << "Want to know the lines? Enter'L'" << endl;

	}

	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's lines" << endl;
	}

	virtual int GetID()//返回GetID接口的值为1
	{
		return 1;
	}

	virtual char *GetNames()//获取插件文件名，输入L即可
	{
		return LINE;
	}

	virtual void Function(char* FileNames)//插件执行函数，实现统计行数的功能，并计算
	{
		int fd, num = 0;
		char tmp;
		while((fd = open(FileNames, O_RDONLY)) == -1)//打开文件失败
		{
			cout << "open failed" << FileNames<< endl;//产生失败提示
			return;
		}
		while (read(fd, &tmp, 1))//循环遍历文件行数
		{
			if (tmp == '\n')
			{
				num++;
			}
		}
		close(fd);
		cout << FileNames << " total lines: " << num+1 << endl;//末尾行没有\n，所以会少统计一行，故+1
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