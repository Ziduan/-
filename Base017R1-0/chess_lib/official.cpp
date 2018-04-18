#include "official.h"

Official::Official(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=4;
//构造函数开始

//第89页红仕矩阵
		int positionvalue[16*16]=
	{
	//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*4 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*5 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*6 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*7 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*8 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*9 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*10*/	0, 0, 0, 0, 0, 0, 30, 0, 30, 0, 0, 0, 0, 0, 0, 0,
/*11*/	0, 0, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0,
/*12*/	0, 0, 0, 0, 0, 0, 30, 0, 30, 0, 0, 0, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	this->InitMatrix(positionvalue);

//构造函数结束
}

Official::~Official(void)
{
}

void Official::GetMove(const Matrix& chessboard, moves& temp) const
{
	//******************
	//******************
	//******1***2*******
	//********h*********
	//******3***4*******
	//******************
	//******************
	vector<Position> direction;
	direction.push_back(make_pair(-1,-1));
	direction.push_back(make_pair(-1,+1));
	direction.push_back(make_pair(+1,-1));
	direction.push_back(make_pair(+1,+1));
	for(int i=0;i<4;i++)
		{
			int xto=location_.first+direction[i].first;
			int yto=location_.second+direction[i].second;
			int targetman=chessboard[xto][yto];
			if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
				if(targetman==0)
				{
					temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
				}
				else if(targetman/32!=sidetag_)
				{
					temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
				}
		}
}

void Official::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//******************
	//******1***2*******
	//********h*********
	//******3***4*******
	//******************
	//******************
	vector<Position> direction;
	direction.push_back(make_pair(-1,-1));
	direction.push_back(make_pair(-1,+1));
	direction.push_back(make_pair(+1,-1));
	direction.push_back(make_pair(+1,+1));
	for(int i=0;i<4;i++)
		{
			int xto=location_.first+direction[i].first;
			int yto=location_.second+direction[i].second;
			int targetman=chessboard[xto][yto];
			if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
				if(targetman==0)
				{
					flex.push_back(2);
				}
				else if(targetman>>5!=sidetag_)
				{
					flex.push_back(this->chessmanvalue_[targetman]);
				}
				//目标位置为本方棋子，本方棋子受到保护，增加分值
				else if(targetman>>5==sidetag_)
				{
					flex.push_back(this->chessmanvalue_[targetman]>>2);
				}
		}
}

bool Official::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}