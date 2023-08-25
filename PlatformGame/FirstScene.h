#pragma once
#include "Scene.h"
#include "Bitmap.h"
#include "Background.h"
#include "Button.h"
#include <fstream>

class FirstScene : public Scene
{
public:
	virtual void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	void			LoadMap();  //맵 불러오기
	void			SaveMap();  //맵 저장

private:
	//맵에서 불러올 변수들 선언
	POINT			m_ScreenSize;	//화면 크기
	POINT			m_MapSize;		//맵 크기		
	POINT			m_ItemListSize;	//아이템 리스트 크기

	Bitmap			m_TileMap;		//타일맵 이미지
	Bitmap			m_Monster;		//몬스터 이미지
	Bitmap			m_Guide;		//가이드 이미지

	DWORD			m_MapAcrossCount = 8;	//맵을 8개로 나누어줄거임(이미지 가로로 8개로 나누어져있음)
	DWORD			m_MapMaxCount = 32;		//맵 타일 최대 개수

	DWORD			m_ScelectNumber = 0;	//선택된 타일 인덱스
	DWORD			m_AddNum = 0;			//아이템 리스트 이동 값

	BOOL			m_IsColl = FALSE;		//충돌체크
	BOOL			m_IsMakeMonster = FALSE;	//몬스터 생성 모드

	DWORD			m_KeyTime = 0;			//키 입력시간 체크

	Button			m_NextButton;			//버튼의 시작버튼을 맵툴에 설정

public:
	FirstScene();
	~FirstScene();
};

