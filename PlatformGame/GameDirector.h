#pragma once
#include "WrappedWind.h"
#include "SceneManager.h"

class GameDirector : public WrappedWind
{
public:
	//�̱����� �ϱ����� �Լ���
	static GameDirector*		GetGameDirector();
	static LRESULT CALLBACK		WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);
	LRESULT CALLBACK			MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);

public:
	//WrappedWind�� Loop���� ����ϱ� ����
	virtual void				ProcessingLoop();

	//��ƾ�� ó���ؾ���
	void						Update(float dt);
	void						Render(HDC hdc, float dt);

	//dt���� ����
	void						SetFrameInterval(DWORD interval);
	DWORD						GetFrameInterval();

	SceneManager*				GetSceneManager();

private:
	SceneManager*				m_SceneManager = nullptr;
	DWORD						m_FrameInterval = 0;  //Frame������ �ޱ� ����

public:
	GameDirector();
	~GameDirector();
};

//�����α׷��� �����Ҽ� �ֵ��� ��������
static GameDirector*			ApplicationHandle = 0;
static GameDirector*			GetApplicationHandle() { return ApplicationHandle; }