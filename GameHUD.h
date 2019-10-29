#pragma once

class CImage_Loader;
class CTextMgr;
class cFont;

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
	map<string, CImage_Loader *> m_mapImage;
	cFont * m_Text;

	CTextMgr*					m_TextMgr;

	bool m_isLButtonDown;
};

