#pragma once
#include "GameDefine.h"

class PrepareWind; //상속을 받도록

//Loop문, window가져오기, 보여주기 등을 하는 class
class WrappedWind
{
public:
	//Loop문을 해주는 함수생성
	int				Loop(HINSTANCE hInstance, LPSTR IpCmdLine, int nCmdShow);

private:
	void			registerWndClass(const PrepareWind& value);
	void			createWindow(const PrepareWind& value);
	void			showWindow(const PrepareWind& value);
	int				MessageLoop();

public:
	//순수가상함수 루프문실행함수
	virtual void	ProcessingLoop() = 0;

protected:
	//관리를 할수있도록 식별자 등을 선언
	HWND			m_hWnd			= nullptr;
	HINSTANCE		m_hInstance		= nullptr;

public:
	//위의 식별자들을 가져오기 위한 함수
	HWND			GetWindHandle();
	HINSTANCE		GetInstanceHandle();

public:
	WrappedWind();
	~WrappedWind();
};

