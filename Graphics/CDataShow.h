#pragma once


// CDataShow 窗体视图

class CDataShow : public CFormView
{
	DECLARE_DYNCREATE(CDataShow)

protected:
	CDataShow();           // 动态创建所使用的受保护的构造函数
	virtual ~CDataShow();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = datashow };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Length;
	CString m_Area;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg void OnEnChangeeditlength();
	CString Point1;
	CString Point2;
	CString Point3;
	CString Point4;
	CString Radius;
	CString maxaxit;
	CString minaxit;
	CString chang;
	CString kuan;
	CString vertex;
};


