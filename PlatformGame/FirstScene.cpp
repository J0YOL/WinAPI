#include "FirstScene.h"
#include "GameDirector.h"

#define MAP_WIDTH	10
#define MAP_HEIGHT	10

int tempMap[MAP_HEIGHT][MAP_WIDTH];		//타일 맵
int collMap[MAP_HEIGHT][MAP_WIDTH];		//충돌 맵
int monsterMap[MAP_HEIGHT][MAP_WIDTH];	//몬스터 맵

void FirstScene::Init()
{
	//버튼을 제작
	RECT rc4 = { 640, 100, 890, 162 };  //가로 250, 세로 62
	m_NextButton.Init(const_cast<char*>("start_Button.bmp"), rc4);
	m_NextButton.SetTag(const_cast<char*>(TAG_NEXT_BUTTON));
	m_NextButton.SetTransparentColor(RGB(255, 0, 255));

	m_NextButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_NextButton.GetButtonCropRect()[BTN_STATE_HOVAL] = { 0,72,200,72 };
	m_NextButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };

	//리소스파일 저장
	m_TileMap.LoadBitmapByPath("Resource/tilemap.bmp");
	m_Monster.LoadBitmapByPath("ResourceM/eagle-attack-1.bmp");
	m_Guide.LoadBitmapByPath("ResourceM/guide.bmp");

	//각 그림에 제거할 색깔을 지정
	//m_TileMap.SetTransparentColor(RGB(255, 255, 255));	-> 이거는 배경을 제거하니까 징그러워서 일단 주석처리
	m_Monster.SetTransparentColor(RGB(255, 255, 255));

	//맵 크기 결정
	m_MapSize.x = MAP_WIDTH;
	m_MapSize.y = MAP_HEIGHT;

	//스크린 크기 결정 -> MapTool이 실행되는 스크린(작동)
	m_ScreenSize.x = m_MapSize.x * TILE_SIZE;
	m_ScreenSize.y = m_MapSize.y * TILE_SIZE + 20;

	//아이템 리스트 사이즈 결정
	m_ItemListSize.x = m_ScreenSize.x;
	m_ItemListSize.y = m_ScreenSize.y + TILE_SIZE;

	//맵들을 초기화
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			tempMap[i][j]		= 0;
			collMap[i][j]		= 0;
			monsterMap[i][j]	= -1;
		}
	}

	//타일맵 불러오기
	LoadMap();
}

//Key를 입력할 때 기능을 넣음
void FirstScene::Update(float dt)
{
	m_NextButton.Update(dt);

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_AddNum > 0) m_AddNum--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_AddNum < m_MapMaxCount - m_MapSize.x) m_AddNum++;
	}

	//마우스 왼쪽을 클릭
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT mPosi;  //Cursor위치값을 받아내는 변수

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		//1. 맵타일범위를 클릭했을때
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x &&
			mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			//Cursor의 위치가 ScreenSize안의 영역일때 그 위치값을 각 Map에 넣어라
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;

			if (m_IsMakeMonster)
			{
				monsterMap[mY][mX] = m_ScelectNumber;
			}
			else
			{
				tempMap[mY][mX] = m_ScelectNumber;
		
				//충돌체크가 되었을 경우 충돌처리
				if (m_IsColl)	collMap[mY][mX] = 1;
				else			collMap[mY][mX] = 0;
			}
		}

		//2. 아이템 범위를 클릭했을 때
		else if (mPosi.x <= m_ItemListSize.x && mPosi.y <= m_ItemListSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;  //Y축으로는 값이 필요없음(1줄로 ItemList가 나옴)
			m_ScelectNumber = mX + m_AddNum;
		}
	}

	//오른쪽 클릭시 삭제
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		POINT mPosi;

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		//1. 맵타일범위를 클릭했을때
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x&&
			mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;
		
			monsterMap[mY][mX] = -1;		
		}
	}

	//S키 저장
	if (GetAsyncKeyState(0x53))
	{
		MessageBox(NULL, TEXT("맵을 저장했습니다."), TEXT("알림"), MB_OK);
		SaveMap();
	}

	//C키를 눌렀을 시 충돌 활성화/비활성화
	if (GetAsyncKeyState(0x43) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsColl = !m_IsColl;
	}

	//M키를 누를 때 몬스터/ 맵타일 모드 변경
	if (GetAsyncKeyState(0x4D) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsMakeMonster = !m_IsMakeMonster;

		//선택타일 넘버 초기화
		m_ScelectNumber = 0;
		m_AddNum		= 0;
	}
}

