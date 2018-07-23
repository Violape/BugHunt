#pragma once
#include <afxwin.h>
#include "Sprite.h"

class Bug : public Sprite
{
public:
	Bug(const CString& strBitmapFile, int nRow, int nCol,
		int nMoveStep, int nSpeed, int nHitsRequired,
		int nDirChangeProb);
	virtual ~Bug();

	BOOL IsHit(const CPoint& ptMouse);
	BOOL IsDying()const { return (m_iHitsTaken >= m_nHitsRequired); };
	void Kill(CDC* pDC);
	void IsEaten();

	void ChangeDirection();
	virtual void Move() = 0;

protected:
	int  GetCurrDir()const{ return m_iCurrentDir; }
	void SetCurrDir(int iDirection){ m_iCurrentDir = iDirection; }
	int  GetDirChangeProb()const{ return m_nDirChangeProb; }

protected:
	int m_nHitsRequired;    //the required hit number to kill the bug
	int m_iHitsTaken;       //the hit number that bug has be taken
	int m_nDirChangeProb;   //the probs of the bug changing direction
	int m_iCurrentDir;      //the current moving direction
	int m_nSpeed;           //the moving speed of bug (the time to refresh, Unite: ms) 
};

class FastBug : public Bug
{
public:
	FastBug(const CString& strBitmapFile, int nRow, int nCol,
		int nMoveStep, int nSpeed, int nHitsRequired,
		int nDirChangeProb) :
		Bug(strBitmapFile, nRow, nCol, nMoveStep, nSpeed, nHitsRequired, nDirChangeProb){}

	~FastBug(){}

	virtual void Move();
};

class SlowBug : public Bug
{
public:
	SlowBug(const CString& strBitmapFile, int nRow, int nCol,
		int nMoveStep, int nSpeed, int nHitsRequired,
		int nDirChangeProb):
		Bug(strBitmapFile, nRow, nCol, nMoveStep, nSpeed, nHitsRequired, nDirChangeProb){}

	~SlowBug(){}

	virtual void Move();
};