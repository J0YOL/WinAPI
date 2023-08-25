#pragma once
#include "GameDefine.h"

class PrepareWind
{
public: 
	//window class를 등록을 할때 필요한 정보들
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
	//window 창을 만들때 필요한 정보들
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

