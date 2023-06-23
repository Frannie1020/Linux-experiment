#include<iostream>
#include <stdio.h>
#include <unistd.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <string.h>
#include <string>
#include"IPrintPlugin.h"

#define N 80

using namespace std;

char LENGTH[] = "ML"; //统计某个文件的行数

class CPlugin :
	public IPrintPlugin//继承虚基类IPrintPlugin的特性
{
public:
	CPlugin()
	{
		FUNC_NUM = 7;//和之前版本一样，默认FUNC_NUM为7
	}

	virtual ~CPlugin()//析构函数
	{
	}

	virtual void Print()//打印函数的内容，提示用户输入ML可以获取文件最大行长度
	{
		cout << "Want to know the length of the max line? Enter'ML'" << endl;

	}

	virtual void Help()//获取help接口的如下内容并打印
	{
		cout << "Func NUM " << FUNC_NUM << ":this function will know the doc's length of the max line" << endl;
	}

	virtual int GetID()//返回GetID接口的值为7
	{
		return 7;
	}

	virtual char *GetNames()//获取插件文件名，输入ML即可
	{
		return LENGTH;
	}

	virtual void Function(char* FileNames)
	{
		FILE *fp;
		char h[N], zc[N], zd[N];
		int n = 0, len, maxno, minno;
		if (fp == NULL)
		printf("文件打开失败!\n");
		else
		{
			while (!feof(fp))
			{
				fgets(h, N, fp);
				if (n == 1)
				{
					maxno = 1;
					//minno = 1;
					strcpy(zc, h);
					//strcpy(zd, h);
				}
				else
				{
					if (strlen(zc) <= strlen(h))
					{
						maxno = n;
						strcpy(zc, h);
					}
					/*if (strlen(zd) >= strlen(h))
					{
						minno = n;
						strcpy(zd, h);
					}*/
				}
				n++;
			}
			fclose(fp);
			n--;
		//	printf("说明：文件中共有：%d行!\n", n);
			printf("第%d行最长，有%d个字符", maxno, strlen(zc));
		//	printf("第%d行最短，有%d个字符，内容为：\n%s\n", minno, strlen(zd), zd);
		}

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
