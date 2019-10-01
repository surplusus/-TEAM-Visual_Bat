#include"BaseInclude.h"
#include "Device.h"

CDevice::CDevice(void)
	: m_p3D(NULL)
	, m_pDevice(NULL)
	, m_pSprite(NULL)
	, m_pFont(NULL)
{
}

CDevice::~CDevice(void)
{
	Release();
}

HRESULT CDevice::InitDevice(HWND hWnd, WINMODE Mode, const UINT& iWinCX
	, const UINT& iWinCY)
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9			d3dCaps;
	ZeroMemory(&d3dCaps, sizeof(D3DCAPS9));

	// 장치의 정보를 가지고 온다.
	m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps);

	DWORD		Behavior = 0x00000000;

	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		Behavior |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		Behavior |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;

	d3dpp.hDeviceWindow = hWnd;

	d3dpp.Windowed = Mode;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd
		, Behavior, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(g_hWnd,L"Device Create Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(g_hWnd,L"Sprite Create Failed");
		return E_FAIL;
	}

	D3DXFONT_DESC			FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESC));

	FontInfo.Width = 11;
	FontInfo.Height = 21;
	FontInfo.Weight = FW_HEAVY;
	FontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(FontInfo.FaceName, L"궁서");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &FontInfo, &m_pFont)))
	{
		ERR_MSG(g_hWnd,L"Font Create Failed");
		return E_FAIL;
	}
	return S_OK;
}

void CDevice::SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag)
{
	m_pDevice->SetRenderState(Type, dwFlag);
}

void CDevice::SetSamplerState(_D3DSAMPLERSTATETYPE SampOp, _D3DTEXTUREFILTERTYPE FilterType)
{
	m_pDevice->SetSamplerState(0, SampOp, FilterType);

}

void CDevice::SetTransform(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* pmatrix)
{
	m_pDevice->SetTransform(Type, pmatrix);
}

void CDevice::SetTexture(DWORD dwStage, LPDIRECT3DTEXTURE9 pTexture)
{
	m_pDevice->SetTexture(dwStage, pTexture);

}

void CDevice::SetCubeTexture(DWORD dwStage, LPDIRECT3DCUBETEXTURE9  pTexture)
{
	m_pDevice->SetTexture(dwStage, pTexture);
}

void CDevice::Begin_Render(void)
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	m_pDevice->BeginScene();
}

void CDevice::End_Render(HWND hWnd)
{
	m_pDevice->EndScene();

	m_pDevice->Present(NULL, NULL, hWnd, NULL);
}

void CDevice::FontRender(const TCHAR* szFont, int iX, int iY, DWORD dwColor)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT		rcFont = { iX, iY };
	m_pFont->DrawTextW(m_pSprite, szFont, lstrlen(szFont)
		, &rcFont, DT_NOCLIP, dwColor);

	m_pSprite->End();
}

void CDevice::FontRender(const char* szFont, int iX, int iY, DWORD dwColor)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT		rcFont = { iX, iY };
	m_pFont->DrawTextA(m_pSprite, szFont, strlen(szFont), &rcFont, DT_NOCLIP, dwColor);
	m_pSprite->End();
}

void CDevice::GetTransform(_D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix)
{
	m_pDevice->GetTransform(Type, pMatrix);
}



void CDevice::Release(void)
{
	if(m_pFont!=NULL)
	m_pFont->Release();

	if(m_pSprite!=NULL)
	m_pSprite->Release();

	if(m_pDevice !=NULL)
	m_pDevice->Release();
	if(m_p3D !=NULL)
	m_p3D->Release();
}