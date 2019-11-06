#include "BaseInclude.h"
#include "TextMgr.h"
#include "Text.h"
#include "LoadingScene.h"
#include "SceneMgr.h"


/*
Initialize
: CText* AA = new CText(폰트 위치, 높이, 넓이, 폰트파일안에 내장된 폰트명, RECT값, 출력할 정보)

Render() <- 파라메터 있는건 스펠용이라 없는거 만들어 놓음
: AA->멤버 폰트->drawtexta호출 하면됨
*/


CTextMgr::CTextMgr()
	: m_vpos(0, 0, 0)
	, m_MAXTIME(80.0f)
	/*, m_fSec(0.0f)
	, m_fMin(0.0f)
	, m_nCount(0)
	, m_CS(NULL)
	, m_nKill(0)
	, m_nDeath(0)
	, m_nAsist(0)*/
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
	m_rcName = { (LONG)m_vpos.x + 45, (LONG)m_vpos.y / 2  - 30,	(LONG)m_vpos.x + 45, (LONG)m_vpos.y / 2 };
	m_rcInfo = { (LONG)m_vpos.x + 45, (LONG)m_vpos.y / 2,		(LONG)m_vpos.x + 45, (LONG)m_vpos.y / 2 };
	//Spell Name setting
	{
		CtSpell_Name.m_pCleanse_name = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"Beaufort for LOL", m_rcName, Spell_name.m_cleanse);

		CtSpell_Name.m_pExhaust_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pExhaust_name->m_sInfo = Spell_name.m_Exhaust;

		CtSpell_Name.m_pGhost_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pGhost_name->m_sInfo = Spell_name.m_Ghost;

		CtSpell_Name.m_pFlash_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pFlash_name->m_sInfo = Spell_name.m_Flash;

		CtSpell_Name.m_pGhost_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pGhost_name->m_sInfo = Spell_name.m_Ghost;

		CtSpell_Name.m_pHeal_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pHeal_name->m_sInfo = Spell_name.m_heal;

		CtSpell_Name.m_pSmite_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pSmite_name->m_sInfo = Spell_name.m_Smite;

		CtSpell_Name.m_pTeleport_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pTeleport_name->m_sInfo = Spell_name.m_Teleport;

		CtSpell_Name.m_pIgnite_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pIgnite_name->m_sInfo = Spell_name.m_Ignite;

		CtSpell_Name.m_pBarrier_name = new CText(*CtSpell_Name.m_pCleanse_name);
		CtSpell_Name.m_pBarrier_name->m_sInfo = Spell_name.m_Barrier;
	}

	//Spell Info setting
	{
		CtSpell_Info.m_pCleanse = new CText("Resource/Fonts/BeaufortforLOL-Bold.ttf", 10, 4, L"arial", m_rcInfo, Spell_list.m_cleanse);

		CtSpell_Info.m_pExhaust = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pExhaust->m_sInfo = Spell_list.m_Exhaust;

		CtSpell_Info.m_pFlash = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pFlash->m_sInfo = Spell_list.m_Flash;

		CtSpell_Info.m_pGhost = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pGhost->m_sInfo = Spell_list.m_Ghost;

		CtSpell_Info.m_pHeal = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pHeal->m_sInfo = Spell_list.m_heal;

		CtSpell_Info.m_pSmite = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pSmite->m_sInfo = Spell_list.m_Smite;

		CtSpell_Info.m_pTeleport = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pTeleport->m_sInfo = Spell_list.m_Teleport;

		CtSpell_Info.m_pIgnite = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pIgnite->m_sInfo = Spell_list.m_Ignite;

		CtSpell_Info.m_pBarrier = new CText(*CtSpell_Info.m_pCleanse);
		CtSpell_Info.m_pBarrier->m_sInfo = Spell_list.m_Barrier;
	}
	RECT alarm;
	SetRect(&alarm, WINSIZEX / 2, 50, WINSIZEX / 2, 50);

	RECT time;
	SetRect(&time, WINSIZEX / 4 - 15, 50, WINSIZEX / 4 - 15, 50);
	m_pAlarm =	new CText("Resource/choen/Fonts/DejaVuSans.ttf", 25, 15, L"Dejavu Sans", alarm, string("챔피언을 선택해 주세요"));
	m_pTime =	new CText(*m_pAlarm);
	m_pTime->m_Rect = time;
	m_pNotice = new CText(*m_pAlarm);
	m_pNotice->m_sInfo = m_sNotice;

	RECT rc;
	SetRect(&rc, 1000, 5, 1000, 10);
	
	/*m_pSec = new CText("Resource/choen/Fonts/DejaVuSans.ttf", 20, 5, L"Dejavu Sans", rc, string(""));
	
	m_pMin = new CText(*m_pSec);
	m_pMin->m_Rect = RECT{ m_pSec->m_Rect.left - 20, m_pSec->m_Rect.top, m_pSec->m_Rect.right - 20, m_pSec->m_Rect.bottom };

	m_TimeDivide = new CText(*m_pSec);
	m_TimeDivide->m_sInfo = string(" : ");
	m_TimeDivide->m_Rect = RECT{ m_pMin->m_Rect.left + 10, m_pMin->m_Rect.top, m_pMin->m_Rect.right + 10, m_pSec->m_Rect.bottom };*/
}

