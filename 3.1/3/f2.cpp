#include <iostream>
using namespace std;

const int FUNC_NUM = 2;//���峣��ȫ�ֱ�����Ψһ

extern "C" void out()
{
	cout << "Hello China" << endl;//���hello china

}

extern"C" void Help()
{
	cout << "Function NUM" << FUNC_NUM << ": this fuction will print Hello China" << endl;//�����Ӧ��functionID����ӡ����
}