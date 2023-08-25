#include "Button.h"
#include "GameDirector.h"

#pragma warning(disable : 4996)		//보안에 관련된 오류무시

void Button::Init(char * imageName, RECT rect)
{
	//이미지 이름값을 받아서 찾아감
	const char* path = "ResourceM/";
	char FilePath[256];
	sprintf(FilePath, "%s%s", path, imageName);
	GetBitmap()->LoadBitmapByPath(FilePath);

	SetX(rect.left);
	SetY(rect.top);

	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;

	//버튼의 상태가 클릭이 되지 않은 상태로 초기화를 시킴
	m_BtnState = BTN_STATE_NOMAL;
	m_nowRect = &m_ButtonRC[BTN_STATE_NOMAL];

	m_IsClicked = FALSE;
}

void Button::Init()
{

}

void Button::Update(float dt)
{
	//Click이벤트를 발생시킬거
	int mX = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
	int mY = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

	if (mX >= GetX() && mX <= GetX() + m_Width &&
		mY >= GetY() && mY <= GetY() + m_Height)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_IsClicked = TRUE;

			if (m_BtnState != BTN_STATE_CLICKED)
			{
				m_BtnState = BTN_STATE_CLICKED;
				m_nowRect = &m_ButtonRC[BTN_STATE_CLICKED];
			}
		}
		else if (m_IsClicked)
		{
			m_IsClicked = FALSE;  //클릭을 한 후 땐 상태를 말함
			ButtonEvent();
		}
		else if (m_BtnState != BTN_STATE_HOVAL)
		{
			//그 범위 안에 있지만 누른 상태가 아니라면
			m_IsClicked = FALSE;
			m_BtnState = BTN_STATE_HOVAL;
			m_nowRect = &m_ButtonRC[BTN_STATE_HOVAL];
		}
	}
	else
	{
		//누르지도, 그 위에 있는 상태도 아닐때
		m_IsClicked = FALSE;

		if (m_BtnState != BTN_STATE_NOMAL)
		{
			m_BtnState = BTN_STATE_NOMAL;
			m_nowRect = &m_ButtonRC[BTN_STATE_NOMAL];
		}
	}
}

void Button::Render(HDC hdc, float dt)
{
	GetBitmap()->DrawBitmapCropping(hdc, GetX(), GetY(), m_Width, m_Height,
		m_nowRect->x, m_nowRect->y, m_nowRect->width, m_nowRect->height);
}

void Button::Destroy()
{

}

void Button::SetTag(char * value)
{
	strcpy(m_Tag, value);
}

void Button::SetTransparentColor(DWORD color)
{
	GetBitmap()->SetTransparentColor(color);
}

CRECT * Button::GetButtonCropRect()
{
	return m_ButtonRC;
}

void Button::ButtonEvent()
{
	//문자열 비교를 사용
	if (strcmp(m_Tag, TAG_START_BUTTON) == 0)
	{
		//누른 버튼이 게임시작이면 FirstScene으로 Scene전환
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("FirstScene");
	}

	if (strcmp(m_Tag, TAG_NEXT_BUTTON) == 0)
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameScene");
	}

	if (strcmp(m_Tag, TAG_EXIT_BUTTON) == 0)
	{
		//누른 버튼이 종료버튼이면 종료
		PostQuitMessage(0);
	}
}

Button::Button()
{

}

Button::~Button()
{

}