// >> jiyun's code

// Initialize_Text(값, Rect 왼쪽, Rect 위, Rect 오른쪽, Rect 아래)
void CTextMgr::Initialize_Text(float val, int xLeft, int yTop, int xRight, int yBottom)
{
	// jiyun
	RECT box;
	SetRect(&box, xLeft, yTop, xRight, yBottom);

	m_StateBox = new CText("Resource/choen/Fonts/DejaVuSans.ttf", 11, 6, L"DejavuSans", box, m_sState);
	m_StateBox->m_Rect = box;
	
	value = (int)val;
	m_sState = to_string(value);
	m_StateBox->m_sInfo = m_sState;
}

// Render() 로 하면 오류나서 지우고 새로 Render_Text()라는 함수를 만듦
void CTextMgr::Render_Text()
{
	m_StateBox->m_pFont->DrawTextA(
		NULL,
		m_StateBox->m_sInfo.c_str(),
		m_StateBox->m_sInfo.length(),
		&m_StateBox->m_Rect,
		DT_LEFT | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0)
	);
}
//<<

void CTextMgr::Render(UI_SPELLTYPE type)//UI Render << 2D(spell)
{
	switch (type)
	{
	case cleanse:
		CtSpell_Name.m_pCleanse_name->m_pFont->DrawTextA
		(NULL, 
			CtSpell_Name.m_pCleanse_name->m_sInfo.c_str(), 
			CtSpell_Name.m_pCleanse_name->m_sInfo.length(), 
			&CtSpell_Name.m_pCleanse_name->m_Rect, 
			DT_CENTER | DT_NOCLIP, 
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pCleanse->m_pFont->DrawTextA
		(
			NULL, 
			CtSpell_Info.m_pCleanse->m_sInfo.c_str(), 
			CtSpell_Info.m_pCleanse->m_sInfo.length(), 
			&CtSpell_Info.m_pCleanse->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Exhaust:
		CtSpell_Name.m_pExhaust_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pExhaust_name->m_sInfo.c_str(),
			CtSpell_Name.m_pExhaust_name->m_sInfo.length(),
			&CtSpell_Name.m_pExhaust_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pExhaust->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pExhaust->m_sInfo.c_str(),
			CtSpell_Info.m_pExhaust->m_sInfo.length(),
			&CtSpell_Info.m_pExhaust->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Flash:
		CtSpell_Name.m_pExhaust_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pExhaust_name->m_sInfo.c_str(),
			CtSpell_Name.m_pExhaust_name->m_sInfo.length(),
			&CtSpell_Name.m_pExhaust_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pExhaust->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pExhaust->m_sInfo.c_str(),
			CtSpell_Info.m_pExhaust->m_sInfo.length(),
			&CtSpell_Info.m_pExhaust->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Ghost:
		CtSpell_Name.m_pGhost_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pGhost_name->m_sInfo.c_str(),
			CtSpell_Name.m_pGhost_name->m_sInfo.length(),
			&CtSpell_Name.m_pGhost_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pGhost->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pGhost->m_sInfo.c_str(),
			CtSpell_Info.m_pGhost->m_sInfo.length(),
			&CtSpell_Info.m_pGhost->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Heal:
		CtSpell_Name.m_pHeal_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pHeal_name->m_sInfo.c_str(),
			CtSpell_Name.m_pHeal_name->m_sInfo.length(),
			&CtSpell_Name.m_pHeal_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pHeal->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pHeal->m_sInfo.c_str(),
			CtSpell_Info.m_pHeal->m_sInfo.length(),
			&CtSpell_Info.m_pHeal->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Smite:
		CtSpell_Name.m_pSmite_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pSmite_name->m_sInfo.c_str(),
			CtSpell_Name.m_pSmite_name->m_sInfo.length(),
			&CtSpell_Name.m_pSmite_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pSmite->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pSmite->m_sInfo.c_str(),
			CtSpell_Info.m_pSmite->m_sInfo.length(),
			&CtSpell_Info.m_pSmite->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Teleport:
		CtSpell_Name.m_pTeleport_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pTeleport_name->m_sInfo.c_str(),
			CtSpell_Name.m_pTeleport_name->m_sInfo.length(),
			&CtSpell_Name.m_pTeleport_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pTeleport->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pTeleport->m_sInfo.c_str(),
			CtSpell_Info.m_pTeleport->m_sInfo.length(),
			&CtSpell_Info.m_pTeleport->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Ignite:
		CtSpell_Name.m_pIgnite_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pIgnite_name->m_sInfo.c_str(),
			CtSpell_Name.m_pIgnite_name->m_sInfo.length(),
			&CtSpell_Name.m_pIgnite_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pIgnite->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pIgnite->m_sInfo.c_str(),
			CtSpell_Info.m_pIgnite->m_sInfo.length(),
			&CtSpell_Info.m_pIgnite->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	case Barrier:
		CtSpell_Name.m_pBarrier_name->m_pFont->DrawTextA(
			NULL,
			CtSpell_Name.m_pBarrier_name->m_sInfo.c_str(),
			CtSpell_Name.m_pBarrier_name->m_sInfo.length(),
			&CtSpell_Name.m_pBarrier_name->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		CtSpell_Info.m_pBarrier->m_pFont->DrawTextA(
			NULL,
			CtSpell_Info.m_pBarrier->m_sInfo.c_str(),
			CtSpell_Info.m_pBarrier->m_sInfo.length(),
			&CtSpell_Info.m_pBarrier->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
		break;
	default:
		break;
	}
}

void CTextMgr::Render_time(bool Reddy)
{
	if (!Reddy)
	{
		m_pAlarm->m_pFont->DrawTextA(
			NULL,
			m_pAlarm->m_sInfo.c_str(),
			m_pAlarm->m_sInfo.length(),
			&m_pAlarm->m_Rect,
			DT_CENTER | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 255)
		);
	}
	

	m_MAXTIME -= GetTime();
	if (m_MAXTIME < 0) m_MAXTIME = 0;
	m_pTime->m_sInfo = to_string((int)m_MAXTIME);
	

	m_pTime->m_pFont->DrawTextA(
		NULL, 
		m_pTime->m_sInfo.c_str(),
		m_pTime->m_sInfo.length(),
		&m_pTime->m_Rect, 
		DT_CENTER | DT_NOCLIP, 
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void CTextMgr::LoadingNoticeRender()
{
	RECT rc;
	SetRect(&rc, 0, 350, 1000, 380);
	m_pNotice->m_pFont->DrawTextA(
		NULL,
		m_sNotice.c_str(),
		m_sNotice.length(),
		&rc,
		DT_CENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(0, 0, 0));
}

void CTextMgr::Reelase()
{
	delete m_pNotice;
	delete m_pTime;
	delete m_pAlarm;

	delete CtSpell_Info.m_pCleanse	;
	delete CtSpell_Info.m_pExhaust	;
	delete CtSpell_Info.m_pBarrier	;
	delete CtSpell_Info.m_pFlash	;
	delete CtSpell_Info.m_pGhost	;
	delete CtSpell_Info.m_pHeal		;
	delete CtSpell_Info.m_pIgnite	;
	delete CtSpell_Info.m_pSmite	;
	delete CtSpell_Info.m_pTeleport ;

	m_pNotice					= NULL;
	m_pTime						= NULL;
	m_pAlarm					= NULL;

	CtSpell_Info.m_pCleanse		= NULL;
	CtSpell_Info.m_pExhaust		= NULL;
	CtSpell_Info.m_pBarrier		= NULL;
	CtSpell_Info.m_pFlash		= NULL;
	CtSpell_Info.m_pGhost		= NULL;
	CtSpell_Info.m_pHeal		= NULL;
	CtSpell_Info.m_pIgnite		= NULL;
	CtSpell_Info.m_pSmite		= NULL;
	CtSpell_Info.m_pTeleport	= NULL;

	//jiyun
	SAFE_DELETE(m_StateBox);
}

//void CTextMgr::Progress()
//{
//	//DeltaTime = 1/60 초
//	m_fSec += g_fDeltaTime;
//	if (m_fSec >= 60)
//	{
//		m_fSec = 0;
//		m_fMin++;
//	}
//}

//void CTextMgr::IngameTimer()
//{
//	m_pSec->m_sInfo = to_string((int)m_fSec);
//	m_pMin->m_sInfo = to_string((int)m_fMin);
//
//	m_pSec->m_pFont->DrawTextA(
//		NULL,
//		m_pSec->m_sInfo.c_str(),
//		m_pSec->m_sInfo.length(),
//		&m_pSec->m_Rect,
//		DT_CENTER | DT_NOCLIP,
//		D3DCOLOR_XRGB(255, 255, 255)
//	);
//
//	m_TimeDivide->m_pFont->DrawTextA(
//		NULL,
//		m_TimeDivide->m_sInfo.c_str(),
//		m_TimeDivide->m_sInfo.length(),
//		&m_TimeDivide->m_Rect,
//		DT_CENTER | DT_NOCLIP,
//		D3DCOLOR_XRGB(255, 255, 255)
//	);
//
//	m_pMin->m_pFont->DrawTextA(
//		NULL,
//		m_pMin->m_sInfo.c_str(),
//		m_pMin->m_sInfo.length(),
//		&m_pMin->m_Rect,
//		DT_CENTER | DT_NOCLIP,
//		D3DCOLOR_XRGB(255, 255, 255)
//	);
//}

//void CTextMgr::CS_Count()
//{
//	////m_nCount += count;
//	//string sCount = to_string(m_nCount);
//
//	//RECT rc;
//	//SetRect(&rc, 950, 5, 950, 10);
//	//m_CS = new CText("Resource/choen/Fonts/DejaVuSans.ttf", 20, 5, L"Dejavu Sans", rc, sCount);
//	//m_CS->m_pFont->DrawTextA(
//	//	NULL,
//	//	m_CS->m_sInfo.c_str(),
//	//	m_CS->m_sInfo.length(),
//	//	&m_CS->m_Rect,
//	//	DT_CENTER | DT_NOCLIP,
//	//	D3DCOLOR_XRGB(255, 255, 255)
//	//);
//}

//void CTextMgr::KDA_Count(int K, int D, int A)
//{
//	string sKill = to_string(m_nKill);
//	string sDeath = to_string(m_nDeath);
//	string sAsist = to_string(m_nAsist);
//	RECT rc;
//	SetRect(&rc, 900, 5, 900, 10);
//	m_Kill = new CText("Resource/choen/Fonts/DejaVuSans.ttf", 20, 5, L"Dejavu Sans", rc, sKill);
//	
//	m_Death = new CText(*m_Kill);
//	m_Death->m_sInfo = sDeath;
//
//	m_Asist = new CText(*m_Kill);
//	m_Asist->m_sInfo = sAsist;
//
//	m_Kill->m_pFont->DrawTextA(
//		NULL,
//		m_Kill->m_sInfo.c_str(),
//		m_Kill->m_sInfo.length(),
//		&m_Kill->m_Rect,
//		DT_CENTER | DT_NOCLIP,
//		D3DCOLOR_XRGB(255, 255, 255)
//	);
//}
