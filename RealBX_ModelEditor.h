
// RealBX_ModelEditor.h : RealBX_ModelEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CRealBX_ModelEditorApp:
// �� Ŭ������ ������ ���ؼ��� RealBX_ModelEditor.cpp�� �����Ͻʽÿ�.
//

class CRealBX_ModelEditorApp : public CWinApp
{
public:
	CRealBX_ModelEditorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRealBX_ModelEditorApp theApp;
