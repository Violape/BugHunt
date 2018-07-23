#include "stdafx.h"
#include "Frog.h"
Frog::Frog(const CString& strBitmapFile, int nRow, int nCol,
	int nMoveStep)
{
	m_nMoveStep = nMoveStep;
	LoadImage(strBitmapFile, nRow, nCol);
}

void Frog::Move()
{
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);
	int dir = GetCurrDir();
	switch (dir)
	{
	case 1: 
		if(m_nMoveStep < m_rcSprite.top)
			m_rcSprite.OffsetRect(0, -m_nMoveStep);
		break;
	case 2:
		if (m_rcSprite.bottom + m_nMoveStep < rectClient.Height())
			m_rcSprite.OffsetRect(0, m_nMoveStep);
		break;
	case 3:
		if (m_nMoveStep < m_rcSprite.left)
			m_rcSprite.OffsetRect(-m_nMoveStep, 0);
		break;
	case 4:
		if (m_rcSprite.right + m_nMoveStep < rectClient.Width())
			m_rcSprite.OffsetRect(m_nMoveStep, 0);
		break;
	}
}