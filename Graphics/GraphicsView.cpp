
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
#include "Line_With.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int RTriangle::nRTriangle = 0;
int ITriangle::nITriangle = 0;
int MultiShape::nMultiShape = 0;
int Rectangles::nRectangle = 0;
int Circle::nCircle = 0;
int Ellipses::nEllipse = 0;
int Line::nLine = 0;
int PolyLine::nPolyLine = 0;
#define MAX 50

// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CGraphicsView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, &CGraphicsView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, &CGraphicsView::OnFileSave)
	ON_COMMAND(ID_32775, &CGraphicsView::OnMultiShape)
	ON_COMMAND(ID_32771, &CGraphicsView::OnSingleLine)
	ON_COMMAND(ID_32772, &CGraphicsView::OnMultiLine)
	ON_COMMAND(ID_32778, &CGraphicsView::OnITriange)
	ON_COMMAND(ID_32779, &CGraphicsView::OnRTriangle)
	ON_COMMAND(ID_32780, &CGraphicsView::OnTriangle)
	ON_COMMAND(ID_32774, &CGraphicsView::OnRectangle)
	ON_COMMAND(ID_32776, &CGraphicsView::OnCircle)
	ON_COMMAND(ID_32777, &CGraphicsView::OnEllipse)
	ON_COMMAND(32782, &CGraphicsView::OnRed)
	ON_COMMAND(ID_32784, &CGraphicsView::OnSolid_Line)
	ON_COMMAND(ID_32785, &CGraphicsView::OnDash_Line)
	ON_COMMAND(ID_32786, &CGraphicsView::OnDot_Line)
	ON_COMMAND(ID_32787, &CGraphicsView::OnDASHDOT_Line)
	ON_COMMAND(ID_32788, &CGraphicsView::OnDASHDOTDOT_Line)
	ON_COMMAND(ID_32789, &CGraphicsView::OnLineWidth)
	ON_COMMAND(ID_32790, &CGraphicsView::OnCountLine)
	ON_COMMAND(ID_32791, &CGraphicsView::OnCountMultiLine)
	ON_COMMAND(ID_32793, &CGraphicsView::OnCountITriangle)
	ON_COMMAND(ID_32794, &CGraphicsView::OnCountRTriangle)
	ON_COMMAND(ID_32795, &CGraphicsView::OnCountRectangle)
	ON_COMMAND(ID_32796, &CGraphicsView::OnCountMultiShape)
	ON_COMMAND(ID_32797, &CGraphicsView::OnCountCircle)
	ON_COMMAND(ID_32798, &CGraphicsView::OnCountEllipse)
	ON_COMMAND(32799, &CGraphicsView::OnBottenMove)
	ON_COMMAND(ID_32800, &CGraphicsView::OnChangeSize)
	ON_COMMAND(32801, &CGraphicsView::OnRotate)
	ON_COMMAND(32802, &CGraphicsView::OnClearDraw)
END_MESSAGE_MAP()

// CGraphicsView 构造/析构

CGraphicsView::CGraphicsView() noexcept
{
	// TODO: 在此处添加构造代码
	m_startRect = FALSE;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	//ShapeType = 1;
	m_LineWidth = 0;
	move = false;

	numquad = 0; //调色板数
	flagOpen = 0; //标志是否打开bmp
	pbi = 0; //记录图像细节
	lpbuf = 0; //图像数据
	quad = 0; //调色板

	flag = 0;
	if ((newMultiShape = new MultiShape[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newRTriangle= new RTriangle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newITriangle = new ITriangle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newRectangle = new Rectangles[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newCircle = new Circle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newEllipse = new Ellipses[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newLine = new Line[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newPolyLine = new PolyLine[MAX]) == NULL)
	{
		exit(0);
	}
	if ((strPoint = new CString[4]) == NULL)
	{
		exit(0);
	}
	if ((strAxis = new CString[2]) == NULL)
	{
		exit(0);
	}
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

void CGraphicsView::OnDraw(CDC* pDC)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//是否已打开某个BMP文件
	if (flagOpen == 1)
	{
		//这个函数显示DIB
		SetDIBitsToDevice(pDC->m_hDC,   //DIB将输出的设备描述表
			0,							//设备描述表中位图输出起始逻辑x地址
			0,							//设备描述表中位图输出起始逻辑x地址
			bi.biWidth,					//DIB的宽度
			bi.biHeight,				//DIB的高度
			0,							//DIB开始读取输出的像素数据的x位置
			0,							//DIB开始读取输出的像素数据的y位置
			0,							//DIB中像素的水平行号,它对应lpBits内存缓冲区第一行数据
			bi.biHeight,				//DIB的行数，对应包含在由lpBits所指内存缓冲区中的数据
			lpbuf,						//包含像素数据的内存缓冲区的指针
			pbi,						//指向初始化了的BITMAPINFO数据结构的指针，描述了位图的大小和色彩数据
			DIB_RGB_COLORS);			//指定是显示的颜色      
	}
		
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

////////////////////////////线段/////////////////////////////////////////////////////
	if (flag == 1)
	{
		newLine[Line::nLine].setFirstPoint(point);
		newLine[Line::nLine].setEndPoint(point);
	}
	if (flag == 111)
	{
		move = FALSE;
		brpoint = newLine[Line::nLine].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newLine[Line::nLine].currentPoint = point;
			newLine[Line::nLine].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 1111)
	{
		Scale = FALSE;
		brpoint = this->newLine[Line::nLine].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newLine[Line::nLine].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newLine[Line::nLine].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newLine[Line::nLine].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newLine[Line::nLine].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 11111)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newLine[Line::nLine].Rotate(pDC);
	}

/////////////////////////////多线段//////////////////////////////////////////////////////
	if (flag == 22)
	{
		newPolyLine[PolyLine::nPolyLine].SetPoint(point);
		CDC* pDC = GetDC();
		newPolyLine[PolyLine::nPolyLine].OnDraw(pDC);
		ReleaseDC(pDC);
	}
	if (flag == 2)
	{
		newPolyLine[PolyLine::nPolyLine].SetPoint(point);
		flag = 22;
	}
	if (flag == 222)
	{
		move = FALSE;
		brpoint = newPolyLine[PolyLine::nPolyLine].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newPolyLine[PolyLine::nPolyLine].currentPoint = point;
			newPolyLine[PolyLine::nPolyLine].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 2222)
	{
		Scale = FALSE;
		brpoint = this->newPolyLine[PolyLine::nPolyLine].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newPolyLine[PolyLine::nPolyLine].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newPolyLine[PolyLine::nPolyLine].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newPolyLine[PolyLine::nPolyLine].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newPolyLine[PolyLine::nPolyLine].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 22222) 
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newPolyLine[PolyLine::nPolyLine].Rotate(pDC);
	}
/////////////////////////////等腰三角形/////////////////////////////////////////////////
	if (flag == 31)
	{
		newITriangle[ITriangle::nITriangle].setStartPoint(point);
		newITriangle[ITriangle::nITriangle].setOldPoint(point);
	}
	if (flag == 3111)
	{
		move = FALSE;
		brpoint = newITriangle[ITriangle::nITriangle].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			newITriangle[ITriangle::nITriangle].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 31111)
	{
		Scale = FALSE;
		brpoint = this->newITriangle[ITriangle::nITriangle].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 311111)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newITriangle[ITriangle::nITriangle].Rotate(pDC);

		strPoint[0].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[0].x, newITriangle[ITriangle::nITriangle].pt[0].y);
		strPoint[1].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[1].x, newITriangle[ITriangle::nITriangle].pt[1].y);
		strPoint[2].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[2].x, newITriangle[ITriangle::nITriangle].pt[2].y);
		strPoint[3].Empty();
		sendPoint(strPoint);

		ReleaseDC(pDC);
	}
	
