#include "king.h"
#include "global.h"
#include "chessbase.h"

King::King(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=2;
//构造函数开始

//第89页红帅矩阵
//默认以小号棋子为准
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
/*10*/	0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
/*11*/	0, 0, 0, 0, 0, 0, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0,
/*12*/	0, 0, 0, 0, 0, 0, 15, 20, 15, 0, 0, 0, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	this->InitMatrix(positionvalue);

//构造函数结束
}
King::~King(void)
{
}
bool King::IsKingKillKing(const IdType _id, const int _xTo, const int _yTo) const
{
	IdType anotherKingThere = (_id == m_bigKingId) ? m_smallKingId : m_bigKingId;
	
	int anotherY = g_chessman[anotherKingThere]->location().second;
	//两个老将不在一条直线上
	if (anotherY != _yTo)
	{
		return false;
	}
	//两个老将在一条直线上
	bool kill = true;
	int anotherX = g_chessman[anotherKingThere]->location().first;
	int start, end;
	(_xTo < anotherX) ? (start = _xTo, end = anotherX) : (start = anotherX, end = _xTo);
	for (int i = start + 1; i <= end -1; ++i)
	{
		if (g_chessboard[i][anotherY] !=0)
		{
			kill = false;
			break;
		}
	}
	return kill;
}
void King::GetMove(const Matrix& chessboard, moves& _temp) const
{
	//******************
	//******************
	//********2*********
	//******1*h*3*******
	//********4*********
	//******************
	//******************
	//四个方向前进的距离
	vector<Position> direction;
	direction.push_back(make_pair(+0,-1));
	direction.push_back(make_pair(-1,+0));
	direction.push_back(make_pair(+0,+1));
	direction.push_back(make_pair(+1,+0));
	//四个方向都尝试走一遍
	for(int i=0;i<4;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
		if(legalposition_[sidetag_][xto][yto] & m_legalcharacter)//只考虑当前棋子本身在走法上能不能到达目的位置
        {
			if(targetman==0 && !IsKingKillKing(GetSelfKing(), xto, yto) /*&& !ExistPeopleKillKing(xto, yto)*/)
			{
				_temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
			}
			else if (targetman != 0 && (targetman / 32 != sidetag_) && !IsKingKillKing(GetSelfKing(), xto, yto) /*&& !ExistPeopleKillKing(xto, yto)*/)//吃掉对方棋子
			{
				_temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
			}
        }
	}
}

void King::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//******************
	//********2*********
	//******1*h*3*******
	//********4*********
	//******************
	//******************
	vector<Position> direction;
	direction.push_back(make_pair(+0,-1));
	direction.push_back(make_pair(-1,+0));
	direction.push_back(make_pair(+0,+1));
	direction.push_back(make_pair(+1,+0));
	//四个可能的方向
	for(int i=0;i<4;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
		//can arrive  to -> (xto,yto)
		if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
			if(targetman==0)
			{
				flex.push_back(2);
			}
			else if(targetman>>5!=sidetag_)
			{
				flex.push_back(chessmanvalue_[targetman]);
			}
			else if(targetman>>5==sidetag_)
			{
				flex.push_back(chessmanvalue_[targetman]>>2);
			}
	}
	//Kill the opposite king
	//小号棋子的将
	if(sidetag_==0)
	{
		for(int i=location_.first-1;i>=3;--i)
			//两将之间暂时探测出无棋子
			if(chessboard[i][location_.second]==0) continue;
			//其他棋子挡在两将之间
			else if(chessboard[i][location_.second]!=32) break;
			//目标位置为对方的将
			else
			{
				flex.push_back(2);
			}
	}
	//大号棋子的将
	else
	{
		for(int i=location_.first+1;i<=12;++i)
			if(chessboard[i][location_.second]==0) continue;
			else if(chessboard[i][location_.second]!=16) break;
			else
			{
				flex.push_back(2);
			}
	}
}

bool King::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}