// CDataShow.cpp: 实现文件
//

#include "pch.h"
#include "Graphics.h"
#include "CDataShow.h"

#include "GraphicsDoc.h"

// CDataShow

IMPLEMENT_DYNCREATE(CDataShow, CFormView)

CDataShow::CDataShow()
	: CFormView(datashow)
	, m_Length(_T(""))
	, m_Area(_T(""))
	, Point1(_T(""))
	, Point2(_T(""))
	, Point3(_T(""))
	, Point4(_T(""))
	, Radius(_T(""))
	, maxaxit(_T(""))
	, minaxit(_T(""))
	, chang(_T(""))
	, kuan(_T(""))
	, vertex(_T(""))
{

}

CDataShow::~CDataShow()
{
}

void CDataShow::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, editLength, m_Length);
	DDX_Text(pDX, editArea, m_Area);
	DDX_Text(pDX, editLength2, Point1);
	DDX_Text(pDX, editLength3, Point2);
	DDX_Text(pDX, editArea2, Point3);
	DDX_Text(pDX, editLength4, Point4);
	DDX_Text(pDX, editLength5, Radius);
	DDX_Text(pDX, editLength6, maxaxit);
	DDX_Text(pDX, editLength7, minaxit);
	DDX_Text(pDX, editLength8, chang);
	DDX_Text(pDX, editLength9, kuan);
	DDX_Text(pDX, editLength10, vertex);
}

BEGIN_MESSAGE_MAP(CDataShow, CFormView)
	ON_EN_CHANGE(editLength, &CDataShow::OnEnChangeeditlength)
END_MESSAGE_MAP()


// CDataShow 诊断

#ifdef _DEBUG
void CDataShow::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataShow::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataShow 消息处理程序


void CDataShow::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	CGraphicsDoc* pDoc = (CGraphicsDoc*)GetDocument();
	m_Length = pDoc->m_Length;
	m_Area = pDoc->m_Area;
	Point1 = pDoc->m_Point[0];
	Point2 = pDoc->m_Point[1];
	Point3 = pDoc->m_Point[2];
	Point4 = pDoc->m_Point[3];
	Radius = pDoc->m_radius;
	maxaxit = pDoc->m_axis[0];
	minaxit = pDoc->m_axis[1];
	chang = pDoc->m_width;
	kuan = pDoc->m_height;
	vertex = pDoc->m_vertex;
	UpdateData(FALSE);
}


void CDataShow::OnEnChangeeditlength()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