/////////////////////////////直角三角形/////////////////////////////////////////////////
	if (flag == 32)
	{
		newRTriangle[RTriangle::nRTriangle].setStartPoint(point);
		newRTriangle[RTriangle::nRTriangle].setOldPoint(point);
	}
	if (flag == 3222)
	{
		move = false;
		brpoint = newRTriangle[RTriangle::nRTriangle].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			newRTriangle[RTriangle::nRTriangle].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 32222)
	{
		Scale = FALSE;
		brpoint = this->newRTriangle[RTriangle::nRTriangle].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 322222)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newRTriangle[RTriangle::nRTriangle].Rotate(pDC);

		strPoint[0].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[0].x, newRTriangle[RTriangle::nRTriangle].pt[0].y);
		strPoint[1].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[1].x, newRTriangle[RTriangle::nRTriangle].pt[1].y);
		strPoint[2].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[2].x, newRTriangle[RTriangle::nRTriangle].pt[2].y);
		strPoint[3].Empty();
		sendPoint(strPoint);

		ReleaseDC(pDC);
	}

//////////////////////////////////矩形//////////////////////////////////////////////////
	if (flag == 4)
	{
		newRectangle[Rectangles::nRectangle].setStartPoint(point);
		newRectangle[Rectangles::nRectangle].setOldPoint(point);
	}
	if (flag == 444)
	{
		move = FALSE;
		brpoint = newRectangle[Rectangles::nRectangle].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			newRectangle[Rectangles::nRectangle].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 4444)
	{
		Scale = FALSE;
		brpoint = this->newRectangle[Rectangles::nRectangle].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 44444)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newRectangle[Rectangles::nRectangle].Rotate(pDC);
		
		strPoint[0].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
		strPoint[1].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
		strPoint[2].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
		strPoint[3].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
		sendPoint(strPoint);
		str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().x - newRectangle[Rectangles::nRectangle].getOldPoint().x));
		sendWidth(str);
		str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().y - newRectangle[Rectangles::nRectangle].getOldPoint().y));
		sendHeight(str);

		ReleaseDC(pDC);
	}

//////////////////////////////////N边形/////////////////////////////////////////////////
	if (flag == 55)
	{
		newMultiShape[MultiShape::nMultiShape].SetPoint(point);
		CDC* pDC = GetDC();
		if (newMultiShape[MultiShape::nMultiShape].judge())
		{
			MessageBox(_T("请构成不相交封闭多边形！"), _T("注意"), MB_ICONWARNING);
			newMultiShape[MultiShape::nMultiShape].DecnCount();
		}
		newMultiShape[MultiShape::nMultiShape].OnDraw(pDC);
		ReleaseDC(pDC);
	}
	if (flag == 5)
	{
		newMultiShape[MultiShape::nMultiShape].SetPoint(point);
		flag = 55;
	}
	if(flag==555)
	{
		move = FALSE;
		brpoint = newMultiShape[MultiShape::nMultiShape].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newMultiShape[MultiShape::nMultiShape].currentPoint = point;
			newMultiShape[MultiShape::nMultiShape].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 5555)
	{
		Scale = FALSE;
		brpoint = this->newMultiShape[MultiShape::nMultiShape].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newMultiShape[MultiShape::nMultiShape].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newMultiShape[MultiShape::nMultiShape].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newMultiShape[MultiShape::nMultiShape].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newMultiShape[MultiShape::nMultiShape].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 55555)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newMultiShape[MultiShape::nMultiShape].Rotate(pDC);
	}
///////////////////////////////////圆形//////////////////////////////////////////////////////	
	if (flag == 6)
	{
		newCircle[Circle::nCircle].setStartPoint(point);
		newCircle[Circle::nCircle].setOldPoint(point);
	}
	if (flag == 666)
	{
		move = false;
		brpoint = newCircle[Circle::nCircle].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newCircle[Circle::nCircle].currentPoint = point;
			newCircle[Circle::nCircle].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 6666)
	{
		Scale = FALSE;
		brpoint = this->newCircle[Circle::nCircle].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newCircle[Circle::nCircle].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newCircle[Circle::nCircle].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newCircle[Circle::nCircle].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newCircle[Circle::nCircle].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	
//////////////////////////////////椭圆/////////////////////////////////////////////////////
	if (flag == 7)
	{
		newEllipse[Ellipses::nEllipse].setStartPoint(point);
		newEllipse[Ellipses::nEllipse].setOldPoint(point);
	}
	if (flag == 777)
	{
		move = false;
		brpoint = newEllipse[Ellipses::nEllipse].getBorderPoint();
		if (point.x > brpoint[0].x && point.x < brpoint[1].x && point.y>brpoint[0].y && point.y < brpoint[3].y)
		{
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			newEllipse[Ellipses::nEllipse].currentPointBeforeMove = point;
			move = TRUE;
		}
	}
	if (flag == 7777)
	{
		Scale = FALSE;
		brpoint = this->newEllipse[Ellipses::nEllipse].getBorderPoint();
		if (point.x < (brpoint[2].x + 50) && point.x >(brpoint[2].x - 50) && point.y < (brpoint[2].y + 50) && point.y >(brpoint[2].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			chs = 1;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[3].x + 50) && point.x >(brpoint[3].x - 50) && point.y < (brpoint[3].y + 50) && point.y >(brpoint[3].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			chs = 2;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[0].x + 50) && point.x >(brpoint[0].x - 50) && point.y < (brpoint[0].y + 50) && point.y >(brpoint[0].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); //双箭头指向西北和东南
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			chs = 3;
			Scale = TRUE;
		}
		else if (point.x < (brpoint[1].x + 50) && point.x >(brpoint[1].x - 50) && point.y < (brpoint[1].y + 50) && point.y >(brpoint[1].y - 50))
		{
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); //双箭头指向东北和西南
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			chs = 4;
			Scale = TRUE;
		}
	}
	if (flag == 77777)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->SelectStockObject(NULL_BRUSH);
		newEllipse[Ellipses::nEllipse].Rotate(pDC);
		ReleaseDC(pDC);
	}

