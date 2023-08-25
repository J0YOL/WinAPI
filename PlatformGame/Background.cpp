#include "Background.h"
#pragma warning(disable : 4996)

void Background::Init(char * imageName, RECT rect)
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
