#pragma once
class CTextMgr
{
	DECLARE_SINGLETON(CTextMgr);
public:
	CTextMgr();
	~CTextMgr();
private:
	LPD3DXFONT				m_pFont;
	LPD3DXFONT				m_pName;
	LPD3DXFONT				m_pAlarm;
	LPD3DXFONT				m_pTimeFont;
	LPD3DXFONT				m_pNotice;
public:
	void Initialize();
	void Create_Font();
	void Render(RECT rt, RECT rc, UI_SPELLTYPE type = SPELLTYPE_End);
	void Render_time();

	void LoadingNoticeRender();
private:
	string m_sTime;

	string m_cleanse;
	string m_Ghost;
	string m_heal;
	string m_Exhaust;
	string m_Flash;
	string m_Smite;
	string m_Teleport;
	string m_Ignite;
	string m_Barrier;



	vector<string> m_vecNotice;
	string m_sNotice;

	float MAXTIME;
};