//////////////////////////////////////////////////////////////////////////////////////////

	SetCapture(); // 设置鼠标捕获
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (flag == 55)
	{
		CDC* pDC = GetDC();
		if (newMultiShape[MultiShape::nMultiShape].EndJudge())
		{
			MessageBox(_T("请构成不相交封闭多边形！"), _T("注意"), MB_ICONWARNING);
			ReleaseDC(pDC);
		}
		else
		{
			newMultiShape[MultiShape::nMultiShape].FinishShape(pDC);
			//newMultiShape[MultiShape::nMultiShape].Echo(pDC, newMultiShape[MultiShape::nMultiShape].getStartPoint(), newMultiShape[MultiShape::nMultiShape].getOldPoint());
			ReleaseDC(pDC);

			str.Format(CString("%0.2f"), newMultiShape[MultiShape::nMultiShape].getLength());
			sendLength(str);
			str.Format(CString("%0.2lf"), newMultiShape[MultiShape::nMultiShape].getarea());
			sendArea(str);
			strPoint[0].Empty(); strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
			sendPoint(strPoint);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Format(CString("%d"), newMultiShape[MultiShape::nMultiShape].nCount);
			sendVertex(str);
			str.Empty();
			sendRadius(str);
			sendWidth(str);
			sendHeight(str);

			flag = 5;
			MultiShape::nMultiShape++;
		}
	}

	if (flag == 22)
	{
		//CDC* pDC = GetDC();
		CPoint* brpoint = newPolyLine[PolyLine::nPolyLine].FindBorderpoint();
		newPolyLine[PolyLine::nPolyLine].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
		//newPolyLine[PolyLine::nPolyLine].Echo(pDC, newPolyLine[PolyLine::nPolyLine].getStartPoint(), newPolyLine[PolyLine::nPolyLine].getOldPoint());
		//ReleaseDC(pDC);

		str.Format(CString("%0.2f"), newPolyLine[PolyLine::nPolyLine].getLength());
		sendLength(str);
		strPoint[0].Empty(); strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
		sendPoint(strPoint);
		strAxis[0].Empty(); strAxis[1].Empty();
		sendaxis(strAxis);
		str.Format(CString("%d"), newPolyLine[PolyLine::nPolyLine].numPoint);
		sendVertex(str);
		str.Empty();
		sendArea(str);
		sendRadius(str);
		sendWidth(str);
		sendHeight(str);

		PolyLine::nPolyLine++;
		flag = 2;
	}

	switch (flag)
	{
	case 111:
		move = FALSE;
		Line::nLine++;
		flag = 1;
		break;
	case 1111:
		Scale = FALSE;
		Line::nLine++;
		flag = 1;
		break;
	case 11111:
		Line::nLine++;
		flag = 1;
		break;
	case 222:
		move = FALSE;
		PolyLine::nPolyLine++;
		flag = 2;
		break;
	case 2222:
		Scale = FALSE;
		PolyLine::nPolyLine++;
		flag = 2;
		break;
	case 22222:
		PolyLine::nPolyLine++;
		flag = 2;
		break;
	case 3111:
		move = FALSE;
		ITriangle::nITriangle++;
		flag = 31;
		break;
	case 31111:
		Scale = FALSE;
		ITriangle::nITriangle++;
		flag = 31;
		break;
	case 311111:
		ITriangle::nITriangle++;
		flag = 31;
		break;
	case 3222:
		move = FALSE;
		RTriangle::nRTriangle++;
		flag = 32;
		break;
	case 32222:
		Scale = FALSE;
		RTriangle::nRTriangle++;
		flag = 32;
		break;
	case 322222:
		RTriangle::nRTriangle++;
		flag = 32;
		break;
	case 444:
		move = FALSE;
		Rectangles::nRectangle++;
		flag = 4;
		break;
	case 4444:
		Scale = FALSE;
		Rectangles::nRectangle++;
		flag = 4;
		break;
	case 44444:
		Rectangles::nRectangle++;
		flag = 4;
		break;
	case 555:
		move = FALSE;
		MultiShape::nMultiShape++;
		flag = 5;
		break;
	case 5555:
		Scale = FALSE;
		MultiShape::nMultiShape++;
		flag = 5;
		break;
	case 55555:
		MultiShape::nMultiShape++;
		flag = 5;
		break;
	case 666:
		move = FALSE;
		Circle::nCircle++;
		flag = 6;
		break;
	case 6666:
		Scale = FALSE;
		Circle::nCircle++;
		flag = 6;
		break;
	case 777:
		move = FALSE;
		Ellipses::nEllipse++;
		flag = 7;
		break;
	case 7777:
		Scale = FALSE;
		Ellipses::nEllipse++;
		flag = 7;
		break;
	case 77777:
		Ellipses::nEllipse++;
		flag = 7;
		break;
	}


	CView::OnRButtonDown(nFlags, point);
}

