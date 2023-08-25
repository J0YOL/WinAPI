#pragma once
#include "GameDefine.h"

class PrepareWind; //����� �޵���

//Loop��, window��������, �����ֱ� ���� �ϴ� class
class WrappedWind
{
public:
	//Loop���� ���ִ� �Լ�����
	int				Loop(HINSTANCE hInstance, LPSTR IpCmdLine, int nCmdShow);

private:
	void			registerWndClass(const PrepareWind& value);
	void			createWindow(const PrepareWind& value);
	void			showWindow(const PrepareWind& value);
	int				MessageLoop();

public:
	//���������Լ� �����������Լ�
	virtual void	ProcessingLoop() = 0;

protected:
	//������ �Ҽ��ֵ��� �ĺ��� ���� ����
	HWND			m_hWnd			= nullptr;
	HINSTANCE		m_hInstance		= nullptr;

public:
	//���� �ĺ��ڵ��� �������� ���� �Լ�
	HWND			GetWindHandle();
	HINSTANCE		GetInstanceHandle();

public:
	WrappedWind();
	~WrappedWind();
};

