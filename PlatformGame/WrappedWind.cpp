#include "WrappedWind.h"
#include "PrepareWind.h"

HWND WrappedWind::GetWindHandle()
{
	return m_hWnd;
}

HINSTANCE WrappedWind::GetInstanceHandle()
{
	return m_hInstance;
}

WrappedWind::WrappedWind()
{
}

WrappedWind::~WrappedWind()
{
}

int WrappedWind::Loop(HINSTANCE hInstance, LPSTR IpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;

	//value값을 설정(매개변수를 통해서)
	PrepareWind value;

	value.hInstance = hInstance;
	value.nCmdShow = nCmdShow;

	//이 value의 값으로 Window설정
	this->registerWndClass(value);
	this->createWindow(value);
	this->showWindow(value);

	return this->MessageLoop();
}

void WrappedWind::registerWndClass(const PrepareWind & value)
{
	//말그대로 등록하는 함수(값을 정비)
	WNDCLASSEX wcex = { 0, };

	wcex.cbSize			= sizeof(wcex);
	wcex.style			= value.style;
	wcex.hInstance		= value.hInstance;
	wcex.hCursor		= value.hCursor;
	wcex.hbrBackground	= value.hbrBackground;
	wcex.lpszClassName	= (LPCSTR)value.lpszClassName;
	wcex.lpfnWndProc	= value.lpfnWndProc;

	RegisterClassEx(&wcex);  //등록
}

void WrappedWind::createWindow(const PrepareWind & value)
{
	m_hWnd = CreateWindow(
		value.lpszClassName, value.lpWindowName, value.dwStyle,
		value.X, value.Y, value.nWidth, value.nHeight,
		value.hWndParent, value.hMenu, value.hInstance, value.lpParam);
}

void WrappedWind::showWindow(const PrepareWind & value)
{
	ShowWindow(m_hWnd, value.nCmdShow);
	UpdateWindow(m_hWnd);
}

int WrappedWind::MessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg)); //0으로 초기화

	//씬 설정 함수

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->ProcessingLoop();
		}
	}

	return (int)msg.wParam;
}