void CGraphicsView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC* pDC = GetDC();
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectStockObject(NULL_BRUSH);

	if (m_startRect)
	{
		switch (flag) {
			case 1:
				newLine[Line::nLine].currentPoint = point;
				newLine[Line::nLine].OnDraw(pDC);
				break;
			case 111:
				if (move)
				{
					newLine[Line::nLine].currentPoint = point;
					newLine[Line::nLine].Move(pDC);
				}
				break;
			case 1111:
				if (Scale)
				{
					newLine[Line::nLine].currentPoint = point;
					newLine[Line::nLine].Scale(pDC, chs);
				}
			case 222:
				if (move)
				{
					newPolyLine[PolyLine::nPolyLine].currentPoint = point;
					newPolyLine[PolyLine::nPolyLine].Move(pDC);
				}
				break;
			case 2222:
				if (Scale) {
					newPolyLine[PolyLine::nPolyLine].currentPoint = point;
					newPolyLine[PolyLine::nPolyLine].ScaleManyVertices(pDC, chs);
				}
				break;
			case 4:
				newRectangle[Rectangles::nRectangle].currentPoint = point;
				newRectangle[Rectangles::nRectangle].OnDraw(pDC);
				break;
			case 444:
				if (move) 
				{
					newRectangle[Rectangles::nRectangle].currentPoint = point;
					newRectangle[Rectangles::nRectangle].Move(pDC);
				}
				break;
			case 4444:
				if (Scale) {
					newRectangle[Rectangles::nRectangle].currentPoint = point;
					newRectangle[Rectangles::nRectangle].Scale(pDC, chs);
				}
				break;
			case 555:
				if (move) 
				{
					newMultiShape[MultiShape::nMultiShape].currentPoint = point;
					newMultiShape[MultiShape::nMultiShape].Move(pDC);
				}
				break;
			case 5555:
				if (Scale) {
					newMultiShape[MultiShape::nMultiShape].currentPoint = point;
					newMultiShape[MultiShape::nMultiShape].ScaleManyVertices(pDC, chs);
				}
				break;
			case 6:
				newCircle[Circle::nCircle].currentPoint = point;
				newCircle[Circle::nCircle].OnDraw(pDC);
				break;
			case 666:
				if (move)
				{
					newCircle[Circle::nCircle].currentPoint = point;
					newCircle[Circle::nCircle].Move(pDC);
				}
				break;
			case 6666:
				if (Scale) {
					newCircle[Circle::nCircle].currentPoint = point;
					newCircle[Circle::nCircle].Scale(pDC, chs);
				}
				break;
			case 7:
				newEllipse[Ellipses::nEllipse].currentPoint = point;
				newEllipse[Ellipses::nEllipse].OnDraw(pDC);
				break;
			case 777:
				if (move)
				{
					newEllipse[Ellipses::nEllipse].currentPoint = point;
					newEllipse[Ellipses::nEllipse].Move(pDC);
				}
				break;
			case 7777:
				if (Scale) {
					newEllipse[Ellipses::nEllipse].currentPoint = point;
					newEllipse[Ellipses::nEllipse].Scale(pDC, chs);
				}
				break;
			case 32:
				newRTriangle[RTriangle::nRTriangle].currentPoint = point;
				newRTriangle[RTriangle::nRTriangle].OnDraw(pDC);
				break;
			case 3222:
				if (move)
				{
					newRTriangle[RTriangle::nRTriangle].currentPoint = point;
					newRTriangle[RTriangle::nRTriangle].Move(pDC);
				}
				break;
			case 32222:
				if (Scale) {
					newRTriangle[RTriangle::nRTriangle].currentPoint = point;
					newRTriangle[RTriangle::nRTriangle].Scale(pDC, chs);
				}
				break;
			case 31:
				newITriangle[ITriangle::nITriangle].currentPoint = point;
				newITriangle[ITriangle::nITriangle].OnDraw(pDC);
				break;
			case 3111:
				if (move)
				{
					newITriangle[ITriangle::nITriangle].currentPoint = point;
					newITriangle[ITriangle::nITriangle].Move(pDC);
				}
				break;
			case 31111:
				if (Scale) {
					newITriangle[ITriangle::nITriangle].currentPoint = point;
					newITriangle[ITriangle::nITriangle].Scale(pDC, chs);
				}
				break;
		}
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
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->SelectStockObject(NULL_BRUSH);

	switch (flag) {
		case 1:
			newLine[Line::nLine].currentPoint = point;
			newLine[Line::nLine].OnDraw(pDC);
			
			str.Format(CString("%0.2f"), newLine[Line::nLine].getLength());
			sendLength(str);
			strPoint[0].Format(CString("(%d , %d)"), newLine[Line::nLine].getFirstPoint().x, newLine[Line::nLine].getFirstPoint().y);
			strPoint[1].Format(CString("(%d , %d)"), newLine[Line::nLine].getCurrentPoint().x, newLine[Line::nLine].getCurrentPoint().y);
			strPoint[2].Empty(); strPoint[3].Empty();
			sendPoint(strPoint);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Format(CString("%d"), 2);
			sendVertex(str);
			str.Empty();
			sendArea(str);
			sendRadius(str);
			sendWidth(str);
			sendHeight(str);

			Line::nLine++;
			break;
		case 31:
			newITriangle[ITriangle::nITriangle].currentPoint = point;
			newITriangle[ITriangle::nITriangle].OnDraw(pDC);

			str.Format(CString("%0.2f"), newITriangle[ITriangle::nITriangle].getLength(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
			sendLength(str);
			str.Format(CString("%0.2lf"), newITriangle[ITriangle::nITriangle].getArea(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
			sendArea(str);
			strPoint[0].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[0].x, newITriangle[ITriangle::nITriangle].pt[0].y);
			strPoint[1].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[1].x, newITriangle[ITriangle::nITriangle].pt[1].y);
			strPoint[2].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[2].x, newITriangle[ITriangle::nITriangle].pt[2].y);
			strPoint[3].Empty();
			sendPoint(strPoint);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Format(CString("%d"), 3);
			sendVertex(str);
			str.Empty();
			sendRadius(str);
			sendWidth(str);
			sendHeight(str);

			ITriangle::nITriangle++;
			break;
		case 32:
			newRTriangle[RTriangle::nRTriangle].currentPoint = point;
			newRTriangle[RTriangle::nRTriangle].OnDraw(pDC);

			str.Format(CString("%0.2f"), newRTriangle[RTriangle::nRTriangle].getLength(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
			sendLength(str);
			str.Format(CString("%0.2lf"), newRTriangle[RTriangle::nRTriangle].getArea(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
			sendArea(str);
			strPoint[0].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[0].x, newRTriangle[RTriangle::nRTriangle].pt[0].y);
			strPoint[1].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[1].x, newRTriangle[RTriangle::nRTriangle].pt[1].y);
			strPoint[2].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[2].x, newRTriangle[RTriangle::nRTriangle].pt[2].y);
			strPoint[3].Empty();
			sendPoint(strPoint);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Format(CString("%d"), 3);
			sendVertex(str);
			str.Empty();
			sendRadius(str);
			sendWidth(str);
			sendHeight(str);

			RTriangle::nRTriangle++;
			break;
		case 4:
			newRectangle[Rectangles::nRectangle].currentPoint = point;
			newRectangle[Rectangles::nRectangle].OnDraw(pDC);

			str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getLength(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
			sendLength(str);
			str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getArea(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
			sendArea(str);
			strPoint[0].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
			strPoint[1].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
			strPoint[2].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
			strPoint[3].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
			sendPoint(strPoint);
			str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().x- newRectangle[Rectangles::nRectangle].getOldPoint().x));
			sendWidth(str);
			str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().y - newRectangle[Rectangles::nRectangle].getOldPoint().y));
			sendHeight(str);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Format(CString("%d"), 4);
			sendVertex(str);
			str.Empty();
			sendRadius(str);

			Rectangles::nRectangle++;
			break;
		case 6:
			newCircle[Circle::nCircle].currentPoint = point;
			newCircle[Circle::nCircle].OnDraw(pDC);

			str.Format(CString("%0.2f"), newCircle[Circle::nCircle].getLength(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
			sendLength(str);
			str.Format(CString("%0.2lf"), newCircle[Circle::nCircle].getArea(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
			sendArea(str);
			strPoint[0].Format(CString("(%0.1f , %0.1f)"), fabs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().x + newCircle[Circle::nCircle].getOldPoint().x))), abs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().y + newCircle[Circle::nCircle].getOldPoint().y))));
			strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
			sendPoint(strPoint);
			str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
			sendRadius(str);
			strAxis[0].Empty(); strAxis[1].Empty();
			sendaxis(strAxis);
			str.Empty();
			sendWidth(str);
			sendHeight(str);
			sendVertex(str);

			Circle::nCircle++;
			break;
		case 7:
			newEllipse[Ellipses::nEllipse].currentPoint = point;
			newEllipse[Ellipses::nEllipse].OnDraw(pDC);
			
			str.Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getLength(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
			sendLength(str);
			str.Format(CString("%0.2lf"), newEllipse[Ellipses::nEllipse].getArea(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
			sendArea(str);
			strPoint[0].Empty();strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
			sendPoint(strPoint);
			str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
			strAxis[0].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getmaxaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
			strAxis[1].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getminaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
			sendaxis(strAxis);
			str.Empty();
			sendRadius(str);
			sendWidth(str);
			sendHeight(str);
			sendVertex(str);
			
			Ellipses::nEllipse++;
			break;
		case 111:
			if (move)
			{
				newLine[Line::nLine].currentPoint = point;
				newLine[Line::nLine].Move(pDC);
				newLine[Line::nLine].UpdateBorderpoint();

				str.Format(CString("%0.2f"), newLine[Line::nLine].getLength());
				sendLength(str);
				strPoint[0].Format(CString("(%d , %d)"), newLine[Line::nLine].getFirstPoint().x, newLine[Line::nLine].getFirstPoint().y);
				strPoint[1].Format(CString("(%d , %d)"), newLine[Line::nLine].getCurrentPoint().x, newLine[Line::nLine].getCurrentPoint().y);
				strPoint[2].Empty(); strPoint[3].Empty();
				sendPoint(strPoint);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 2);
				sendVertex(str);
				str.Empty();
				sendArea(str);
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
			}
			break;
		case 1111:
			if (Scale)
			{
				newLine[Line::nLine].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;
				break;
			}
		case 222:
			if (move)
			{
				newPolyLine[PolyLine::nPolyLine].currentPoint = point;
				newPolyLine[PolyLine::nPolyLine].Move(pDC);
				newPolyLine[PolyLine::nPolyLine].UpdateBorderpoint();
			}
			break;
		case 2222:
			if (Scale)
			{
				newPolyLine[PolyLine::nPolyLine].currentPoint = point;
				newPolyLine[PolyLine::nPolyLine].ScaleManyVertices(pDC, chs);
				if (chs == 1)     //右下角缩放
				{
					brpoint[0].x = brpoint[0].x;
					brpoint[1].x = point.x;
					brpoint[2].x = point.x;
					brpoint[3].x = brpoint[3].x;
					brpoint[0].y = brpoint[0].y;
					brpoint[1].y = brpoint[1].y;
					brpoint[2].y = point.y;
					brpoint[3].y = point.y;
					newPolyLine[PolyLine::nPolyLine].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 2)     //左下角缩放
				{
					brpoint[0].x = point.x;
					brpoint[1].x = brpoint[1].x;
					brpoint[2].x = brpoint[2].x;
					brpoint[3].x = point.x;
					brpoint[0].y = brpoint[0].y;
					brpoint[1].y = brpoint[1].y;
					brpoint[2].y = point.y;
					brpoint[3].y = point.y;
					newPolyLine[PolyLine::nPolyLine].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 3)     //左上角缩放
				{
					brpoint[0].x = point.x;
					brpoint[1].x = brpoint[1].y;
					brpoint[2].x = brpoint[2].y;
					brpoint[3].x = point.x;
					brpoint[0].y = point.y;
					brpoint[1].y = point.y;
					brpoint[2].y = brpoint[2].y;
					brpoint[3].y = brpoint[3].y;
					newPolyLine[PolyLine::nPolyLine].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 4)     //右上角缩放
				{
					brpoint[0].x = brpoint[0].x;
					brpoint[1].x = point.x;
					brpoint[2].x = point.x;
					brpoint[3].x = brpoint[3].x;
					brpoint[0].y = point.y;
					brpoint[1].y = point.y;
					brpoint[2].y = brpoint[2].y;
					brpoint[3].y = brpoint[3].y;
					newPolyLine[PolyLine::nPolyLine].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				newPolyLine[PolyLine::nPolyLine].UpdatePtLine();
				chs = 0;
				Scale = FALSE;
				break;
			}
		case 3111:
			if (move) {
				newITriangle[ITriangle::nITriangle].currentPoint = point;
				newITriangle[ITriangle::nITriangle].Move(pDC);
				newITriangle[ITriangle::nITriangle].UpdateBorderpoint();
				newITriangle[ITriangle::nITriangle].setStartPoint(newITriangle[ITriangle::nITriangle].moveStartPoint);
				newITriangle[ITriangle::nITriangle].setOldPoint(newITriangle[ITriangle::nITriangle].moveEndPoint);

				str.Format(CString("%0.2f"), newITriangle[ITriangle::nITriangle].getLength(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newITriangle[ITriangle::nITriangle].getArea(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[0].x, newITriangle[ITriangle::nITriangle].pt[0].y);
				strPoint[1].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[1].x, newITriangle[ITriangle::nITriangle].pt[1].y);
				strPoint[2].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[2].x, newITriangle[ITriangle::nITriangle].pt[2].y);
				strPoint[3].Empty();
				sendPoint(strPoint);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 3);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
			}
			break;
		case 31111:
			if (Scale) {
				newITriangle[ITriangle::nITriangle].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;

				str.Format(CString("%0.2f"), newITriangle[ITriangle::nITriangle].getLength(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newITriangle[ITriangle::nITriangle].getArea(newITriangle[ITriangle::nITriangle].getStartPoint(), newITriangle[ITriangle::nITriangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[0].x, newITriangle[ITriangle::nITriangle].pt[0].y);
				strPoint[1].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[1].x, newITriangle[ITriangle::nITriangle].pt[1].y);
				strPoint[2].Format(CString("(%d , %d)"), newITriangle[ITriangle::nITriangle].pt[2].x, newITriangle[ITriangle::nITriangle].pt[2].y);
				strPoint[3].Empty();
				sendPoint(strPoint);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 3);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
			}
			break;
		case 3222:
			if (move) {
				newRTriangle[RTriangle::nRTriangle].currentPoint = point;
				newRTriangle[RTriangle::nRTriangle].Move(pDC);
				newRTriangle[RTriangle::nRTriangle].UpdateBorderpoint();
				newRTriangle[RTriangle::nRTriangle].setStartPoint(newRTriangle[RTriangle::nRTriangle].moveStartPoint);
				newRTriangle[RTriangle::nRTriangle].setOldPoint(newRTriangle[RTriangle::nRTriangle].moveEndPoint);

				str.Format(CString("%0.2f"), newRTriangle[RTriangle::nRTriangle].getLength(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newRTriangle[RTriangle::nRTriangle].getArea(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[0].x, newRTriangle[RTriangle::nRTriangle].pt[0].y);
				strPoint[1].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[1].x, newRTriangle[RTriangle::nRTriangle].pt[1].y);
				strPoint[2].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[2].x, newRTriangle[RTriangle::nRTriangle].pt[2].y);
				strPoint[3].Empty();
				sendPoint(strPoint);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 3);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
			}
			break;
		case 32222:
			if (Scale) {
				newRTriangle[RTriangle::nRTriangle].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;

				str.Format(CString("%0.2f"), newRTriangle[RTriangle::nRTriangle].getLength(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newRTriangle[RTriangle::nRTriangle].getArea(newRTriangle[RTriangle::nRTriangle].getStartPoint(), newRTriangle[RTriangle::nRTriangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[0].x, newRTriangle[RTriangle::nRTriangle].pt[0].y);
				strPoint[1].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[1].x, newRTriangle[RTriangle::nRTriangle].pt[1].y);
				strPoint[2].Format(CString("(%d , %d)"), newRTriangle[RTriangle::nRTriangle].pt[2].x, newRTriangle[RTriangle::nRTriangle].pt[2].y);
				strPoint[3].Empty();
				sendPoint(strPoint);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 3);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
			}
			break;
		case 444:
			if (move) {
				newRectangle[Rectangles::nRectangle].currentPoint = point;
				newRectangle[Rectangles::nRectangle].Move(pDC);
				newRectangle[Rectangles::nRectangle].UpdateBorderpoint();
				newRectangle[Rectangles::nRectangle].setStartPoint(newRectangle[Rectangles::nRectangle].moveStartPoint);
				newRectangle[Rectangles::nRectangle].setOldPoint(newRectangle[Rectangles::nRectangle].moveEndPoint);

				str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getLength(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getArea(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
				strPoint[1].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
				strPoint[2].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
				strPoint[3].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
				sendPoint(strPoint);
				str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().x - newRectangle[Rectangles::nRectangle].getOldPoint().x));
				sendWidth(str);
				str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().y - newRectangle[Rectangles::nRectangle].getOldPoint().y));
				sendHeight(str);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 4);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
			}
			break;
		case 4444:
			if (Scale) {
				newRectangle[Rectangles::nRectangle].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;

				newRectangle[Rectangles::nRectangle].setStartPoint(newRectangle[Rectangles::nRectangle].changStartPoint);
				newRectangle[Rectangles::nRectangle].setOldPoint(newRectangle[Rectangles::nRectangle].changEndPoint);
				str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getLength(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2f"), newRectangle[Rectangles::nRectangle].getArea(newRectangle[Rectangles::nRectangle].getStartPoint(), newRectangle[Rectangles::nRectangle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
				strPoint[1].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getStartPoint().y);
				strPoint[2].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getStartPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
				strPoint[3].Format(CString("(%d , %d)"), newRectangle[Rectangles::nRectangle].getOldPoint().x, newRectangle[Rectangles::nRectangle].getOldPoint().y);
				sendPoint(strPoint);
				str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().x - newRectangle[Rectangles::nRectangle].getOldPoint().x));
				sendWidth(str);
				str.Format(CString("%d"), abs(newRectangle[Rectangles::nRectangle].getStartPoint().y - newRectangle[Rectangles::nRectangle].getOldPoint().y));
				sendHeight(str);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Format(CString("%d"), 4);
				sendVertex(str);
				str.Empty();
				sendRadius(str);
			}
			break;
		case 555:
			if (move)
			{
				newMultiShape[MultiShape::nMultiShape].currentPoint = point;
				newMultiShape[MultiShape::nMultiShape].Move(pDC);
				newMultiShape[MultiShape::nMultiShape].UpdateBorderpoint();
				//newMultiShape[MultiShape::nMultiShape].Echo(pDC, newMultiShape[MultiShape::nMultiShape].getStartPoint(), newMultiShape[MultiShape::nMultiShape].getOldPoint());
			}
			break;
		case 5555:
			if (Scale)
			{
				newMultiShape[MultiShape::nMultiShape].currentPoint = point;
				newMultiShape[MultiShape::nMultiShape].ScaleManyVertices(pDC, chs);
				if (chs == 1)     //右下角缩放
				{
					brpoint[0].x = brpoint[0].x;
					brpoint[1].x = point.x;
					brpoint[2].x = point.x;
					brpoint[3].x = brpoint[3].x;
					brpoint[0].y = brpoint[0].y;
					brpoint[1].y = brpoint[1].y;
					brpoint[2].y = point.y;
					brpoint[3].y = point.y;
					newMultiShape[MultiShape::nMultiShape].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 2)     //左下角缩放
				{
					brpoint[0].x = point.x;
					brpoint[1].x = brpoint[1].x;
					brpoint[2].x = brpoint[2].x;
					brpoint[3].x = point.x;
					brpoint[0].y = brpoint[0].y;
					brpoint[1].y = brpoint[1].y;
					brpoint[2].y = point.y;
					brpoint[3].y = point.y;
					newMultiShape[MultiShape::nMultiShape].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 3)     //左上角缩放
				{
					brpoint[0].x = point.x;
					brpoint[1].x = brpoint[1].y;
					brpoint[2].x = brpoint[2].y;
					brpoint[3].x = point.x;
					brpoint[0].y = point.y;
					brpoint[1].y = point.y;
					brpoint[2].y = brpoint[2].y;
					brpoint[3].y = brpoint[3].y;
					newMultiShape[MultiShape::nMultiShape].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				else if (chs == 4)     //右上角缩放
				{
					brpoint[0].x = brpoint[0].x;
					brpoint[1].x = point.x;
					brpoint[2].x = point.x;
					brpoint[3].x = brpoint[3].x;
					brpoint[0].y = point.y;
					brpoint[1].y = point.y;
					brpoint[2].y = brpoint[2].y;
					brpoint[3].y = brpoint[3].y;
					newMultiShape[MultiShape::nMultiShape].setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
				}
				newMultiShape[MultiShape::nMultiShape].UpdateMultiPoint();
				chs = 0;
				Scale = FALSE;
				break;
			}
		case 666:
			if (move) {
				newCircle[Circle::nCircle].currentPoint = point;
				newCircle[Circle::nCircle].Move(pDC);
				newCircle[Circle::nCircle].UpdateBorderpoint();
				newCircle[Circle::nCircle].setStartPoint(newCircle[Circle::nCircle].moveStartPoint);
				newCircle[Circle::nCircle].setOldPoint(newCircle[Circle::nCircle].moveEndPoint);

				str.Format(CString("%0.2f"), newCircle[Circle::nCircle].getLength(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newCircle[Circle::nCircle].getArea(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%0.1f , %0.1f)"), fabs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().x + newCircle[Circle::nCircle].getOldPoint().x))), abs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().y + newCircle[Circle::nCircle].getOldPoint().y))));
				strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
				sendPoint(strPoint);
				str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
				sendRadius(str);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Empty();
				sendWidth(str);
				sendHeight(str);
				sendVertex(str);
			}
			break;
		case 6666:
			if (Scale) {
				newCircle[Circle::nCircle].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;

				str.Format(CString("%0.2f"), newCircle[Circle::nCircle].getLength(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newCircle[Circle::nCircle].getArea(newCircle[Circle::nCircle].getStartPoint(), newCircle[Circle::nCircle].getOldPoint()));
				sendArea(str);
				strPoint[0].Format(CString("(%0.1f , %0.1f)"), fabs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().x + newCircle[Circle::nCircle].getOldPoint().x))), abs(0.5 * float((newCircle[Circle::nCircle].getStartPoint().y + newCircle[Circle::nCircle].getOldPoint().y))));
				strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
				sendPoint(strPoint);
				str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
				sendRadius(str);
				strAxis[0].Empty(); strAxis[1].Empty();
				sendaxis(strAxis);
				str.Empty();
				sendWidth(str);
				sendHeight(str);
				sendVertex(str);
			}
			break;
		case 777:
			if (move) {
				newEllipse[Ellipses::nEllipse].currentPoint = point;
				newEllipse[Ellipses::nEllipse].Move(pDC);
				newEllipse[Ellipses::nEllipse].UpdateBorderpoint();
				newEllipse[Ellipses::nEllipse].setStartPoint(newEllipse[Ellipses::nEllipse].moveStartPoint);
				newEllipse[Ellipses::nEllipse].setOldPoint(newEllipse[Ellipses::nEllipse].moveEndPoint);

				str.Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getLength(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newEllipse[Ellipses::nEllipse].getArea(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendArea(str);
				strPoint[0].Empty(); strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
				sendPoint(strPoint);
				str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
				strAxis[0].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getmaxaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				strAxis[1].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getminaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendaxis(strAxis);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
				sendVertex(str);
			}
			break;
		case 7777:
			if (Scale) {
				newEllipse[Ellipses::nEllipse].changesize(brpoint, point, chs, pDC);
				chs = 0;
				Scale = FALSE;

				str.Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getLength(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendLength(str);
				str.Format(CString("%0.2lf"), newEllipse[Ellipses::nEllipse].getArea(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendArea(str);
				strPoint[0].Empty(); strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
				sendPoint(strPoint);
				str.Format(CString("%0.2f"), sqrt(pow((newCircle[Circle::nCircle].getOldPoint().x - newCircle[Circle::nCircle].getStartPoint().x), 2) * 2));
				strAxis[0].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getmaxaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				strAxis[1].Format(CString("%0.2f"), newEllipse[Ellipses::nEllipse].getminaxit(newEllipse[Ellipses::nEllipse].getStartPoint(), newEllipse[Ellipses::nEllipse].getOldPoint()));
				sendaxis(strAxis);
				str.Empty();
				sendRadius(str);
				sendWidth(str);
				sendHeight(str);
				sendVertex(str);
			}
			break;
	}
	CView::OnLButtonUp(nFlags, point);
}

void CGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CGraphicsView::OnFileOpen()
{
	//CString strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png |其他格式(*.*) | *.* || ");

	LPCTSTR strFilter = _T("BMP文件(*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, strFilter,
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, NULL);
	CString filepath;
	CFile file;

	//打开文件对话框
	if (dlg.DoModal() == IDOK)
	{
		filepath = dlg.GetPathName();
		if (file.Open(filepath, CFile::modeRead | CFile::shareDenyNone, NULL) == 0)
		{
			//读取文件失败
			AfxMessageBox(_T("无法打开文件！"), MB_OK, 0);
			return;
		}
		//读取文件头
		file.Read(&bf, sizeof(bf));
		//判断是否是BMP文件
		if (bf.bfType != 0x4d42)//'BM'
		{
			AfxMessageBox(_T("非BMP文件！"), MB_OK, 0);
			return;
		}
		//判断文件是否损坏
		if (file.GetLength() != bf.bfSize)
		{
			AfxMessageBox(_T("文件已损坏，请检查！"), MB_OK, 0);
			return;
		}

		//读文件信息头
		file.Read(&bi, sizeof(bi));

		//计算调色板数目
		numquad = 0;
		if (bi.biBitCount < 24)
		{
			numquad = 1 << bi.biBitCount;
		}

		//为图像信息pbi申请空间
		pbi = (BITMAPINFO*)HeapAlloc(
			GetProcessHeap(), 0, sizeof(BITMAPINFOHEADER) + numquad * sizeof(RGBQUAD));
		if (pbi == 0) {
			AfxMessageBox(_T("文件内无信息，请检查！"), MB_OK, 0);
			return;
		}
		else {
			memcpy(pbi, &bi, sizeof(bi));
		}
		quad = (RGBQUAD*)((BYTE*)pbi + sizeof(BITMAPINFOHEADER));

		//读取调色板
		if (numquad != 0)
		{
			file.Read(quad, sizeof(RGBQUAD) * numquad);
		}

		//为图像数据申请空间
		bi.biSizeImage = bf.bfSize - bf.bfOffBits;
		lpbuf = (BYTE*)HeapAlloc(GetProcessHeap(), 0, bi.biSizeImage);
		//读取图像数据
		file.Read(lpbuf, bi.biSizeImage);

		//图像读取完毕，关闭文件，设置标志
		file.Close();
		flagOpen = 1;

		Invalidate(FALSE);
	}
}


void CGraphicsView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CRect rect;
	BOOL  showMsgTag;					   //是否要弹出”图像保存成功对话框" 
	GetClientRect(&rect);                  //获取画布大小
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);

	//创建兼容位图
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
	//将屏幕DC的图像复制到内存DC中
	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像


	showMsgTag = TRUE;
	CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png |其他格式(*.*) | *.* || ");
	CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);

	if (dlg.DoModal() != IDOK)
		return;

	CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;

	if (dlg.m_ofn.nFileExtension == 0)               //扩展名项目为0
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName + "." + strExtension;
	}
	saveFilePath = strFileName;     //saveFilePath为视类中的全局变量,类型为CString

	HRESULT hResult = image.Save(saveFilePath);     //保存图像
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}
	else
	{
		if (showMsgTag) MessageBox(_T("文件保存成功！"));
	}
	image.Detach();
	SelectObject(hdc, hOldMap);
}


