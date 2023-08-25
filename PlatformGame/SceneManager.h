#pragma once
#include "GameDefine.h"

using namespace std;

class Scene;

class SceneManager
{
public: 
	void		RegisterScene(const std::string& SceneName, Scene* scene);  //�� ���
	void		reserveChangeScene(const std::string& sceneName); //��ü�� �� ����

public:
	void		Update(float dt);
	void		Render(HDC hdc, float dt);

public:
	//���콺������ ���� ����������
	DWORD		GetMousePositionX();
	DWORD		GetMousePositionY();

	void		SetMousePosition(DWORD x, DWORD y);

private:
	std::map<std::string, Scene*> m_SceneContainer;

	Scene*		m_ReservedScene = nullptr;
	Scene*		m_CurrentScene = nullptr;

	DWORD		m_MousePositionX = 0;
	DWORD		m_MousePositionY = 0;

public:
	SceneManager();
	~SceneManager();
};

