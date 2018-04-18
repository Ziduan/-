// chessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "chess.h"
#include "chessDlg.h"
#include <fstream>
#include <sstream>
#include <array>
#include <cassert>

#include "chess_lib/global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CchessDlg 对话框
CchessDlg::CchessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CchessDlg::IDD, pParent)
{
    m_prePoint.x=0;
    m_prePoint.y=0;
    m_evaluate = 0;
    m_depth = 1;
    m_duration=0;
	m_pChessObject = CCHESSPLAY();//第一次初始化成员指针的时候创建ChessPlay对象
}
CchessDlg::~CchessDlg()
{
    for (auto itr = m_pieceBitmap.begin(); itr != m_pieceBitmap.end(); ++itr)
    {
       delete itr->second;
       itr->second = nullptr;
    }
	CCHESSPLAY()->ReleaseInstance();
}
void CchessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_duration);
	DDX_Control(pDX, IDC_EDIT_DEPTH, m_editDepth);
}
BEGIN_MESSAGE_MAP(CchessDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CchessDlg::OnBnClickedOk)
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_BN_CLICKED(IDC_BUTTON_GO_BACK, &CchessDlg::OnBnClickedButtonGoBack)
    ON_BN_CLICKED(IDC_BUTTON_NEW, &CchessDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_START, &CchessDlg::OnBnClickedButtonStart)
	ON_EN_CHANGE(IDC_EDIT_DEPTH, &CchessDlg::OnEnChangeEditDepth)
