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
	CRECT			m_ButtonRC[3];   //���ҽ��� ��ư�� ��Ȳ�� 3���� ����(�׳�, ���콺 �ö�����, ���콺�� Ŭ���� ���� ��)

	//Sound�� ���õ� ��������
	MCIDEVICEID		MusicID = 0;
	MCIERROR		Error;
	MCI_OPEN_PARMSA Data = {};

public:
	Button();
	~Button();
};

