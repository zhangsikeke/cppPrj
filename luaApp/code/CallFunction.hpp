#pragma once
#include "luaAPI.hpp"
#include <sstream>
#include <vector>
#include <string>
#define EXTERN extern
#define EXPORT __declspec (dllexport)
/*1.将msg转换为string放到string对象tempStr中*/
#define TOSTRING(msg,tempStr) \
	do{ \
	std::ostringstream os;\
	os<<msg; \
	tempStr.assign(os.str());\
	}while(0);
	
/************************************************************************
 2.
 @调用lua脚本中指定的函数
 @filePath:lua文件路径
 @moduleName：模块路径
 @funcName： 函数名称
************************************************************************/
EXPORT void call_lua_function(lua_State *L, char *filePath,char *moduleName,char *funcName);
/*3.查找单个目录下指定后缀文件路径*/
EXPORT void findExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);
/*4.加载指定目录下的所有lua文件*/
EXPORT void loadAllLua(lua_State *L,const std::string &filePath);
/*查找指定目录下所有的文件夹名*/
EXPORT void findAllDir(const std::string &filePath,std::vector<std::string> &fileDirList);
/*5.查找指定目录下指定的后缀的文件路径*/
EXPORT void findAllExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);
/*6.将字符串转换为int*/
EXPORT int transStringToInt(const std::string &str);
/*7.读取指定文件，按照行数存在vector里*/
EXTERN void readFile(const std::string &filePath,std::vector<std::string> &contentList);
/*8.获取指定文件的行数*/
EXPORT unsigned int getFileNum(const std::string &filePath);
/*9.获取当前时间的字符*/
EXPORT void getTimeStr(std::string &timeStr);
/*10.将str中的source替换成tagStr*/
EXPORT void rePlaceAll(std::string &str,std::string souceStr,std::string tagStr);
/*11.将string转换为T*/
template<typename T> 
EXPORT T stringtoT(const std::string &str)
{
	bool intFlag=false;
	bool douleFlag=false;
	std::string::size_type pos=str.find(".");
	if(pos!=std::string::npos)
	{
		douleFlag=true;
	}
	else
	{
		intFlag=true;
	}

	if (intFlag)
	{
		return std::atoi(str.c_str());
	}

	if (douleFlag)
	{
		return std::atof(str.c_str());;
	}	
}
/*12.将T转换为string*/
template<typename T> 
EXPORT void tToString(std::string &resultStr,const T &t)
{
	std::ostringstream os;
	os<<t;
	resultStr.assign(os.str());
}
/*13将字符串转换为任意类型泛型*/
/*EXPORT bool fromStringToExt(int &in,const std::string &str);
EXPORT bool fromStringToExt(double &do,const std::string &str);
template<typename T>
EXPORT T stringToTemplate(const std::string &str)
{
	T t;
	if (!fromStringToExt(t,str))
	{
		throw ("trans to "+typeid(T).name()+" failed!")
	}
}*/




