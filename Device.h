#pragma once
#include "Include.h"
class CDevice
{
	DECLARE_SINGLETON(CDevice)
private:
	CDevice();
public:
	~CDevice();
private:
	LPDIRECT3D9					g_pD3D;
	LPDIRECT3DDEVICE9			g_pd3dDevice;
public:
	void						CleanUp();
	HRESULT						InitD3D(HWND hWnd);
	HRESULT						Render_Begin();
	HRESULT						Render_End();
	LPDIRECT3DDEVICE9			GetDevice() { return g_pd3dDevice; }
};

