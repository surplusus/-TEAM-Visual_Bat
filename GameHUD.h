#pragma once

class cImageLoader;

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

private:
	map<string, cImageLoader *> m_mapImage;
	bool m_isLButtonDown;
};

