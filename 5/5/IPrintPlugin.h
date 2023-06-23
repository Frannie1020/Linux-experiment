#ifndef IPRINTPLUGIN_H
#define IPRINTPLUGIN_H

class IPrintPlugin  // 基类虚函数
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
	virtual char* GetPluginNames() = 0;//获取插件名
	virtual void Function(char*) = 0;//获取函数
};

#endif
