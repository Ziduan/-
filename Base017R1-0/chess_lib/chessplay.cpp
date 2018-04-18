#include "chessplay.h"
#include<algorithm>
#include<vector>
#include <cassert>
using namespace std;

CChessPlay* CChessPlay::s_instance = nullptr;

CChessPlay* CChessPlay::Instance(void)
{
	if (s_instance == nullptr)
	{
		s_instance = new CChessPlay;
	}
	return s_instance;
}
void CChessPlay::ReleaseInstance(void)
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
CChessPlay* CCHESSPLAY(void)
{
	return CChessPlay::Instance();
}
CChessPlay::CChessPlay(void) 
{
	//构造计算机的棋子(大号棋子)
	g_chessman.assign(48,nullptr);
	g_chessman[39]=new Chariot(1,90,make_pair(3,3));
	g_chessman[40]=new Chariot(1,90,make_pair(3,11));
	//构造两个马
	g_chessman[37]=new Horse(1,40,make_pair(3,4));
	g_chessman[38]=new Horse(1,40,make_pair(3,10));
	////构造两个炮
	g_chessman[41]=new Cannon(1,45,make_pair(5,4));
	g_chessman[42]=new Cannon(1,45,make_pair(5,10));
	//构造将
	g_chessman[32]=new King(1,1000,make_pair(3,7));
	//构造两个士
	g_chessman[33]=new Official(1,20,make_pair(3,6));
	g_chessman[34]=new Official(1,20,make_pair(3,8));
	//构造两个相
	g_chessman[35]=new Minister(1,20,make_pair(3,5));
	g_chessman[36]=new Minister(1,20,make_pair(3,9));
	//////构造五个兵
	g_chessman[43]=new Soldier(1,10,make_pair(6,3 ));
	g_chessman[44]=new Soldier(1,10,make_pair(6,5 ));
	g_chessman[45]=new Soldier(1,10,make_pair(6,7 ));
	g_chessman[46]=new Soldier(1,10,make_pair(6,9 ));
	g_chessman[47]=new Soldier(1,10,make_pair(6,11));

	//构造小号棋子，在棋盘下方
	//构造将
	g_chessman[16]=new King(0,1000,make_pair(12,7));
	//构造两个士
	g_chessman[17]=new Official(0,20,make_pair(12,6));
	g_chessman[18]=new Official(0,20,make_pair(12,8));
	//构造两个相
	g_chessman[19]=new Minister(0,20,make_pair(12,5));
	g_chessman[20]=new Minister(0,20,make_pair(12,9));
	//构造两个马
	g_chessman[21]=new Horse(0,40,make_pair(12,4));
	g_chessman[22]=new Horse(0,40,make_pair(12,10));
	//构造两个车
	g_chessman[23]=new Chariot(0,90,make_pair(12,3));
	g_chessman[24]=new Chariot(0,90,make_pair(12,11));
	//构造两个炮
	g_chessman[25]=new Cannon(0,45,make_pair(10,4));
	g_chessman[26]=new Cannon(0,45,make_pair(10,10));
	////构造五个兵
	g_chessman[27]=new Soldier(0,10,make_pair(9,3 ));
	g_chessman[28]=new Soldier(0,10,make_pair(9,5 ));
	g_chessman[29]=new Soldier(0,10,make_pair(9,7 ));
	g_chessman[30]=new Soldier(0,10,make_pair(9,9 ));
	g_chessman[31]=new Soldier(0,10,make_pair(9,11));
}
CChessPlay::~CChessPlay(void)
{
  for(vector<ChessBase*>::size_type i=0;i<g_chessman.size();++i)
    delete g_chessman[i];
}
void CChessPlay::Init(void)
{
	g_chessman[39]->set_location(make_pair(3,3));
	g_chessman[40]->set_location(make_pair(3,11));
	//构造两个马
	g_chessman[37]->set_location(make_pair(3,4));
	g_chessman[38]->set_location(make_pair(3,10));
	////构造两个炮
	g_chessman[41]->set_location(make_pair(5,4));
	g_chessman[42]->set_location(make_pair(5,10));
	//构造将
	g_chessman[32]->set_location(make_pair(3,7));
	//构造两个士
	g_chessman[33]->set_location(make_pair(3,6));
	g_chessman[34]->set_location(make_pair(3,8));
	//构造两个相
	g_chessman[35]->set_location(make_pair(3,5));
	g_chessman[36]->set_location(make_pair(3,9));
	//////构造五个兵
	g_chessman[43]->set_location(make_pair(6,3 ));
	g_chessman[44]->set_location(make_pair(6,5 ));
	g_chessman[45]->set_location(make_pair(6,7 ));
	g_chessman[46]->set_location(make_pair(6,9 ));
	g_chessman[47]->set_location(make_pair(6,11));

	//构造小号棋子，在棋盘下方
	//构造将
	g_chessman[16]->set_location(make_pair(12,7));
	//构造两个士
	g_chessman[17]->set_location(make_pair(12,6));
	g_chessman[18]->set_location(make_pair(12,8));
	//构造两个相
	g_chessman[19]->set_location(make_pair(12,5));
	g_chessman[20]->set_location(make_pair(12,9));
	//构造两个马
	g_chessman[21]->set_location(make_pair(12,4));
	g_chessman[22]->set_location(make_pair(12,10));
	//构造两个车
	g_chessman[23]->set_location(make_pair(12,3));
	g_chessman[24]->set_location(make_pair(12,11));
	//构造两个炮
	g_chessman[25]->set_location(make_pair(10,4));
	g_chessman[26]->set_location(make_pair(10,10));
	////构造五个兵
	g_chessman[27]->set_location(make_pair(9,3 ));
	g_chessman[28]->set_location(make_pair(9,5 ));
	g_chessman[29]->set_location(make_pair(9,7 ));
	g_chessman[30]->set_location(make_pair(9,9 ));
	g_chessman[31]->set_location(make_pair(9,11));

    //构造棋盘数组
    //All zeros in g_chessboard[i][j] = id at begin
    g_chessboard.clear();
    vector<int> tempLine(16,0);
    for(int i=0;i<16;++i)
	{
        g_chessboard.push_back(tempLine);
	}
    for(int i=16;i<=47;i++)
    {    
		int x = g_chessman[i]->location().first;
		int y = g_chessman[i]->location().second;
		g_chessboard[x][y]=i;
		g_chessman[i]->SetAlive(true);
	}
	//初始化合法位置
    ChessBase::InitLegalPosition();
}
void CChessPlay::ClearChessMan(void)
{
	for (size_t i = 16; i <= 47; ++i)
	{
		g_chessman[i]->SetAlive(false);
	}
}
void CChessPlay::ClearChessBoard(void)
{
	for (size_t i =3;i <= 12;++i)
	{
		for (size_t j=3;j <= 11;++j)
		{
			g_chessboard[i][j] = 0;
		}
	}
}
IdType CChessPlay::chessboard(const Position& p) const
{
    return g_chessboard[p.first][p.second];
}
void CChessPlay::SetChessBoard(const Position& p, int _id)
{
	if (g_chessboard[p.first][p.second] != 0)
	{
		int oldId = g_chessboard[p.first][p.second];
		g_chessman[oldId]->SetAlive(false);
	}
	g_chessboard[p.first][p.second] = _id;
	g_chessman[_id]->SetAlive(true);
	g_chessman[_id]->set_location(p);
}

