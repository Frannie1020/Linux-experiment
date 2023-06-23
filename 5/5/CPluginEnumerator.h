#ifndef CPLUGINENUMERATOR_H  // 声明头文件
#define CPLUGINENUMERATOR_H

#include <vector>
#include<dirent.h>
#include<cstring>
#include <string>
#include<iostream>

using namespace std;

class CPluginEnumerator   // 插件枚举器
{
public:
    CPluginEnumerator();           // 构造函数
    virtual ~CPluginEnumerator();  // 析构函数

    bool GetPluginNames(vector<string>& vPluginNames);  // 插件注册函数
};

#endif
