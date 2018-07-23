#include "stdafx.h"
#include "Sprite.h"
CWnd* Sprite::m_pParentWnd = NULL;

Sprite::Sprite()
{
	m_rcSprite;
	m_nMoveStep = 0;
	m_nStepX = 0;
	m_nStepY = 0;
	m_Bmp;
	m_nCol = 0;
	m_nRow = 0;
	m_idxPic = 0;
}

Sprite::~Sprite()
{

}

void Sprite::LoadImage(const CString& strBitmapFile, int nRow, int nCol)
{
	//ASSERT(strBitmapFile != ""&&nRow > 0 && nCol > 0);
	HRESULT ret = m_Bmp.Load(strBitmapFile);
	if (ret == NOERROR)
	{
		m_nRow = nRow;
		m_nCol = nCol;
		/*随机数生成
		int randn = time(NULL);
		srand((unsigned)randn * 19019);
		*/
		int x = rand() % 833 + 100;
		int y = rand() % 254 + 100;
		int cx = m_Bmp.GetWidth() / nCol;
		int cy = m_Bmp.GetHeight() / nRow;
		m_rcSprite.SetRect(x, y, x + cx, y + cy);
	}
	else
	{
		CString strPrompt;
		strPrompt.Format(_T("Load image file <%s> failed!"), strBitmapFile);
		AfxMessageBox(strPrompt);
	}
}

CSize Sprite::GetPictureDimension() const
{
	int width = m_Bmp.GetWidth();
	int height = m_Bmp.GetHeight();
	return CSize(width, height);
}

CSize Sprite::GetSinglePicture() const
{
	int width = m_Bmp.GetWidth() / m_nCol;
	int height = m_Bmp.GetHeight() / m_nRow;
	return CSize(width, height);
}

void Sprite::Draw(CDC*pDC)
{
	int nRow = m_idxPic / m_nCol;
	int nCol = m_idxPic % m_nCol;
	int cx = m_rcSprite.Width();
	int cy = m_rcSprite.Height();
	int x = nCol*m_rcSprite.Width();
	int y = nRow*m_rcSprite.Height();
	COLORREF clrBkgnd = m_Bmp.GetPixel(x, y);
	m_Bmp.TransparentBlt(pDC->GetSafeHdc(), m_rcSprite.left, m_rcSprite.top, cx, cy, x, y, cx, cy, clrBkgnd);
}

void Sprite::SetPictureIdx(int idx)
{
	m_idxPic = idx;
	double angle = idx*6.2832 / GetPictureCount();
	m_nStepX = int(m_nMoveStep*cos(angle));
	m_nStepY = -int(m_nMoveStep*sin(angle));
}

BOOL Sprite::AtLeftEdge() const {
	if (m_pParentWnd)
		return m_rcSprite.left <= 0;
	return FALSE;
}

BOOL Sprite::AtRightEdge() const {
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);
	if (m_pParentWnd)
		return m_rcSprite.right >= rectClient.Width();
	return FALSE;
}

BOOL Sprite::AtTopEdge() const {
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);
	if (m_pParentWnd)
		return m_rcSprite.top <= 0;
	return FALSE;
}

BOOL Sprite::AtBottomEdge() const {
	CRect rectClient;
	m_pParentWnd->GetClientRect(rectClient);
	if (m_pParentWnd)
		return m_rcSprite.bottom > rectClient.Height();
	return FALSE;
}
