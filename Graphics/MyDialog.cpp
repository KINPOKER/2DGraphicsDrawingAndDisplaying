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
	DDX_Control(pDX, IDC_ShapeRadio1, ShapeRadio1);
	DDX_Control(pDX, IDC_ShapeRadio2, ShapeRadio2);
	DDX_Control(pDX, IDC_ShapeRadio3, ShapeRadio3);
	DDX_Control(pDX, IDC_ShapeRadio4, ShapeRadio4);
	DDX_Control(pDX, IDC_ShapeRadio5, ShapeRadio5);
	DDX_Control(pDX, IDC_ShapeRadio6, ShapeRadio6);
}

BEGIN_MESSAGE_MAP(MyDialog, CFormView)
	ON_BN_CLICKED(IDC_ShapeRadio1, &MyDialog::OnBnClickedShaperadio1)
	ON_BN_CLICKED(IDC_ShapeRadio2, &MyDialog::OnBnClickedShaperadio2)
	ON_BN_CLICKED(IDC_ShapeRadio3, &MyDialog::OnBnClickedShaperadio3)
	ON_BN_CLICKED(IDC_ShapeRadio4, &MyDialog::OnBnClickedShaperadio4)
	ON_BN_CLICKED(IDC_ShapeRadio5, &MyDialog::OnBnClickedShaperadio5)
	ON_BN_CLICKED(IDC_ShapeRadio6, &MyDialog::OnBnClickedShaperadio6)
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

void MyDialog::OnInitialUpdate()
{

	CheckRadioButton(IDC_ShapeRadio1, IDC_ShapeRadio6, IDC_ShapeRadio1);

	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

// MyDialog 消息处理程序

void MyDialog::OnBnClickedShaperadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("radio1"));
}

void MyDialog::OnBnClickedShaperadio2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MyDialog::OnBnClickedShaperadio3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MyDialog::OnBnClickedShaperadio4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MyDialog::OnBnClickedShaperadio5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MyDialog::OnBnClickedShaperadio6()
{
	// TODO: 在此添加控件通知处理程序代码
}

