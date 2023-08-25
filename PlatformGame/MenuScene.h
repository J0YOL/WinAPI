#pragma once
#include "Scene.h"
#include "Background.h"
#include "Button.h"

//����̶� �޴���� �⺻ UI�� ��� ȭ��
class MenuScene : public Scene
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

private:
	Background	mBackground;
	Background	mTitle;
	Background	mChar;

	Button m_StartButton;
	Button m_ExitButton;

public:
	MenuScene();
	~MenuScene();
};

