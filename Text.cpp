#include "BaseInclude.h"
#include "Text.h"


CText::CText() : m_pFont(NULL), m_pName(NULL), m_pAlarm(NULL), m_pTimeFont(NULL), MAXTIME(80.0f), m_pNotice(NULL)
{
}


CText::~CText()
{
}

void CText::Initialize()
{
	m_cleanse  = "è�Ǿ� �ɸ� ��� �̵� �Ұ���(���� �� ����\n���� ���� ȿ�� ����) ��ȯ�� �ֹ��� ���� ��\n�ο� ȿ���� �����ϰ� ���� ����Ǵ� �̵� �Ұ�\n ȿ������ ���ӽð��� 3�ʰ� 65 % ���ҽ�ŵ��\n��.\n�⺻ ���� ��� �ð�:210��";
	m_Ghost	   = "è�Ǿ��� 10�ʵ��� ���ְ� �浹���� �ʰ� ��\n�� �̵��ӵ��� ����մϴ�. �̵� �ӵ��� 2��\n���� ���� ������ ������ ���� �ִ� 28~45%\n���� ����մϴ�.\n�⺻ ���� ���ð�:180��";
	m_heal	   = "è�Ǿ�� ��� �Ʊ��� ü���� 90~345��ŭ(è\n�Ǿ� ������ ���� ����) ȸ�� ��Ű�� 1�ʵ��� \n�̵��ӵ��� 30% �����մϴ�. �ֱ� ��ȯ�� ��\n�� ȸ���� ������ ���� ������ ��� ġ������\n ���ݸ� ����˴ϴ�.\n\n�⺻ ���� ���ð�:240��";
	m_Exhaust  = "�� è�Ǿ��� ��ġ�� ����� 2.5�ʵ��� �̵���\n���� 30% ���߸�, �� ���� ���ϴ� ���ط��� \n40% ����ϴ�.\n\n�⺻ ���� ���ð�:210��";
	m_Flash	   = "Ŀ�� �������� è�Ǿ��� ª�� �Ÿ��� �����̵�\n �մϴ�.�⺻ ���� ���ð�:300��";
	m_Smite	   = "��� ���� �� ����/���� ����, Ȥ�� �� �̴�\n�𿡰� 390~1000(è�Ǿ� ������ ���� ����)\n�� ���� ���ظ� �����ϴ�. ���Ϳ��� ����ϸ�\n �ڽ��� �ִ� ü�¿� ����� ü���� ȸ���մϴ�.\n\n�⺻ ���� ���ð�:15��";
	m_Teleport = "4�� ���� ������ ������ ����, è�Ǿ��� ������\n �Ʊ� ������, �̴Ͼ�, Ȥ�� �͵�� �����̵���\n�ϴ�.\n�⺻ ���� ���ð� 360��";
	m_Ignite   = "�� è�Ǿ��� ���¿� 5�ʵ��� 70~410�� ����\n ����(è�Ǿ� ������ ���� ����)�� ������ ���\n�� �巯���� ġ�� ȿ���� ���ҽ�ŵ�ϴ�.\n\n�⺻ ���� ���ð�:180��";
	m_Barrier  = "2�ʵ��� ������ ���� ���ظ�\n 115~455(è�Ǿ� ������ ���� ����)��ŭ ���\n�մϴ�.\n�⺻ ���� ���ð�:180��";

	
	m_vecNotice.push_back(string("UI�۾��ϸ鼭 ���� ��������ϴ�.\n�Ƕ˽δ��� �˾Ҿ��"));
	m_vecNotice.push_back(string("������ �󸶳� ������ �𸣰�����,\n �̰͵� �ߴµ� ������ ���ϸ� ����ȸ�翡 ��� �ȵɰŶ��� �˾Ҿ��."));
	m_vecNotice.push_back(string("4�ְ� �ٵ� ��� �����̽��ϴ�."));
	m_vecNotice.push_back(string("UI�� �̷��� ����� ���̾�"));
	m_vecNotice.push_back(string("�ٰ��� ��������� ���ڳ׿�"));
	m_vecNotice.push_back(string("������ �� ������ ��̴ϴ�."));

	m_sNotice = m_vecNotice[rand() % m_vecNotice.size()];

	Create_Font();
}

void CText::Create_Font()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 15;
	fd.Width = 8;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"����ü");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pName);

	
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 10;
	fd.Width = 4;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"����ü");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pFont);


	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 30;
	fd.Width = 20;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"����ü");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pAlarm);

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 30;
	fd.Width = 20;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"����ü");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pTimeFont);

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"����ü");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pNotice);

	{
		/*AddFontResourceA("font/umberto.ttf"); // �ý��ۿ� ������ �߰�.
		lstrcpy(fd.FaceName, L"umberto");*/
	}
}

void CText::Render(UI_SPELLTYPE type)
{
	RECT rc;
	SetRect(&rc, 1120, 400, 0, 0);
	RECT rt;
	SetRect(&rt, 1120, 370, 0, 0);
	switch (type)
	{
	case cleanse:
		m_pName->DrawTextA(NULL, string("��ȭ").c_str(), string("��ȭ").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_cleanse.c_str(), m_cleanse.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Exhaust:
		m_pName->DrawTextA(NULL, string("Ż��").c_str(), string("Ż��").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Exhaust.c_str(), m_Exhaust.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Flash:
		m_pName->DrawTextA(NULL, string("����").c_str(), string("����").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Flash.c_str(), m_Flash.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Ghost:
		m_pName->DrawTextA(NULL, string("��üȭ").c_str(), string("��üȭ").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Ghost.c_str(), m_Ghost.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Heal:
		m_pName->DrawTextA(NULL, string("��").c_str(), string("��").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_heal.c_str(), m_heal.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Smite:
		m_pName->DrawTextA(NULL, string("��Ÿ").c_str(), string("��Ÿ").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Smite.c_str(), m_Smite.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Teleport:
		m_pName->DrawTextA(NULL, string("�����̵�").c_str(), string("�����̵�").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Teleport.c_str(), m_Teleport.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Ignite:
		m_pName->DrawTextA(NULL, string("��ȭ").c_str(), string("��ȭ").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Ignite.c_str(), m_Ignite.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Barrier:
		m_pName->DrawTextA(NULL, string("��").c_str(), string("��").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Barrier.c_str(), m_Barrier.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	default:
		break;
	}
	RECT rect;
	SetRect(&rect, 0, 20,1000, 50);
	m_pAlarm->DrawTextA(NULL, string("è�Ǿ��� �����ϼ���.").c_str(), string("è�Ǿ��� �����ϼ���").length(), &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));	
	
	RECT rec;
	SetRect(&rec, 0, 70, 1000, 120);

	MAXTIME -= GetTime();
	if (MAXTIME < 0) MAXTIME = 0;
	cout << GetTime << " delta" << endl;
	m_sTime = to_string((int)MAXTIME);	
	m_pTimeFont->DrawTextA(NULL, m_sTime.c_str(), m_sTime.length(), &rec, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}

void CText::LoadingNoticeRender()
{
	RECT rc;
	SetRect(&rc, 0, 350, 1000, 380);
	m_pNotice->DrawTextA(
		NULL,
		m_sNotice.c_str(),
		m_sNotice.length(),
		&rc,
		DT_CENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(0, 0, 0));
}
