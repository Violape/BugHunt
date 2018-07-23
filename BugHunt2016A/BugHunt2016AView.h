
// BugHunt2016AView.h : CBugHunt2016AView ��Ľӿ�
//

#pragma once
#include <vector>
#include "Sprite.h"
#include "Bug.h"
#include "Frog.h"

class CBugHunt2016AView : public CView
{
protected: // �������л�����
	CBugHunt2016AView();
	DECLARE_DYNCREATE(CBugHunt2016AView)
// ����
public:
	CBugHunt2016ADoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
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

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // BugHunt2016AView.cpp �еĵ��԰汾
inline CBugHunt2016ADoc* CBugHunt2016AView::GetDocument() const
   { return reinterpret_cast<CBugHunt2016ADoc*>(m_pDocument); }
#endif

