#pragma once
#include "ImageLoader.h"

struct SkillList {
	cImageLoader m_Skill[5];
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

	void WndProc(HWND hwnd, UINT message,
		WPARAM wParam, LPARAM lParam);

	void Render_Text();

private:
	map<string, cImageLoader *> m_mapImage;
	//cFont * m_Text;

	bool m_isLButtonDown;

	SkillList Ezreal;
};

