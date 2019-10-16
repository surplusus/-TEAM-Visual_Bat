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
public:
	void Initialize();
	void Create_Font();
	void Render(UI_SPELLTYPE type= SPELLTYPE_End);
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
};

