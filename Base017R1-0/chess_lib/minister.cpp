#include "minister.h"

Minister::Minister(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=16;
//构造函数开始

//第89页红相矩阵
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
/*8 */	0, 0, 0, 0, 0, 25, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0,
/*9 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*10*/	0, 0, 0, 20, 0, 0, 0, 35, 0, 0, 0, 20, 0, 0, 0, 0,
/*11*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*12*/	0, 0, 0, 0, 0, 30, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	this->InitMatrix(positionvalue);

//构造函数结束
}

Minister::~Minister(void)
{
}

void Minister::GetMove(const Matrix& chessboard, moves& temp) const
{
	//******************
	//******************
	//***1*******2******
	//*****0***0********
	//*******m**********
	//*****0***0********
	//***3*******4******
	//******************
	//要移动的向量
	vector<Position> direction;
	direction.push_back(make_pair(-2,-2));//1
	direction.push_back(make_pair(-2,+2));//2
	direction.push_back(make_pair(+2,-2));//3
	direction.push_back(make_pair(+2,+2));//4
	vector<Position> check;
	check.push_back(make_pair(-1,-1));
	check.push_back(make_pair(-1,+1));
	check.push_back(make_pair(+1,-1));
	check.push_back(make_pair(+1,+1));
	for(int i=0;i<4;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
		//如果下一位置在棋盘上
		if(legalposition_[sidetag_][xto][yto] & m_legalcharacter )
			//如果相眼位置无棋子
			if(chessboard[location_.first+check[i].first][location_.second+check[i].second]==0)
			//如果目标位置无本方棋子
				if(targetman==0)
				{
					temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
					//temp.push_back(make_pair(location_,make_pair(xto,yto)));
				}
				else if(targetman/32!=sidetag_)
				{
					temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
				}
	}
}

void Minister::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//******************
	//***1*******2******
	//*****0***0********
	//*******m**********
	//*****0***0********
	//***3*******4******
	//******************
	//要移动的向量
	vector<Position> direction;
	direction.push_back(make_pair(-2,-2));//1
	direction.push_back(make_pair(-2,+2));//2
	direction.push_back(make_pair(+2,-2));//3
	direction.push_back(make_pair(+2,+2));//4
	vector<Position> check;
	check.push_back(make_pair(-1,-1));
	check.push_back(make_pair(-1,+1));
	check.push_back(make_pair(+1,-1));
	check.push_back(make_pair(+1,+1));
	for(int i=0;i<4;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
		//如果下一位置在棋盘上
		if(legalposition_[sidetag_][xto][yto] & m_legalcharacter )
			//如果相眼位置无棋子
			if(chessboard[location_.first+check[i].first][location_.second+check[i].second]==0)
			    //如果目标位置无棋子
				if(targetman==0)
				{
					flex.push_back(2);
				}
				//目标位置为对方棋子
				else if(targetman>>5!=sidetag_)
				{
					flex.push_back(this->chessmanvalue_[targetman]);
				}
				//目标位置为本方棋子
				else if(targetman/32==sidetag_)
				{
					flex.push_back(this->chessmanvalue_[targetman]>>2);
				}
	}
}

bool Minister::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}