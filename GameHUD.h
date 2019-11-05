#pragma once
#include"Image_Loader.h"

class CTextMgr;

struct SkillList {
	CImage_Loader m_Skill[5];
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

	void Progress_Minimap();

private:
	map<string, CImage_Loader *> m_mapImage;
	//cFont * m_Text;

	bool m_isLButtonDown;

	SkillList Ezreal;
	SkillList Ezreal_copy;

	map<string, CTextMgr *> m_mapTextMgr;
	INFO_CHAMP m_Stats;
};

