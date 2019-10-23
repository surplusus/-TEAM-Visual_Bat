#include "BaseInclude.h"
#include "Font.h"


 cFont::cFont()
	 :m_pFont(NULL)
{
}


cFont::~cFont()
{
}

void cFont::Initialize(int height, int width, LPCTSTR fontName)
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = height;
	fd.Width = width;
	fd.Weight = FW_MEDIUM;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;

	lstrcpy(fd.FaceName, fontName);

	D3DXCreateFontIndirect(GetDevice(), &fd, &m_pFont);
}

void cFont::Progress()
{
}

void cFont::Render(string str)
{

	RECT rc;
	SetRect(&rc, 100, 100, 101, 101);
	
	m_pFont->DrawTextA(
		NULL,
		str.c_str(),
		str.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0)
	);
}

void cFont::Release()
{
	SAFE_RELEASE(m_pFont);
}
