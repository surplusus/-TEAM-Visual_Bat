#pragma once

using std::string;
class CText
{
public:
	CText() {}
	~CText();
	explicit CText(LPCSTR root, int height, int width, LPCTSTR fontname, RECT rc);

private:
	LPD3DXFONT							m_pFont;

public:
	RECT								m_Rect;


public:
	string								m_sInfo;
};

