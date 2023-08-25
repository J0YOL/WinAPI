#include "GameDirector.h"

GameDirector::GameDirector()
{
	ApplicationHandle = this;
	m_SceneManager = new SceneManager;
}

GameDirector::~GameDirector()
{
	delete m_SceneManager;
}

GameDirector * GameDirector::GetGameDirector()
{
	static GameDirector dir;
	return &dir;
}

LRESULT GameDirector::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return ApplicationHandle->MessageHandler(hwnd, message, wParam, IParam);
	}
}

LRESULT GameDirector::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		//마우스가 움직였을때 (LOWORD와 HIWORD비교)
		m_SceneManager->SetMousePosition(LOWORD(IParam), HIWORD(IParam));
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, IParam);
}

void GameDirector::ProcessingLoop()
{
	//Update, Render호출
	static DWORD prevFrameTime = 0;  //이전의 프레임타임을 체크

	//-> 프레임타임이 항상 60을 유지하도록
	if (GetTickCount() - prevFrameTime > m_FrameInterval)
	{
		prevFrameTime = GetTickCount();
		HDC hdc = GetDC(m_hWnd);

		Update(((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		Render(hdc, ((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		ReleaseDC(m_hWnd, hdc);
	}

}

void GameDirector::Update(float dt)
{
	m_SceneManager->Update(dt);
}

void GameDirector::Render(HDC hdc, float dt)
{
	//더블버퍼를 적용시키기위함
	HDC			hMemDC;  //도화지그림
	RECT		windowRect;  //도화지 생성
	HBITMAP		bitmap;  //버퍼 생성

	GetClientRect(this->GetWindHandle(), &windowRect);

	//생성
	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	//위 비트맵을 설정
	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	//Render을 호출
	m_SceneManager->Render(hMemDC, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemDC, 0, 0, SRCCOPY);

	//끝났다면 파괴
	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void GameDirector::SetFrameInterval(DWORD interval)
{
	m_FrameInterval = interval;
}

DWORD GameDirector::GetFrameInterval()
{
	return m_FrameInterval;
}

SceneManager * GameDirector::GetSceneManager()
{
	return m_SceneManager;
}
