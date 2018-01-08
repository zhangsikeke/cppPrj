#pragma once
#include "luaAPI.hpp"
#include <sstream>
#include <vector>
#include <string>
#define EXTERN extern
#define EXPORT __declspec (dllexport)
/*1.��msgת��Ϊstring�ŵ�string����tempStr��*/
#define TOSTRING(msg,tempStr) \
	do{ \
	std::ostringstream os;\
	os<<msg; \
	tempStr.assign(os.str());\
	}while(0);
	
/************************************************************************
 2.
 @����lua�ű���ָ���ĺ���
 @filePath:lua�ļ�·��
 @moduleName��ģ��·��
 @funcName�� ��������
************************************************************************/
EXPORT void call_lua_function(lua_State *L, char *filePath,char *moduleName,char *funcName);
/*3.���ҵ���Ŀ¼��ָ����׺�ļ�·��*/
EXPORT void findExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);
/*4.����ָ��Ŀ¼�µ�����lua�ļ�*/
EXPORT void loadAllLua(lua_State *L,const std::string &filePath);
/*����ָ��Ŀ¼�����е��ļ�����*/
EXPORT void findAllDir(const std::string &filePath,std::vector<std::string> &fileDirList);
/*5.����ָ��Ŀ¼��ָ���ĺ�׺���ļ�·��*/
EXPORT void findAllExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);
/*6.���ַ���ת��Ϊint*/
EXPORT int transStringToInt(const std::string &str);
/*7.��ȡָ���ļ���������������vector��*/
EXTERN void readFile(const std::string &filePath,std::vector<std::string> &contentList);
/*8.��ȡָ���ļ�������*/
EXPORT unsigned int getFileNum(const std::string &filePath);
/*9.��ȡ��ǰʱ����ַ�*/
EXPORT void getTimeStr(std::string &timeStr);
/*10.��str�е�source�滻��tagStr*/
EXPORT void rePlaceAll(std::string &str,std::string souceStr,std::string tagStr);
/*11.��stringת��ΪT*/
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
/*12.��Tת��Ϊstring*/
template<typename T> 
EXPORT void tToString(std::string &resultStr,const T &t)
{
	std::ostringstream os;
	os<<t;
	resultStr.assign(os.str());
}
/*13���ַ���ת��Ϊ�������ͷ���*/
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




