#include "Monster.h"
#include "GameScene.h"

void Monster::Init(GameScene * pGameScene)
{
	//�ڵ����� ���ư��Բ�
	m_pGameScene = pGameScene;
}

void Monster::SetMoveType(int x, int y, MoveType type)
{
	//��ǥ���� �Է��ϰ� ������, ���ʺ����� Check
	SetX(x * TILE_SIZE);
	SetY(y * TILE_SIZE);

	m_MoveType = type;

	m_TileIndex_X = x;
	m_TileIndex_Y = y;

	switch (m_MoveType)
	{
	case MoveType::LEFT:
		m_SpriteIndex = 0;

		m_SpriteAnimStart = 0;
		m_SpriteAnimEnd = 3;
		break;

	case MoveType::RIGHT:
		m_SpriteIndex = 4;

		m_SpriteAnimStart = 4;
		m_SpriteAnimEnd = 7;
		break;
	}
}

void Monster::Init()
{
	GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-1.bmp");
	m_SpriteIndex = 0;
}

void Monster::Update(float dt)
{
	switch (m_MoveType)
	{
	case MoveType::LEFT:
		if (m_pGameScene->CheckMoveAble(m_TileIndex_X - 1, m_TileIndex_Y))
		{
			if (m_TileIndex_X > 0) SetX(GetX() - 3);
		}
		else if ((m_TileIndex_X * TILE_SIZE) < GetX())
		{
			SetX(GetX() - 3);
		}
		else
		{
			SetX(m_TileIndex_X * TILE_SIZE);

			m_MoveType = MoveType::RIGHT;
			m_SpriteIndex = 4;

			m_SpriteAnimStart = 4;
			m_SpriteAnimEnd = 7;
		}

		if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
		break;

	case MoveType::RIGHT:
		if (m_pGameScene->CheckMoveAble(m_TileIndex_X + 1, m_TileIndex_Y))
		{
			if (m_TileIndex_X < TILE_NUM_X - 1) SetX(GetX() + 3);
		}
		else if ((m_TileIndex_X * TILE_SIZE) > GetX())
		{
			SetX(GetX() + 3);
		}
		else
		{
			SetX(m_TileIndex_X * TILE_SIZE);

			m_MoveType = MoveType::LEFT;
			m_SpriteIndex = 0;

			m_SpriteAnimStart = 0;
			m_SpriteAnimEnd = 3;
		}

		if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
		break;
	}

	m_TileIndex_X = (GetX() + 32) / TILE_SIZE;
	m_TileIndex_Y = (GetY() + 32) / TILE_SIZE;

	//ĳ���Ϳ� ���� �浹�ϸ� Menu������ ���ư�
	RECT dest;
	if (IntersectRect(&dest, &m_pGameScene->GetCharReck(), &GetRect()))
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("MenuScene");
	}
}

void Monster::Render(HDC hdc, float dt)
{
	GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
	GetBitmap()->DrawBitmap(hdc, GetX(), GetY(), TILE_SIZE, TILE_SIZE);

	//��������Ʈ�� �ε��� �Է�
	switch (m_SpriteIndex)
	{
	case 0:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-1.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 1:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-2.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 2:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-3.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 3:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-4.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 4:
		//�¿����
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-5.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 5:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-6.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 6:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-7.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
		break;
	case 7:
		GetBitmap()->LoadBitmapByPath("ResourceM/eagle-attack-8.bmp");
		GetBitmap()->SetTransparentColor(RGB(255, 255, 255));
	}
}

void Monster::Destroy()
{

}

RECT Monster::GetRect()
{
	//������ Rect���� �����ü�����
	RECT rect = { GetX() + 20, GetY() + 20, GetX() + TILE_SIZE - 20, GetY() + TILE_SIZE - 20 };
	return rect;
}
