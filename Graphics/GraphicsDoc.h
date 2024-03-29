﻿
// GraphicsDoc.h: CGraphicsDoc 类的接口
//


#pragma once


class CGraphicsDoc : public CDocument
{
protected: // 仅从序列化创建
	CGraphicsDoc() noexcept;
	DECLARE_DYNCREATE(CGraphicsDoc)

// 特性
public:
	
// 操作
public:
	
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CGraphicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CString m_Length;//周长
	CString m_Area;//面积
	CString m_Point[4];//四边形一下的顶点
	CString m_axis[2];//长、短半轴
	CString m_radius;//半径
	CString m_width;//矩形长
	CString m_height;//矩形宽
	CString m_vertex;//顶点个数
};
