#pragma once
#include"Image_Loader.h"

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

	void Render_Text();

private:
	map<string, CImage_Loader *> m_mapImage;
	//cFont * m_Text;

	bool m_isLButtonDown;

	SkillList Ezreal;
	SkillList Ezreal_copy;

	float m_StartTime;
};

