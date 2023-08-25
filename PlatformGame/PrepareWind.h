#pragma once
#include "GameDefine.h"

class PrepareWind
{
public: 
	//window class�� ����� �Ҷ� �ʿ��� ������
	UINT		cbSize;
	UINT		style;
	WNDPROC		lpfnWndProc;
	int			cbClsExtra;
	int			cbWndExtra;
	HINSTANCE	hInstance;
	HICON		hIcon;
	HCURSOR		hCursor;
	HBRUSH		hbrBackground;
	LPCSTR		lpszMenuName;
	LPCSTR		lpszClassName;

public:
	//window â�� ���鶧 �ʿ��� ������
	LPCSTR		lpWindowName;
	DWORD		dwStyle;
	int			X;
	int			Y;
	int			nWidth;
	int			nHeight;
	HWND		hWndParent;
	HMENU		hMenu;
	LPVOID		lpParam;

	int nCmdShow;

public:
	PrepareWind();
	~PrepareWind();
};

