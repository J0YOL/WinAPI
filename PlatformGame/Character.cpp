#include "Character.h"
#include "GameScene.h"
#pragma warning(disable : 4996)

void Character::Init(GameScene * pGameScene)
{
	m_pGameScene = pGameScene;
}

void Character::Init()
{
	//ĳ���� ��ġ �ʱ�ȭ
	m_CharX = 0;
	m_CharY = 7;

	m_CharImageX = m_CharX * TILE_SIZE;
	m_CharImageY = m_CharY * TILE_SIZE;

	GetBitmap()->LoadBitmapByPath("ResourceM/player-run-3.bmp");
	GetBitmap()->SetTransparentColor(RGB(255, 255, 255));

	m_SpriteIndex = 0;  //�����ε����� ����
}

void Character::Update(float dt)
{
	//ĳ���� �������� ����
	if (GetAsyncKeyState(VK_UP))
	{
		//��ٸ��� �ö󰥶��� UP�� ���
		if (m_pGameScene->CheckLadder(m_CharX, m_CharY))
		{
			if (abs((double)(m_CharX * TILE_SIZE) - m_CharImageX) < 10) {
				if (m_CharY > 0) m_CharImageY -= m_CharSpeed;
			}
		}
		else if ((m_CharY * TILE_SIZE) < m_CharImageY)
		{
			//������ �ö�Դ����� Check
			m_CharImageY -= m_CharSpeed;
		}

		if (m_MoveType != MoveType::UP)
		{
			//�ִϸ��̼��� ����
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::UP;
			m_SpriteIndex = 6;

			m_SpriteAnimStart = 6;
			m_SpriteAnimEnd = 8;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		//��ٸ��� �ö󰥶��� UP�� ���
		if (m_pGameScene->CheckLadder(m_CharX, m_CharY + 1))
		{
			if (abs((double)(m_CharX * TILE_SIZE) - m_CharImageX) < 30) {
				if (m_CharY < TILE_NUM_Y -1) m_CharImageY += m_CharSpeed;
			}
		}
		else if ((m_CharY * TILE_SIZE) > m_CharImageY)
		{
			//������ �ö�Դ����� Check
			m_CharImageY += m_CharSpeed;
		}

		if (m_MoveType != MoveType::UP)
		{
			//�ִϸ��̼��� ����
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::UP;
			m_SpriteIndex = 6;

			m_SpriteAnimStart = 6;
			m_SpriteAnimEnd = 8;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		//��ٸ��� �ö󰥶��� UP�� ���
		if (m_pGameScene->CheckMoveAble(m_CharX - 1, m_CharY))
		{
			if (abs((double)(m_CharY * TILE_SIZE) - m_CharImageY) < 30) {
				if (m_CharY > 0) m_CharImageX -= m_CharSpeed;
			}
		}
		else if ((m_CharX * TILE_SIZE) < m_CharImageX)
		{
			//������ �ö�Դ����� Check
			m_CharImageX -= m_CharSpeed;
		}

		if (m_MoveType != MoveType::LEFT)
		{
			//�ִϸ��̼��� ����
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::LEFT;
			m_SpriteIndex = 14;

			m_SpriteAnimStart = 9;
			m_SpriteAnimEnd = 13;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		//��ٸ��� �ö󰥶��� UP�� ���
		if (m_pGameScene->CheckMoveAble(m_CharX + 1, m_CharY))
		{
			if (abs((double)(m_CharY * TILE_SIZE) - m_CharImageY) < 10) {
				if (m_CharY < TILE_NUM_X - 1) m_CharImageX += m_CharSpeed;
			}
		}
		else if ((m_CharX * TILE_SIZE) > m_CharImageX)
		{
			//������ �ö�Դ����� Check
			m_CharImageX += m_CharSpeed;
		}

		if (m_MoveType != MoveType::RIGHT)
		{
			//�ִϸ��̼��� ����
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::RIGHT;
			m_SpriteIndex = 0;

			m_SpriteAnimStart = 0;
			m_SpriteAnimEnd = 5;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	//ĳ���� ��ǥ ����
	m_CharX = (m_CharImageX + 32) / TILE_SIZE;
	m_CharY = (m_CharImageY + 32) / TILE_SIZE;
}

void Character::Render(HDC hdc, float dt)
{
	//ó������ #endif���� ĳ������ ��ġ���� �˱����� ǥ���Ѱ�
//#define VIEW_CHARINFO
#ifdef VIEW_CHARINFO

	//ĳ������ ����ǥ��
	Rectangle(hdc, m_CharX * TILE_SIZE, m_CharY * TILE_SIZE,
		m_CharX * TILE_SIZE + TILE_SIZE, m_CharY * TILE_SIZE + TILE_SIZE);

	//��ġ���� ���
	char text[256];

	sprintf(text, "L : %d, T : %d", m_CharImageX, m_CharImageY);
	TextOutA(hdc, m_CharImageX, m_CharImageY - 30, text, strlen(text));

	sprintf(text, "R : %d, B : %d", m_CharImageX + TILE_SIZE, m_CharImageY + TILE_SIZE);
	TextOutA(hdc, m_CharImageX, m_CharImageY - 10, text, strlen(text));
	
#endif

	GetBitmap()->DrawBitmap(hdc, m_CharImageX, m_CharImageY, TILE_SIZE, TILE_SIZE);

	switch (m_SpriteIndex)
	{
	case 0:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-3.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 1:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-4.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 2:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-5.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 3:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-6.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 4:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-1.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 5:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-2.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 6:
		//�����ϴ� �ε���
		GetBitmap()->LoadBitmapByPath("ResourceM/player-climb-1.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 7:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-climb-2.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 8:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-climb-3.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 9:
		//�¿츦 ����
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-7.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 10:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-8.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 11:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-10.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 12:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-11.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 13:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-12.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 14:
		GetBitmap()->LoadBitmapByPath("ResourceM/player-run-9.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	}
}

void Character::Destroy()
{
}

RECT Character::GetRect()
{
	//Rect�� �����ö� ĳ������ ��ġ���� ����������
	RECT rect = { m_CharImageX, m_CharImageY, m_CharImageX + TILE_SIZE, m_CharImageY + TILE_SIZE };
	return rect;
}

Character::Character()
{
}

Character::~Character()
{
}
