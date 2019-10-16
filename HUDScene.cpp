#include "BaseInclude.h"
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
	GET_SINGLE(cGameHUD)->Initialize();

	return S_OK;
}

void cHUDScene::Progress()
{

}

void cHUDScene::Render()
{
	GET_SINGLE(cGameHUD)->Render();
}

void cHUDScene::Release()
{
}

void cHUDScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(cGameHUD)->WndProc(hwnd, message, wParam, lParam);
}