void FirstScene::Render(HDC hdc, float dt)
{
	m_NextButton.Render(hdc, dt);

	//MapTool' Guide
	m_Guide.DrawBitmap(hdc, 650, 300, 250, 250);


	//1.맵타일 그리기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			m_TileMap.DrawBitmapCropping(hdc, TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE,
				(tempMap[i][j] % m_MapAcrossCount)*ORI_TILE_SIZE,
				(tempMap[i][j] / m_MapAcrossCount)*ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);

			//몬스터 그리기
			if (monsterMap[i][j] != -1)
			{
				m_Monster.DrawBitmap(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE);
			}

			//충돌맵 그리기
			if (collMap[i][j] == 1)
			{
				Ellipse(hdc, TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE*j + 20, TILE_SIZE*i + 20);
			}
		}
	}

	//2.아이템 리스트 그리기
	//일반타일 / 몬스터 그리기
	for (int i = 0; i < m_MapSize.x; i++)
	{
		if (m_IsMakeMonster)
		{
			m_Monster.DrawBitmap(hdc, TILE_SIZE * i, m_ScreenSize.y, TILE_SIZE, TILE_SIZE);
		}
		else
		{
			m_TileMap.DrawBitmapCropping(hdc, TILE_SIZE*i, m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
				((i + m_AddNum) % m_MapAcrossCount)*ORI_TILE_SIZE,
				((i + m_AddNum) / m_MapAcrossCount)*ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);
		}
	}

	//3.선택한 타일 이미지 그리기
	RECT rect = {
		TILE_SIZE * m_MapSize.x + 20, m_ScreenSize.y - 20,
		TILE_SIZE * m_MapSize.x + 105 , m_ScreenSize.y };

	DrawText(hdc, TEXT("선택한 타일"), 12, &rect, NULL);

	if (m_IsMakeMonster)
	{
		m_Monster.DrawBitmap(hdc, TILE_SIZE * m_MapSize.x + 20,
			m_ScreenSize.y, TILE_SIZE, TILE_SIZE);
	}
	else
	{
		m_TileMap.DrawBitmapCropping(hdc, TILE_SIZE * m_MapSize.x + 20,
			m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
			(m_ScelectNumber % m_MapAcrossCount) * ORI_TILE_SIZE,
			(m_ScelectNumber / m_MapAcrossCount) * ORI_TILE_SIZE,
			ORI_TILE_SIZE, ORI_TILE_SIZE);

		//충돌처리
		if (m_IsColl)
		{
			Ellipse(hdc, TILE_SIZE * m_MapSize.x + 20, m_ScreenSize.y,
				TILE_SIZE * m_MapSize.x + 40, m_ScreenSize.y + 20);
		}
	}
}

void FirstScene::Destroy()
{
	m_NextButton.Destroy();
}

void FirstScene::LoadMap()
{
	std::ifstream inputFile("output.txt");
	
	// 1. 일반 타일 불러오기(말그대로 일반 타일)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> tempMap[i][j];  //inputFile에서 타일맵 입력받음
		}
	}

	// 2. 충돌 타일 불러오기(다른 오브젝트와 충돌체크가 된 타일)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> collMap[i][j];  //inputFile에서 충돌맵 입력받음
		}
	}

	// 3. 몬스터 오브젝트 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> monsterMap[i][j];  //inputFile에서 몬스터맵 입력받음
		}
	}

	inputFile.close();
}

//txt파일에 저장하는 형식
void FirstScene::SaveMap()
{
	std::ofstream outputFile("output.txt");

	// 1. 일반 타일 불러오기(말그대로 일반 타일)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << tempMap[i][j] << " ";  //inputFile에서 타일맵 입력받음
		}
		outputFile << std::endl;
	}

	// 2. 충돌 타일 불러오기(다른 오브젝트와 충돌체크가 된 타일)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << collMap[i][j] << " ";  //inputFile에서 충돌맵 입력받음
		}
		outputFile << std::endl;
	}

	// 3. 몬스터 오브젝트 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << monsterMap[i][j] << " ";  //inputFile에서 몬스터맵 입력받음
		}
		outputFile << std::endl;
	}

	outputFile.close();
}

FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}
