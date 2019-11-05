#include "BaseInclude.h"
#include "GameHUD.h"
#include "CameraMgr.h"

#include "Image_Loader.h"
//#include "Font.h"
#include "CubePC.h"
#include "C2DMouse.h"
#include "TextMgr.h"

cGameHUD::cGameHUD()
{
	m_isLButtonDown = false;

	m_Stats.fBase_Attack = NULL;
}


cGameHUD::~cGameHUD()
{
}

void cGameHUD::Initialize()
{
	// 미니맵
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

	// 중앙
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

	CImage_Loader * stats = new CImage_Loader(
		"Resource/jiyun/state.png",
		D3DXVECTOR3(WINSIZEX - 905, WINSIZEY - 101, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["stats"] = stats;
	m_mapImage["stats"]->Initialize();

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
	m_Text->Initialize(10, 5, L"궁서체");*/

	/*CImage_Loader * character_state = new CImage_Loader(
		"Resource/jiyun/character_state.png",
		D3DXVECTOR3(0, WINSIZEY -  )
	)*/

	GET_SINGLE(cCubePC)->Initialize();

	/*Ezreal.m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(376, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ezreal.m_Skill[0].Initialize();

	Ezreal_copy.m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(376, 660, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ezreal_copy.m_Skill[0].Initialize();*/
	
	// 능력치
	{
		// 임의로 값줌
		{
			m_Stats.fBase_Attack = 40;
			m_Stats.fMagic_Attack = 40;
			m_Stats.fBase_Defence = 100;
			m_Stats.fMagic_Defence = 100;
			m_Stats.fCriticalRatio = 20;
			m_Stats.fMoveSpeed = 30;
			m_Stats.fHP = 100;
			m_Stats.fSkillTimeRatio = 45;
			m_Stats.fAttackRange = 34;
		}

		// 공격력
		CTextMgr * Base_Attack = new CTextMgr;
		m_mapTextMgr["Base_Attack"] = Base_Attack;
		m_mapTextMgr["Base_Attack"]->Initialize_Text(
			m_Stats.fBase_Attack,
			m_mapImage["stats"]->GetPosition().x + 90,
			m_mapImage["stats"]->GetPosition().y + 14,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 주문력
		CTextMgr * Magic_Attack = new CTextMgr;
		m_mapTextMgr["Magic_Attack"] = Magic_Attack;
		m_mapTextMgr["Magic_Attack"]->Initialize_Text(
			m_Stats.fMagic_Attack,
			m_mapImage["stats"]->GetPosition().x + 90,
			m_mapImage["stats"]->GetPosition().y + 13,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 방어력
		CTextMgr * Base_Defence = new CTextMgr;
		m_mapTextMgr["Base_Defence"] = Base_Defence;
		m_mapTextMgr["Base_Defence"]->Initialize_Text(
			m_Stats.fBase_Defence,
			m_mapImage["stats"]->GetPosition().x + 90,
			m_mapImage["stats"]->GetPosition().y + 36,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 마법 저항력
		CTextMgr * Magic_Defence = new CTextMgr;
		m_mapTextMgr["Magic_Defence"] = Magic_Defence;
		m_mapTextMgr["Magic_Defence"]->Initialize_Text(
			m_Stats.fMagic_Defence,
			m_mapImage["stats"]->GetPosition().x + 90,
			m_mapImage["stats"]->GetPosition().y + 35,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);
	}
}

void cGameHUD::Progress()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	Progress_Minimap();

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
}

void cGameHUD::Render()
{
	m_mapImage["minimap"]->Render();
	m_mapImage["minimap_frame"]->Render();

	m_mapImage["mini_cham"]->Render();

	m_mapImage["spell"]->Render();
	m_mapImage["item"]->Render();
	//m_mapImage["garen"]->Render();

	m_mapImage["stats"]->Render();
	m_mapImage["champion"]->Render();
	m_mapImage["coin"]->Render();
	m_mapImage["time"]->Render();

	GET_SINGLE(cCubePC)->Render();

	/*Ezreal.m_Skill[0].Render();
	Ezreal_copy.m_Skill[0].Render();*/

	m_mapTextMgr["Base_Attack"]->Render_Text();
	m_mapTextMgr["Magic_Attack"]->Render_Text();
	m_mapTextMgr["Base_Defence"]->Render_Text();
	m_mapTextMgr["Magic_Defence"]->Render_Text();
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

	m_mapTextMgr["Base_Attack"]->Reelase();
	m_mapTextMgr["Magic_Attack"]->Reelase();
	m_mapTextMgr["Base_Defence"]->Reelase();
	m_mapTextMgr["Magic_Defence"]->Reelase();
}

void cGameHUD::Progress_Minimap()
{
	if (CheckPushKey(DIK_RIGHT))
	{
		(GET_SINGLE(cCubePC)->GetPosition().x) += 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().x)++;
	}

	if (CheckPushKey(DIK_LEFT))
	{
		(GET_SINGLE(cCubePC)->GetPosition().x) -= 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().x)--;
	}

	if (CheckPushKey(DIK_UP))
	{
		(GET_SINGLE(cCubePC)->GetPosition().z) += 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().y)--;
	}

	if (CheckPushKey(DIK_DOWN))
	{
		(GET_SINGLE(cCubePC)->GetPosition().z) -= 0.22f;
		(m_mapImage["mini_cham"]->Get_Position().y)++;
	}
}
