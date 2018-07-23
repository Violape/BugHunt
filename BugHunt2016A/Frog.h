#pragma once
#include <afxwin.h>
#include "Sprite.h"

class Frog : public Sprite
{
public:
	Frog(const CString& strBitmapFile, int nRow, int nCol,
		int nMoveStep);

	void Move();

	int m_iCurrentDir;
	int GetCurrDir()const { return m_iCurrentDir; }
	void SetCurrDir(int iDirection) { m_iCurrentDir = iDirection; }
};