#include <iostream>
using namespace std;

const int FUNC_NUM = 1;//定义常数全局变量，唯一

extern "C" void out()
{
	cout << "Hello World" << endl;//输出hello world

}

extern"C" void Help()
{
	cout << "Function NUM" << FUNC_NUM << ": this fuction will print Hello World"<< endl;
}//输出functionNUM并打印Hello World