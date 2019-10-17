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
	m_cleanse  = "챔피언에 걸린 모든 이동 불가와(제압 및 공중\n으로 띄우는 효과 제외) 소환사 주문에 의한 해\n로운 효과를 제거하고 새로 적용되는 이동 불가\n 효과들의 지속시간을 3초가 65 % 감소시킵니\n다.\n기본 재사용 대기 시간:210초";
	m_Ghost	   = "챔피언이 10초동안 유닛과 충돌하지 않게 되\n며 이동속도가 상승합니다. 이동 속도는 2초\n동안 점차 빨라져 레벨에 따라 최대 28~45%\n까지 상승합니다.\n기본 재사용 대기시간:180초";
	m_heal	   = "챔피언과 대상 아군의 체력을 90~345만큼(챔\n피언 레벨에 따라 변동) 회복 시키고 1초동안 \n이동속도가 30% 증가합니다. 최근 소환사 주\n문 회복의 영향을 받은 유닛의 경우 치유량이\n 절반만 적용됩니다.\n\n기본 재사용 대기시간:240초";
	m_Exhaust  = "적 챔피언을 지치게 만들어 2.5초동안 이동속\n도를 30% 낮추며, 이 동안 가하는 피해량을 \n40% 낮춥니다.\n\n기본 재사용 대기시간:210초";
	m_Flash	   = "커서 방향으로 챔피언이 짧은 거리를 순간이동\n 합니다.기본 재사용 대기시간:300초";
	m_Smite	   = "대상 에픽 및 대형/중형 몬스터, 혹은 적 미니\n언에게 390~1000(챔피언 레벨에 따라 변동)\n의 고정 피해를 입힙니다. 몬스터에게 사용하면\n 자신의 최대 체력에 비례해 체력을 회복합니다.\n\n기본 재사용 대기시간:15초";
	m_Teleport = "4초 동안 정신을 집중한 다음, 챔피언이 지정한\n 아군 구조물, 미니언, 혹은 와드로 순간이동합\n니다.\n기본 재사용 대기시간 360초";
	m_Ignite   = "적 챔피언을 불태워 5초동안 70~410의 고정\n 피해(챔피언 레벨에 따라 변동)를 입히고 모습\n을 드러내며 치료 효과를 감소시킵니다.\n\n기본 재사용 대기시간:180초";
	m_Barrier  = "2초동안 방어막으로 감싸 피해를\n 115~455(챔피언 레벨에 따라 변동)만큼 흡수\n합니다.\n기본 재사용 대기시간:180초";

	
	m_vecNotice.push_back(string("UI작업하면서 차암 힘들었습니다.\n피똥싸는줄 알았어요"));
	m_vecNotice.push_back(string("엔진이 얼마나 쉬울지 모르겠지만,\n 이것도 했는데 엔진을 못하면 게임회사에 취업 안될거란걸 알았어요."));
	m_vecNotice.push_back(string("4주간 다들 고생 많으셨습니다."));
	m_vecNotice.push_back(string("UI가 이렇게 어려울 줄이야"));
	m_vecNotice.push_back(string("다같이 취업됬으면 좋겠네요"));
	m_vecNotice.push_back(string("앞으로 더 열심히 살겁니다."));

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
	lstrcpy(fd.FaceName, L"굴림체");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pName);

	
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 10;
	fd.Width = 4;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"굴림체");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pFont);


	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 30;
	fd.Width = 20;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"굴림체");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pAlarm);

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 30;
	fd.Width = 20;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"굴림체");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pTimeFont);

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 20;
	fd.Width = 10;
	fd.Weight = FW_HEAVY;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	lstrcpy(fd.FaceName, L"굴림체");
	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pNotice);

	{
		/*AddFontResourceA("font/umberto.ttf"); // 시스템에 없으면 추가.
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
		m_pName->DrawTextA(NULL, string("정화").c_str(), string("정화").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_cleanse.c_str(), m_cleanse.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Exhaust:
		m_pName->DrawTextA(NULL, string("탈진").c_str(), string("탈진").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Exhaust.c_str(), m_Exhaust.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Flash:
		m_pName->DrawTextA(NULL, string("점멸").c_str(), string("점멸").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Flash.c_str(), m_Flash.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Ghost:
		m_pName->DrawTextA(NULL, string("유체화").c_str(), string("유체화").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Ghost.c_str(), m_Ghost.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Heal:
		m_pName->DrawTextA(NULL, string("힐").c_str(), string("힐").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_heal.c_str(), m_heal.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Smite:
		m_pName->DrawTextA(NULL, string("강타").c_str(), string("강타").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Smite.c_str(), m_Smite.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Teleport:
		m_pName->DrawTextA(NULL, string("순간이동").c_str(), string("순간이동").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Teleport.c_str(), m_Teleport.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Ignite:
		m_pName->DrawTextA(NULL, string("점화").c_str(), string("점화").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Ignite.c_str(), m_Ignite.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	case Barrier:
		m_pName->DrawTextA(NULL, string("방어막").c_str(), string("방어막").length(), &rt, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		m_pFont->DrawTextA(NULL, m_Barrier.c_str(), m_Barrier.length(), &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		break;
	default:
		break;
	}
	RECT rect;
	SetRect(&rect, 0, 20,1000, 50);
	m_pAlarm->DrawTextA(NULL, string("챔피언을 선택하세요.").c_str(), string("챔피언을 선택하세요").length(), &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));	
	
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
