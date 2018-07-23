
// BugHunt2016AView.h : CBugHunt2016AView 类的接口
//

#pragma once
#include <vector>
#include "Sprite.h"
#include "Bug.h"
#include "Frog.h"

class CBugHunt2016AView : public CView
{
protected: // 仅从序列化创建
	CBugHunt2016AView();
	DECLARE_DYNCREATE(CBugHunt2016AView)
// 特性
public:
	CBugHunt2016ADoc* GetDocument() const;

// 操作
public:

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
	virtual ~CBugHunt2016AView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImage m_background;
	CBitmap m_memBmp;
	Frog frog;
	std::vector<Bug*> m_vecSprites;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // BugHunt2016AView.cpp 中的调试版本
inline CBugHunt2016ADoc* CBugHunt2016AView::GetDocument() const
   { return reinterpret_cast<CBugHunt2016ADoc*>(m_pDocument); }
#endif

