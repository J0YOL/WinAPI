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

	//value���� ����(�Ű������� ���ؼ�)
	PrepareWind value;

	value.hInstance = hInstance;
	value.nCmdShow = nCmdShow;

	//�� value�� ������ Window����
	this->registerWndClass(value);
	this->createWindow(value);
	this->showWindow(value);

	return this->MessageLoop();
}

void WrappedWind::registerWndClass(const PrepareWind & value)
{
	//���״�� ����ϴ� �Լ�(���� ����)
	WNDCLASSEX wcex = { 0, };

	wcex.cbSize			= sizeof(wcex);
	wcex.style			= value.style;
	wcex.hInstance		= value.hInstance;
	wcex.hCursor		= value.hCursor;
	wcex.hbrBackground	= value.hbrBackground;
	wcex.lpszClassName	= (LPCSTR)value.lpszClassName;
	wcex.lpfnWndProc	= value.lpfnWndProc;

	RegisterClassEx(&wcex);  //���
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
	memset(&msg, 0, sizeof(msg)); //0���� �ʱ�ȭ

	//�� ���� �Լ�

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