int CChessPlay::EvaluateSmall(void)
{
	//位置价值+棋子价值
	int smallvalue=0;
	for(vector<ChessBase*>::size_type i=16;i<=31;++i)
		if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
			smallvalue+=g_chessman[i]->ContributeValue();
	//保护价值+威胁价值
	Flex flexsmall;
	GetValueSmallMan(flexsmall);
	for(Flex::size_type i=0;i<flexsmall.size();i++)
	{
		smallvalue+=flexsmall[i];
	}
	return smallvalue;
}
int CChessPlay::EvaluateBig(void)
{
	//位置价值+棋子价值
	int bigvalue=0;
    for(vector<ChessBase*>::size_type i=32;i<=47;++i)
		if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
			bigvalue+=g_chessman[i]->ContributeValue();
	//保护价值+威胁价值
	Flex flexbig;
	GetValueBigMan(flexbig);
	for(Flex::size_type i=0;i<flexbig.size();i++)
	{
		bigvalue+=flexbig[i];
	}
	return bigvalue;
}

int CChessPlay::Evaluate(void)
{
	return EvaluateSmall()-EvaluateBig();
}
//根据m所指示的一个走法，走子，改变棋盘数组和棋子数组，并返回这个走法对应的走子
OneStep CChessPlay::GoAhead(const OneStep& m) 
{
  //获取起点棋子和终点棋子
	int id_from = g_chessboard[m.first.first.first][m.first.first.second];   //起点棋子的坐标
	int id_to = g_chessboard[m.first.second.first][m.first.second.second];   //终点棋子的坐标
    assert(id_from != 0);
    g_chessboard[m.first.first.first][m.first.first.second] = 0;
    g_chessboard[m.first.second.first][m.first.second.second] = id_from;
    g_chessman[id_from]->set_location(m.first.second);

    if(id_to != 0) 
    {
        g_chessman[id_to]->SetAlive(false);
    }
  return m;
}
void CChessPlay::GoBack(const OneStep& one) 
{
    Position fromLocation=one.first.first,
           toLocation=one.first.second;
    //修改移动棋子
    int idHaveToBack = g_chessboard[toLocation.first][toLocation.second]; 
    assert(idHaveToBack != 0);
    assert(g_chessboard[fromLocation.first][fromLocation.second] == 0);
    g_chessboard[fromLocation.first][fromLocation.second] = idHaveToBack;
    g_chessman[idHaveToBack]->set_location(fromLocation);
    //修改被吃棋子
    int idBeKilled = one.second;
    g_chessboard[toLocation.first][toLocation.second] = idBeKilled;
    if(idBeKilled != 0) 
    {
        g_chessman[idBeKilled]->SetAlive(true);
    }
}

