#include <iostream>
#include "IPrintPlugin.h"

using namespace std;

class CPrintPlugin : public IPrintPlugin    //继承基类
{
	public:
		CPrintPlugin()          
		{
			FUNC_NUM = 1;//定义FUNC_NUM为1
		}

		virtual ~CPrintPlugin()//析构函数
		{
		}

		virtual void Print()//打印函数Print
		{
			cout << "Hello World" << endl;//输出hello world
		}

		virtual void Help()//help函数
		{
			cout << "Function NUM " << FUNC_NUM << " : This function will print Hello World." << endl;
		}//输出Function NUM并打印Hello World

		virtual int GetID(void)//GetID接口函数
		{
			return FUNC_NUM;
		}
	private:
		int FUNC_NUM;    //功能ID
};

extern "C" void CreateObj(IPrintPlugin **ppPlugin)  //创建对象
{
	static CPrintPlugin plugin;
	*ppPlugin = &plugin;
}
