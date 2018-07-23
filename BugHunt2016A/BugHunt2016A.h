
// BugHunt2016A.h : BugHunt2016A 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CBugHunt2016AApp:
// 有关此类的实现，请参阅 BugHunt2016A.cpp
//

class CBugHunt2016AApp : public CWinApp
{
public:
	CBugHunt2016AApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBugHunt2016AApp theApp;
