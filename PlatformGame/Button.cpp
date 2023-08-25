#include "Button.h"
#include "GameDirector.h"

#pragma warning(disable : 4996)		//���ȿ� ���õ� ��������

void Button::Init(char * imageName, RECT rect)
{
	//�̹��� �̸����� �޾Ƽ� ã�ư�
	const char* path = "ResourceM/";
	char FilePath[256];
	sprintf(FilePath, "%s%s", path, imageName);
	GetBitmap()->LoadBitmapByPath(FilePath);

	SetX(rect.left);
	SetY(rect.top);

	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;

	//��ư�� ���°� Ŭ���� ���� ���� ���·� �ʱ�ȭ�� ��Ŵ
	m_BtnState = BTN_STATE_NOMAL;
	m_nowRect = &m_ButtonRC[BTN_STATE_NOMAL];

	m_IsClicked = FALSE;
}

void Button::Init()
{

}

void Button::Update(float dt)
{
	//Click�̺�Ʈ�� �߻���ų��
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
			m_IsClicked = FALSE;  //Ŭ���� �� �� �� ���¸� ����
			ButtonEvent();
		}
		else if (m_BtnState != BTN_STATE_HOVAL)
		{
			//�� ���� �ȿ� ������ ���� ���°� �ƴ϶��
			m_IsClicked = FALSE;
			m_BtnState = BTN_STATE_HOVAL;
			m_nowRect = &m_ButtonRC[BTN_STATE_HOVAL];
		}
	}
	else
	{
		//��������, �� ���� �ִ� ���µ� �ƴҶ�
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
	//���ڿ� �񱳸� ���
	if (strcmp(m_Tag, TAG_START_BUTTON) == 0)
	{
		//���� ��ư�� ���ӽ����̸� FirstScene���� Scene��ȯ
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("FirstScene");
	}

	if (strcmp(m_Tag, TAG_NEXT_BUTTON) == 0)
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameScene");
	}

	if (strcmp(m_Tag, TAG_EXIT_BUTTON) == 0)
	{
		//���� ��ư�� �����ư�̸� ����
		PostQuitMessage(0);
	}
}

Button::Button()
{

}

Button::~Button()
{

}