#pragma once

#ifdef CHESS_LIB_EXPORTS  
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif 

#include "global.h"

class CHESS_LIB_API ChessBase
{
 public:
	
	ChessBase(int sidetag,int value,const Position& newlocation);																///<	用于构造一个棋子的基类部分
	virtual ~ChessBase(void);																									///<	基类虚析构函数
	virtual void GetMove(const Matrix& _chessboard, moves& tem) const=0;														///<	得到棋子走法，属性不得修改
	virtual void GetValue(const Matrix& _chessboard, Flex& flex) const=0;														///<	得到棋子的价值
	virtual bool KillKing(const Matrix& _chessboard, const Position& positionofking) const=0;									///<	胜利的判定
	//	一个棋子贡献的价值 = 位置价值+棋子本身的价值
	inline int ContributeValue(void) const { return positionvalue_[location_.first][location_.second]+value_;}					///<	inline内联函数
	//	返回棋子所属的
	inline int sidetag(void) const {return sidetag_;}
	inline bool IsBigMan(void) const { return sidetag_ == 1 ? true : false; }													///<	是否是大号棋子的判定
	inline Position& location(void) {return location_;}																			///<	返回棋子在棋盘上的位置
	inline void set_location(const Position& newlocat) {this->location_=newlocat;}												///<	设定棋子在棋盘上的位置
	inline int value(void) const { return value_;}																				///<	
	inline bool Alive(void) {return alive_;}																					///<	判断棋子是否还在
	inline void SetAlive(bool a) {alive_=a;}																					///<	
	IdType GetSelfKing(void) const;																								///<

public:
	static void InitLegalPosition(void);																						///<	static函数

private:
	ChessBase(const ChessBase&);																								///<	拷贝构造
	ChessBase& operator=(const ChessBase&);																						///<	重载赋值运算符

protected:
	
	void InitMatrix(int* begin);																								// 供派生类构造函数使用，实现位置价值数组的初始化
	//合法位置数组,legalposition_[0],legalposition_[1]
	
	int sidetag_;																												//sidetag =0 小号棋子 sidetag =1 大号棋子
	
	int m_legalcharacter;																										//棋子的位置特征值，跟合法位置数组按位与之后可以得出能否到达目标位置
	
	Position location_;																											// 棋子在棋盘上的位置
	
	Matrix positionvalue_;																										//位置价值数组
	
	bool alive_;																												//标志棋子是否被吃掉
	int value_;

protected:
	static const IdType m_bigKingId;
	static const IdType m_smallKingId;
	//合法位置数组
	static  vector<Matrix> legalposition_;
	static  int chessmanvalue_[48];
};