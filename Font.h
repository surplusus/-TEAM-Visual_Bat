#pragma once
class cFont
{
public:
	cFont();
	~cFont();

public:
	void Initialize(int height, int width, LPCTSTR fontName);
	void Progress();
	void Render(string str);
	void Release();

private:
	LPD3DXFONT m_pFont;
};

