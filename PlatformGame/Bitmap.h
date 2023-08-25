#pragma once
#include "GameDefine.h"

#pragma comment(lib, "msimg32.lib")

class Bitmap
{
//생성자들과 소멸자를 생성
public:
	Bitmap();
	Bitmap(const std::string fileDir);
	Bitmap(const Bitmap& bitmap);
	~Bitmap();

public:
	BOOL LoadBitmapByPath(const std::string fileDir);  //경로를 받아 비트맵파일을 불러오는 함수

public:
	BOOL Empty() const;
	//Bitmap을 다루는 함수
	HBITMAP GetBitmapHandle() const;
	const BITMAP GetBitmapInfo() const;  //반환하는 값이 const, 함수에 객체도 const
	std::string GetFileDirectory() const;

//비트맵을 그려주는 함수들
public:
	void DrawBitmap(HDC hdc, int x, int y, int width, int height) const;
	void DrawBitmapCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const;
	//스프라이트 그림을 잘라서 사용하기 위한 함수

//정보들을 가지고있음
protected:
	HBITMAP m_BitmapHandle = nullptr;
	BITMAP m_BitmapInfo;
	std::string m_FileDir = "";

//크로마키 색을 지정하는 함수
public:
	void SetTransparentColor(DWORD color);
	DWORD GetTransparentColor() const;

private:
	DWORD m_TransparentColor = RGB(255, 0, 255);  //색의 기본값을 설정
};

