#pragma once

using std::string;
class CText
{
public:
	CText() {}
	~CText();
	explicit CText(const CText& text);
	explicit CText(LPCSTR root, int height, int width, LPCTSTR fontname, RECT rc, string sInfo);

public:
	LPD3DXFONT							m_pFont;

public:
	RECT								m_Rect;
	
public:
	string								m_sInfo;

public:
	int									m_iHeight;
	int									m_iWidth;
};

