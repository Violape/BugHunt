#include "stdafx.h"
#include "Bug.h"
Bug::Bug(const CString& strBitmapFile, int nRow, int nCol,
	int nMoveStep, int nSpeed, int nHitsRequired,
	int nDirChangeProb)
{
	m_nMoveStep = nMoveStep;
	m_nSpeed = nSpeed;
	m_nHitsRequired = nHitsRequired;
	m_nDirChangeProb = nDirChangeProb;
	m_iHitsTaken = 0;
	m_iCurrentDir = 0;
	LoadImage(strBitmapFile, nRow, nCol);
	/*随机数生成
	int randn = time(NULL);
	srand((unsigned)randn * 40145);
	*/
	m_iCurrentDir = rand() % 36;
	SetPictureIdx(m_iCurrentDir);
}

Bug::~Bug()
{

}
void Bug::IsEaten()
{
	m_iHitsTaken = m_nHitsRequired;
}

BOOL Bug::IsHit(const CPoint&ptMouse)
{
	if (m_rcSprite.PtInRect(ptMouse))
	{
		CRect RectClient;
		m_pParentWnd->GetClientRect(RectClient);
		int x = ptMouse.x - m_rcSprite.left;
		int y = ptMouse.y - m_rcSprite.top;
		BOOL bHit = m_Bmp.GetPixel(x, y) != m_Bmp.GetPixel(0, 0);
		if (bHit)
			++m_iHitsTaken;

		return bHit;
	}
	return FALSE;
}

void Bug::ChangeDirection()
{
	int nProb = rand() % 100;
	if (nProb < m_nDirChangeProb)
	{
		m_iCurrentDir = rand() % GetPictureCount();
		SetPictureIdx(m_iCurrentDir);
	}
}

void FastBug::Move()
{
	ChangeDirection();
	m_rcSprite.OffsetRect(m_nStepX, m_nStepY);
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);

	int xOff = rectClient.Width() - m_rcSprite.Width();
	int yOff = rectClient.Height() - m_rcSprite.Height();
	if (AtLeftEdge())
		m_rcSprite.OffsetRect(xOff, 0);
	if (AtTopEdge()) 
		m_rcSprite.OffsetRect(0, yOff);
	if (AtRightEdge())
		m_rcSprite.OffsetRect(-xOff, 0);
	if (AtBottomEdge())
		m_rcSprite.OffsetRect(0, -yOff);
}

void SlowBug::Move()
{
	m_rcSprite.OffsetRect(m_nStepX, m_nStepY);
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);
	BOOL l = AtLeftEdge();
	BOOL r = AtRightEdge();
	BOOL t = AtTopEdge();
	BOOL b = AtBottomEdge();
	if (l||r||t||b)
	{
		int nDirs = GetPictureCount() / 2;
		m_iCurrentDir >= nDirs ? m_iCurrentDir -= nDirs : m_iCurrentDir += nDirs;
		SetPictureIdx(m_iCurrentDir);
	}
	else
		ChangeDirection();
	CSize dim = GetSinglePicture();
	if (m_rcSprite.right > rectClient.Width())
	{
		m_rcSprite.left = rectClient.Width() - dim.cx;
		m_rcSprite.right = rectClient.Width();
	}
}