#include "soldier.h"

Soldier::Soldier(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=8;
//构造函数开始

//第91页红兵矩阵
	int positionvalue[16*16]=
	{
	//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0, 10, 10, 10, 20, 25, 20, 10, 10, 10, 0, 0, 0, 0,
/*4 */	0, 0, 0, 25, 30, 40, 50, 60, 50, 40, 30, 25, 0, 0, 0, 0,
/*5 */	0, 0, 0, 25, 30, 30, 40, 40, 40, 30, 30, 25, 0, 0, 0, 0,
/*6 */	0, 0, 0, 20, 25, 25, 30, 30, 30, 25, 25, 20, 0, 0, 0, 0,
/*7 */	0, 0, 0, 15, 20, 20, 20, 20, 20, 20, 20, 15, 0, 0, 0, 0,
/*8 */	0, 0, 0, 10,  0, 15,  0, 15,  0, 15,  0, 10, 0, 0, 0, 0,
/*9 */	0, 0, 0, 10,  0, 10,  0, 15,  0, 10,  0, 10, 0, 0, 0, 0,
/*10*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*11*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*12*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	this->InitMatrix(positionvalue);

//构造函数结束
}

Soldier::~Soldier(void)
{
}

void Soldier::GetMove(const Matrix& chessboard, moves& temp) const
{
	//******************
	//*******3*r*2******
	//*********1********
	//******************
	//*********1********
	//*******2*b*3******
	//******************
	vector<vector<Position>> direction;
	vector<Position> blackdirection,reddirection;

	blackdirection.push_back(make_pair(+0,-1));
	blackdirection.push_back(make_pair(-1,+0));
	blackdirection.push_back(make_pair(+0,+1));

	reddirection.push_back(make_pair(+0,-1));
	reddirection.push_back(make_pair(+1,+0));
	reddirection.push_back(make_pair(+0,+1));
	direction.push_back(blackdirection);
	direction.push_back(reddirection);
	//三个前进的方向，前，左，右
	for(int i=0;i<3;i++)
	{
		int xto=location_.first+direction[sidetag_][i].first;
		int yto=location_.second+direction[sidetag_][i].second;
		int targetman=chessboard[xto][yto];
		//下一位置在棋盘上
		if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
		{
			bool across=(sidetag_==1)?((xto>=8 && xto<=12)?true:false):((xto<=7 && xto>=3)?true:false);
			//假设默认情况为过河之后
			if(targetman==0)
			{
				temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
				//temp.push_back(make_pair(location_,make_pair(xto,yto)));
				//如果没过河，则不再向左走，不再向又走
				if(!across)
					break;
			}
			else if( targetman/32!=sidetag_)
			{
				temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
				if(!across)
					break;
			}
		}
	}
}

void Soldier::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//*******3*r*2******
	//*********1********
	//******************
	//*********1********
	//*******2*b*3******
	//******************
	vector<vector<Position>> direction;
	vector<Position> blackdirection,reddirection;

	blackdirection.push_back(make_pair(+0,-1));
	blackdirection.push_back(make_pair(-1,+0));
	blackdirection.push_back(make_pair(+0,+1));

	reddirection.push_back(make_pair(+0,-1));
	reddirection.push_back(make_pair(+1,+0));
	reddirection.push_back(make_pair(+0,+1));
	direction.push_back(blackdirection);
	direction.push_back(reddirection);
	//三个前进的方向，前，左，右
	for(int i=0;i<3;i++)
	{
		int xto=location_.first+direction[sidetag_][i].first;
		int yto=location_.second+direction[sidetag_][i].second;
		int targetman=chessboard[xto][yto];
		//下一位置在棋盘上
		if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
		{
			bool across=(sidetag_==1)?((xto>=8 && xto<=12)?true:false):((xto<=7 && xto>=3)?true:false);
			//假设默认情况为过河之后
			if(targetman==0)
			{
				flex.push_back(2);
				//如果没过河，则不再向左走，不再向又走
				if(!across)
					break;
			}
			else if( targetman>>5!=sidetag_)
			{
				flex.push_back(this->chessmanvalue_[targetman]);
				if(!across)
					break;
			}
			else if(targetman>>5==sidetag_)
			{
				flex.push_back(this->chessmanvalue_[targetman]>>2);
				if(!across)
					break;
			}
		}
	}
}

bool Soldier::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}