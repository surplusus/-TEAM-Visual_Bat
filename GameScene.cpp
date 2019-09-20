#include "BaseInclude.h"
#include "GameScene.h"
#include "Grid.h"
#include "XFileUtil.h"
#include"ResourceFunc.h"
#include "CameraMgr.h"
#include"Factory.h"
#include"ObjMgr.h"
#include"Player.h"
#include"Terrian.h"
#include"CameraMgr.h"
GameScene::GameScene()
	:m_pGrid(NULL),m_pCube(NULL)
{
	m_pObjMgr = (GET_SINGLE(CObjMgr));
}


GameScene::~GameScene()
{
}

HRESULT GameScene::Initalize()
{
	if (FAILED(GET_SINGLE(CCameraMgr)->SetCamera(CAMMODE_DYNAMIC, D3DXVECTOR3(0.f, 50.f, -20.f)
		, D3DXVECTOR3(0.f, 20.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f)
		, D3DX_PI / 4.f, float(WINSIZEX) / WINSIZEY, 1.f, 1000.f)))
		return E_FAIL;

	if (Setup())
		return E_FAIL;

	//if (FAILED(AddMesh(GetDevice(), L"./Mesh/Dynamic/Sylva/",L"Sylva.X",L"amumu",MESHTYPE_DYNAMIC)))
	//{
	//	ERR_MSG(g_hWnd, L"Sylva Load Failed"); 
	//	return E_FAIL;
	//}

	if (FAILED(AddMesh(GetDevice(), L"./Resource/Aatrox/", L"Atrax.x", L"amumu", MESHTYPE_DYNAMIC)))
	{
		ERR_MSG(g_hWnd, L"Sylva Load Failed");
		return E_FAIL;
	}
	if (FAILED(AddMesh(GetDevice(), L"./Resource/MapSommon/", L"SummonMap.x", L"Map", MESHTYPE_STATIC)))
	{
		ERR_MSG(g_hWnd, L"Summon Map Load Failed");
		return E_FAIL;
	}

	//if (FAILED(InsertTexture(GetDevice()
	//	, TEXTYPE_NORMAL
	//	, L"./Terrain/Multi%d.bmp"
	//	, L"Environment", L"Terrain", 3)))
	//{
	//	ERR_MSG(g_hWnd,L"Texture Create Failed");
	//	return E_FAIL;
	//}
	//Terrain관련 텍스쳐 추가
	if (FAILED(InsertTexture(GetDevice()
		, TEXTYPE_NORMAL
		, L"./Resource/MapSommon/grnd_terrain_%c.png"
		, L"Environment", L"Terrain", 25,INSERTTYPE_ENGLISH)))
	{
		ERR_MSG(g_hWnd, L"Texture Create Failed");
		return E_FAIL;
	}

	if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		return E_FAIL;

	if (FAILED(m_pObjMgr->AddObject(L"Player", CFactory<CObj, CPlayer>::CreateObject())))
	{
		return E_FAIL;
	}

}

void GameScene::Progress()
{
	GET_SINGLE(CCameraMgr)->Progress();
	m_pObjMgr->Progress();
	
}

void GameScene::Render()
{
	m_pObjMgr->Render();

}

void GameScene::Release()
{
	SAFE_DELETE(m_pGrid);
}

HRESULT GameScene::Setup()
{
	SetRenderState(D3DRS_LIGHTING, FALSE);
	return S_OK;

}

void GameScene::Update()
{
	m_pObjMgr->Progress();
	GET_SINGLE(CCameraMgr)->Progress();
}

void GameScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}
