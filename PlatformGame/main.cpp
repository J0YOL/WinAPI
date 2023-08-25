#include "GameDefine.h"
#include "SceneDefine.h"
#include "GameDirector.h"
#include "FirstScene.h"

GameDirector* director = nullptr;

void InitScene();
void LoadScene(int index);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR IpCmdLine, int nCmdShow)
{
	InitScene();
	LoadScene(0);

	director->Loop(hInstance, IpCmdLine, nCmdShow);
}

void InitScene()
{
	director = GameDirector::GetGameDirector();			//GameDirector를 가져와
	director->GetSceneManager()->RegisterScene("MenuScene", new MenuScene);
	director->GetSceneManager()->RegisterScene("FirstScene", new FirstScene);
	director->GetSceneManager()->RegisterScene("GameScene", new GameScene);
}

void LoadScene(int index)
{
	switch (index)
	{
	case 0:
		//시작씬 설정
		director->GetSceneManager()->reserveChangeScene("MenuScene");
		break;
	case 1:
		director->GetSceneManager()->reserveChangeScene("FirstScene");
		break;
	case 2:
		director->GetSceneManager()->reserveChangeScene("GameScene");
		break;
	}
}