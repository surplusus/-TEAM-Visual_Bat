#include "BaseInclude.h"
#include "Text.h"
#include "TextList.h"

CText::~CText()
{
	SAFE_RELEASE(m_pFont);
}

CText::CText(LPCSTR root, int height, int width, LPCTSTR fontname, RECT rc)
	:m_Rect(rc)
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