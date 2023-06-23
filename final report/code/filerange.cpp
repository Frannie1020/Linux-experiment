#include <unistd.h>
#include <fcntl.h>
#include<cstring>
#include<string.h>
#include<string>
#include<iostream>
#include "IPrintPlugin.h"

using namespace std;

char RANGE[] = "R";//统计某个文件的大小，借鉴了linux中的wc命令，所以添加此功能

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 5;//和之前版本一样，默认FUNC_NUM为5
	}

	virtual ~CPlugin()//析构函数
	{
	}
	virtual void Print()//打印函数的内容，提示用户输入R可以获取文件大小
	{
		cout << "Want to know the file range? Enter'R'" << endl;

	}
	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's range" << endl;
	}

	virtual int GetID()//返回GetID接口的值为5
	{
		return 5;
	}

	virtual char *GetNames()//获取插件文件名，输R以后即可
	{
		return RANGE;
	}
	virtual void Function(char* FileNames)//插件执行函数，实现统计行数的功能，并计算
	{
		int fd, num = 0;
		char tmp;
		while((fd = open(FileNames, O_RDONLY)) == -1)//打开文件失败
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