void CGraphicsView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	OnFileSaveAs();
}

void CGraphicsView::OnSingleLine() //线段控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 1;
}

void CGraphicsView::OnMultiLine() //多段折线控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 2;
}

void CGraphicsView::OnITriange()  //等腰三角形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 31;
}

void CGraphicsView::OnRTriangle()  //直角三角形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 32;
}

void CGraphicsView::OnTriangle()  //普通三角形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 33;
}

void CGraphicsView::OnRectangle()  //矩形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 4;
}

void CGraphicsView::OnMultiShape()  //N边形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 5;
}

void CGraphicsView::OnCircle()  //圆形控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 6;
}

void CGraphicsView::OnEllipse()  //椭圆控件
{
	// TODO: 在此添加命令处理程序代码
	flag = 7;
}


void CGraphicsView::OnRed()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;//设置颜色对话框的初始颜色由用户指定
	dlg.m_cc.rgbResult = RGB(0,0,0);//初始颜色
	if (IDOK == dlg.DoModal())
	{
		m_clr = dlg.m_cc.rgbResult;//保存用户选定的颜色
	}
	
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 6:
		newCircle[Circle::nCircle].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setColor(GetRValue(m_clr), GetGValue(m_clr), GetBValue(m_clr));
		break;
	}
}


void CGraphicsView::OnSolid_Line()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setLinear(PS_SOLID);
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_SOLID);
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_SOLID);
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setLinear(PS_SOLID);
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setLinear(PS_SOLID);
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setLinear(PS_SOLID);
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_SOLID);
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_SOLID);
		break;
	case 6:
		newCircle[Circle::nCircle].setLinear(PS_SOLID);
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setLinear(PS_SOLID);
		break;
	}
}