//生成小号棋子的全部走法
void CChessPlay::GetMoveSmallMan(moves& m){
  for(vector<ChessBase*>::size_type i=16;i<=31;++i)
     if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
        g_chessman[i]->GetMove(g_chessboard,m);
}
//生成(电脑的)大号棋子的全部走法
void CChessPlay::GetMoveBigMan(moves& m)
{
    for(vector<ChessBase*>::size_type i=32;i<=47;++i)
    {
        if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
	    {
		    g_chessman[i]->GetMove(g_chessboard,m);
	    }
    }
}

//生成小号棋子的全部价值
void CChessPlay::GetValueSmallMan(Flex& flex)
{
	for(vector<ChessBase*>::size_type i=16;i<=31;++i)
     if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
        g_chessman[i]->GetValue(g_chessboard,flex);
}
//生成大号棋子的全部价值
void CChessPlay::GetValueBigMan(Flex& flex)
{
  for(vector<ChessBase*>::size_type i=32;i<=47;++i)
    if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
      g_chessman[i]->GetValue(g_chessboard,flex);
}

void CChessPlay::GetMoveOneMan(int id, moves& m) const
{
	g_chessman[id]->GetMove(g_chessboard,m);
}

vector<Position> CChessPlay::AliveMan(void) {
  vector<Position> aliveman;
  for(vector<ChessBase*>::size_type i=16;i<=47;++i)
    if(g_chessman[i]!=(ChessBase*)0 && g_chessman[i]->Alive())
      aliveman.push_back(g_chessman[i]->location());
  return aliveman;
}

