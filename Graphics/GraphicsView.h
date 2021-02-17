
// GraphicsView.h: CGraphicsView 类的接口
//

#pragma once
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"

#include "MyDialog.h"


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


	HCURSOR m_HCross;
	BOOL m_startRect;
	int nCount;		//顶点计数器

	
	Triangle newTriangle;//3
	Rectangles newRectangle;//4

	Circle newCircle;//6
	Ellipses newEllipse;//7


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
	/*afx_msg void OnShaperadio1();
	afx_msg void OnShaperadio2();
	afx_msg void OnShaperadio3();
	afx_msg void OnShaperadio4();
	afx_msg void OnShaperadio5();
	afx_msg void OnShaperadio6();
	afx_msg void OnShaperadio7();*/
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GraphicsView.cpp 中的调试版本
inline CGraphicsDoc* CGraphicsView::GetDocument() const
   { return reinterpret_cast<CGraphicsDoc*>(m_pDocument); }
#endif

