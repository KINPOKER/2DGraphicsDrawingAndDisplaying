﻿
// GraphicsView.cpp: CGraphicsView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphics.h"
#endif

#include "GraphicsDoc.h"
#include "GraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGraphicsView 构造/析构

CGraphicsView::CGraphicsView() noexcept
{
	// TODO: 在此处添加构造代码

	m_startRect = FALSE;

	//初始化m_HCross为十字光标
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphicsView 绘图

void CGraphicsView::OnDraw(CDC* /*pDC*/)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGraphicsView 打印


void CGraphicsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicsView 诊断

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsView 消息处理程序

void CGraphicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_startRect = TRUE; //鼠标左键单击，设置可以开始绘制
	//设置光标为十字光标
	::SetCursor(m_HCross);

	newCircle.setStartPoint(point);
	newCircle.setOldPoint(point);

	SetCapture(); // 设置鼠标捕获
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC* pDC = GetDC();
	pDC->SetROP2(R2_NOT);
	pDC->SelectStockObject(NULL_BRUSH);

	if (m_startRect)
	{
		newCircle.currentPoint = point;
		newCircle.OnDraw(pDC);
	}
	ReleaseDC(pDC); // 释放设备上下文

	CView::OnMouseMove(nFlags, point);
}

void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	m_startRect = FALSE;
	::ClipCursor(NULL);
	
	CDC* pDC = GetDC();

	newCircle.currentPoint = point;
	newCircle.OnDraw(pDC);

	CView::OnLButtonUp(nFlags, point);
}