void CGraphicsView::OnDash_Line()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setLinear(PS_DASH);
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASH);
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASH);
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setLinear(PS_DASH);
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setLinear(PS_DASH);
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setLinear(PS_DASH);
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASH);
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASH);
		break;
	case 6:
		newCircle[Circle::nCircle].setLinear(PS_DASH);
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setLinear(PS_DASH);
		break;
	}
}


void CGraphicsView::OnDot_Line()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setLinear(PS_DOT);
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DOT);
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DOT);
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setLinear(PS_DOT);
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setLinear(PS_DOT);
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setLinear(PS_DOT);
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DOT);
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DOT);
		break;
	case 6:
		newCircle[Circle::nCircle].setLinear(PS_DOT);
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setLinear(PS_DOT);
		break;
	}
}

void CGraphicsView::OnDASHDOT_Line()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setLinear(PS_DASHDOT);
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASHDOT);
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASHDOT);
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setLinear(PS_DASHDOT);
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setLinear(PS_DASHDOT);
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setLinear(PS_DASHDOT);
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASHDOT);
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASHDOT);
		break;
	case 6:
		newCircle[Circle::nCircle].setLinear(PS_DASHDOT);
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setLinear(PS_DASHDOT);
		break;
	}
}

void CGraphicsView::OnDASHDOTDOT_Line()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		newLine[Line::nLine].setLinear(PS_DASHDOTDOT);
		break;
	case 2:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASHDOTDOT);
		break;
	case 22:
		newPolyLine[PolyLine::nPolyLine].setLinear(PS_DASHDOTDOT);
		break;
	case 31:
		newITriangle[ITriangle::nITriangle].setLinear(PS_DASHDOTDOT);
		break;
	case 32:
		newRTriangle[RTriangle::nRTriangle].setLinear(PS_DASHDOTDOT);
		break;
	case 4:
		newRectangle[Rectangles::nRectangle].setLinear(PS_DASHDOTDOT);
		break;
	case 5:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASHDOTDOT);
		break;
	case 55:
		newMultiShape[MultiShape::nMultiShape].setLinear(PS_DASHDOTDOT);
		break;
	case 6:
		newCircle[Circle::nCircle].setLinear(PS_DASHDOTDOT);
		break;
	case 7:
		newEllipse[Ellipses::nEllipse].setLinear(PS_DASHDOTDOT);
		break;
	}
}

