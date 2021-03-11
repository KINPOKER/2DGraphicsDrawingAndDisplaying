
// ChildFrm.cpp: CChildFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Graphics.h"

#include "ChildFrm.h"

#include "GraphicsDoc.h"
#include "GraphicsView.h"
#include "CDataShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRect rc;
	GetClientRect(&rc);
	try {
		m_wndSplitter.CreateStatic(this, 2, 1);	//create static splite windows
		m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphicsView), CSize(rc.Width(), 1.32*rc.Height()), pContext);
		m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CDataShow), CSize(rc.Width(), rc.Height() / 7), pContext);
	}
	catch (...) {
		AfxMessageBox(_T("静态分割窗口出现错误!程序退出..."), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}
