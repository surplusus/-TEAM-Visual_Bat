#include"BaseInclude.h"
#include "Device.h"



CDevice::CDevice()
	: g_pD3D(NULL), g_pd3dDevice(NULL)
{

}


CDevice::~CDevice()
{
}

void CDevice::CleanUp()
{
	if (g_pd3dDevice != NULL) 	g_pd3dDevice->Release();	
	if (g_pD3D != NULL) 		g_pD3D->Release();	
}

HRESULT CDevice::InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		ERR_MSG(g_hWnd, L"디바이스 생성 실패");		return E_FAIL;
	}
	D3DCAPS9 stCaps;
	int nVertexProcessing;
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,		D3DDEVTYPE_HAL,
		g_hWnd,		nVertexProcessing, &stD3DPP, &g_pd3dDevice))) 
{
		ERR_MSG(g_hWnd, L"디바이스 생성 실패");		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDevice::Render_End()
{
	if (FAILED(g_pd3dDevice->EndScene()))
	{
		ERR_MSG(g_hWnd, L"랜더링 종료 실패");
		return E_FAIL;
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT CDevice::Render_Begin()
{
	if (NULL == g_pd3dDevice)
	{
		ERR_MSG(g_hWnd, L"디바이스가 존재하지 않습니다.");
		return E_FAIL;
	}
	g_pd3dDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 121, 40), 1.0f, 0);
	if (FAILED(g_pd3dDevice->BeginScene())) return E_FAIL;

}
