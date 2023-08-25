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

	void			LoadMap();  //�� �ҷ�����
	void			SaveMap();  //�� ����

private:
	//�ʿ��� �ҷ��� ������ ����
	POINT			m_ScreenSize;	//ȭ�� ũ��
	POINT			m_MapSize;		//�� ũ��		
	POINT			m_ItemListSize;	//������ ����Ʈ ũ��

	Bitmap			m_TileMap;		//Ÿ�ϸ� �̹���
	Bitmap			m_Monster;		//���� �̹���
	Bitmap			m_Guide;		//���̵� �̹���

	DWORD			m_MapAcrossCount = 8;	//���� 8���� �������ٰ���(�̹��� ���η� 8���� ������������)
	DWORD			m_MapMaxCount = 32;		//�� Ÿ�� �ִ� ����

	DWORD			m_ScelectNumber = 0;	//���õ� Ÿ�� �ε���
	DWORD			m_AddNum = 0;			//������ ����Ʈ �̵� ��

	BOOL			m_IsColl = FALSE;		//�浹üũ
	BOOL			m_IsMakeMonster = FALSE;	//���� ���� ���

	DWORD			m_KeyTime = 0;			//Ű �Է½ð� üũ

	Button			m_NextButton;			//��ư�� ���۹�ư�� ������ ����

public:
	FirstScene();
	~FirstScene();
};

