#include "BaseInclude.h"
#include "Cursor.h"


CCursor::CCursor()
{
}


CCursor::~CCursor()
{
}

bool CCursor::InitCursor()
{
	LPDIRECT3DTEXTURE9 tex;
	if (FAILED(D3DXCreateTextureFromFile(GetDevice(), L"./Resource/Cursors/Hand1.tga", &tex)))
	{
		ERR_MSG(NULL, L"커서로드 실패");
		return E_FAIL;
	}

	m_MapCursorTexture.insert(make_pair(CURSORTYPE_INGAME, tex));

}

void CCursor::SetCursor(CURSORTYPE type)
{
	LPDIRECT3DSURFACE9 surfCursor;
	LPDIRECT3DTEXTURE9 pTex;
	string path = "";
	switch (type)
	{
	case CURSORTYPE_INGAME:
		pTex =m_MapCursorTexture[CURSORTYPE_INGAME];
		path = "./Resource/Cursors/Hand1.tga";
		
		break;
	}
	pTex->GetSurfaceLevel(0, &surfCursor);
	LoadBmp(path, surfCursor);
	GetDevice()->SetCursorProperties(0, 0, surfCursor);
	GetDevice()->ShowCursor(true);
	
}

IDirect3DSurface9* CCursor::LoadBmp(string pFileName, IDirect3DSurface9 * pSurface)
{
	D3DXIMAGE_INFO ImageInfo;
	HRESULT hr = D3DXGetImageInfoFromFileA(pFileName.c_str(), &ImageInfo);

	GetDevice()->CreateOffscreenPlainSurface(
		ImageInfo.Width	, ImageInfo.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pSurface, NULL);
	
	D3DXLoadSurfaceFromFileA(pSurface, NULL, NULL, pFileName.c_str(),NULL,D3DX_DEFAULT,0,NULL);
	return pSurface;
}
