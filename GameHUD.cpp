#include "BaseInclude.h"
#include "GameHUD.h"
#include "CameraMgr.h"

#include "ImageLoader.h"
//#include "Font.h"
#include "CubePC.h"

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
		L"Resource/jiyun/minimap-01.png",
		D3DXVECTOR3(WINSIZEX - 178, WINSIZEY - 179, 0));
	m_mapImage["minimap"] = minimap;
	m_mapImage["minimap"]->Initialize();

	cImageLoader * minimap_frame = new cImageLoader(
		L"Resource/jiyun/minimap_frame-01.png",
		D3DXVECTOR3(WINSIZEX - 187, WINSIZEY - 188, 0));
	m_mapImage["minimap_frame"] = minimap_frame;
	m_mapImage["minimap_frame"]->Initialize();

	cImageLoader * mini_cham = new cImageLoader(
		L"Resource/jiyun/mini_cham-01.png",
		D3DXVECTOR3(
			850 + 57.0f * (GET_SINGLE(cCubePC))->GetPosition().x,
			780 + 60.0f * (GET_SINGLE(cCubePC))->GetPosition().z, 0));
	m_mapImage["mini_cham"] = mini_cham;
	m_mapImage["mini_cham"]->Initialize();

	// Áß¾Ó
	cImageLoader * spell = new cImageLoader(
		L"Resource/jiyun/spell-01.png",
		D3DXVECTOR3(WINSIZEX - 724, WINSIZEY - 104, 0));
	m_mapImage["spell"] = spell;
	m_mapImage["spell"]->Initialize();

	cImageLoader * item = new cImageLoader(
		L"Resource/jiyun/item-01.png",
		D3DXVECTOR3(WINSIZEX - 391, WINSIZEY - 104, 0));
	m_mapImage["item"] = item;
	m_mapImage["item"]->Initialize();

	/*cImageLoader * garen = new cImageLoader(
		L"Resource/jiyun/Garen_Circle.dds",
		D3DXVECTOR3(410, 1190, 0));
	m_mapImage["garen"] = garen;
	m_mapImage["garen"]->Initialize();*/

	cImageLoader * champion = new cImageLoader(
		L"Resource/jiyun/champion-01.png",
		D3DXVECTOR3(WINSIZEX - 784, WINSIZEY - 98, 0));
	m_mapImage["champion"] = champion;
	m_mapImage["champion"]->Initialize();

	cImageLoader * coin = new cImageLoader(
		L"Resource/jiyun/coin-01.png",
		D3DXVECTOR3(WINSIZEX - 381, WINSIZEY - 21, 0));
	m_mapImage["coin"] = coin;
	m_mapImage["coin"]->Initialize();

	cImageLoader * time = new cImageLoader(
		L"Resource/jiyun/time-01.png",
		D3DXVECTOR3(WINSIZEX - 334, 0, 0));
	m_mapImage["time"] = time;
	m_mapImage["time"]->Initialize();

	/*m_Text = new cFont;
	m_Text->Initialize(10, 5, L"±Ã¼­Ã¼");*/

	cImageLoader * exam = new cImageLoader(
		L"Resource/jiyun/example-01.png",
		D3DXVECTOR3(WINSIZEX - 424, WINSIZEY - 794, 0));
	m_mapImage["exam"] = exam;
	m_mapImage["exam"]->Initialize();

	GET_SINGLE(cCubePC)->Initialize();

	Ezreal.m_Skill[0] = cImageLoader(
		L"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(380, 670, 0));
	Ezreal.m_Skill[0].Initialize();
}

void cGameHUD::Progress()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (CheckPushKey(DIK_RIGHT))
	{
		//(m_mapImage["exam"]->GetImagePos()->x)++;

		(GET_SINGLE(cCubePC)->GetPosition().x) += 0.25f;
		(m_mapImage["mini_cham"]->GetImagePos()->x) += 2.0f;

		cout << m_mapImage["mini_cham"]->GetImagePos()->x << " "
			<< m_mapImage["mini_cham"]->GetImagePos()->y << endl;
	}

	if (CheckPushKey(DIK_LEFT))
	{
		//(m_mapImage["exam"]->GetImagePos()->x)--;

		(GET_SINGLE(cCubePC)->GetPosition().x) -= 0.25f;
		(m_mapImage["mini_cham"]->GetImagePos()->x) -= 2.0f;

		cout << m_mapImage["mini_cham"]->GetImagePos()->x << " "
			<< m_mapImage["mini_cham"]->GetImagePos()->y << endl;
	}

	if (CheckPushKey(DIK_UP))
	{
		//(m_mapImage["exam"]->GetImagePos()->y)--;

		(GET_SINGLE(cCubePC)->GetPosition().z) += 0.25f;
		(m_mapImage["mini_cham"]->GetImagePos()->y) -= 2.0f;

		cout << m_mapImage["mini_cham"]->GetImagePos()->x << " "
			<< m_mapImage["mini_cham"]->GetImagePos()->y << endl;
	}

	if (CheckPushKey(DIK_DOWN))
	{
		// (m_mapImage["exam"]->GetImagePos()->y)++;

		(GET_SINGLE(cCubePC)->GetPosition().z) -= 0.25f;
		(m_mapImage["mini_cham"]->GetImagePos()->y) += 2.0f;

		cout << m_mapImage["mini_cham"]->GetImagePos()->x << " "
			<< m_mapImage["mini_cham"]->GetImagePos()->y << endl;
	}

	GET_SINGLE(cCubePC)->Progress();
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

	m_mapImage["exam"]->Render();

	GET_SINGLE(cCubePC)->Render();

	Ezreal.m_Skill[0].Render();
}

void cGameHUD::Release()
{
	for (auto it = m_mapImage.begin();
		it != m_mapImage.end(); it++)
	{
		it->second->Release();
	}

	Ezreal.m_Skill[0].Release();
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
		//cout << m_mapImage["coin"]->GetX() << endl;

	}
		break;
		
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
		break;
	}
}

void cGameHUD::Render_Text()
{
	/*m_Text->Render("abcd");*/
}