void CGraphicsView::OnLineWidth()
{
	// TODO: 在此添加命令处理程序代码
	Line_With dlg;
	dlg.m_LineWidth = m_LineWidth;
	if (IDOK == dlg.DoModal())
	{
		m_LineWidth = dlg.m_LineWidth;
		switch (flag)
		{
		case 1:
			newLine[Line::nLine].setLineWidth(m_LineWidth);
			break;
		case 2:
			newPolyLine[PolyLine::nPolyLine].setLineWidth(m_LineWidth);
			break;
		case 22:
			newPolyLine[PolyLine::nPolyLine].setLineWidth(m_LineWidth);
			break;
		case 31:
			newITriangle[ITriangle::nITriangle].setLineWidth(m_LineWidth);
			break;
		case 32:
			newRTriangle[RTriangle::nRTriangle].setLineWidth(m_LineWidth);
			break;
		case 4:
			newRectangle[Rectangles::nRectangle].setLineWidth(m_LineWidth);
			break;
		case 5:
			newMultiShape[MultiShape::nMultiShape].setLineWidth(m_LineWidth);
			break;
		case 55:
			newMultiShape[MultiShape::nMultiShape].setLineWidth(m_LineWidth);
			break;
		case 6:
			newCircle[Circle::nCircle].setLineWidth(m_LineWidth);
			break;
		case 7:
			newEllipse[Ellipses::nEllipse].setLineWidth(m_LineWidth);
			break;
		}
	}
}

