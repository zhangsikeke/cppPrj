#ifndef COMMONUTIL
#define COMMONUTIL
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#define EXTERN extern
#define EXPORT __declspec (dllexport)
/*��msgת��Ϊstring�ŵ�string����tempStr��*/
#define TOSTRING(msg,tempStr) \
	do{ \
	std::ostringstream os;\
	os<<msg; \
	tempStr.assign(os.str());\
	}while(0);
namespace util
{	
/*1.���ҵ���Ŀ¼��ָ����׺�ļ�·��
   @param: path      �ļ���·��
   @param: ext       �ļ���׺
   @param: fileList  �ļ�·������
*/
EXPORT void findExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);

/*2.����ָ��Ŀ¼�����е��ļ�����
	@param: filePath   �ļ���·��
	@param: fileList   �ļ���·������
*/
EXPORT void findAllDir(const std::string &filePath,std::vector<std::string> &fileDirList);

/*3.����ָ��Ŀ¼������ָ���ĺ�׺���ļ�·��
	@param: path      �ļ���·��
    @param: ext       �ļ���׺
    @param: fileList  �ļ�·������
*/
EXPORT void findAllExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList);

/*4.���ַ���ת��Ϊint*/
EXPORT int transStringToInt(const std::string &str);

/*5.��ȡָ���ļ���������������vector��*/
EXTERN void readFile(const std::string &filePath,std::vector<std::string> &contentList);

/*6.��ȡָ���ļ�������*/
EXPORT unsigned int getFileNum(const std::string &filePath);

/*7.��ȡ��ǰʱ����ַ�*/
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
/*13.��list�е�����д���ļ�*/
EXPORT bool writeFile(const std::string &path,std::vector<std::string> &contentList);
/*14.ִ��shell*/
EXPORT void runCmd(const std::string &cmd);
}

/*��Ļ�������*/
template<typename T>
void print(const T &t)
{
	std::cout<<t<<std::endl;
}
#endif