#include "BaseInclude.h"
#include "GameHUD.h"
#include "CameraMgr.h"

#include "Image_Loader.h"
//#include "Font.h"
#include "CubePC.h"
#include "C2DMouse.h"
#include "Text.h"
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
		"Resource/jiyun/Howling_Abyss_Minimap.png",
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
			(GET_SINGLE(cCubePC)->GetPosition().x + 855),
			(GET_SINGLE(cCubePC)->GetPosition().z + 780), 0),
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

	CImage_Loader * recall = new CImage_Loader(
		"Resource/jiyun/Recall.png",
		D3DXVECTOR3(WINSIZEX - 285, WINSIZEY - 54, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_mapImage["recall"] = recall;
	m_mapImage["recall"]->Initialize();

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
		"Resource/jiyun/state-01.png",
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

	GET_SINGLE(cCubePC)->Initialize();

	Initialize_Skill();
	InitializeKey();
	
	// 능력치
	{
		// 공격력
		CTextMgr * Base_Attack = new CTextMgr;
		m_mapStatsMgr["Base_Attack"] = Base_Attack;

		// 주문력
		CTextMgr * Magic_Attack = new CTextMgr;
		m_mapStatsMgr["Magic_Attack"] = Magic_Attack;

		// 방어력
		CTextMgr * Base_Defence = new CTextMgr;
		m_mapStatsMgr["Base_Defence"] = Base_Defence;

		// 마법 저항력
		CTextMgr * Magic_Defence = new CTextMgr;
		m_mapStatsMgr["Magic_Defence"] = Magic_Defence;

		// 사거리
		CTextMgr * AttackRange = new CTextMgr;
		m_mapStatsMgr["AttackRange"] = AttackRange;

		// 재사용 대기시간 감소
		CTextMgr * SkillTimeRatio = new CTextMgr;
		m_mapStatsMgr["SkillTimeRatio"] = SkillTimeRatio;

		// 치명타
		CTextMgr * CriticalRatio = new CTextMgr;
		m_mapStatsMgr["CriticalRatio"] = CriticalRatio;

		// 이동속도
		CTextMgr * MoveSpeed = new CTextMgr;
		m_mapStatsMgr["MoveSpeed"] = MoveSpeed;

		InitializeStats();
	}

}

void cGameHUD::Progress()
{
	Progress_Minimap();
<<<<<<< HEAD
	GET_SINGLE(cCubePC)->Progress();
	
=======

	//GET_SINGLE(cCubePC)->Progress();

	CheckMouse();

>>>>>>> origin/master
	Update_StateText();

	//CheckMouse();
}

void cGameHUD::Render()
{
	m_mapImage["minimap"]->Render();
	m_mapImage["minimap_frame"]->Render();

	m_mapImage["mini_cham"]->Render();

	m_mapImage["spell"]->Render();

	m_mapImage["recall"]->Render();
	m_mapImage["item"]->Render();
	//m_mapImage["garen"]->Render();

	m_mapImage["stats"]->Render();
	m_mapImage["champion"]->Render();
	m_mapImage["coin"]->Render();
	m_mapImage["time"]->Render();

	//GET_SINGLE(cCubePC)->Render();

	Render_Skill();
	RenderKey();

	for (auto it = m_mapStatsMgr.begin();
		it != m_mapStatsMgr.end(); it++)
	{
		it->second->RenderStats();
	}
}

void cGameHUD::Release()
{
	for (auto it = m_mapImage.begin();
		it != m_mapImage.end(); it++)
	{
		it->second->Release();
	}

	Release_Skill();
	ReleaseKey();

	for (auto it = m_mapStatsMgr.begin();
		it != m_mapStatsMgr.end(); it++)
	{
		it->second->Release();
	}
}

void cGameHUD::Initialize_Skill()
{
	// Ezreal
	m_MapSkill.insert(make_pair("Ezreal", new SkillList));

	m_MapSkill["Ezreal"]->m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Mystic_Shot.png",
		D3DXVECTOR3(376, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Ezreal"]->m_Skill[1] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Essence_Flux.png",
		D3DXVECTOR3(420, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Ezreal"]->m_Skill[2] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Arcane_Shift.png",
		D3DXVECTOR3(464, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Ezreal"]->m_Skill[3] = CImage_Loader(
		"Resource/jiyun/skill/Ezreal/Trueshot_Barrage.png",
		D3DXVECTOR3(508, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//// Ez_copy
	//Ezreal_copy.m_Skill[0] = CImage_Loader(
	//	"Resource/jiyun/skill/Ezreal/Mystic_Shot.png",
	//	D3DXVECTOR3(376, 660, 0),
	//	D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//Udyr
	m_MapSkill.insert(make_pair("Udyr", new SkillList));

	m_MapSkill["Udyr"]->m_Skill[0] = CImage_Loader(
		"Resource/jiyun/skill/Udyr/Tiger_Stance.png",
		D3DXVECTOR3(376, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Udyr"]->m_Skill[1] = CImage_Loader(
		"Resource/jiyun/skill/Udyr/Turtle_Stance.png",
		D3DXVECTOR3(420, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Udyr"]->m_Skill[2] = CImage_Loader(
		"Resource/jiyun/skill/Udyr/Bear_Stance.png",
		D3DXVECTOR3(464, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	m_MapSkill["Udyr"]->m_Skill[3] = CImage_Loader(
		"Resource/jiyun/skill/Udyr/Phoenix_Stance.png", 
		D3DXVECTOR3(508, 713, 0),
		D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	
	for (int i = 0; i < SkillCount; i++)
	{
		m_MapSkill["Ezreal"]->m_Skill[i].Initialize();
		m_MapSkill["Udyr"]->m_Skill[i].Initialize();
	}

	//Ezreal_copy.m_Skill[0].Initialize();
}

void cGameHUD::Render_Skill()
{
	for (int i = 0; i < SkillCount; i++)
	{
		//m_MapSkill["Ezreal"]->m_Skill[i].Render();
		m_MapSkill["Udyr"]->m_Skill[i].Render();
		//Ezreal.m_Skill[i].Render();
	}
		
	/*if (m_isLButtonDown == true)
	{
		Ezreal_copy.m_Skill[0].Render();
	}*/
}

void cGameHUD::Release_Skill()
{
	for (int i = 0; i < SkillCount; i++)
	{
		//m_MapSkill["Ezreal"]->m_Skill[i].Release();
		m_MapSkill["Udyr"]->m_Skill[i].Release();
	}
}

void cGameHUD::InitializeKey()
{
	RECT QBox;
	SetRect(&QBox, 376, 742, 415, 742);
	st_key.m_pQKey = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", QBox, string("Q"));

	RECT WBox;
	SetRect(&WBox, 420, 742, 459, 742);
	st_key.m_pWKey = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", WBox, string("W"));

	RECT EBox;
	SetRect(&EBox, 464, 742, 503, 742);
	st_key.m_pEKey = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", EBox, string("E"));

	RECT RBox;
	SetRect(&RBox, 508, 742, 547, 742);
	st_key.m_pRKey = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", RBox, string("R"));
}

void cGameHUD::RenderKey()
{
	st_key.m_pQKey->m_pFont->DrawTextA(
		NULL,
		st_key.m_pQKey->m_sInfo.c_str(),
		st_key.m_pQKey->m_sInfo.length(),
		&st_key.m_pQKey->m_Rect,
		DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	st_key.m_pWKey->m_pFont->DrawTextA(
		NULL,
		st_key.m_pWKey->m_sInfo.c_str(),
		st_key.m_pWKey->m_sInfo.length(),
		&st_key.m_pWKey->m_Rect,
		DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	st_key.m_pEKey->m_pFont->DrawTextA(
		NULL,
		st_key.m_pEKey->m_sInfo.c_str(),
		st_key.m_pEKey->m_sInfo.length(),
		&st_key.m_pEKey->m_Rect,
		DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	st_key.m_pRKey->m_pFont->DrawTextA(
		NULL,
		st_key.m_pRKey->m_sInfo.c_str(),
		st_key.m_pRKey->m_sInfo.length(),
		&st_key.m_pRKey->m_Rect,
		DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void cGameHUD::ReleaseKey()
{
	SAFE_DELETE(st_key.m_pQKey);
	SAFE_DELETE(st_key.m_pWKey);
	SAFE_DELETE(st_key.m_pEKey);
	SAFE_DELETE(st_key.m_pRKey);
}

void cGameHUD::InitializeStats()
{
	// 능력치
	{
		// 공격력
		m_mapStatsMgr["Base_Attack"]->InitializeStats(
			m_Stats.fBase_Attack,
			m_mapImage["stats"]->GetPosition().x + 33,
			m_mapImage["stats"]->GetPosition().y + 13,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 마법력
		m_mapStatsMgr["Magic_Attack"]->InitializeStats(
			m_Stats.fMagic_Attack,
			m_mapImage["stats"]->GetPosition().x + 100,
			m_mapImage["stats"]->GetPosition().y + 13,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 방어력
		m_mapStatsMgr["Base_Defence"]->InitializeStats(
			m_Stats.fBase_Defence,
			m_mapImage["stats"]->GetPosition().x + 33,
			m_mapImage["stats"]->GetPosition().y + 36,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 마법저항력
		m_mapStatsMgr["Magic_Defence"]->InitializeStats(
			m_Stats.fMagic_Defence,
			m_mapImage["stats"]->GetPosition().x + 100,
			m_mapImage["stats"]->GetPosition().y + 35,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 사거리
		m_mapStatsMgr["AttackRange"]->InitializeStats(
			m_Stats.fAttackRange,
			m_mapImage["stats"]->GetPosition().x + 33,
			m_mapImage["stats"]->GetPosition().y + 58,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 재사용 대기시간 감소
		m_mapStatsMgr["SkillTimeRatio"]->InitializeStats(
			m_Stats.fSkillTimeRatio,
			m_mapImage["stats"]->GetPosition().x + 100,
			m_mapImage["stats"]->GetPosition().y + 58,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 치명타
		m_mapStatsMgr["CriticalRatio"]->InitializeStats(
			m_Stats.fCriticalRatio,
			m_mapImage["stats"]->GetPosition().x + 33,
			m_mapImage["stats"]->GetPosition().y + 80,
			m_mapImage["stats"]->GetPosition().x,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);

		// 이동속도
		m_mapStatsMgr["MoveSpeed"]->InitializeStats(
			m_Stats.fMoveSpeed,
			m_mapImage["stats"]->GetPosition().x + 100,
			m_mapImage["stats"]->GetPosition().y + 80,
			m_mapImage["stats"]->GetPosition().x + 135,
			m_mapImage["stats"]->GetImageInfo().Height
			+ m_mapImage["stats"]->GetPosition().y);
	}
}

void cGameHUD::Update_StateText()
{

	// 공격력
	m_mapStatsMgr["Base_Attack"]->SetText(m_Stats.fBase_Attack);

	// 마법력
	m_mapStatsMgr["Magic_Attack"]->SetText(m_Stats.fMagic_Attack);

	// 방어력
	m_mapStatsMgr["Base_Defence"]->SetText(m_Stats.fBase_Defence);
	// 마법저항력
	m_mapStatsMgr["Magic_Defence"]->SetText(m_Stats.fMagic_Defence);
	// 사거리
	m_mapStatsMgr["AttackRange"]->SetText(m_Stats.fAttackRange);
	// 재사용 대기시간 감소
	m_mapStatsMgr["SkillTimeRatio"]->SetText(m_Stats.fSkillTimeRatio);
	// 치명타
	m_mapStatsMgr["CriticalRatio"]->SetText(m_Stats.fCriticalRatio);
	// 이동속도
	m_mapStatsMgr["MoveSpeed"]->SetText(m_Stats.fMoveSpeed);

}

void cGameHUD::Progress_Minimap()
{
	if (CheckPushKey(DIK_RIGHT))
	{
		(GET_SINGLE(cCubePC)->GetPosition().x) += 0.25f;
		(m_mapImage["mini_cham"]->Get_Position().x) += 0.55f;

		cout << m_mapImage["mini_cham"]->Get_Position().x << ", "
			<< m_mapImage["mini_cham"]->Get_Position().y << endl;
	}

	if (CheckPushKey(DIK_LEFT))
	{
		(GET_SINGLE(cCubePC)->GetPosition().x) -= 0.25f;
		(m_mapImage["mini_cham"]->Get_Position().x) -= 0.55f;

		cout << m_mapImage["mini_cham"]->Get_Position().x << ", "
			<< m_mapImage["mini_cham"]->Get_Position().y << endl;
	}

	if (CheckPushKey(DIK_UP))
	{
		(GET_SINGLE(cCubePC)->GetPosition().z) += 0.25f;
		(m_mapImage["mini_cham"]->Get_Position().y) -= 0.55f;

		cout << m_mapImage["mini_cham"]->Get_Position().x << ", "
			<< m_mapImage["mini_cham"]->Get_Position().y << endl;
	}

	if (CheckPushKey(DIK_DOWN))
	{
		(GET_SINGLE(cCubePC)->GetPosition().z) -= 0.25f;
		(m_mapImage["mini_cham"]->Get_Position().y) += 0.55f;

		cout << m_mapImage["mini_cham"]->Get_Position().x << ", "
			<< m_mapImage["mini_cham"]->Get_Position().y << endl;
	}
}

//void cGameHUD::CheckMouse()
//{
//	if (GetAsyncKeyState(VK_LBUTTON))
//	{
//		if (GET_SINGLE(C2DMouse)->IsClicked_Button(&(Ezreal.m_Skill[0])))
//		{
//			m_isLButtonDown = true;
//		}
//		else
//		{
//			m_isLButtonDown = false;
//		}
//	}
//}