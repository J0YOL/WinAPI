#pragma once
#include "GameDefine.h"

#pragma comment(lib, "msimg32.lib")

class Bitmap
{
//�����ڵ�� �Ҹ��ڸ� ����
public:
	Bitmap();
	Bitmap(const std::string fileDir);
	Bitmap(const Bitmap& bitmap);
	~Bitmap();

public:
	BOOL LoadBitmapByPath(const std::string fileDir);  //��θ� �޾� ��Ʈ�������� �ҷ����� �Լ�

public:
	BOOL Empty() const;
	//Bitmap�� �ٷ�� �Լ�
	HBITMAP GetBitmapHandle() const;
	const BITMAP GetBitmapInfo() const;  //��ȯ�ϴ� ���� const, �Լ��� ��ü�� const
	std::string GetFileDirectory() const;

//��Ʈ���� �׷��ִ� �Լ���
public:
	void DrawBitmap(HDC hdc, int x, int y, int width, int height) const;
	void DrawBitmapCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const;
	//��������Ʈ �׸��� �߶� ����ϱ� ���� �Լ�

//�������� ����������
protected:
	HBITMAP m_BitmapHandle = nullptr;
	BITMAP m_BitmapInfo;
	std::string m_FileDir = "";

//ũ�θ�Ű ���� �����ϴ� �Լ�
public:
	void SetTransparentColor(DWORD color);
	DWORD GetTransparentColor() const;

private:
	DWORD m_TransparentColor = RGB(255, 0, 255);  //���� �⺻���� ����
};

