
// JX3KeyBoard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJX3KeyBoardApp: 
// �йش����ʵ�֣������ JX3KeyBoard.cpp
//

class CJX3KeyBoardApp : public CWinApp
{
public:
	CJX3KeyBoardApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJX3KeyBoardApp theApp;