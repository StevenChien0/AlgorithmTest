
// AlgorithmTest.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CAlgorithmTestApp: 
// �аѾ\��@�����O�� AlgorithmTest.cpp
//

class CAlgorithmTestApp : public CWinApp
{
public:
	CAlgorithmTestApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CAlgorithmTestApp theApp;