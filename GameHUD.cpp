#include "BaseInclude.h"
#include "GameHUD.h"
#include "CameraMgr.h"

#include "ImageLoader.h"
//#include "Font.h"
#include "CubePC.h"
#include "Image_Loader.h"
#include "TextMgr.h"
#include "ObjMgr.h"

#include "ChampGauge.h"
#include "MinionGauge.h"

cGameHUD::cGameHUD()
	:m_TextMgr(NULL)
{
	m_isLButtonDown = false;
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
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["minimap"] = minimap;

	CImage_Loader * minimap_frame = new CImage_Loader(
		"Resource/jiyun/minimap_frame-01.png",
		D3DXVECTOR3(WINSIZEX - 187, WINSIZEY - 188, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["minimap_frame"] = minimap_frame;

	CImage_Loader * mini_cham = new CImage_Loader(
		"Resource/jiyun/mini_cham-01.png",
		D3DXVECTOR3(
			 (m_mapImage["minimap"]->GetPosition().x) + 20 * ((GET_SINGLE(cCubePC)->GetPosition().x) / m_mapImage["minimap"]->GetPosition().x),
				 (m_mapImage["minimap"]->GetImageInfo().Height) + (m_mapImage["minimap"]->GetPosition().y) + 20 * ((GET_SINGLE(cCubePC)->GetPosition().z)
					/ m_mapImage["minimap"]->GetPosition().y), 0)
	, D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["mini_cham"] = mini_cham;

	// Áß¾Ó
	CImage_Loader * spell = new CImage_Loader(
		"Resource/jiyun/spell-01.png",
		D3DXVECTOR3(WINSIZEX - 724, WINSIZEY - 104, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["spell"] = spell;

	CImage_Loader * item = new CImage_Loader(
		"Resource/jiyun/item-01.png",
		D3DXVECTOR3(WINSIZEX - 391, WINSIZEY - 104, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["item"] = item;

	CImage_Loader * coin = new CImage_Loader(
		"Resource/jiyun/coin-01.png",
		D3DXVECTOR3(WINSIZEX - 381, WINSIZEY - 21, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["coin"] = coin;

	CImage_Loader * time = new CImage_Loader(
		"Resource/jiyun/time-01.png",
		D3DXVECTOR3(WINSIZEX - 334, 0, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["time"] = time;

	/*m_Text = new cFont;
	m_Text->Initialize(10, 5, L"±Ã¼­Ã¼");*/

	CImage_Loader * exam = new CImage_Loader(
		"Resource/jiyun/example-01.png",
		D3DXVECTOR3(WINSIZEX - 424, WINSIZEY - 794, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["exam"] = exam;

	CImage_Loader * champion = new CImage_Loader(
		"Resource/jiyun/champion-01.png",
		D3DXVECTOR3(WINSIZEX - 784, WINSIZEY - 98, 0),
		D3DXVECTOR3(1.0f, 1.0f, 0));
	m_mapImage["champion"] = champion;

	for (auto it = m_mapImage.begin(); it != m_mapImage.end(); it++)
		it->second->Initialize();

	m_TextMgr = new CTextMgr();
	m_TextMgr->Initialize();
	GET_SINGLE(cCubePC)->Initialize();


	m_Gauge = new CChampGauge;
	m_Gauge->Initialize();

	m_Minion = new CMinionGauge;
	m_Minion->Initialize();
}

void cGameHUD::Progress()
{
	m_TextMgr->Progress();
	GET_SINGLE(cCubePC)->Progress();

	
	m_Gauge->Progress();
	m_Minion->Progress();
}

void cGameHUD::Render()
{
	m_mapImage["minimap"]->Render();
	m_mapImage["minimap_frame"]->Render();

	m_mapImage["mini_cham"]->Render();

	m_mapImage["spell"]->Render();
	m_mapImage["item"]->Render();
	
	
	m_mapImage["coin"]->Render();
	m_mapImage["time"]->Render();
	m_mapImage["champion"]->Render();
	

#pragma region HUD ¿ì»ó´Ü¿¡ KDA, CS, TIMER
	m_TextMgr->IngameTimer();
	/*m_TextMgr->CS_Count();
	m_TextMgr->KDA_Count(1, 1, 1);*/
#pragma endregion
	//GET_SINGLE(cCubePC)->Render();

	m_Gauge->Render();
	m_Minion->Render();
}

void cGameHUD::Release()
{
	for (auto it = m_mapImage.begin();
		it != m_mapImage.end(); it++)
	{
		it->second->Release();
	}
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
