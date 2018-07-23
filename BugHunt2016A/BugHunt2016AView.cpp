
// BugHunt2016AView.cpp : CBugHunt2016AView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BugHunt2016A.h"
#endif

#include "BugHunt2016ADoc.h"
#include "BugHunt2016AView.h"
#include "Sprite.h"
#include "Bug.h"
#include "Frog.h"

#include   <mmsystem.h>   
#pragma   comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBugHunt2016AView

IMPLEMENT_DYNCREATE(CBugHunt2016AView, CView)

BEGIN_MESSAGE_MAP(CBugHunt2016AView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CBugHunt2016AView ����/����

CBugHunt2016AView::CBugHunt2016AView() :frog(_T(".\\Bitmap\\Frogblue.bmp"), 1, 2, 20)
{
	// TODO: �ڴ˴���ӹ������
	HRESULT loadresult = m_background.Load(_T(".\\Bitmap\\Frog.jpg"));
	if (loadresult != S_OK)
		AfxMessageBox(_T("Load Failed!"));
	AfxMessageBox(_T("Welcome to Bug Hunt 2016A designed by Lorenzo Wu!\nMove Fast: four arrows\nMove Slowly: W A S D\nEat the bug: Space\nYou can also kill the bugs by clicking on them!\nEnjoy your game!"));
	for (int i = 0; i < 10; i++)
	{
		Bug* fbug = new FastBug(_T(".\\Bitmap\\BlueBug36x36.bmp" ), 4, 18, 3, 15, 3, 6);
		m_vecSprites.push_back(fbug);
		Bug* sbug = new SlowBug(_T(".\\Bitmap\\LargeBug64x64.bmp"), 4, 18, 3, 15, 3, 3);
		m_vecSprites.push_back(sbug);
	}
	Sprite::SetParentWnd(this);
	sndPlaySound(_T(".\\res\\bgm.wav"), SND_ASYNC | SND_LOOP);
}

CBugHunt2016AView::~CBugHunt2016AView()
{

}

BOOL CBugHunt2016AView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBugHunt2016AView ����

void CBugHunt2016AView::OnDraw(CDC* pDC)
{
	CBugHunt2016ADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	CRect rectClient;
	GetClientRect(&rectClient);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&m_memBmp);
	memDC.FillSolidRect(rectClient, RGB(255, 255, 255));
	int x = (rectClient.Width() - m_background.GetWidth())/2;
	int y = (rectClient.Height() - m_background.GetHeight()) / 2;
	m_background.Draw(memDC.GetSafeHdc(), x, y);
	for each (auto p in m_vecSprites)
		if(p)
			p->Draw(&memDC);
	frog.Draw(&memDC);
	pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
}

BOOL CBugHunt2016AView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBugHunt2016AView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBugHunt2016AView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CBugHunt2016AView ���

#ifdef _DEBUG
void CBugHunt2016AView::AssertValid() const
{
	CView::AssertValid();
}

void CBugHunt2016AView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBugHunt2016ADoc* CBugHunt2016AView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBugHunt2016ADoc)));
	return (CBugHunt2016ADoc*)m_pDocument;
}
#endif //_DEBUG


// CBugHunt2016AView ��Ϣ�������


int CBugHunt2016AView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(0, 15, 0);
	return 0;
}

void CBugHunt2016AView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	for each(auto p in m_vecSprites)
		if(p)
			p->Move();
	Invalidate();
	CView::OnTimer(nIDEvent);
}


BOOL CBugHunt2016AView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}


void CBugHunt2016AView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_memBmp.GetSafeHandle())
		m_memBmp.DeleteObject();
	CDC*pDC = GetDC();
	if (pDC)
		m_memBmp.CreateCompatibleBitmap(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CBugHunt2016AView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BOOL flag = 1;
	for (size_t i = 0; i < m_vecSprites.size(); ++i)
	{
		Bug* bug = dynamic_cast<Bug*>(m_vecSprites[i]);
		if (bug&&bug->IsHit(point) && bug->IsDying())
		{
			delete bug;
			m_vecSprites[i] = NULL;
		}
		if (bug)
			flag = 0;
	}
	if(flag)
		AfxMessageBox(_T("Congratulations! You win!"));
}

void CBugHunt2016AView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case 'W':
	case 'w':
		frog.SetCurrDir(1);
		frog.Move();
		break;
	case 'S':
	case 's':
		frog.SetCurrDir(2);
		frog.Move();
		break;
	case 'A':
	case 'a':
		frog.SetCurrDir(3);
		frog.SetPictureIdx(1);
		frog.Move();
		break;
	case 'D':
	case 'd':
		frog.SetCurrDir(4);
		frog.SetPictureIdx(0);
		frog.Move();
		break;
	case VK_UP:
		frog.SetCurrDir(1);
		frog.Move();
		frog.Move();
		break;
	case VK_DOWN:
		frog.SetCurrDir(2);
		frog.Move();
		frog.Move();
		break;
	case VK_LEFT:
		frog.SetCurrDir(3);
		frog.SetPictureIdx(1);
		frog.Move();
		frog.Move();
		break;
	case VK_RIGHT:
		frog.SetCurrDir(4);
		frog.SetPictureIdx(0);
		frog.Move();
		frog.Move();
		break;
	case VK_SPACE:
		for each(auto p in m_vecSprites)
		{
			if (p != NULL)
			{
				if (frog.GetPictureIdx() == 0)
					if (p->m_rcSprite.left<frog.m_rcSprite.right
						&& p->m_rcSprite.right>frog.m_rcSprite.right
						&& p->m_rcSprite.top < frog.m_rcSprite.top + 10
						&& p->m_rcSprite.bottom>frog.m_rcSprite.top + 30)
					{
						p->IsEaten();
					}
				if (frog.GetPictureIdx() == 1)
					if (p->m_rcSprite.left<frog.m_rcSprite.left
						&& p->m_rcSprite.right>frog.m_rcSprite.left
						&& p->m_rcSprite.top<frog.m_rcSprite.top+10
						&& p->m_rcSprite.bottom>frog.m_rcSprite.top + 30)
					{
						p->IsEaten();
					}
			}
		}
		BOOL flag = 1;
		for (size_t i = 0; i < m_vecSprites.size(); ++i)
		{
			Bug* bug = dynamic_cast<Bug*>(m_vecSprites[i]);
			if (bug && bug->IsDying())
			{
				delete bug;
				m_vecSprites[i] = NULL;
			}
			if (bug)
				flag = 0;
		}
		if(flag)
			AfxMessageBox(_T("Congratulations! You win!"));
}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
