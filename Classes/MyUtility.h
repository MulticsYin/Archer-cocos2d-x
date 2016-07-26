#ifndef  _MY_UTILITY_H_
#define  _MY_UTILITY_H_

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

//通用类
class MyUtility 
{
public:
	static string getCurrentTime();		//获得当前

	static string gbk_2_utf8(const string text);	//在win32和windows phone 8 平台下将GBK编码字符串转换为UTF-8编码；

	static string getUTF8Char(const string key);	//从文件 utf8_char.plist 中按照键读取UTF-8字符串；

};

#endif // _MY_UTILITY_H_
