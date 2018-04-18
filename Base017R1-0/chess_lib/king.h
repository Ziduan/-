#pragma once

#ifdef CHESS_LIB_EXPORTS  
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif 

#include "chessbase.h"

class CHESS_LIB_API King : public ChessBase
{
public:
	King(int sidetag,int value,const Position& newlocation);
	~King(void);
	void GetMove(const Matrix& chessboard, moves& temp) const;
	void GetValue(const Matrix& chessboard,Flex& flex) const;
	bool KillKing(const Matrix& chessboard, const Position& positionofking) const;

private:
	//将_id走到_moveToPosition位置后会不会导致将帅照面
	bool King::IsKingKillKing(const IdType _id, const int _xTo, const int _yTo) const;
};
