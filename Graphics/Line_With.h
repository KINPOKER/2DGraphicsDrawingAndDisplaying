#pragma once


// Line_With 对话框

class Line_With : public CDialog
{
	DECLARE_DYNAMIC(Line_With)

public:
	Line_With(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Line_With();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = LineWith };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_LineWidth;
};
