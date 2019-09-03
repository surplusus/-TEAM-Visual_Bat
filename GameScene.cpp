#include "BaseInclude.h"
#include "GameScene.h"
#include "Cube.h"
#include "TargetCam.h"
#include "Grid.h"
#include "XFileUtil.h"

GameScene::GameScene()
	:m_pGrid(NULL),m_pCamera(NULL),m_pCube(NULL)
{
	
}


GameScene::~GameScene()
{
}

void GameScene::Initalize()
{
	Setup();
}

void GameScene::Progress()
{
	Update();
}

void GameScene::Render()
{
	// d3 object render here
	if (m_pGrid)
		m_pGrid->Render();
	if (m_pCube)
		m_pCube->Render();

	m_XImg[0]->XFileRender();

}

void GameScene::Release()
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
}

void GameScene::Setup()
{
	m_pCube = new CCube;
	m_pCube->SetUp();

	m_pCamera = new CTargetCam;
	((CTargetCam*)m_pCamera)->Setup(&(m_pCube->GetPosition()));

	m_pGrid = new CGrid;
	m_pGrid->SetUp();
	GET_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	m_XImg.push_back((new CXFileUtil)->XFileLoad("./Iz/Iz.X"));
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
		PostMessage(NULL, WM_QUIT, NULL, NULL);
	if (m_pCube)
		m_pCube->Update();
	if (m_pCamera)
		m_pCamera->Update();
}

void GameScene::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
	{
		m_pCamera->WndProc(g_hWnd, message, wParam, lParam);
	}
}