//baseMin代表上层已经找到的局面最小值,而上层要的就是最小值
//MaxSearch要的是最大值,只要找到了一个最大值比上层的baseMin大,就退出
int CChessPlay::KillSortAlfaBataMaxSearch(int depth,int baseMin)
{
  int max=-10000,tempMax=-baseMin;
  moves m;
  if(depth==0)
  {
	//如果是吃子走法，则调用静态搜索，直至局面静止
	if(flag==1)
	{
		val=Evaluate();
		return QuiesMinSearch(-10000,10000);
	}
	//如果局面已经静止(到达此局面的上一步没有吃子)，则直接返回局面值
	else
	{
		return Evaluate();
	}
  }
  GetMoveSmallMan(m);
  //吃子走法优先走
  sort(m.begin(),m.end(),good_step);

  for(moves::size_type i=0;i<m.size();++i)
  {
    GoAhead(m[i]);
	flag=m[i].second;//如果是个吃子走法
    tempMax=KillSortAlfaBataMinSearch(depth-1,tempMax);
	if(tempMax>baseMin)
	{
		max=tempMax;
		GoBack(m[i]);
		break;
	}
	else if(tempMax>max)
		max=tempMax;
	GoBack(m[i]);
  }
  return max;
}
int CChessPlay::KillSortAlfaBataMinSearch(int depth,int base)
{
  int Min=10000,tempMin=-base;
  moves m,s;
  if(depth==0)
  {
	//如果是吃子走法，则调用静态搜索，直至局面静止
	if(flag==1)
	{
		m_evaluate=Evaluate();
		val=m_evaluate;
		m_evaluate=QuiesMaxSearch(-10000,10000);
		return m_evaluate;
	}
	//如果局面已经静止，则直接返回局面值
	else
	{
		m_evaluate=Evaluate();
		return m_evaluate;
	}
  }
  GetMoveBigMan(m);
  //吃子走法优先走
  sort(m.begin(),m.end(),good_step);

  for(moves::size_type i=0;i<m.size();i++)
  {
    GoAhead(m[i]);
	flag=m[i].second;
    tempMin=KillSortAlfaBataMaxSearch(depth-1,tempMin);
    if(tempMin<base)
	{
		Min=tempMin;
		GoBack(m[i]);
		break;
	}
	else if(tempMin<Min)
		Min=tempMin;
	GoBack(m[i]);
  }
  return Min;
}
//计算机走棋,找到一个min局面
OneStep CChessPlay::KillSortAlfaBataSearch(int depth)
{
  int Min=10000,base=10000,tempMin;
  tempMin=base;
  moves m;
  GetMoveBigMan(m);
  //吃子走法优先走
  sort(m.begin(),m.end(),good_step);
  int beststep=0;

  for(moves::size_type i=0;i<m.size();i++)
  {
    GoAhead(m[i]);
	//用已经找到的最小值更新接下来的搜索,使得搜索窗口缩小,更容易发生剪枝
    tempMin=KillSortAlfaBataMaxSearch(depth-1,tempMin);
    if(tempMin<Min)
    {
        Min=tempMin;
        beststep=i;
    }
    GoBack(m[i]);
  }
  return std::move(m[beststep]);
}

int CChessPlay::QuiesMinSearch(int alpha,int beta)
{
	if(val<alpha)
	{
		return val;
	}
	if(val<beta)
	{
		beta=val;
	}
	moves m;
	GetMoveBigMan(m);
	sort(m.begin(),m.end(),good_step);
	for(moves::size_type i=0;i<m.size();i++)
	{
		GoAhead(m[i]);
		if(m[i].second==1)
		{
			val=Evaluate();
			val=QuiesMaxSearch(alpha,beta);
			GoBack(m[i]);
			if(val<alpha)
			{
				return beta;
			}
			if(val<beta)
			{
				beta=val;
			}
		}
		else
		{
			GoBack(m[i]);
		}
	}
	return beta;
}

