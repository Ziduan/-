// chessDlg.h : 头文件
//

#pragma once
#include "chess_lib/chessplay.h"
#include<ctime>
#include <list>
#include<algorithm>
#include <map>
#include "afxwin.h"


// CchessDlg 对话框
class CchessDlg : public CDialog
{
// 构造
public:
	CchessDlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CchessDlg();
public:
	void LoadChessManBitMap(void);    
	void PaintChoose(CPoint point);
	void PaintChessboard(void);
	void PaintSourceChessMan(void);
	void PaintBack(void);
	void PaintChessman(void);
	void PaintOneChessman(const Position& p,int id);
	void PositionToMove(const Position& p, MoveOnce& m) const;
	IdType chessboard(const Position& p) const { return m_pChessObject->chessboard(p); };
	bool CheckPosition(Position p) const;
	OneStep GoAhead(const OneStep& m);
	void GoBack(void);
	CString PaintID(int id);
	//检查从当前位置是否可达目标位置(point)
	bool CanMoveTo(CPoint point) const;
	void PointToPosition(const CPoint& point, Position& p)const;
	OneStep KillSortAlfaBataSearch(void);
	void ButtonUp(UINT _nFlags, CPoint _point);
	void BaiZiButtonUp(UINT _nFlags, CPoint _point);
	void OutStatus(void);

private:
	void BaiZiPointToPosition(const CPoint& point, Position& p)const;
	bool BaiZiCanMoveTo(CPoint point) const;
	bool BaiZiCheckPosition(Position p) const;
	int BaiZiGetChessboard(const Position& p);
	void BaiZiGoAhead(const Position& _targetPosition, int _id);
	void InitSamePieceCount(void);
	
private:
  CPoint m_prePoint;
  //the only object contained the data of playing  chess
  CChessPlay* m_pChessObject;
  int m_depth;
  int m_evaluate;
  double m_duration;
  //棋盘
  CBitmap m_chessBoardBitmap;
  map<int,CBitmap*> m_pieceBitmap;
  bool m_isStarted;
  std::vector<std::vector<int> > m_baiZiSamePieceStart;
  //用来判断摆子的时候某个棋子是否已经拖动到了棋盘上，不允许重复（比如拖入第三个红车）
  std::vector<std::vector<int> > m_baiZiSamePieceCount;

private:
    CRect m_dlgRect;
	int m_chessManSize;
	CDC m_dcCompatible;

protected:
    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
	void InitDCInMemory(void);
    DECLARE_MESSAGE_MAP()
    enum { IDD = IDD_CHESS_DIALOG };
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonGoBack();
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonStart();
	CEdit m_editDepth;
	afx_msg void OnEnChangeEditDepth();
};