END_MESSAGE_MAP()
void CchessDlg::LoadChessManBitMap(void)
{
	size_t IDB;
	for (size_t id = 16 ; id <= 47; ++id)
	{
		switch(id) {
			//将
		case 16: IDB = IDB_BITMAP_RED_JIANG; break;
		case 32: IDB = IDB_BITMAP_BLACK_JIANG;   break;
			//士
		case 17: IDB = IDB_BITMAP_RED_SHI;  break;
		case 18: IDB = IDB_BITMAP_RED_SHI;  break;
		case 33: IDB = IDB_BITMAP_BLACK_SHI;  break;
		case 34: IDB = IDB_BITMAP_BLACK_SHI;  break;
			//象
		case 19: IDB = IDB_BITMAP_RED_XIANG;  break;
		case 20: IDB = IDB_BITMAP_RED_XIANG;  break;
		case 35: IDB = IDB_BITMAP_BLACK_XIANG;  break;
		case 36: IDB = IDB_BITMAP_BLACK_XIANG;  break;
			//马
		case 21: IDB = IDB_BITMAP_RED_HORSE;  break;
		case 22: IDB = IDB_BITMAP_RED_HORSE;  break;
		case 37: IDB = IDB_BITMAP_BLACK_HORSE;  break;
		case 38: IDB = IDB_BITMAP_BLACK_HORSE;  break;
			//车
		case 23: IDB = IDB_BITMAP_RED_CHE;  break;
		case 24: IDB = IDB_BITMAP_RED_CHE;  break;
		case 39: IDB = IDB_BITMAP_BLACK_CHE;  break;
		case 40: IDB = IDB_BITMAP_BLACK_CHE;  break;
			//炮
		case 25: IDB = IDB_BITMAP_RED_PAO;  break;
		case 26: IDB = IDB_BITMAP_RED_PAO;  break;
		case 41: IDB = IDB_BITMAP_BLACK_PAO;  break;
		case 42: IDB = IDB_BITMAP_BLACK_PAO;  break;
		case 27: IDB = IDB_BITMAP_RED_BING;  break;
		case 28: IDB = IDB_BITMAP_RED_BING;  break;
		case 29: IDB = IDB_BITMAP_RED_BING;  break;
		case 30: IDB = IDB_BITMAP_RED_BING;  break;
		case 31: IDB = IDB_BITMAP_RED_BING;  break;
		case 43: IDB = IDB_BITMAP_BLACK_BING;  break;
		case 44: IDB = IDB_BITMAP_BLACK_BING;  break;
		case 45: IDB = IDB_BITMAP_BLACK_BING;  break;
		case 46: IDB = IDB_BITMAP_BLACK_BING;  break;
		case 47: IDB = IDB_BITMAP_BLACK_BING;  break;
		default:  IDB = NULL;  break;
		}

		if (m_pieceBitmap.find(id) == m_pieceBitmap.end())
		{
			CBitmap* pBitmapSource = new CBitmap;
			m_pieceBitmap.insert(make_pair(id,pBitmapSource));
			m_pieceBitmap[id]->LoadBitmap(IDB);
		}
	}
}
void CchessDlg::InitSamePieceCount(void)
{
	std::vector<int> temp;
	temp.assign(7, 0);
	temp[0]=1;
	temp[1]=2;
	temp[2]=2;
	temp[3]=2;
	temp[4]=2;
	temp[5]=2;
	temp[6]=5;
	m_baiZiSamePieceCount.push_back(temp);
	m_baiZiSamePieceCount.push_back(temp);
}
BOOL CchessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitSamePieceCount();
	m_isStarted = true;
	m_chessManSize = 57;
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
    CCHESSPLAY()->Init();
    m_chessBoardBitmap.LoadBitmap(IDB_CHESSBOARD);//添加位图
    GetClientRect(m_dlgRect);
	LoadChessManBitMap();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CchessDlg::OnBnClickedOk()
{
	OnOK();
}
void CchessDlg::InitDCInMemory(void)
{
	if (!m_dcCompatible.m_hDC)
	{
		CClientDC dc(this);
		CBrush*  pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		m_dcCompatible.CreateCompatibleDC(&dc);
		CRect rect;
		GetClientRect(&rect);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		m_dcCompatible.SelectObject(&bitmap);
		m_dcCompatible.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
	}
}
void CchessDlg::OnPaint()
{
	InitDCInMemory();	
	PaintBack();
	PaintChessboard();
	PaintSourceChessMan();
	PaintChessman();
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcCompatible, 0, 0, SRCCOPY);
	CDialog::OnPaint();
}
void CchessDlg::PaintSourceChessMan(void)
{
	std::array<int,14> sourceId = {16, 18, 20, 22, 24, 26, 28, 32, 34, 36, 38, 40, 42, 44};
	for (size_t i = 0; i < sourceId.size(); ++i)
	{
		int IDB = sourceId[i];
		BITMAP bmpSize;
		m_pieceBitmap[IDB]->GetBitmap(&bmpSize);//获取位图的大小等信息
		CDC  memDC;
		memDC.CreateCompatibleDC(&m_dcCompatible);
		memDC.SelectObject(*m_pieceBitmap[IDB]);
		int x = 600;
		int y = 30 + i*m_chessManSize;
		if (sourceId[i] >= 32)
		{
			x += m_chessManSize;
			y = 30 + (i-7)*m_chessManSize;
		}
		m_dcCompatible.StretchBlt(x, y, m_chessManSize, m_chessManSize,
			&memDC, 0, 0, bmpSize.bmWidth,bmpSize.bmHeight, SRCCOPY);
		memDC.DeleteDC();
	}
	
}
void CchessDlg::PaintBack()
{
    //画黑色背景
    CBrush brushBack(RGB(25,50,60));
    m_dcCompatible.FillRect(m_dlgRect,&brushBack);
    brushBack.DeleteObject();
}
void CchessDlg::PaintChessboard(void)
{
    BITMAP bmpSize;
    m_chessBoardBitmap.GetBitmap(&bmpSize);//获取位图的大小等信息

    CDC memChessBoardDC;
    memChessBoardDC.CreateCompatibleDC(&m_dcCompatible);
    memChessBoardDC.SelectObject(&m_chessBoardBitmap);
    //画棋盘
    CRect rect(30+10,30+10,61*9+15,61*10+15);
    m_dcCompatible.StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memChessBoardDC, 0, 0, bmpSize.bmWidth,bmpSize.bmHeight, SRCCOPY);
    memChessBoardDC.DeleteDC();
}
void CchessDlg::PaintChessman(void) {
	vector<Position> aliveman;
	aliveman=m_pChessObject->AliveMan();
	for(vector<Position>::size_type i=0;i<aliveman.size();++i)
	{
		PaintOneChessman(aliveman[i],m_pChessObject->chessboard(aliveman[i]));
	}
}
void CchessDlg::PaintOneChessman(const Position& p,int _id)
{
  MoveOnce m;
  PositionToMove(p,m);
  int IDB = _id;
  BITMAP bmpSize;
  m_pieceBitmap[IDB]->GetBitmap(&bmpSize);//获取位图的大小等信息
  CDC  memDC;
  memDC.CreateCompatibleDC(&m_dcCompatible);
  memDC.SelectObject(*m_pieceBitmap[IDB]);
  m_dcCompatible.StretchBlt(m.first.first, m.first.second, 57, 57, &memDC, 0, 0, bmpSize.bmWidth,bmpSize.bmHeight, SRCCOPY);
  memDC.DeleteDC();
}
BOOL CchessDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}
CString CchessDlg::PaintID(int id) {
  switch(id) {
    case 16:
    case 32:return CString("帅");
    case 17:
    case 18:
    case 33:
    case 34:return CString("士");
    case 19:
    case 20:
    case 35:
    case 36:return CString("相");
    case 21:
    case 22:
    case 37:
    case 38:return CString("马");
    case 23:
    case 24:
    case 39:
    case 40:return CString("车");
    case 25:
    case 26:
    case 41:
    case 42:return CString("炮");
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:return CString("兵");
    default: return CString("操");
  }
}
void CchessDlg::PositionToMove(const Position& p,MoveOnce& m) const
{
  //数据转换 （x,y）->(x1,y1,x2,y2)
  int basex=30,basey=30;
  //由棋盘数组中的坐标值得到窗口棋盘中的左上坐标值
  m.first.first=basex+(p.second-3)*61;//棋盘方格小正方形的边长62
  m.first.second=basey+(p.first-3)*61;
  //绘制圆形在长为40的正方形内部
  m.second.first=m.first.first+47;
  m.second.second=m.first.second+47;
}
//数据转换 (x1,y1,x2,y2)->（x,y）
void CchessDlg::PointToPosition(const CPoint& point, Position& p)const
{
	p.second=(point.x-30)/61+3;
	p.first=(point.y-30)/61+3;
}
void CchessDlg::BaiZiPointToPosition(const CPoint& point, Position& p)const
{
	//left(point.x) top(point.y)   x(p.first) y(p.second)
	//left->y    top->x
	//左上角像素（600,29），棋子长宽59
	if(point.x < 600 || point.x > 713 || point.y < 29 || point.y > 429) 
	{
		p.second = -1;
		p.first = -1;
		return ;
	};
	p.second=(point.x-600)/59;
	p.first=(point.y-29)/59;
}
bool CchessDlg::CheckPosition(Position p) const
{
  return (3<=p.first && p.first<=12 &&
          3<=p.second && p.second<=11);
}
bool CchessDlg::BaiZiCheckPosition(Position p) const
{
	return (0 <= p.first && p.first <= 6 &&
		    0 <= p.second && p.second <= 1);
}
OneStep CchessDlg::KillSortAlfaBataSearch(void)
{
	return std::move(m_pChessObject->KillSortAlfaBataSearch(m_depth));
}
bool CchessDlg::CanMoveTo(CPoint point) const
{
	Position positionstart,positiontarget;
	PointToPosition(m_prePoint,positionstart);
	PointToPosition(point,positiontarget);
	moves m;
	//检查起点棋子是不是用户的棋子,并且棋子的位置在棋盘上
	if(CheckPosition(positionstart) && chessboard(positionstart)/16==1)
	{
		//检查目标位置是不是一个可达的位置
		if (CheckPosition(positiontarget))
		{
			//获取所有可能的走法
			m_pChessObject->GetMoveOneMan(chessboard(positionstart), m);
			moves::const_iterator iter=find(m.begin(),m.end(),make_pair(make_pair(positionstart,positiontarget),chessboard(positiontarget)));
			if( iter!=m.end())
			return true;
		}
	}
	return false;
}
bool CchessDlg::BaiZiCanMoveTo(CPoint point) const
{
	Position startPosition, targetPosition;
	BaiZiPointToPosition(m_prePoint, startPosition);
	PointToPosition(point, targetPosition);
	moves m;
	//检查起点棋子是不是用户的棋子,并且棋子的位置在棋盘上
	bool checkStart = BaiZiCheckPosition(startPosition);
	bool checkTarget = CheckPosition(targetPosition);
	bool checkBoard = chessboard(targetPosition) == 0 ? true : false;
	if(checkStart && checkTarget && checkBoard)
	{
		return true;
	}
	return false;
}
OneStep CchessDlg::GoAhead(const OneStep& m)
{
	m_pChessObject->GoAheadAndRecordHistory(m);
    return m;
}
void CchessDlg::BaiZiGoAhead(const Position& _targetPosition, int _id)
{
	m_pChessObject->SetChessBoard(_targetPosition, _id);
}
void CchessDlg::GoBack(void)
{
	m_pChessObject->GoBackAndRemoveHistory();
	Invalidate();
}
void CchessDlg::PaintChoose(CPoint point)
{
}
void CchessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    m_prePoint=point;
    PaintChoose(point);
    CDialog::OnLButtonDown(nFlags, point);
}
int CchessDlg::BaiZiGetChessboard(const Position& p)
{
	if (p.first == 0 && p.second == 0)
	{
		return 16;
	} 
	else if (p.first == 0 && p.second == 1)
	{
		return 32;
	}
	else 
	{
		if (m_baiZiSamePieceStart[p.second][p.first] == m_baiZiSamePieceCount[p.second][p.first])
		{
			AfxMessageBox(_T("该类型的棋子已经摆满了!\n不可以增加该类型的棋子！"));
			return -1;
		}
		
		int id = (p.first * 2 - 1) + 16 + m_baiZiSamePieceStart[p.second][p.first]++;
		id += p.second * 16;
		return id;
	}
	assert(true);
	return -1;
}
void CchessDlg::BaiZiButtonUp(UINT _nFlags, CPoint _point)
{
	Position positionstart,positiontarget;
	BaiZiPointToPosition(m_prePoint,positionstart);
	PointToPosition(_point,positiontarget);
	//检查从当前位置是否可达目标位置(point)
	if (BaiZiCanMoveTo(_point))
	{
		//执行人选择的走法
		int id = BaiZiGetChessboard(positionstart);
		if (id == -1)
		{
			return ;
		}
		BaiZiGoAhead(positiontarget, id);
		Invalidate();
	}
}
void CchessDlg::ButtonUp(UINT _nFlags, CPoint _point)
{
	Position positionstart,positiontarget;
	PointToPosition(m_prePoint,positionstart);
	PointToPosition(_point,positiontarget);
	//检查从当前位置是否可达目标位置(point)
	if (CanMoveTo(_point))
	{
		//执行人选择的走法
		OneStep userStep = make_pair(make_pair(positionstart,positiontarget),chessboard(positiontarget));
		GoAhead(userStep);

		OneStep computerStep = KillSortAlfaBataSearch();
		GoAhead(computerStep);
		Invalidate();
	}
	else
	{
		AfxMessageBox(_T("不能走到那里！\n请重新走子。"));
	}
}
void CchessDlg::OnLButtonUp(UINT _nFlags, CPoint _point)
{
	m_isStarted ? ButtonUp(_nFlags, _point) : BaiZiButtonUp(_nFlags, _point);
    CDialog::OnLButtonUp(_nFlags, _point);
}
void CchessDlg::OnBnClickedButtonGoBack()
{
    GoBack();
    OnPaint();
}
void CchessDlg::OnBnClickedButtonNew()
{
    // TODO: 在此添加控件通知处理程序代码
	m_pChessObject->Init();
	m_isStarted = true;
	Invalidate();
}
void CchessDlg::OutStatus(void)
{
    ofstream fout("status.txt",ios::app);
	m_pChessObject->OutStatus(fout);
}
void CchessDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isStarted = true;
}
void CchessDlg::OnEnChangeEditDepth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString cstrDepth;
	m_editDepth.GetWindowText(cstrDepth);
	stringstream ss(Global::converter.to_bytes(cstrDepth.GetBuffer()));
	ss >> m_depth;
}