int CChessPlay::QuiesMaxSearch(int alpha,int beta)
{
	if(val>=beta)
	{
		return beta;
	}
	if(val>alpha)
	{
		alpha=val;
	}
	moves m;
	GetMoveSmallMan(m);
	sort(m.begin(),m.end(),good_step);
	for(moves::size_type i=0;i<m.size();i++)
	{
		GoAhead(m[i]);
		if(m[i].second==1)
		{
			val=Evaluate();
			val=QuiesMinSearch(alpha,beta);
			GoBack(m[i]);
			if(val>=beta)
			{
				return beta;
			}
			if(val>alpha)
			{
				alpha=val;
			}
		}
		else
		{
			GoBack(m[i]);
		}
	}
	return alpha;
}

void CChessPlay::SaveSituation(const std::string& _fullPathFile) const
{
	ofstream fout;
	fout.open(_fullPathFile);
	for (int i=16;i<48;i++)
	{
		if (g_chessman[i]->Alive())
		{
			fout<<i<<" "
				<<g_chessman[i]->location().first<<" "
				<<g_chessman[i]->location().second<<endl;
		}
	}
}
void CChessPlay::ReadSituation(const std::string& _fullPathFile)
{
	ifstream fin;
	fin.open(_fullPathFile);
	vector<vector<int> > onesituation;
	while (fin)
	{
		int id,x,y;
		vector<int> oneman;
		fin>>id>>x>>y;
		oneman.push_back(id);
		oneman.push_back(x);
		oneman.push_back(y);
		onesituation.push_back(oneman);
	}
	fin.close();
	//清空棋盘
	for (int i=3;i<=12;i++)
	{
		for (int j=3;j<=11;j++)
		{
			g_chessboard[i][j]=0;
		}
	}
	//修改棋子
	for (int i=16;i<48;i++)
	{
		g_chessman[i]->SetAlive(false);
	}
	for (auto itr = onesituation.begin(); itr != onesituation.end(); itr++)
	{
		g_chessman[(*itr)[0]]->SetAlive(true);
		g_chessman[(*itr)[0]]->set_location(make_pair((*itr)[1], (*itr)[2]));
		g_chessboard[(*itr)[1]][(*itr)[2]] = (*itr)[0];
	}
}
void CChessPlay::OutStatus(ostream& os)
{
    os<<"chessboard:\n";
    for (size_t i =3;i <= 12;++i)
    {
        for (size_t j=3;j <= 11;++j)
        {
            os<<std::setw(2)<<g_chessboard[i][j]<<" ";
        }
        os<<"\n";
    }
    os<<"\n";
    os<<"chess man:\n";
    for (size_t i = 16 ;i < g_chessman.size(); ++i)
    {
        os<<std::setw(2)<<i<<" ";
    }
    os<<"\n";
    for (size_t i = 16;i < g_chessman.size(); ++i)
    {
            bool alive = g_chessman[i]->Alive() ? true : false;
            os<<std::setw(2)<<alive<<" ";
    }
    os<<"\n";

}
OneStep CChessPlay::GoAheadAndRecordHistory(const OneStep& _oneStep)
{
    GoAhead(_oneStep);
    m_moveHistory.push_back(_oneStep);

    return _oneStep;
}
void CChessPlay::GoBackAndRemoveHistory(void)
{
    if (!IsMoveHistoryEmpty())
    {
        GoBack(m_moveHistory.back());
        m_moveHistory.pop_back();

        GoBack(m_moveHistory.back());
        m_moveHistory.pop_back();
    }
}
bool CChessPlay::IsUserCanMoveTo(const OneStep& _oneStep) const
{
	//获取所有可能的走法
	auto from = _oneStep.first.first;
	moves m;
	GetMoveOneMan(chessboard(from), m);
	auto iter = find(m.begin(), m.end(), _oneStep);
	if (iter != m.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
