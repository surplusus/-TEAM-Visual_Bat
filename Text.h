#pragma once
class CText
{
	DECLARE_SINGLETON(CText);
public:
	CText();
	~CText();
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

public:
	string GetCleanse() { return m_cleanse; }
	string GetGhost() { return m_Ghost; }
	string GetHeal() { return m_heal; }
	string GetExhaust() { return m_Exhaust; }
	string GetFlash() { return m_Flash; }
	string GetSmite() { return m_Smite; }
	string GetTeleport() { return m_Teleport; }
	string GetIgnite() { return m_Ignite; }
	string GetBairrer() { return m_Barrier; }

	string GetTimer() { return m_sTime; }
};

