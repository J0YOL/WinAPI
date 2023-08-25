#include "FirstScene.h"
#include "GameDirector.h"

#define MAP_WIDTH	10
#define MAP_HEIGHT	10

int tempMap[MAP_HEIGHT][MAP_WIDTH];		//Ÿ�� ��
int collMap[MAP_HEIGHT][MAP_WIDTH];		//�浹 ��
int monsterMap[MAP_HEIGHT][MAP_WIDTH];	//���� ��

void FirstScene::Init()
{
	//��ư�� ����
	RECT rc4 = { 640, 100, 890, 162 };  //���� 250, ���� 62
	m_NextButton.Init(const_cast<char*>("start_Button.bmp"), rc4);
	m_NextButton.SetTag(const_cast<char*>(TAG_NEXT_BUTTON));
	m_NextButton.SetTransparentColor(RGB(255, 0, 255));

	m_NextButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_NextButton.GetButtonCropRect()[BTN_STATE_HOVAL] = { 0,72,200,72 };
	m_NextButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142,200,72 };

	//���ҽ����� ����
	m_TileMap.LoadBitmapByPath("Resource/tilemap.bmp");
	m_Monster.LoadBitmapByPath("ResourceM/eagle-attack-1.bmp");
	m_Guide.LoadBitmapByPath("ResourceM/guide.bmp");

	//�� �׸��� ������ ������ ����
	//m_TileMap.SetTransparentColor(RGB(255, 255, 255));	-> �̰Ŵ� ����� �����ϴϱ� ¡�׷����� �ϴ� �ּ�ó��
	m_Monster.SetTransparentColor(RGB(255, 255, 255));

	//�� ũ�� ����
	m_MapSize.x = MAP_WIDTH;
	m_MapSize.y = MAP_HEIGHT;

	//��ũ�� ũ�� ���� -> MapTool�� ����Ǵ� ��ũ��(�۵�)
	m_ScreenSize.x = m_MapSize.x * TILE_SIZE;
	m_ScreenSize.y = m_MapSize.y * TILE_SIZE + 20;

	//������ ����Ʈ ������ ����
	m_ItemListSize.x = m_ScreenSize.x;
	m_ItemListSize.y = m_ScreenSize.y + TILE_SIZE;

	//�ʵ��� �ʱ�ȭ
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			tempMap[i][j]		= 0;
			collMap[i][j]		= 0;
			monsterMap[i][j]	= -1;
		}
	}

	//Ÿ�ϸ� �ҷ�����
	LoadMap();
}

//Key�� �Է��� �� ����� ����
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

	//���콺 ������ Ŭ��
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT mPosi;  //Cursor��ġ���� �޾Ƴ��� ����

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		//1. ��Ÿ�Ϲ����� Ŭ��������
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x &&
			mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			//Cursor�� ��ġ�� ScreenSize���� �����϶� �� ��ġ���� �� Map�� �־��
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;

			if (m_IsMakeMonster)
			{
				monsterMap[mY][mX] = m_ScelectNumber;
			}
			else
			{
				tempMap[mY][mX] = m_ScelectNumber;
		
				//�浹üũ�� �Ǿ��� ��� �浹ó��
				if (m_IsColl)	collMap[mY][mX] = 1;
				else			collMap[mY][mX] = 0;
			}
		}

		//2. ������ ������ Ŭ������ ��
		else if (mPosi.x <= m_ItemListSize.x && mPosi.y <= m_ItemListSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;  //Y�����δ� ���� �ʿ����(1�ٷ� ItemList�� ����)
			m_ScelectNumber = mX + m_AddNum;
		}
	}

	//������ Ŭ���� ����
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		POINT mPosi;

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		//1. ��Ÿ�Ϲ����� Ŭ��������
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x&&
			mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;
		
			monsterMap[mY][mX] = -1;		
		}
	}

	//SŰ ����
	if (GetAsyncKeyState(0x53))
	{
		MessageBox(NULL, TEXT("���� �����߽��ϴ�."), TEXT("�˸�"), MB_OK);
		SaveMap();
	}

	//CŰ�� ������ �� �浹 Ȱ��ȭ/��Ȱ��ȭ
	if (GetAsyncKeyState(0x43) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsColl = !m_IsColl;
	}

	//MŰ�� ���� �� ����/ ��Ÿ�� ��� ����
	if (GetAsyncKeyState(0x4D) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsMakeMonster = !m_IsMakeMonster;

		//����Ÿ�� �ѹ� �ʱ�ȭ
		m_ScelectNumber = 0;
		m_AddNum		= 0;
	}
}

void FirstScene::Render(HDC hdc, float dt)
{
	m_NextButton.Render(hdc, dt);

	//MapTool' Guide
	m_Guide.DrawBitmap(hdc, 650, 300, 250, 250);


	//1.��Ÿ�� �׸���
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			m_TileMap.DrawBitmapCropping(hdc, TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE, TILE_SIZE,
				(tempMap[i][j] % m_MapAcrossCount)*ORI_TILE_SIZE,
				(tempMap[i][j] / m_MapAcrossCount)*ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);

			//���� �׸���
			if (monsterMap[i][j] != -1)
			{
				m_Monster.DrawBitmap(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE);
			}

			//�浹�� �׸���
			if (collMap[i][j] == 1)
			{
				Ellipse(hdc, TILE_SIZE*j, TILE_SIZE*i, TILE_SIZE*j + 20, TILE_SIZE*i + 20);
			}
		}
	}

	//2.������ ����Ʈ �׸���
	//�Ϲ�Ÿ�� / ���� �׸���
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

	//3.������ Ÿ�� �̹��� �׸���
	RECT rect = {
		TILE_SIZE * m_MapSize.x + 20, m_ScreenSize.y - 20,
		TILE_SIZE * m_MapSize.x + 105 , m_ScreenSize.y };

	DrawText(hdc, TEXT("������ Ÿ��"), 12, &rect, NULL);

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

		//�浹ó��
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
	
	// 1. �Ϲ� Ÿ�� �ҷ�����(���״�� �Ϲ� Ÿ��)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> tempMap[i][j];  //inputFile���� Ÿ�ϸ� �Է¹���
		}
	}

	// 2. �浹 Ÿ�� �ҷ�����(�ٸ� ������Ʈ�� �浹üũ�� �� Ÿ��)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> collMap[i][j];  //inputFile���� �浹�� �Է¹���
		}
	}

	// 3. ���� ������Ʈ �ҷ�����
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			inputFile >> monsterMap[i][j];  //inputFile���� ���͸� �Է¹���
		}
	}

	inputFile.close();
}

//txt���Ͽ� �����ϴ� ����
void FirstScene::SaveMap()
{
	std::ofstream outputFile("output.txt");

	// 1. �Ϲ� Ÿ�� �ҷ�����(���״�� �Ϲ� Ÿ��)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << tempMap[i][j] << " ";  //inputFile���� Ÿ�ϸ� �Է¹���
		}
		outputFile << std::endl;
	}

	// 2. �浹 Ÿ�� �ҷ�����(�ٸ� ������Ʈ�� �浹üũ�� �� Ÿ��)
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << collMap[i][j] << " ";  //inputFile���� �浹�� �Է¹���
		}
		outputFile << std::endl;
	}

	// 3. ���� ������Ʈ �ҷ�����
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++) 
		{
			outputFile << monsterMap[i][j] << " ";  //inputFile���� ���͸� �Է¹���
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
