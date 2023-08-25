#include "Gem.h"
#include "GameScene.h"

void Gem::Init(GameScene * pGameScene)
{
	m_pGameScene = pGameScene;
}

void Gem::Init()
{
	GetBitmap()->LoadBitmapByPath("ResourceM/gem.bmp");
	GetBitmap()->SetTransparentColor(RGB(255, 255, 255));

	SetX(m_PosX * TILE_SIZE);
	SetY(m_PosY * TILE_SIZE);
}

void Gem::Update(float dt)
{
	


}

void Gem::Render(HDC hdc, float dt)
{
	GetBitmap()->DrawBitmap(hdc, GetX(), GetY(), TILE_SIZE, TILE_SIZE);

	//충돌 처리
	RECT dest;
	RECT gemRect = { GetX(), GetY(), GetX() + TILE_SIZE, GetY() + TILE_SIZE };

	if (IntersectRect(&dest, &m_pGameScene->GetCharReck(), &gemRect))
	{
		MessageBox(NULL, TEXT("GAME CLEAR!!!"), TEXT("축하합니다^ㅁ^"), MB_OK);
		PostQuitMessage(0);
	}
}

void Gem::Destroy()
{
}
