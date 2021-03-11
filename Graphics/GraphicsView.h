
// GraphicsView.h: CGraphicsView 类的接口
//

#pragma once
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "MultiShape.h"
#include "RTriangle.h"
#include "ITriangle.h"
#include "Line.h"
#include "PolyLine.h"
#include "GraphicsDoc.h"
#include "CDataShow.h"

class CGraphicsView : public CView
{
protected: // 仅从序列化创建
	CGraphicsView() noexcept;
	DECLARE_DYNCREATE(CGraphicsView)

// 特性
public:
	CGraphicsDoc* GetDocument() const;

// 操作
public:


	/////////////////////////////新增//////////////////////////////////////////////////////
	
	CPoint* brpoint;
	BOOL move;
	BOOL Scale;
	int chs = 0;  //放缩点选择
	
	/////////////////////////////新增/////////////////////////////////////////////////////////


	int flag;//图形选择标志：1-线段，2-多段折线，3-三角形(31等腰，32直角，33普通)，4-矩形，5-N边形，6-圆形，7-椭圆形

	HCURSOR m_HCross;
	BOOL m_startRect;
	
	Triangle newTriangle;//3
	Rectangles *newRectangle;//4
	MultiShape* newMultiShape;//5
	Circle *newCircle;//6
	Ellipses *newEllipse;//7
	RTriangle *newRTriangle;
	ITriangle *newITriangle;
	Line* newLine;
	PolyLine* newPolyLine;

	COLORREF m_clr;
	UINT m_LineWidth;
	CString str;
	CString* strPoint;
	CString* strAxis;

	int numquad; //调色板数
	int flagOpen; //标志是否打开bmp
	BITMAPINFO* pbi; //记录图像细节
	BYTE* lpbuf; //图像数据
	RGBQUAD* quad; //调色板
	BITMAPFILEHEADER bf;//文件头
	BITMAPINFOHEADER bi; //信息头	

	BOOL saveTag = FALSE;
	CString saveFilePath;

	void sendLength(CString& str);//周长
	void sendArea(CString& str);//面积
	void sendPoint(CString* str);//四边形一下的顶点
	void sendaxis(CString* str);//长、短半轴
	void sendRadius(CString& str);//半径
	void sendWidth(CString& str);//矩形长
	void sendHeight(CString& str);//矩形宽
	void sendVertex(CString& str);//顶点个数

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMultiShape();
//	afx_msg void OnPaint();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
	afx_msg void OnMultiShape();
	afx_msg void OnSingleLine();
	afx_msg void OnMultiLine();
	afx_msg void OnITriange();
	afx_msg void OnRTriangle();
	afx_msg void OnTriangle();
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnEllipse();
	afx_msg void OnRed();
	afx_msg void OnSolid_Line();
	afx_msg void OnDash_Line();
	afx_msg void OnDot_Line();
	afx_msg void OnDASHDOT_Line();
	afx_msg void OnDASHDOTDOT_Line();
	afx_msg void OnLineWidth();
	afx_msg void OnCountLine();
	afx_msg void OnCountMultiLine();
	afx_msg void OnCountITriangle();
	afx_msg void OnCountRTriangle();
	afx_msg void OnCountRectangle();
	afx_msg void OnCountMultiShape();
	afx_msg void OnCountCircle();
	afx_msg void OnCountEllipse();
	afx_msg void OnBottenMove();
	afx_msg void OnChangeSize();
	afx_msg void OnRotate();
	afx_msg void OnClearDraw();
};

#ifndef _DEBUG  // GraphicsView.cpp 中的调试版本
inline CGraphicsDoc* CGraphicsView::GetDocument() const
   { return reinterpret_cast<CGraphicsDoc*>(m_pDocument); }
#endif

