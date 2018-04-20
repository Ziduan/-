#include "global.h"																				//包含global的头文件																										

std::wstring_convert<std::codecvt_utf8<wchar_t>> Global::converter;                             //处理UTF8与WChar之间的互转

Matrix g_chessboard;																			//	全局变量，棋盘数组的 定义
vector<ChessBase*> g_chessman;																	//	全局变量，棋子数组的 定义

bool IsKillStep(OneStep s1, OneStep s2)															//	选取优秀的一步，返回OneStep的value大的一个
{
	return s1.second > s2.second;
}


bool good_step(const OneStep& s1, const OneStep& s2)											//	严格弱排序排序,相等的返回false
{
	
	if ((s1.second == 16 || s1.second == 32) && !(s2.second == 16 || s2.second == 32))			//	将军走法优先
	{
		return true;
	}
	
	if (s1.second != 0 && s2.second == 0)														//	吃子走法优先
	{
		return true;
	}
	return false;
}
