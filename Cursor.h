#pragma once
class CCursor
{
public:
	enum CURSORTYPE
	{
		CURSORTYPE_INGAME,
	};
public:
	CCursor();
	~CCursor();
private:
	map<CURSORTYPE, LPDIRECT3DTEXTURE9> m_MapCursorTexture;
public:
	bool InitCursor();
	void SetCursor(CURSORTYPE type);
	IDirect3DSurface9* LoadBmp(string pFileName, IDirect3DSurface9* pSurface);
};

