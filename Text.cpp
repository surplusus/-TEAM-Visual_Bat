#include "BaseInclude.h"
#include "Text.h"

CText::~CText()
{
	SAFE_DELETE(m_pFont);
	m_pFont = NULL;
}

CText::CText(const CText & text)
	:m_pFont(NULL)
{
	m_pFont = text.m_pFont;
	m_Rect = text.m_Rect;
	m_sInfo = text.m_sInfo;
	m_iHeight = text.m_iHeight;
	m_iWidth = text.m_iWidth;
}

CText::CText( LPCSTR root, int height, int width, LPCTSTR fontname, RECT rc, string sinfo)
	: m_Rect(rc)
	, m_sInfo(sinfo)
	, m_iHeight(height)
	, m_iWidth(width)
{
	m_pFont = NULL;

	D3DXFONT_DESC fd;

	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = height;
	fd.Width = width;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	{
		AddFontResourceA(root); // 시스템에 없으면 추가.
		lstrcpy(fd.FaceName, fontname);
	}

	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pFont);
}