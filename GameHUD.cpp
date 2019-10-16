#include "BaseInclude.h"
#include "GameHUD.h"

#include "ImageLoader.h"

cGameHUD::cGameHUD()
{
	m_isLButtonDown = false;
}


cGameHUD::~cGameHUD()
{
}

void cGameHUD::Initialize()
{
	// ¹Ì´Ï¸Ê
	cImageLoader * minimap = new cImageLoader(
		L"Resource/jiyun/minimap.png",
		D3DXVECTOR3(1395, 1020, 0));
	m_mapImage["minimap"] = minimap;
	m_mapImage["minimap"]->Initialize();

	// Áß¾Ó
	cImageLoader * spell = new cImageLoader(
		L"Resource/jiyun/spell.png",
		D3DXVECTOR3(500, 1160, 0));
	m_mapImage["spell"] = spell;
	m_mapImage["spell"]->Initialize();

	cImageLoader * item = new cImageLoader(
		L"Resource/jiyun/item.png",
		D3DXVECTOR3(1055, 1160, 0));
	m_mapImage["item"] = item;
	m_mapImage["item"]->Initialize();

	cImageLoader * champion = new cImageLoader(
		L"Resource/jiyun/champion.png",
		D3DXVECTOR3(400, 1170, 0));
	m_mapImage["champion"] = champion;
	m_mapImage["champion"]->Initialize();

	cImageLoader * coin = new cImageLoader(
		L"Resource/jiyun/coin.png",
		D3DXVECTOR3(1072, 1298, 0));
	m_mapImage["coin"] = coin;
	m_mapImage["coin"]->Initialize();
}

void cGameHUD::Progress()
{
}

void cGameHUD::Render()
{
	for (auto it = m_mapImage.begin(); 
		it != m_mapImage.end(); it++)
	{
		it->second->Render();
	}
}

void cGameHUD::Release()
{
}

void cGameHUD::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	float x = LOWORD(lParam);
	float y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		cout << "clicked\n";
	}
		break;
		
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
		break;
	}
}
