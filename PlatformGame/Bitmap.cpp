#include "Bitmap.h"

Bitmap::Bitmap()
{
	//�Ű������� ���� ��� ��� ������ 0����
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

Bitmap::Bitmap(const std::string fileDir)
{
	//�޾ƿ��� ���� ���� ��� �� ������ ����
	this->LoadBitmapByPath(fileDir);
}

Bitmap::Bitmap(const Bitmap & bitmap)
{
	//Bitmap�� �޾ƿ� ��� �� ������ ����
	this->LoadBitmapByPath(bitmap.GetFileDirectory());
}

Bitmap::~Bitmap()
{
	if (!this->Empty())
		DeleteObject(m_BitmapHandle);
}

//Bitmap�� �� -> m_BitmapHandle -> m_BitmapInfo
BOOL Bitmap::LoadBitmapByPath(const std::string fileDir)
{
	//fileDir�� �̹����� ���� ũ��� m_BitmapHandle�� �ҷ���
	m_BitmapHandle = (HBITMAP)LoadImageA(nullptr, fileDir.c_str(),
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);  
	
	if (this->Empty())
		return FALSE;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);
	//m_BitmapInfo�� m_BitmapHandle�� ���� �ҷ���
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
	//������ ũ��� �߶� hdc��
	this->DrawBitmapCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void Bitmap::DrawBitmapCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	//dc�ȿ� GetObject�� Bitmap�������Ѽ� �̹����ֱ� -> hdc�ȿ� �� dc�� �ֱ�
	HDC memDC = CreateCompatibleDC(hdc);  //hdc�� ȣȯ�� �����ϵ���
	SelectObject(memDC, m_BitmapHandle);
	
	//Bitmap�� ����� �� ���ϴ� ���� �����ϴ� �Լ�
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
