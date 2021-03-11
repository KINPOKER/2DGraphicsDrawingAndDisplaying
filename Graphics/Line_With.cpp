// Line_With.cpp: 实现文件
//

#include "pch.h"
#include "Graphics.h"
#include "Line_With.h"
#include "afxdialogex.h"


// Line_With 对话框

IMPLEMENT_DYNAMIC(Line_With, CDialog)

Line_With::Line_With(CWnd* pParent /*=nullptr*/)
	: CDialog(LineWith, pParent)
	, m_LineWidth(0)
{

}

Line_With::~Line_With()
{
}

void Line_With::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_With, m_LineWidth);
}


BEGIN_MESSAGE_MAP(Line_With, CDialog)
END_MESSAGE_MAP()


// Line_With 消息处理程序
