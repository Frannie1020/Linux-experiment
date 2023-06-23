#include <iostream>

using namespace std;

const int FUNC_NUM = 2;

extern "C" void Out()
{
	cout << "Hello China" << endl;

}

extern "C" void Help()
{
	cout << "Function NUM " << FUNC_NUM << ": this fuction will print Hello China" << endl;
}

extern "C" int GetNUM()
{
	return FUNC_NUM; //·µ»ØNUM
}