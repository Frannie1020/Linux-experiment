#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H
#include <vector>

using namespace std;

class IPrintPlugin;   //基类

class CPluginController  //插件控制器
{
public:
	CPluginController(void);            // 构造函数
	virtual ~CPluginController(void);   // 析构函数
	
	bool InitializeController(void);    // 初始化插件句柄
	bool UninitializeController(void);  // 卸载插件

	bool ProcessHelp(void);              // 打开所有动态库把help实现
	bool ProcessRequest(int FunctionNUM); // 功能ID输出命令处理进程

private:
	vector<void *> m_vForPlugin;        // htype动态链接库句柄容器
	vector<IPrintPlugin*> m_vpPlugin;     // 插件类容器
};

#endif
