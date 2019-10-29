#include "BaseInclude.h"
#include "GameHUD.h"
#include "CameraMgr.h"

#include "Image_Loader.h"
//#include "Font.h"
#include "CubePC.h"
#include "C2DMouse.h"

cGameHUD::cGameHUD()
{
	m_isLButtonDown = false;
	m_StartTime = g_fDeltaTime;
}


cGameHUD::~cGameHUD()
{
}

void cGameHUD::Initialize()
{
	// ¹Ì´Ï¸Ê
	CImage_Loader * minimap = new CImage_Loader(
		"Resource/jiyun/minimap-01.png",
		D3DXVECTOR3(WINSIZEX - 178, WINSIZEY - 179, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["minimap"] = minimap;
	m_mapImage["minimap"]->Initialize();

	CImage_Loader * minimap_frame = new CImage_Loader(
		"Resource/jiyun/minimap_frame-01.png",
		D3DXVECTOR3(WINSIZEX - 187, WINSIZEY - 188, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["minimap_frame"] = minimap_frame;
	m_mapImage["minimap_frame"]->Initialize();

	CImage_Loader * mini_cham = new CImage_Loader(
		"Resource/jiyun/mini_cham-01.png",
		D3DXVECTOR3(
			(-57) * (GET_SINGLE(cCubePC)->GetPosition().x),
			(-60) * (GET_SINGLE(cCubePC)->GetPosition().z), 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["mini_cham"] = mini_cham;
	m_mapImage["mini_cham"]->Initialize();

	// Áß¾Ó
	CImage_Loader * spell = new CImage_Loader(
		"Resource/jiyun/spell-01.png",
		D3DXVECTOR3(WINSIZEX - 724, WINSIZEY - 104, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["spell"] = spell;
	m_mapImage["spell"]->Initialize();

	CImage_Loader * item = new CImage_Loader(
		"Resource/jiyun/item-01.png",
		D3DXVECTOR3(WINSIZEX - 391, WINSIZEY - 104, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["item"] = item;
	m_mapImage["item"]->Initialize();

	/*CImage_Loader * garen = new CImage_Loader(
		L"Resource/jiyun/Garen_Circle.dds",
		D3DXVECTOR3(410, 1190, 0));
	m_mapImage["garen"] = garen;
	m_mapImage["garen"]->Initialize();*/

	CImage_Loader * champion = new CImage_Loader(
		"Resource/jiyun/champion-01.png",
		D3DXVECTOR3(WINSIZEX - 784, WINSIZEY - 98, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["champion"] = champion;
	m_mapImage["champion"]->Initialize();

	CImage_Loader * coin = new CImage_Loader(
		"Resource/jiyun/coin-01.png",
		D3DXVECTOR3(WINSIZEX - 381, WINSIZEY - 21, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["coin"] = coin;
	m_mapImage["coin"]->Initialize();

	CImage_Loader * time = new CImage_Loader(
		"Resource/jiyun/time-01.png",
		D3DXVECTOR3(WINSIZEX - 334, 0, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["time"] = time;
	m_mapImage["time"]->Initialize();

	/*m_Text = new cFont;
	m_Text->Initialize(10, 5, L"±Ã¼­Ã¼");*/

	GET_SINGLE(cCubePC)->Initialize();

	Ezreal.m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(376, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ezreal.m_Skill[0].Initialize();

	Ezreal_copy.m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(376, 660, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ezreal_copy.m_Skill[0].Initialize();
}

void cGameHUD::Progress()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (CheckPushKey(DIK_RIGHT))
	{
		//(m_mapImage["exam"]->GetImagePos()->x)++;

		(GET_SINGLE(cCubePC)->GetPosition().x) += 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().x)++;
	}

	if (CheckPushKey(DIK_LEFT))
	{
		//(m_mapImage["exam"]->GetImagePos()->x)--;

		(GET_SINGLE(cCubePC)->GetPosition().x) -= 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().x)--;
	}
	
	if (CheckPushKey(DIK_UP))
	{
		//(m_mapImage["exam"]->GetImagePos()->y)--;

		(GET_SINGLE(cCubePC)->GetPosition().z) += 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().y)--;
	}

	if (CheckPushKey(DIK_DOWN))
	{
		// (m_mapImage["exam"]->GetImagePos()->y)++;

		(GET_SINGLE(cCubePC)->GetPosition().z) -= 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().y)++;
	}

	GET_SINGLE(cCubePC)->Progress();

	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (GET_SINGLE(C2DMouse)->IsClicked_inImage(&Ezreal.m_Skill[0]))
		{
			m_isLButtonDown = true;
			cout << "clicked\n";
		}
	}
	if (m_isLButtonDown)
	{
	}*/

	float m_CurrentTime = g_fDeltaTime;
}

void cGameHUD::Render()
{
	m_mapImage["minimap"]->Render();
	m_mapImage["minimap_frame"]->Render();

	m_mapImage["mini_cham"]->Render();

	m_mapImage["spell"]->Render();
	m_mapImage["item"]->Render();
	//m_mapImage["garen"]->Render();
	m_mapImage["champion"]->Render();
	m_mapImage["coin"]->Render();
	m_mapImage["time"]->Render();

	GET_SINGLE(cCubePC)->Render();

	Ezreal.m_Skill[0].Render();
	Ezreal_copy.m_Skill[0].Render();
}

void cGameHUD::Release()
{
	for (auto it = m_mapImage.begin();
		it != m_mapImage.end(); it++)
	{
		it->second->Release();
	}

	Ezreal.m_Skill[0].Release();
	Ezreal_copy.m_Skill[0].Release();
}

void cGameHUD::Render_Text()
{
	/*m_Text->Render("abcd");*/
}
