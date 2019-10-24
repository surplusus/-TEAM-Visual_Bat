#pragma once
class CText;
struct SPELL_LIST
{
	string m_cleanse;
	string m_Ghost;
	string m_heal;
	string m_Exhaust;
	string m_Flash;
	string m_Smite;
	string m_Teleport;
	string m_Ignite;
	string m_Barrier;
};

struct SPELL_NAME
{
	string m_cleanse;
	string m_Ghost;
	string m_heal;
	string m_Exhaust;
	string m_Flash;
	string m_Smite;
	string m_Teleport;
	string m_Ignite;
	string m_Barrier;
};

struct CTEXT_INFO
{
	CText*				m_pCleanse;
	CText*				m_pGhost;
	CText*				m_pHeal;
	CText*				m_pExhaust;
	CText*				m_pFlash;
	CText*				m_pSmite;
	CText*				m_pTeleport;
	CText*				m_pIgnite;
	CText*				m_pBarrier;
};

struct  CTEXT_NAME
{
	CText*				m_pCleanse_name;
	CText*				m_pGhost_name;
	CText*				m_pHeal_name;
	CText*				m_pExhaust_name;
	CText*				m_pFlash_name;
	CText*				m_pSmite_name;
	CText*				m_pTeleport_name;
	CText*				m_pIgnite_name;
	CText*				m_pBarrier_name;
};

class CTextMgr
{
	DECLARE_SINGLETON(CTextMgr);
public:
	CTextMgr();
	~CTextMgr();
public:
	void Initialize();
	void Render(UI_SPELLTYPE type = SPELLTYPE_End);
	void Render_time();

	void LoadingNoticeRender();
private:
	string m_sTime;

	SPELL_LIST			Spell_list;
	SPELL_NAME			Spell_name;
	CTEXT_INFO			CtSpell_Info;
	CTEXT_NAME			CtSpell_Name;

	CText*				m_pNotice;
	CText*				m_pTime;
	CText*				m_pAlarm;

	vector<string> m_vecNotice;
	string m_sNotice;

	float MAXTIME;

	D3DXVECTOR3		m_vpos;
public:
	void SetPosition(D3DXVECTOR3 pos) { m_vpos = pos; }
};

