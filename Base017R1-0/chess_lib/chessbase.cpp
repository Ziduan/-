#include "chessbase.h"

vector<Matrix> ChessBase::legalposition_;

const IdType ChessBase::m_bigKingId = 32;

const IdType ChessBase::m_smallKingId = 16;

int ChessBase::chessmanvalue_[48]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0-15
	30,20,20,20,20,40,40,90,90,45,45,10,10,10,10,10,//16-31
	30,20,20,20,20,40,40,90,90,45,45,10,10,10,10,10,//32-48
};
ChessBase::ChessBase(int sidetag,int value,const Position& newlocation)
  :sidetag_(sidetag),value_(value),location_(newlocation),alive_(true) {
	//大号棋子1,小号棋子0
}

ChessBase::~ChessBase(void)
{
}

void ChessBase::GetMove(const Matrix& _chessboard,moves& temp) const
{
}

void ChessBase::GetValue(const Matrix& _chessboard,Flex& flex)const
{
}
IdType ChessBase::GetSelfKing(void) const
{
	return	sidetag_ == 1 ? m_bigKingId : m_smallKingId;
}
// 供派生类构造函数使用，实现位置价值数组的初始化
void ChessBase::InitMatrix(int* begin)
{
	//positionvalue_.reserve(256);
	//假设输入的价值数组所对应的棋子在棋盘的下方(开局时)
	vector<int> tempLine;

	if(sidetag_==0)//小号棋子在棋盘下方
		for(int i=0;i<16;++i)
		{
			tempLine.assign(begin+i*16,begin+(i+1)*16);															//	将区间[first, last)的元素赋值到当前的vector容器中，或者赋n个值为x的元素到vector容器中，这个容器会清除掉vector容器中以前的内容。
			positionvalue_.push_back(tempLine);
			tempLine.clear();																					//	清空临时容器
		}
	else if(sidetag_==1)//大号棋子在棋盘上方
		for(int i=15;i>=0;--i)
		{
			tempLine.assign(begin+i*16,begin+(i+1)*16);
			positionvalue_.push_back(tempLine);
			tempLine.clear();
		}
	else cout<<"invalid sidetag"<<this->sidetag_<<endl;
}

void ChessBase::InitLegalPosition(void)
{
	//初始化合法位置数组
	int legalPosition[256]=
	{
		//默认为大号棋子的合法位置
	//	0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //0
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //1
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //2
		0, 0, 0, 1, 1, 17,7, 3, 7, 17,1, 1, 0, 0, 0, 0,  //3
		0, 0, 0, 1, 1, 1, 3, 7, 3, 1, 1, 1, 0, 0, 0, 0,  //4
		0, 0, 0, 17,1, 1, 7, 19,7, 1, 1, 17,0, 0, 0, 0,   //5
		0, 0, 0, 9, 1, 9, 1, 9, 1, 9, 1, 9, 0, 0, 0, 0,   //6
		0, 0, 0, 9, 1, 25,1, 9, 1, 25,1, 9, 0, 0, 0, 0,  //7
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,  //8
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,  //9
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,  //10
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,  //11
		0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0,  //12
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //13
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //14
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //15
	};
	vector<int> tempLine;
	Matrix redlegalposition,blacklegalposition;
	//先放小号棋子legalposition[0]
	for(int i=15;i>=0;--i)
	{
		tempLine.assign(legalPosition+i*16,legalPosition+(i+1)*16);
		blacklegalposition.push_back(tempLine);
		tempLine.clear();
	}
	legalposition_.push_back(blacklegalposition);
	//再放大号棋子legalposition[1]
	for(int i=0;i<16;++i)
	{
		tempLine.assign(legalPosition+i*16,legalPosition+(i+1)*16);
		redlegalposition.push_back(tempLine);
		tempLine.clear();
	}
	legalposition_.push_back(redlegalposition);
}