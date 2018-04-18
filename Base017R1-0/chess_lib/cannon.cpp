#include "cannon.h"
Cannon::Cannon(int sidetag,int value,const Position& newlocation)
	:ChessBase(sidetag,value,newlocation){
  m_legalcharacter=1;
//构造函数开始
//第90页红炮矩阵
  int positionvalue[16*16]= {
  //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
/*0 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*2 */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

/*3 */	0, 0, 0,125,130,100, 70, 60, 70,100,130,125, 0, 0, 0, 0,
/*4 */	0, 0, 0,110,125,100, 70, 60, 70,100,125,110, 0, 0, 0, 0,
/*5 */	0, 0, 0,100,120, 90, 80, 80, 80, 90,120,100, 0, 0, 0, 0,
/*6 */	0, 0, 0, 90,110, 90,110,130,110, 90,110, 90, 0, 0, 0, 0,
/*7 */	0, 0, 0, 90,110, 90,110,130,110, 90,110, 90, 0, 0, 0, 0,
/*8 */	0, 0, 0, 90,100, 90,110,130,110, 90,100, 90, 0, 0, 0, 0,
/*9 */	0, 0, 0, 90,100, 90, 90,110, 90, 90,100, 90, 0, 0, 0, 0,
/*10*/	0, 0, 0, 90,100, 80, 80, 70, 80, 80,100, 90, 0, 0, 0, 0,
/*11*/	0, 0, 0, 80, 90, 80, 70, 65, 70, 80, 90, 80, 0, 0, 0, 0,
/*12*/	0, 0, 0, 80, 90, 80, 70, 60, 70, 80, 90, 80, 0, 0, 0, 0,

/*13*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*14*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*15*/	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  this->InitMatrix(positionvalue);
//构造函数结束
}

Cannon::~Cannon(void) {
}

void Cannon::GetMove(const Matrix& chessboard,moves& temp) const
{
  //********2*********
  //********|*********
  //********2*********
  //********|*********
  //**1<-1<-h->3->3***
  //********|*********
  //********4*********
  //********|*********
  //********4*********
  vector<Position> direction;
  direction.push_back(make_pair(+0,-1));
  direction.push_back(make_pair(-1,+0));
  direction.push_back(make_pair(+0,+1));
  direction.push_back(make_pair(+1,+0));
  bool flag[4]={false,false,false,false};
  for(int i=0;i<4;i++)
    //每个方向最多前进9个位置
    for(int j=1;j<=9;j++) {
      int xto=location_.first+direction[i].first*j;
      int yto=location_.second+direction[i].second*j;
	  int targetman=chessboard[xto][yto];
      //目标位置在棋盘上
      if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
      {
        //未翻山
        if(flag[i]==false ) {
            //目标位置无棋子
            if(targetman==0)
			{
				  temp.push_back(make_pair(make_pair(location_,make_pair(xto,yto)),0));
				  continue;
            }
            //目标位置有棋子
            else
			{
				flag[i]=true;
				continue;
            }
        }
        //翻山之后
        else {
		  //目标位置无棋子
          if(targetman==0)
            continue;
		  //目标位置有对方棋子
          else if(targetman/32!=sidetag_)
		  {
            temp.push_back( make_pair(make_pair(location_,make_pair(xto,yto)),targetman));
		  }
          break;
        }
      }
      //出界，换另一个方向
      else break;
    }
}

void Cannon::GetValue(const Matrix& chessboard,Flex& flex) const
{
  //********2*********
  //********|*********
  //********2*********
  //********|*********
  //**1<-1<-h->3->3***
  //********|*********
  //********4*********
  //********|*********
  //********4*********
  vector<Position> direction;
  direction.push_back(make_pair(+0,-1));
  direction.push_back(make_pair(-1,+0));
  direction.push_back(make_pair(+0,+1));
  direction.push_back(make_pair(+1,+0));
  bool flag[4]={false,false,false,false};
  for(int i=0;i<4;i++)
    //每个方向最多前进9个位置
    for(int j=1;j<=9;j++) {
      int xto=location_.first+direction[i].first*j;
      int yto=location_.second+direction[i].second*j;
	  int targetman=chessboard[xto][yto];
      //目标位置在棋盘上
      if(this->legalposition_[sidetag_][xto][yto] & this->m_legalcharacter)
      {
        //未翻山
        if(flag[i]==false ) {
            //目标位置无棋子
            if(targetman==0)
			{
				  flex.push_back(2);
				  continue;
            }
            //目标位置有棋子
            else
			{
				//目标位置有棋子，且该棋子为对方将，则调用空头炮威胁分值
				if(targetman/32!=sidetag_ && targetman==32)
				{
					flex.push_back(HollowCannonThreat[location_.second-3]);
				}
				else if(targetman/32!=sidetag_ && targetman==16)
				{
					flex.push_back(HollowCannonThreat[12-location_.second]);
				}
				flag[i]=true;
				continue;
            }
        }
        //翻山之后
        else
		{
		  //目标位置无棋子
          if(targetman==0)
            continue;
		  //目标位置有对方棋子
          else if(targetman/32!=sidetag_)
		  {
			flex.push_back(chessmanvalue_[targetman]);
		  }
		  //目标位置有本方棋子，本方棋子受到保护，增加分值
		  else if(targetman/32==sidetag_)
		  {
			  //担子炮
			  if(targetman==41 ||targetman==42)
			  {
				  flex.push_back(20);
			  }
			  else
			  {
				 flex.push_back(chessmanvalue_[targetman]>>2);//  自己一方棋子价值除以2
			  }
		  }
          break;
        }
      }
      //出界，换另一个方向
      else break;
    }
}

bool Cannon::KillKing(const Matrix& chessboard, const Position& positionofking) const
{
	//cannon can kill king just there is only one chessman between the cannon and the king
	//*****************
	//*******c*********
	//*******1*********
	//***c*1*k*1*c*****
	//*******1*********
	//*******c*********
	//*****************
	//the cannon and the king in the same row or in the same col
	if(location_.first==positionofking.first)
	{
		int max=location_.second>positionofking.second?location_.second:positionofking.second;
		int min=location_.second<positionofking.second?location_.second:positionofking.second;
		int chessmanbetween=0;
		for(min+=1;min<max;++min)
			if(chessboard[location_.first][min]!=0)
				++chessmanbetween;
		if(chessmanbetween==1)
			return true;
		else
			return false;
	}
	else if(location_.second==positionofking.second)
	{
		int max=location_.first>positionofking.first?location_.first:positionofking.first;
		int min=location_.first<positionofking.first?location_.first:positionofking.first;
		int chessmanbetween=0;
		for(min+=1;min<max;++min)
			if(chessboard[location_.first][min]!=0)
				++chessmanbetween;
		if(chessmanbetween==1)
			return true;
		else
			return false;
	}
	else
		return false;
}