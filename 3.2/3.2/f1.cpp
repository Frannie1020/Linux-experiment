#include <iostream>

using namespace std;

const int FUNC_NUM = 1;

extern "C" void Out()
{
	cout << "Hello World" << endl;

}

extern "C" void Help()
{
	cout << "Function NUM " << FUNC_NUM << ": this fuction will print Hello World" << endl;
}

extern "C" int GetNUM()
{
	return FUNC_NUM;
}