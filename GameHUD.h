#pragma once
#include"Image_Loader.h"
#include "Text.h"

class CTextMgr;

#define SkillCount 4
#define KeyCount 4

struct SkillList {
	CImage_Loader m_Skill[SkillCount];
};

struct KeyTextList {
	CText * m_pQKey;
	CText * m_pWKey;
	CText * m_pEKey;
	CText * m_pRKey;
};

enum KeyType
{
	Q = 0,
	W,
	E,
	R
};

class cGameHUD
{
	DECLARE_SINGLETON(cGameHUD)
public:
	cGameHUD();
	~cGameHUD();

public:
	void Initialize();
	void Progress();
	void Render();
	void Release();

private:
	map<string, CImage_Loader *> m_mapImage;
	map<string, SkillList*> m_MapSkill;

	bool m_isLButtonDown;

	KeyTextList st_key;

	bool m_isKeyDown[KeyCount];

	map<string, CTextMgr *> m_mapStatsMgr;
	STATUSINFO m_Stats;
	
public:
	void Progress_Minimap();

	void SetInfoChamp(STATUSINFO n_Stats) {
		m_Stats = n_Stats; 
	}
	void Initialize_Skill();
	void Render_Skill();
	void Release_Skill();

	void InitializeStats();
	void Update_StateText();

	void InitializeKey();
	void ProgressKey();
	void RenderKey();
	void ReleaseKey();

	//void CheckMouse();
	void CheckKeyDown();
};

