#include "BaseInclude.h"
#include "TextMgr.h"
#include "Text.h"


CTextMgr::CTextMgr() : m_vpos(0, 0, 0)
{
	{
		Spell_list.m_cleanse = "챔피언에 걸린 모든 이동 불가와(제압 및 공중\n으로 띄우는 효과 제외) 소환사 주문에 의한 해\n로운 효과를 제거하고 새로 적용되는 이동 불가\n 효과들의 지속시간을 3초가 65 % 감소시킵니\n다.\n기본 재사용 대기 시간:210초";
		Spell_list.m_Ghost = "챔피언이 10초동안 유닛과 충돌하지 않게 되\n며 이동속도가 상승합니다. 이동 속도는 2초\n동안 점차 빨라져 레벨에 따라 최대 28~45%\n까지 상승합니다.\n기본 재사용 대기시간:180초";
		Spell_list.m_heal = "챔피언과 대상 아군의 체력을 90~345만큼(챔\n피언 레벨에 따라 변동) 회복 시키고 1초동안 \n이동속도가 30% 증가합니다. 최근 소환사 주\n문 회복의 영향을 받은 유닛의 경우 치유량이\n 절반만 적용됩니다.\n\n기본 재사용 대기시간:240초";
		Spell_list.m_Exhaust = "적 챔피언을 지치게 만들어 2.5초동안 이동속\n도를 30% 낮추며, 이 동안 가하는 피해량을 \n40% 낮춥니다.\n\n기본 재사용 대기시간:210초";
		Spell_list.m_Flash = "커서 방향으로 챔피언이 짧은 거리를 순간이동\n 합니다.기본 재사용 대기시간:300초";
		Spell_list.m_Smite = "대상 에픽 및 대형/중형 몬스터, 혹은 적 미니\n언에게 390~1000(챔피언 레벨에 따라 변동)\n의 고정 피해를 입힙니다. 몬스터에게 사용하면\n 자신의 최대 체력에 비례해 체력을 회복합니다.\n\n기본 재사용 대기시간:15초";
		Spell_list.m_Teleport = "4초 동안 정신을 집중한 다음, 챔피언이 지정한\n 아군 구조물, 미니언, 혹은 와드로 순간이동합\n니다.\n기본 재사용 대기시간 360초";
		Spell_list.m_Ignite = "적 챔피언을 불태워 5초동안 70~410의 고정\n 피해(챔피언 레벨에 따라 변동)를 입히고 모습\n을 드러내며 치료 효과를 감소시킵니다.\n\n기본 재사용 대기시간:180초";
		Spell_list.m_Barrier = "2초동안 방어막으로 감싸 피해를\n 115~455(챔피언 레벨에 따라 변동)만큼 흡수\n합니다.\n기본 재사용 대기시간:180초";
	}


	{
		Spell_name.m_cleanse = "정화";
		Spell_name.m_Teleport = "순간이동";
		Spell_name.m_Exhaust = "탈진";
		Spell_name.m_Ghost = "유체화";
		Spell_name.m_Flash = "점멸";
		Spell_name.m_Smite = "강타";
		Spell_name.m_Ignite = "점화";
		Spell_name.m_Barrier = "방어막";
		Spell_name.m_heal = "회복";
	}

	m_vecNotice.push_back(string("123123123"));
	m_sNotice = m_vecNotice[rand() % m_vecNotice.size()];
}


CTextMgr::~CTextMgr()
{
}

void CTextMgr::Initialize()
{
	RECT name = { m_vpos.x + 510, m_vpos.y - 280, 0, 0 };
	RECT info = { m_vpos.x + 510, m_vpos.y - 250, 0, 0 };
	//Spell Name setting
	CSpell_Name.m_pCleanse_name = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", name, Spell_name.m_cleanse);
	
	CSpell_Name.m_pExhaust_name = new CText(*CSpell_Name.m_pCleanse_name); 
	CSpell_Name.m_pExhaust_name->m_sInfo = Spell_name.m_Exhaust;

	CSpell_Name.m_pGhost_name = new CText(*CSpell_Name.m_pCleanse_name);
	CSpell_Name.m_pGhost_name->m_sInfo = Spell_name.m_Ghost;

	//Spell Info setting
	CSpell_Info.m_pCleanse = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"arial", info, Spell_list.m_cleanse);
}

void CTextMgr::Render(UI_SPELLTYPE type)
{
	switch (type)
	{
	case cleanse:
		CSpell_Name.m_pCleanse_name->m_pFont->DrawTextA
		(NULL, 
			CSpell_Name.m_pCleanse_name->m_sInfo.c_str(), 
			CSpell_Name.m_pCleanse_name->m_sInfo.length(), 
			&CSpell_Name.m_pCleanse_name->m_Rect, 
			DT_CENTER | DT_NOCLIP, 
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CSpell_Info.m_pCleanse->m_pFont->DrawTextA
		(
			NULL, 
			CSpell_Info.m_pCleanse->m_sInfo.c_str(), 
			CSpell_Info.m_pCleanse->m_sInfo.length(), 
			&CSpell_Info.m_pCleanse->m_Rect,
			DT_CENTER | DT_NOCLIP, 
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Exhaust:
		
		break;
	case Flash:
		
		break;
	case Ghost:
		
		break;
	case Heal:
		
		break;
	case Smite:
		
		break;
	case Teleport:
		
		break;
	case Ignite:
		
		break;
	case Barrier:
		
		break;
	default:
		break;
	}
}

void CTextMgr::Render_time()
{
	//RECT rect;
	//SetRect(&rect, 0, 20, 1000, 50);
	//m_pAlarm->DrawTextA(NULL, string("챔피언을 선택하세요.").c_str(), string("챔피언을 선택하세요").length(), &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	//RECT rec;
	//SetRect(&rec, 0, 70, 1000, 120);

	//MAXTIME -= GetTime();
	//if (MAXTIME < 0) MAXTIME = 0;
	//m_sTime = to_string((int)MAXTIME);
	//m_pTimeFont->DrawTextA(NULL, m_sTime.c_str(), m_sTime.length(), &rec, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void CTextMgr::LoadingNoticeRender()
{
	//RECT rc;
	//SetRect(&rc, 0, 350, 1000, 380);
	//m_pNotice->DrawTextA(
	//	NULL,
	//	m_sNotice.c_str(),
	//	m_sNotice.length(),
	//	&rc,
	//	DT_CENTER | DT_NOCLIP,
	//	D3DCOLOR_XRGB(0, 0, 0));
}
