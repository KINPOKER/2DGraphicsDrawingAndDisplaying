// NewDialog.cpp: 实现文件
//

#include "pch.h"
#include "Graphics.h"
#include "NewDialog.h"
#include "afxdialogex.h"


// NewDialog 对话框

IMPLEMENT_DYNAMIC(NewDialog, CDialogEx)

NewDialog::NewDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

NewDialog::~NewDialog()
{
}

void NewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit_Length);
	DDX_Control(pDX, 1002, Edit_Area);
}


BEGIN_MESSAGE_MAP(NewDialog, CDialogEx)
END_MESSAGE_MAP()


// NewDialog 消息处理程序
