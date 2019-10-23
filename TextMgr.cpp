#include "BaseInclude.h"
#include "TextMgr.h"
#include "Text.h"


CTextMgr::CTextMgr() : m_vpos(0, 0, 0)
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
	//m_pAlarm->DrawTextA(NULL, string("è�Ǿ��� �����ϼ���.").c_str(), string("è�Ǿ��� �����ϼ���").length(), &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

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
