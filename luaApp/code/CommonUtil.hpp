#ifndef COMMONUTIL
#define COMMONUTIL
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#define EXTERN extern
#define EXPORT __declspec (dllexport)
/*将msg转换为string放到string对象tempStr中*/
#define TOSTRING(msg,tempStr) \
	do{ \
	std::ostringstream os;\
	os<<msg; \
	tempStr.assign(os.str());\
	}while(0);
namespace util
{	
/*1.查找单个目录下指定后缀文件路径
   @param: path      文件夹路径
   @param: ext       文件后缀
   @param: fileList  文件路径集合
*/
EXPORT void findExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);

/*2.查找指定目录下所有的文件夹名
	@param: filePath   文件夹路径
	@param: fileList   文件夹路径集合
*/
EXPORT void findAllDir(const std::string &filePath,std::vector<std::string> &fileDirList);

/*3.查找指定目录下所有指定的后缀的文件路径
	@param: path      文件夹路径
    @param: ext       文件后缀
    @param: fileList  文件路径集合
*/
EXPORT void findAllExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);

/*4.将字符串转换为int*/
EXPORT int transStringToInt(const std::string &str);

/*5.读取指定文件，按照行数存在vector里*/
EXTERN void readFile(const std::string &filePath,std::vector<std::string> &contentList);

/*6.获取指定文件的行数*/
EXPORT unsigned int getFileNum(const std::string &filePath);

/*7.获取当前时间的字符*/
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
/*13.将list中的数据写入文件*/
EXPORT bool writeFile(const std::string &path,std::vector<std::string> &contentList);
/*14.执行shell*/
EXPORT void runCmd(const std::string &cmd);
}

/*屏幕输出函数*/
template<typename T>
void print(const T &t)
{
	std::cout<<t<<std::endl;
}
#endif