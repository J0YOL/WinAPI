#pragma once
#include "Object.h"
#include "GameDefine.h"

class Button : public Object
{
public:
	virtual void	Init(char* imageName, RECT rect);
	virtual void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	void			SetTag(char* value);
	void			SetTransparentColor(DWORD color);
	CRECT*			GetButtonCropRect();
	void			ButtonEvent();

private:
	DWORD			m_Width;
	DWORD			m_Height;
	
	char			m_Tag[256];
	bool			m_IsClicked = FALSE;

	DWORD			m_BtnState;
	CRECT*			m_nowRect;
	CRECT			m_ButtonRC[3];   //리소스에 버튼의 상황이 3개가 있음(그냥, 마우스 올라갔을때, 마우스가 클릭이 됐을 때)

	//Sound에 관련된 변수선언
	MCIDEVICEID		MusicID = 0;
	MCIERROR		Error;
	MCI_OPEN_PARMSA Data = {};

public:
	Button();
	~Button();
};

