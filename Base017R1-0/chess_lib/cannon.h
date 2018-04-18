#pragma once

#ifdef CHESS_LIB_EXPORTS  
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif 

#include "chessbase.h"

class CHESS_LIB_API Cannon : public ChessBase {
public:
	Cannon(int sidetag,int value,const Position& newlocation);
	~Cannon(void);
	void GetMove(const Matrix& chessboard, moves& temp) const;
	void GetValue(const Matrix& chessboard,Flex& flex) const;
	bool KillKing(const Matrix& chessboard, const Position& positionofking) const;
};