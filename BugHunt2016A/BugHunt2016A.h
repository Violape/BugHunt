
// BugHunt2016A.h : BugHunt2016A Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBugHunt2016AApp:
// �йش����ʵ�֣������ BugHunt2016A.cpp
//

class CBugHunt2016AApp : public CWinApp
{
public:
	CBugHunt2016AApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBugHunt2016AApp theApp;