void CGraphicsView::sendLength(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_Length = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendArea(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_Area = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendPoint(CString* str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_Point[0] = str[0];
	pDoc->m_Point[1] = str[1];
	pDoc->m_Point[2] = str[2];
	pDoc->m_Point[3] = str[3];
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendaxis(CString* str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_axis[0] = str[0];
	pDoc->m_axis[1] = str[1];
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendRadius(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_radius = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendWidth(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_width = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendHeight(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_height = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::sendVertex(CString& str)
{
	CGraphicsDoc* pDoc = GetDocument();
	pDoc->m_vertex = str;
	pDoc->UpdateAllViews(this);
}

void CGraphicsView::OnCountLine()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有线段 %d 条"),Line::nLine);
	MessageBox(str,_T("线段个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountMultiLine()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有多段折线 %d 条"), PolyLine::nPolyLine);
	MessageBox(str, _T("多段折线个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountITriangle()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有等腰三角形 %d 个"), ITriangle::nITriangle);
	MessageBox(str, _T("等腰三角形个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountRTriangle()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有直角三角形 %d 个"), RTriangle::nRTriangle);
	MessageBox(str, _T("直角三角形个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountRectangle()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有矩形 %d 个"), Rectangles::nRectangle);
	MessageBox(str, _T("矩形个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountMultiShape()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有任意N边形 %d 个"), MultiShape::nMultiShape);
	MessageBox(str, _T("任意N边形个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountCircle()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有圆形 %d 个"), Circle::nCircle);
	MessageBox(str, _T("圆形个数统计"));
	str.Empty();
}

void CGraphicsView::OnCountEllipse()
{
	// TODO: 在此添加命令处理程序代码
	str.Format(CString("当前界面有椭圆形 %d 个"), Ellipses::nEllipse);
	MessageBox(str, _T("椭圆形个数统计"));
	str.Empty();
}


void CGraphicsView::OnBottenMove()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		flag = 111;
		Line::nLine--;
		break;
	case 2:
		flag = 222;
		PolyLine::nPolyLine--;
		break;
	case 31:
		flag = 3111;
		ITriangle::nITriangle--;
		break;
	case 32:
		flag = 3222;
		RTriangle::nRTriangle--;
		break;
	case 4:
		flag = 444;
		Rectangles::nRectangle--;
		break;
	case 5:
		flag = 555;
		MultiShape::nMultiShape--;
		break;
	case 6:
		flag = 666;
		Circle::nCircle--;
		break;
	case 7:
		flag = 777;
		Ellipses::nEllipse--;
		break;
	}
}


void CGraphicsView::OnChangeSize()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		flag = 1111;
		Line::nLine--;
		break;
	case 2:
		flag = 2222;
		PolyLine::nPolyLine--;
		break;
	case 31:
		flag = 31111;
		ITriangle::nITriangle--;
		break;
	case 32:
		flag = 32222;
		RTriangle::nRTriangle--;
		break;
	case 4:
		flag = 4444;
		Rectangles::nRectangle--;
		break;
	case 5:
		flag = 5555;
		MultiShape::nMultiShape--;
		break;
	case 6:
		flag = 6666;
		Circle::nCircle--;
		break;
	case 7:
		flag = 7777;
		Ellipses::nEllipse--;
		break;
	}
}


void CGraphicsView::OnRotate()
{
	// TODO: 在此添加命令处理程序代码
	switch (flag)
	{
	case 1:
		flag = 11111;
		Line::nLine--;
		break;
	case 2:
		flag = 22222;
		PolyLine::nPolyLine--;
		break;
	case 31:
		flag = 311111;
		ITriangle::nITriangle--;
		break;
	case 32:
		flag = 322222;
		RTriangle::nRTriangle--;
		break;
	case 4:
		flag = 44444;
		Rectangles::nRectangle--;
		break;
	case 5:
		flag = 55555;
		MultiShape::nMultiShape--;
		break;
	case 7:
		flag = 77777;
		Ellipses::nEllipse--;
		break;
	}
}


void CGraphicsView::OnClearDraw()
{
	// TODO: 在此添加命令处理程序代码


	Invalidate();

	Line::nLine = 0;
	PolyLine::nPolyLine = 0;
	ITriangle::nITriangle = 0;
	RTriangle::nRTriangle = 0;
	Rectangles::nRectangle = 0;
	MultiShape::nMultiShape = 0;
	Circle::nCircle = 0;
	Ellipses::nEllipse = 0;

	strPoint[0].Empty(); strPoint[1].Empty(); strPoint[2].Empty(); strPoint[3].Empty();
	sendPoint(strPoint);
	strAxis[0].Empty(); strAxis[1].Empty();
	sendaxis(strAxis);
	str.Empty();
	sendRadius(str);
	sendWidth(str);
	sendHeight(str);
	sendVertex(str);
	sendLength(str);
	sendArea(str);

	delete[] newMultiShape;
	delete[] newRTriangle;
	delete[] newITriangle;
	delete[] newRectangle;
	delete[] newCircle;
	delete[] newEllipse;
	delete[] newLine;
	delete[] newPolyLine;
	delete[] strPoint;
	delete[] strAxis;

	flag = 0;
	m_startRect = FALSE;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_LineWidth = 0;
	move = false;

	numquad = 0; //调色板数
	flagOpen = 0; //标志是否打开bmp
	pbi = 0; //记录图像细节
	lpbuf = 0; //图像数据
	quad = 0; //调色板

	if ((newMultiShape = new MultiShape[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newRTriangle = new RTriangle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newITriangle = new ITriangle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newRectangle = new Rectangles[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newCircle = new Circle[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newEllipse = new Ellipses[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newLine = new Line[MAX]) == NULL)
	{
		exit(0);
	}
	if ((newPolyLine = new PolyLine[MAX]) == NULL)
	{
		exit(0);
	}
	if ((strPoint = new CString[4]) == NULL)
	{
		exit(0);
	}
	if ((strAxis = new CString[2]) == NULL)
	{
		exit(0);
	}
}
