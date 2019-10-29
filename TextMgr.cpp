#include "BaseInclude.h"
#include "TextMgr.h"
#include "Text.h"
#include "LoadingScene.h"
#include "SceneMgr.h"


/*
Initialize
: CText* AA = new CText(��Ʈ ��ġ, ����, ����, ��Ʈ���Ͼȿ� ����� ��Ʈ��, RECT��, ����� ����)

Render() <- �Ķ���� �ִ°� ������̶� ���°� ����� ����
: AA->��� ��Ʈ->drawtextaȣ�� �ϸ��
*/


CTextMgr::CTextMgr() : m_vpos(0, 0, 0), m_MAXTIME(80.0f), m_fSec(0.0f), m_fMin(0.0f)
{
	{
		Spell_list.m_cleanse = "è�Ǿ� �ɸ� ��� �̵� �Ұ���(���� �� ����\n���� ���� ȿ�� ����) ��ȯ�� �ֹ��� ���� ��\n�ο� ȿ���� �����ϰ� ���� ����Ǵ� �̵� �Ұ�\n ȿ������ ���ӽð��� 3�ʰ� 65 % ���ҽ�ŵ��\n��.\n�⺻ ���� ��� �ð�:210��";
		Spell_list.m_Ghost = "è�Ǿ��� 10�ʵ��� ���ְ� �浹���� �ʰ� ��\n�� �̵��ӵ��� ����մϴ�. �̵� �ӵ��� 2��\n���� ���� ������ ������ ���� �ִ� 28~45%\n���� ����մϴ�.\n�⺻ ���� ���ð�:180��";
		Spell_list.m_heal = "è�Ǿ�� ��� �Ʊ��� ü���� 90~345��ŭ(è\n�Ǿ� ������ ���� ����) ȸ�� ��Ű�� 1�ʵ��� \n�̵��ӵ��� 30% �����մϴ�. �ֱ� ��ȯ�� ��\n�� ȸ���� ������ ���� ������ ��� ġ������\n ���ݸ� ����˴ϴ�.\n\n�⺻ ���� ���ð�:240��";
		Spell_list.m_Exhaust = "�� è�Ǿ��� ��ġ�� ����� 2.5�ʵ��� �̵���\n���� 30% ���߸�, �� ���� ���ϴ� ���ط��� \n40% ����ϴ�.\n\n�⺻ ���� ���ð�:210��";
		Spell_list.m_Flash = "Ŀ�� �������� è�Ǿ��� ª�� �Ÿ��� �����̵�\n �մϴ�.�⺻ ���� ���ð�:300��";
		Spell_list.m_Smite = "��� ���� �� ����/���� ����, Ȥ�� �� �̴�\n�𿡰� 390~1000(è�Ǿ� ������ ���� ����)\n�� ���� ���ظ� �����ϴ�. ���Ϳ��� ����ϸ�\n �ڽ��� �ִ� ü�¿� ����� ü���� ȸ���մϴ�.\n\n�⺻ ���� ���ð�:15��";
		Spell_list.m_Teleport = "4�� ���� ������ ������ ����, è�Ǿ��� ������\n �Ʊ� ������, �̴Ͼ�, Ȥ�� �͵�� �����̵���\n�ϴ�.\n�⺻ ���� ���ð� 360��";
		Spell_list.m_Ignite = "�� è�Ǿ��� ���¿� 5�ʵ��� 70~410�� ����\n ����(è�Ǿ� ������ ���� ����)�� ������ ���\n�� �巯���� ġ�� ȿ���� ���ҽ�ŵ�ϴ�.\n\n�⺻ ���� ���ð�:180��";
		Spell_list.m_Barrier = "2�ʵ��� ������ ���� ���ظ�\n 115~455(è�Ǿ� ������ ���� ����)��ŭ ���\n�մϴ�.\n�⺻ ���� ���ð�:180��";
	}

	{
		Spell_name.m_cleanse = "��ȭ";
		Spell_name.m_Teleport = "�����̵�";
		Spell_name.m_Exhaust = "Ż��";
		Spell_name.m_Ghost = "��üȭ";
		Spell_name.m_Flash = "����";
		Spell_name.m_Smite = "��Ÿ";
		Spell_name.m_Ignite = "��ȭ";
		Spell_name.m_Barrier = "��";
		Spell_name.m_heal = "ȸ��";
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
	m_pAlarm =	new CText("Resource/choen/Fonts/DejaVuSans.ttf", 25, 15, L"Dejavu Sans", alarm, string("è�Ǿ��� ������ �ּ���"));
	m_pTime =	new CText(*m_pAlarm);
	m_pTime->m_Rect = time;
	m_pNotice = new CText(*m_pAlarm);
	m_pNotice->m_sInfo = m_sNotice;

	RECT rc;
	SetRect(&rc, 500, 0, 500, 10);
	
	m_pSec = new CText("Resource/choen/Fonts/DejaVuSans.ttf", 20, 5, L"Dejavu Sans", rc, m_InGameSec);
	
	/*m_pMin = new CText(*m_pSec);
	m_pMin->m_sInfo = m_InGameMin;

	m_TimeDivide = new CText(*m_pSec);
	m_TimeDivide->m_sInfo = string(" : ");*/
}

void CTextMgr::Render() // << ������
{
}

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
	Rectangle(GetDC(g_hWnd), CtSpell_Name.m_pCleanse_name->m_Rect.left, CtSpell_Name.m_pCleanse_name->m_Rect.top, CtSpell_Name.m_pCleanse_name->m_Rect.right, CtSpell_Name.m_pCleanse_name->m_Rect.bottom);
	Rectangle(GetDC(g_hWnd), CtSpell_Info.m_pCleanse->m_Rect.left, CtSpell_Info.m_pCleanse->m_Rect.top, CtSpell_Info.m_pCleanse->m_Rect.right, CtSpell_Info.m_pCleanse->m_Rect.bottom);
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
}

void CTextMgr::Progress()
{
	//DeltaTime = 1/60 ��
	m_fSec += g_fDeltaTime;
	if (m_fSec >= 60)
	{
		m_fSec = 0;
		m_fMin++;
	}
}

void CTextMgr::IngameTimer()
{
	m_pSec->m_sInfo = to_string((int)m_fSec);
	m_InGameMin = to_string((int)m_fMin);

	m_pSec->m_pFont->DrawTextA(
		NULL,
		m_pSec->m_sInfo.c_str(),
		m_pSec->m_sInfo.length(),
		&m_pSec->m_Rect,
		DT_CENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	/*m_TimeDivide->m_pFont->DrawTextA(
		NULL,
		m_TimeDivide->m_sInfo.c_str(),
		m_TimeDivide->m_sInfo.length(),
		&m_TimeDivide->m_Rect,
		DT_CENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	m_pMin->m_pFont->DrawTextA(
		NULL,
		m_pMin->m_sInfo.c_str(),
		m_pMin->m_sInfo.length(),
		&m_pMin->m_Rect,
		DT_CENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255)
	);*/
}
