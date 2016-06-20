
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "RealBX_ModelEditor.h"
#include "ChildView.h"
#include "RBX_ModelViewManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChildView::CChildView()
{
	imgpath_ = "C://Users//SVF//Pictures//1.jpg";
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_COMMAND(ID_MODELTEST_ENABLEMOUSE, &CChildView::OnModeltestEnablemouse)
	ON_COMMAND(ID_MODELTEST_DISABLEMOUSE, &CChildView::OnModeltestDisablemouse)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// 로드된 이미지
	CImage img;
	LPCTSTR imgPath = imgpath_;
	img.Load(imgPath);

	// 화면 DC에 출력
	if(img != NULL) {
		img.BitBlt(dc.m_hDC, 0, 0);
	}
	else {
		return;
	}
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CChildView::OnDestroy()
{
	CWnd::OnDestroy();
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}


void CChildView::OnModeltestEnablemouse()
{
	CRect rect;
	GetClientRect(&rect);
	POINT Pt = rect.CenterPoint();	
	ClientToScreen(&Pt);
	SetCursorPos(Pt.x,Pt.y);
}


void CChildView::OnModeltestDisablemouse()
{
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::SetModel2Dimage(CString imgpath) {
	imgpath_ = imgpath;
	Invalidate();
};