#include <iostream>
using namespace std;

extern "C" void Out()//打印动态库字符函数Out
{
	cout << "Hello World!" << endl;//输出hello china
}