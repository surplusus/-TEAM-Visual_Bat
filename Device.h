#pragma once
#include "Include.h"
class CDevice
{
	DECLARE_SINGLETON(CDevice)
private:
	// 장치의 성능 정보.
	LPDIRECT3D9				m_p3D;

	// 장치를 대표하는 객체
	LPDIRECT3DDEVICE9		m_pDevice;
	// 기본적인 Sprite & Font (용례 : FPS 시간을 나타낼때 / 오류창을 띄울때)
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;

public: //getter
	LPDIRECT3DDEVICE9 GetDevice(void) {
		return m_pDevice;
	}
	void GetTransform(_D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix);

public: // Setter
	void SetTexture(DWORD dwStage, LPDIRECT3DTEXTURE9 pTexture);
	void SetCubeTexture(DWORD dwStage, LPDIRECT3DCUBETEXTURE9  pTexture);
	void SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag);
	void SetTransform(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* pmatrix);
	void SetSamplerState(_D3DSAMPLERSTATETYPE SampOp, _D3DTEXTUREFILTERTYPE FilterType);
public:
	HRESULT InitDevice(HWND hWnd, WINMODE Mode, const UINT& iWinCX
		, const UINT& iWinCY);

	void Begin_Render(void);
	void End_Render(HWND hWnd);
public:
	void FontRender(const TCHAR* szFont, int iX, int iY, DWORD dwColor);
	void FontRender(const char* szFont, int iX, int iY, DWORD dwColor);
	void Release(void);
public:
	CDevice(void);
	~CDevice(void);
};

#define GET_DEVICE ((*(CDevice::GetInstance()))->GetDevice())