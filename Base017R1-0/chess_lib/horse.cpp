#include "horse.h"

Horse::Horse(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=1;
//构造函数开始

//第90页，红马矩阵
	int positionvalue[16*16]=
	{
	//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0, 70, 80, 90, 80, 70, 80, 90, 80, 70, 0, 0, 0, 0,
/*4 */	0, 0, 0, 80,110,125, 90, 70, 90,125,110, 80, 0, 0, 0, 0,
/*5 */	0, 0, 0, 90,100,120,125,120,125,120,100, 90, 0, 0, 0, 0,
/*6 */	0, 0, 0, 90,100,120,130,110,130,120,100, 90, 0, 0, 0, 0,
/*7 */	0, 0, 0, 90,110,110,120,100,120,110,110, 90, 0, 0, 0, 0,
/*8 */	0, 0, 0, 90,100,100,110,100,110,100,100, 90, 0, 0, 0, 0,
/*9 */	0, 0, 0, 80, 90,100,100, 90,100,100, 90, 80, 0, 0, 0, 0,
/*10*/	0, 0, 0, 80, 80, 90, 90, 80, 90, 90, 80, 80, 0, 0, 0, 0,
/*11*/	0, 0, 0, 70, 75, 75, 70, 50, 70, 75, 75, 70, 0, 0, 0, 0,
/*12*/	0, 0, 0, 60, 70, 75, 70, 60, 70, 75, 70, 60, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	this->InitMatrix(positionvalue);

//构造函数结束
}

Horse::~Horse(void)
{
}

void Horse::GetMove(const Matrix& chessboard, moves& temp) const
{
	//******************
	//*******1*2********
	//******3*0*4*******
	//*******0h0********
	//******5*0*6*******
	//*******7*8********
	//******************
	//要移动的向量
	vector<Position> direction;
	direction.push_back(make_pair(-2,-1));//1
	direction.push_back(make_pair(-2,+1));//2
	direction.push_back(make_pair(-1,-2));//3
	direction.push_back(make_pair(-1,+2));//4
	direction.push_back(make_pair(+1,-2));//5
	direction.push_back(make_pair(+1,+2));//6
	direction.push_back(make_pair(+2,-1));//7
	direction.push_back(make_pair(+2,+1));//8
	//马腿位置
	vector<Position> check;
	//check.reserve(8);
	check.push_back(make_pair(-1,0));//1
	check.push_back(make_pair(-1,0));//2
	check.push_back(make_pair(+0,-1));//3
	check.push_back(make_pair(+0,+1));//4
	check.push_back(make_pair(+0,-1));//5
	check.push_back(make_pair(+0,+1));//6
	check.push_back(make_pair(+1,0));//7
	check.push_back(make_pair(+1,0));//8

	//八个可行方向
	for(int i=0;i<8;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
			//如果下一位置在棋盘上
			if(legalposition_[sidetag_][xto][yto] & m_legalcharacter )
				//如果马腿位置无棋子
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

void Horse::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//*******1*2********
	//******3*0*4*******
	//*******0h0********
	//******5*0*6*******
	//*******7*8********
	//******************
	//要移动的向量
	vector<Position> direction;
	direction.push_back(make_pair(-2,-1));//1
	direction.push_back(make_pair(-2,+1));//2
	direction.push_back(make_pair(-1,-2));//3
	direction.push_back(make_pair(-1,+2));//4
	direction.push_back(make_pair(+1,-2));//5
	direction.push_back(make_pair(+1,+2));//6
	direction.push_back(make_pair(+2,-1));//7
	direction.push_back(make_pair(+2,+1));//8
	//马腿位置
	vector<Position> check;
	//check.reserve(8);
	check.push_back(make_pair(-1,0));//1
	check.push_back(make_pair(-1,0));//2
	check.push_back(make_pair(+0,-1));//3
	check.push_back(make_pair(+0,+1));//4
	check.push_back(make_pair(+0,-1));//5
	check.push_back(make_pair(+0,+1));//6
	check.push_back(make_pair(+1,0));//7
	check.push_back(make_pair(+1,0));//8

	//八个可行方向
	for(int i=0;i<8;i++)
	{
		int xto=location_.first+direction[i].first;
		int yto=location_.second+direction[i].second;
		int targetman=chessboard[xto][yto];
			//如果下一位置在棋盘上
			if(legalposition_[sidetag_][xto][yto] & m_legalcharacter )
				//如果马腿位置无棋子
				if(chessboard[location_.first+check[i].first][location_.second+check[i].second]==0)
					//如果目标位置无棋子
					if(targetman==0)
					{
						flex.push_back(5);
					}
					//如果目标位置为对方棋子
					else if(targetman/32!=sidetag_)
					{
						flex.push_back(chessmanvalue_[targetman]);
					}
					//目标位置为本方棋子，本方棋子受到保护，增加分值
					else if(targetman/32==sidetag_)
					{
						//连环马
						if(targetman==21 ||targetman==22)
						{
							flex.push_back(40);
						}
						else
						{
							flex.push_back(chessmanvalue_[targetman]>>2);//本方棋子价值的一半
						}
					}
	}
}

bool Horse::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}