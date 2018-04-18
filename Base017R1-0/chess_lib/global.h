#pragma once																		///<	防止重复引用机制

#pragma warning(disable:4251)														///<	all / off pair<int,int> 为模板类，在推倒导出DLL的时候会有警告

#ifdef CHESS_LIB_EXPORTS  
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif
//#include <vld.h>
#include <codecvt>																	///<	wchar char wstring string 互相转换
#include<vector>																	///<	顺序表容器
#include<iostream>																	///<	输入输出流
#include<iomanip>																	///<	manip是manipulator(操纵器的缩写),setw(域宽)，setbase(n)将数字转换成n进制
#include<utility>																	///<	STL标准模板库，use pair<int,int>模板类
#include<list>																		///<	链表容器
using namespace std;																///<	std命名空间

typedef int IdType;																	///<	ID类型
typedef vector<vector<int>> Matrix;													///<	vector套vector,二维数组
typedef pair<int, int> Position;													///<	位置模板类
typedef pair<Position, Position> MoveOnce;											///<	当前位置，目标位置，移动一次，pair模板类	
typedef pair<MoveOnce, int> OneStep;												///<	走法和int类型的pair模板类
typedef vector<OneStep> moves;														///<	vector容器管理每一个可行的，合理的走法
typedef vector<int> Flex;															///<	Flex容器存储int类型数据
//全局函数
bool IsKillStep(OneStep s1, OneStep s2);											///<	返回OneStep的value比较大的一个								
bool CHESS_LIB_API good_step(const OneStep& s1, const OneStep& s2);					///<	严格弱排序
const int HollowCannonThreat[10] = { 0, 0, 0, 37, 43, 55, 57, 67, 53, 49 };
const int HorseCentralCannonThreat[10] = { 0, 0, 0, 43, 35, 24, 18, 9, 9, 9 };
const int BottomCannonThreat[9] = { 25, 21, 8, 0, 0, 0, 8, 21, 25 };

class ChessBase;																	///<	棋子基类

extern Matrix g_chessboard;															///<	声明棋盘数组,全局变量
extern vector<ChessBase*> g_chessman;												///<	声明棋子数组的顺序表容器

class CHESS_LIB_API Global
{
public:
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
};
