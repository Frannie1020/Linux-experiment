#include <iostream>
using namespace std;

const int FUNC_NUM = 1;//���峣��ȫ�ֱ�����Ψһ

extern "C" void out()
{
	cout << "Hello World" << endl;//���hello world

}

extern"C" void Help()
{
	cout << "Function NUM" << FUNC_NUM << ": this fuction will print Hello World"<< endl;
}//���functionNUM����ӡHello World