#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include"IPrintPlugin.h"

using namespace std;

char BYTE[] = "B"; //统计某个文件的字节数

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 2;//和之前版本一样，默认FUNC_NUM为2
	}

	virtual ~CPlugin()//析构函数
	{
	}

	virtual void Print()//打印函数的内容，提示用户输入B+文件名可以获取文件字节数
	{
		cout << "Want to know the bytes? Enter'B'" << endl;

	}

	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM "<<FUNC_NUM << ":this function will knows the doc's bytes" << endl;
	}

	virtual int GetID()//返回GetID接口的值为2
	{
		return 2;
	}

	virtual char *GetPluginNames()//获取插件文件名，输入B加空格以后即可
	{
		return BYTE;
	}

	virtual void Function(char* FileNames)//插件执行函数，实现统计行数的功能，并计算
	{
		int fd,num = 0;
		char tmp;
		while ((fd = open(FileNames,O_RDONLY)) == -1)//打开文件失败
		{
			cout << "open failed" << FileNames << endl;//产生失败提示
			return;
		}
		while (read(fd, &tmp, 1)==1)//循环遍历文件行数
		{
				num++;
	
		}
		close(fd);
		cout << FileNames << " total bytes: " << num << endl;//打印输出
	}
private:
	int FUNC_NUM;    //功能ID
};


extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //创建对象
{
	static CPlugin plugin;
	*ppPlugin = &plugin;
}