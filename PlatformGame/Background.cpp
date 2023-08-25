#include "Background.h"
#pragma warning(disable : 4996)

void Background::Init(char * imageName, RECT rect)
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
}

void Background::Init()
{
}

void Background::Update(float dt)
{
}

void Background::Render(HDC hdc, float dt)
{

	GetBitmap()->DrawBitmap(hdc, GetX(), GetY(), m_Width, m_Height);
}

void Background::Destroy()
{
}

void Background::SetTransparentColor(DWORD color)
{
	GetBitmap()->SetTransparentColor(color);
}

Background::Background()
{
}

Background::~Background()
{
}
