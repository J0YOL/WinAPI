#include "MenuScene.h"

//���ҽ��� ��ġ�� ����
void MenuScene::Init()
{
	//RECT���� ����
	//�޴��� �ִ� �׸��� ����
	RECT rc = { 0, 0, 920, 800 };
	mBackground.Init(const_cast<char*>("background.bmp"), rc);
	mBackground.SetTransparentColor(RGB(255, 255, 255));

	RECT rc2 = { 0, 0, 500, 75 };
	mTitle.Init(const_cast<char*>("title.bmp"), rc2);
	mTitle.SetTransparentColor(RGB(86, 49, 25)); 

	RECT rc3 = { 40, 200, 420, 700 };
	mChar.Init(const_cast<char*>("house.bmp"), rc3);
	mChar.SetTransparentColor(RGB(255, 255, 255));

	//�޴��� �ִ� ��ư�� ��ġ�� ����(3���� ���� ��� ����)
	RECT rc4 = { 500, 400, 750, 462 };
	m_StartButton.Init(const_cast<char*>("start_Button.bmp"), rc4);
	m_StartButton.SetTag(const_cast<char*>(TAG_START_BUTTON));
	m_StartButton.SetTransparentColor(RGB(255, 0, 255));

	m_StartButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_HOVAL] = { 0,72,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };

	RECT rc5 = { 500, 500, 750, 562 };
	m_ExitButton.Init(const_cast<char*>("exit_button.bmp"), rc5);
	m_ExitButton.SetTag(const_cast<char*>(TAG_EXIT_BUTTON));
	m_ExitButton.SetTransparentColor(RGB(255, 0, 255));

	m_ExitButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_HOVAL] = { 0,72,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };
}

//�� ������ Update, Render, Destroy�� ���Ѿ� ��Ÿ��
void MenuScene::Update(float dt)
{
	//Init���� ������ 3���� ������ ������Ʈ
	mBackground.Update(dt);
	mTitle.Update(dt);
	mChar.Update(dt);
	m_StartButton.Update(dt);
	m_ExitButton.Update(dt);
}

void MenuScene::Render(HDC hdc, float dt)
{
	mBackground.Render(hdc, dt);
	mTitle.Render(hdc, dt);
	mChar.Render(hdc, dt);
	m_StartButton.Render(hdc, dt);
	m_ExitButton.Render(hdc, dt);
}


void MenuScene::Destroy()
{
	mBackground.Destroy();
	mTitle.Destroy();
	mChar.Destroy();
	m_StartButton.Destroy();
	m_ExitButton.Destroy();
}

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}
