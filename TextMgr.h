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
public:
	CTextMgr();
	~CTextMgr();
public:
	void Initialize();

	void Render();

	void Render(UI_SPELLTYPE type = SPELLTYPE_End);
	void Render_time(bool Reddy);

	void LoadingNoticeRender();
private:
	//cheon
	string				m_sTime;
	SPELL_LIST			Spell_list;
	SPELL_NAME			Spell_name;
	CTEXT_INFO			CtSpell_Info;
	CTEXT_NAME			CtSpell_Name;

	CText*				m_pNotice;
	CText*				m_pTime;
	CText*				m_pAlarm;

	vector<string>		m_vecNotice;
	string				m_sNotice;

	float				m_MAXTIME;

	D3DXVECTOR3			m_vpos;

	RECT				m_rcName;
	RECT				m_rcInfo;
public:
	void SetPosition(D3DXVECTOR3 pos) { m_vpos = pos; }
	void SetMaxTime(float MAXTIME_) { m_MAXTIME = MAXTIME_; }
	void Reelase();
	int GetMaxTime() { return (int)m_MAXTIME; }
	//>> 필요한거 작업

public://InGame Timer
	void Progress();
	void IngameTimer();
private:
	float		m_fSec;
	float		m_fMin;

	CText*		m_pSec;
	CText*		m_pMin;
	CText*		m_TimeDivide;

public://InGame CS
	void CS_Count();
	int			m_nCount;
	CText*		m_CS;

public://InGame KDA
	void KDA_Count(int K, int D, int A);
private:
	int			m_nKill;
	int			m_nDeath;
	int			m_nAsist;
	CText*		m_Kill;
	CText*		m_Death;
	CText*		m_Asist;

};

