// MyDialog.cpp: 实现文件
//

#include "pch.h"
#include "Graphics.h"
#include "MyDialog.h"


// MyDialog

IMPLEMENT_DYNCREATE(MyDialog, CFormView)

MyDialog::MyDialog()
	: CFormView(IDD_DIALOG1)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MyDialog, CFormView)
END_MESSAGE_MAP()


// MyDialog 诊断

#ifdef _DEBUG
void MyDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MyDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MyDialog 消息处理程序
