
// LLKan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#define GAMEWND_WIDTH 800
#define GAMEWND_HEIGHT 600

// CLLKanApp: 
// �йش����ʵ�֣������ LLKan.cpp
//

class CLLKanApp : public CWinApp
{
public:
	CLLKanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLLKanApp theApp;