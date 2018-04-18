#include "chariot.h"
//车
Chariot::Chariot(int sidetag,int value,const Position& newlocation)
:ChessBase(sidetag,value,newlocation)
{
	m_legalcharacter=1;
//构造函数开始

//第90页红车矩阵
	int positionvalue[16*16]=
	{
	//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0,160,170,160,150,150,150,160,170,160, 0, 0, 0, 0,
/*4 */	0, 0, 0,170,180,170,190,250,190,170,180,170, 0, 0, 0, 0,
/*5 */	0, 0, 0,170,190,200,220,240,220,200,190,170, 0, 0, 0, 0,
/*6 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*7 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*8 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*9 */	0, 0, 0,170,190,180,220,240,220,180,190,170, 0, 0, 0, 0,
/*10*/	0, 0, 0,170,180,170,170,160,170,170,180,170, 0, 0, 0, 0,
/*11*/	0, 0, 0,160,170,160,160,150,160,160,170,160, 0, 0, 0, 0,
/*12*/	0, 0, 0,150,160,150,160,150,160,150,160,150, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	int m_positionvalue[16*16]=
	{
	//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0,160,170,160,150,150,150,160,170,160, 0, 0, 0, 0,
/*4 */	0, 0, 0,170,180,170,190,250,190,170,180,170, 0, 0, 0, 0,
/*5 */	0, 0, 0,170,190,200,220,240,220,200,190,170, 0, 0, 0, 0,
/*6 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*7 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*8 */	0, 0, 0,180,220,210,240,250,240,210,220,180, 0, 0, 0, 0,
/*9 */	0, 0, 0,170,190,180,220,240,220,180,190,170, 0, 0, 0, 0,
/*10*/	0, 0, 0,170,180,170,170,160,170,170,180,170, 0, 0, 0, 0,
/*11*/	0, 0, 0,160,170,160,160,150,160,160,170,160, 0, 0, 0, 0,
/*12*/	0, 0, 0,150,160,150,160,150,160,150,160,150, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	this->InitMatrix(positionvalue);

//构造函数结束
}

Chariot::~Chariot(void)
{
}

void Chariot::GetMove(const Matrix& chessboard, moves& temp) const
{
	//******************
	//********2*********
	//********|*********
	//*****1<-h->3******
	//********|*********
	//********4*********
	//******************
	//四个方向
	vector<Position> direction;
	direction.push_back(make_pair(+0,-1));
	direction.push_back(make_pair(-1,+0));
	direction.push_back(make_pair(+0,+1));
	direction.push_back(make_pair(+1,+0));
	for(int i=0;i<4;i++)
		//每个方向最多前进9个位置
		for(int j=1;j<=9;j++)
		{
			int xto=location_.first+direction[i].first*j;
			int yto=location_.second+direction[i].second*j;
			int targetman=chessboard[xto][yto];
			//目标位置在棋盘上
			if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
			{
				//目标位置无棋子
				if(targetman==0)
				{
					temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
					//temp.push_back(make_pair(location_,make_pair(xto,yto)));
					continue;
				}
				//目标位置为对方棋子
				else if(targetman/32!=sidetag_)
				{
					temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
					//temp.push_back(make_pair(location_,make_pair(xto,yto)));
					break;
				}
				else break;
			}
			//出界，换另一个方向
			else break;
		}
}

void Chariot::GetValue(const Matrix& chessboard,Flex& flex) const
{
	//******************
	//********2*********
	//********|*********
	//*****1<-h->3******
	//********|*********
	//********4*********
	//******************
	//四个方向
	vector<Position> direction;
	direction.push_back(make_pair(+0,-1));
	direction.push_back(make_pair(-1,+0));
	direction.push_back(make_pair(+0,+1));
	direction.push_back(make_pair(+1,+0));
	for(int i=0;i<4;i++)
		//每个方向最多前进9个位置
		for(int j=1;j<=9;j++)
		{
			int xto=location_.first+direction[i].first*j;
			int yto=location_.second+direction[i].second*j;
			int targetman=chessboard[xto][yto];
			//目标位置在棋盘上
			if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
			{
				//目标位置无棋子
				if(targetman==0)
				{
					flex.push_back(4);
					continue;
				}
				//目标位置为对方棋子
				else if(targetman>>5!=sidetag_)
				{
					flex.push_back(chessmanvalue_[targetman]);
					break;
				}
				//目标位置为本方棋子，本方棋子受到保护，增加分值
				else if(targetman>>5==sidetag_)
				{
					flex.push_back(chessmanvalue_[targetman]>>2);//本方棋子价值的一半
					break;
				}
				else break;
			}
			//出界，换另一个方向
			else break;
		}
}

bool Chariot::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	return false;
}