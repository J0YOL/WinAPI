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
		//���콺�� ���������� (LOWORD�� HIWORD��)
		m_SceneManager->SetMousePosition(LOWORD(IParam), HIWORD(IParam));
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, IParam);
}

void GameDirector::ProcessingLoop()
{
	//Update, Renderȣ��
	static DWORD prevFrameTime = 0;  //������ ������Ÿ���� üũ

	//-> ������Ÿ���� �׻� 60�� �����ϵ���
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
	//������۸� �����Ű������
	HDC			hMemDC;  //��ȭ���׸�
	RECT		windowRect;  //��ȭ�� ����
	HBITMAP		bitmap;  //���� ����

	GetClientRect(this->GetWindHandle(), &windowRect);

	//����
	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	//�� ��Ʈ���� ����
	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	//Render�� ȣ��
	m_SceneManager->Render(hMemDC, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemDC, 0, 0, SRCCOPY);

	//�����ٸ� �ı�
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
