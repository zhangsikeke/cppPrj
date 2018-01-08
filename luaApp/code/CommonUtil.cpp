#include "CommonUtil.hpp"
#include <iostream>
#include <io.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace util
{
void findExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList)
{
	_finddata_t fileDir;
	std::string tempath=path;
	tempath.append("\\"+ext);
	const char* dir=tempath.c_str();
	long lfDir;
	if((lfDir = _findfirst(dir,&fileDir))==-1l)
	{	//printf("No file is found\n");
	}
	else{
		//printf("file list:\n");
		do{
			//printf("%s\n",fileDir.name);
			std::string s(path+"\\");
			s.append(fileDir.name);
			fileList.push_back(s);

		}while( _findnext( lfDir, &fileDir ) == 0 );
	}
	_findclose(lfDir);

}
void findAllDir(const std::string &filePath,std::vector<std::string> &fileDirList)
{
	_finddata_t fileDir;
	std::string tempath=filePath;
	tempath.append("/*.*");
	const char* dir=tempath.c_str();
	fileDirList.push_back(filePath);
	long lfDir;
	if((lfDir = _findfirst(dir,&fileDir))==-1l)
	{	//printf("No file is found\n");
	}
	else{
		//printf("file list:\n");
		do{
			//printf("%s\n",fileDir.name);
			
			
			std::string s(filePath+"/");
			s.append(fileDir.name);

			std::string newFilePaht((s+"/*.*"));
			const char* dire=newFilePaht.c_str();
			long isDir = _findfirst(dire,&fileDir);

			if (s.find("/.")==std::string::npos && isDir!=-1l)
			{
				fileDirList.push_back(s);
				findAllDir(s,fileDirList);
			}
		}while( _findnext( lfDir, &fileDir ) == 0 );
	}
	_findclose(lfDir);
}
void findAllExtFile(const std::string &path,const std::string &ext,std::vector<std::string> &fileList)
{
	std::vector<std::string> v;
	findAllDir(path,v);
	std::vector<std::string>::iterator it=v.begin();
	for (it;it!=v.end();it++)
	{
		findExtFile(*it,ext,fileList);
	}
}
int transStringToInt(const std::string &str)
{
	int maxPos=(int)str.size()-1;
	int result=0;
	for(int i=0;i<=maxPos;i++)
	{
		char c=str[i];
		int temp=atoi(&c);
		result+=temp*pow(10+0.0,maxPos-i+0.0);
	}
	return result;
}

void readFile(const std::string &filePath,std::vector<std::string> &contentList)
{
	std::ifstream infile(filePath.c_str());
	std::string lines;
	while(std::getline(infile,lines))
	{
		contentList.push_back(lines);
	}
	infile.close();
}
unsigned int getFileNum(const std::string &filePath)
{
	unsigned int i=0;
	std::ifstream infile(filePath.c_str());
	std::string lines;
	while(std::getline(infile,lines))
	{
		i++;
	}
	infile.close();
	return i;
}
void getTimeStr(std::string &timeStr)
{
	time_t nowtime;
	time (&nowtime);//获取当前时间，存nowtime里
	struct tm * target_time;
	target_time = localtime (&nowtime); 

	std::ostringstream os;
	os<<target_time->tm_year+1900<<"/"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_mon+1<<"/"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_mday<<" "
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_hour<<":"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_min<<":"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_sec<<"-> ";
	timeStr.assign(os.str());
}
void rePlaceAll(std::string &str,std::string souceStr,std::string tagStr)
{
	std::string::size_type pos;
	while((pos=str.find(souceStr,0))!=std::string::npos)
	{
		str.replace(pos,souceStr.size(),tagStr);
	}
}
bool writeFile(const std::string &path,std::vector<std::string> &contentList)
{
	try
	{
		std::ofstream out(path.c_str());
		std::vector<std::string>::const_iterator it=contentList.begin();
		for (it;it!=contentList.end();it++)
		{
			out<<*it<<std::endl;
		}
		return true;
	}
	catch (...)
	{
		return false;
		throw ("write file"+path+"failed!");
	}
}
void runCmd(const std::string &cmd)
{
	std::system(cmd.c_str());
}

}