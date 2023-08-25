#pragma once
#include "Object.h"

class GameScene;
class Character : public Object
{
public:
	void			Init(GameScene* pGameScene);
	
	virtual void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	RECT			GetRect();

private:
	//ÇÊµå
	int m_CharImageX = 0;
	int m_CharImageY = 0;
	DWORD m_CharSpeed = 5;

	int m_CharX = 0;
	int m_CharY = 0;

	DWORD m_KeyTime = 0;

private:
	//Animation
	MoveType m_MoveType = MoveType::NONE;

	DWORD m_SpriteIndex = 0;

	DWORD m_SpriteAnimStart = 0;
	DWORD m_SpriteAnimEnd = 0;

	DWORD m_SpriteAnimTime = 0;

	DWORD m_SpriteRunCount = 6;  
	DWORD m_SpriteClimbCount = 3;
	DWORD m_SpriteRMaxCount = 6;
	DWORD m_SpriteCMaxCount = 3;

private:
	GameScene*		m_pGameScene;

public:
	Character();
	~Character();
};

