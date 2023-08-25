#include "Bitmap.h"

Bitmap::Bitmap()
{
	//매개변수가 없을 경우 모든 정보를 0으로
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

Bitmap::Bitmap(const std::string fileDir)
{
	//받아오는 값이 있을 경우 그 값으로 정의
	this->LoadBitmapByPath(fileDir);
}

Bitmap::Bitmap(const Bitmap & bitmap)
{
	//Bitmap을 받아올 경우 그 정보로 정의
	this->LoadBitmapByPath(bitmap.GetFileDirectory());
}

Bitmap::~Bitmap()
{
	if (!this->Empty())
		DeleteObject(m_BitmapHandle);
}

//Bitmap의 값 -> m_BitmapHandle -> m_BitmapInfo
BOOL Bitmap::LoadBitmapByPath(const std::string fileDir)
{
	//fileDir의 이미지를 실제 크기로 m_BitmapHandle에 불러옴
	m_BitmapHandle = (HBITMAP)LoadImageA(nullptr, fileDir.c_str(),
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);  
	
	if (this->Empty())
		return FALSE;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);
	//m_BitmapInfo로 m_BitmapHandle의 값을 불러옴
	m_FileDir = fileDir;

	return TRUE;
}

BOOL Bitmap::Empty() const
{
	return m_BitmapHandle == nullptr;
}

HBITMAP Bitmap::GetBitmapHandle() const
{
	return m_BitmapHandle;
}

const BITMAP Bitmap::GetBitmapInfo() const
{
	return m_BitmapInfo;
}

std::string Bitmap::GetFileDirectory() const
{
	return m_FileDir;
}

void Bitmap::DrawBitmap(HDC hdc, int x, int y, int width, int height) const
{
	//원본의 크기로 잘라서 hdc에
	this->DrawBitmapCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void Bitmap::DrawBitmapCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	//dc안에 GetObject로 Bitmap참조시켜서 이미지넣기 -> hdc안에 이 dc를 넣기
	HDC memDC = CreateCompatibleDC(hdc);  //hdc와 호환이 가능하도록
	SelectObject(memDC, m_BitmapHandle);
	
	//Bitmap을 출력할 때 원하는 색을 제거하는 함수
	TransparentBlt(
		hdc, x, y,
		width == 0 ? m_BitmapInfo.bmWidth : width,
		height == 0 ? m_BitmapInfo.bmHeight : height,
		memDC, sx, sy, sw, sh, GetTransparentColor());

	DeleteDC(memDC);
}

void Bitmap::SetTransparentColor(DWORD color)
{
	m_TransparentColor = color;
}

DWORD Bitmap::GetTransparentColor() const
{
	return m_TransparentColor;
}
