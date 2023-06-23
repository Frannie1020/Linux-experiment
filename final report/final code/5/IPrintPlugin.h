#ifndef IPRINTPLUGIN_H
#define IPRINTPLUGIN_H
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
using namespace std;

class IPrintPlugin // 基类虚函数
{
public:
	IPrintPlugin() {
	}// 构造函数
	virtual ~IPrintPlugin() {
	}// 析构函数
public:
	virtual void Help() = 0;  // Help
	virtual void Print() = 0; // Print
	virtual int GetID() = 0;  // 功能ID
	virtual char* GetNames() = 0;//获取插件名
	virtual void Function(char *FileNames) = 0;//获取函数
	virtual void Function(string path, string aftername) = 0;//获取函数在指定路径下的指定后缀名
};

#endif
