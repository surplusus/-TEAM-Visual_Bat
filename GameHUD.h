#pragma once
#include"Image_Loader.h"
#include "TextMgr.h"

struct SkillList {
	CImage_Loader m_Skill[5];
	CTextMgr m_pText;
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
	//cFont * m_Text;

	bool m_isLButtonDown;

	SkillList Ezreal;
	SkillList Ezreal_copy;

	map<string, CTextMgr *> m_mapTextMgr;
	STATUSINFO m_Stats;
	
public:
	void SetInfoChamp(STATUSINFO n_Stats) { m_Stats = n_Stats; }

	void Initialize_Stats();
	void Initialize_Ez_Skill();

	void Progress_Minimap();
	void CheckMouse();
};

