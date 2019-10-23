#include "BaseInclude.h"
#include "CameraMgr.h"

#include "HUDScene.h"
#include "GameHUD.h"

cHUDScene::cHUDScene()
{
}


cHUDScene::~cHUDScene()
{
}

HRESULT cHUDScene::Initialize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 50.f, -10.f)
		, D3DXVECTOR3(0.f, 10.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	GET_SINGLE(cGameHUD)->Initialize();

	return S_OK;
}

void cHUDScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	GET_SINGLE(cGameHUD)->Progress();
}

void cHUDScene::Render()
{
	GET_SINGLE(cGameHUD)->Render();
}

void cHUDScene::Release()
{
	GET_SINGLE(cGameHUD)->Release();
}

void cHUDScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(cGameHUD)->WndProc(hwnd, message, wParam, lParam);
}
