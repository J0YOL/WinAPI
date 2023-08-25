#pragma once
#include "WrappedWind.h"
#include "SceneManager.h"

class GameDirector : public WrappedWind
{
public:
	//싱글톤을 하기위한 함수들
	static GameDirector*		GetGameDirector();
	static LRESULT CALLBACK		WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);
	LRESULT CALLBACK			MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);

public:
	//WrappedWind의 Loop문을 사용하기 위함
	virtual void				ProcessingLoop();

	//루틴을 처리해야함
	void						Update(float dt);
	void						Render(HDC hdc, float dt);

	//dt값을 설정
	void						SetFrameInterval(DWORD interval);
	DWORD						GetFrameInterval();

	SceneManager*				GetSceneManager();

private:
	SceneManager*				m_SceneManager = nullptr;
	DWORD						m_FrameInterval = 0;  //Frame단위로 받기 위함

public:
	GameDirector();
	~GameDirector();
};

//이프로그램을 관리할수 있도록 변수선언
static GameDirector*			ApplicationHandle = 0;
static GameDirector*			GetApplicationHandle() { return ApplicationHandle; }