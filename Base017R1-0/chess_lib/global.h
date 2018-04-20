#pragma once																		//	防止重复引用头文件机制，

#pragma warning(disable:4251)														//	all / off pair<int,int> 为模板类，采用这种方法export DLL中的类，导出DLL的时候会有警告

#ifdef CHESS_LIB_EXPORTS															// 定义导入导出控制符号
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif

#include <codecvt>																	//	wchar char wstring string 互相转换
																					//  wstring是宽char，Unicode编码，一般情况下一个字符占两个字节大小，string是窄char，AscII编码，一个字符占一个字节大小
#include<vector>																	//	顺序表容器
#include<iostream>																	//	输入输出流
#include<iomanip>																	//	manip是manipulator(操纵器的缩写),setw(域宽)，setbase(n)将数字转换成n进制
#include<utility>																	//	STL库，使用pair<int,int>模板类
#include<list>																		//	链表容器
using namespace std;																//	std

typedef int IdType;																	//	重命名整数类型为IDType类型
typedef vector<vector<int>> Matrix;													//	vector套vector,二维数组，就是Matrix
typedef pair<int, int> Position;													//	位置模板类
typedef pair<Position, Position> MoveOnce;											//	当前位置，目标位置，移动一次，pair模板类	
typedef pair<MoveOnce, int> OneStep;												//	一步走法和int类型的pair模板类
typedef vector<OneStep> moves;														//	vector容器管理每一个可行的，合理的走法
typedef vector<int> Flex;															//	Flex容器存储int类型数据

//下面是添加包含要导出的全局变量，全局函数，类，和头文件global.h
bool IsKillStep(OneStep s1, OneStep s2);											//	返回OneStep的value比较大的一个，（选取优秀一步）								
bool CHESS_LIB_API good_step(const OneStep& s1, const OneStep& s2);					//	排序中cmp参数，采用严格弱排序


class ChessBase;																	//	棋子基类

extern Matrix g_chessboard;															//	声明棋盘数组,全局变量，PS：extern声明不是定义，即不分配存储空间
extern vector<ChessBase*> g_chessman;												//	声明棋子数组的顺序表容器

class CHESS_LIB_API Global															
{
public:
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;				//使用std::wstring_convert和 std::codecvt_utf8 来处理UTF8与WChar之间的互转。
};
