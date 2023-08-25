#pragma once
#include "Scene.h"
#include "GameDirector.h"
#include "Bitmap.h"
#include "Character.h"
#include "Monster.h"
#include "Gem.h"

class GameScene : public Scene
{
public:
	virtual void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	void			LoadMap(char* fileDir);
	void			DrawMap(HDC hdc, float dt);

	//움직일수있는지, 장애물을 Chek하는 함수
	bool			CheckMoveAble(DWORD x, DWORD y);
	bool			CheckLadder(DWORD x, DWORD y);

	//현재위치를 알려주는 함수
	RECT			GetCharReck();

private:
	//각 위치값
	DWORD			m_Map[TILE_NUM_Y][TILE_NUM_X];
	DWORD			m_CollMap[TILE_NUM_Y][TILE_NUM_X];
	int				m_MonsterMap[TILE_NUM_Y][TILE_NUM_X];

	Bitmap			m_TileMap;
	DWORD			m_MapAcrossCount = 8;

	BOOL			m_viewIndex = FALSE;
	DWORD			m_KeyTime = 0;

	//캐릭터를 추가
	Character		m_Char;
	list<Monster>	m_MonsterList;
	Gem				m_Gem;

public:
	GameScene();
	~GameScene();
};

