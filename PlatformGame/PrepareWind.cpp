#include "PrepareWind.h"
#include "GameDirector.h"

PrepareWind::PrepareWind()
{
	cbSize				= sizeof(WNDCLASSEX);
	style				= CS_HREDRAW | CS_VREDRAW;
	lpfnWndProc			= GameDirector::WndProc;
	cbClsExtra			= 0;
	cbWndExtra			= 0;
	hIcon				= nullptr;
	hCursor				= LoadCursor(nullptr, IDC_ARROW);
	hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	lpszClassName		= (LPCSTR)TEXT("winclass");
	lpWindowName		= (LPCSTR)TEXT("PlatformGame");
	dwStyle				= WS_OVERLAPPEDWINDOW;
	X					= CW_USEDEFAULT;
	Y					= CW_USEDEFAULT;
	nWidth				= 920;
	nHeight				= 800;
	hWndParent			= nullptr;
	hMenu				= nullptr;
	lpParam				= nullptr;

	nCmdShow			= SW_SHOW;
}

PrepareWind::~PrepareWind()
{
}
