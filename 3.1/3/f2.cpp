#include <iostream>
using namespace std;

const int FUNC_NUM = 2;//定义常数全局变量，唯一

extern "C" void out()
{
	cout << "Hello China" << endl;//输出hello china

}

extern"C" void Help()
{
	cout << "Function NUM" << FUNC_NUM << ": this fuction will print Hello China" << endl;//输出对应的functionID并打印函数
}