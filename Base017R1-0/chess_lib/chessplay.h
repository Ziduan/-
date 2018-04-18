#pragma once

#ifdef CHESS_LIB_EXPORTS  
#define CHESS_LIB_API __declspec(dllexport)   
#else  
#define CHESS_LIB_API __declspec(dllimport)   
#endif 

#include <fstream>
#include"chessbase.h"
#include"cannon.h"
#include"chariot.h"
#include"horse.h"
#include"king.h"
#include"minister.h"
#include"official.h"
#include"soldier.h"
#include "global.h"

using namespace std;

class CHESS_LIB_API CChessPlay
{
public:
	//向外部提供非线程安全的单例
	static CChessPlay* Instance(void);
	static void ReleaseInstance(void);
	~CChessPlay(void);

public:
    void Init(void);
	void ClearChessBoard(void);
	void ClearChessMan(void);
	void ReadSituation(const std::string& _fullPathFile);
	void SaveSituation(const std::string& _fullPathFile) const;
	vector<Position> AliveMan(void);
	bool IsUserCanMoveTo(const OneStep& _oneStep) const;
	IdType chessboard(const Position& p) const;
	int GetChessBoard(const Position& p) const;
	void SetChessBoard(const Position& p, int _id);
	//杀法优先的Alfa-Bata搜索
	int KillSortAlfaBataMaxSearch(int depth,int base);
	int KillSortAlfaBataMinSearch(int depth,int base);
	OneStep KillSortAlfaBataSearch(int depth);
	// 获取当前棋子id的所有走法
	void GetMoveOneMan(int id, moves& m) const;
    
    OneStep GoAhead(const OneStep&);
    void GoBack(const OneStep&);
    bool IsMoveHistoryEmpty(void) const { return (m_moveHistory.size() == 0);}

    OneStep GoAheadAndRecordHistory(const OneStep& );
    void GoBackAndRemoveHistory(void);

    void OutStatus(ostream& os);

private:
	CChessPlay(void);
	void GetMoveSmallMan(moves& m);
	void GetMoveBigMan(moves& m);
	void GetValueSmallMan(Flex& flex);
	void GetValueBigMan(Flex& flex);
	//静态搜索算法
	int QuiesMinSearch(int alpha,int beta);
	int QuiesMaxSearch(int alpha,int beta);
	int Quies(int alpha,int beta);
	int EvaluateBig();
	int EvaluateSmall();
	int Evaluate();

private:
    int m_evaluate;
	int val;
	//判断是否为吃子走法
	int flag;
    list<OneStep> m_moveHistory;
	
private:
	static CChessPlay* s_instance;
};

extern "C" CHESS_LIB_API CChessPlay* CCHESSPLAY(void);