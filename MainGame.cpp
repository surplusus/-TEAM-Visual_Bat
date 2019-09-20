#include "BaseInclude.h"
#include "MainGame.h"
#include"SceneMgr.h"


CMainGame::CMainGame()
{
	ZeroMemory(m_szFps, sizeof(TCHAR) * 128);
	m_iCnt = 0;
	m_fTime = 0.f;
}


CMainGame::~CMainGame()
{
	Release();
}
HRESULT CMainGame::InitResuource()
{
	//=========== Add Buffer ===========//
	if (FAILED(Insert_Buffer(GetDevice(), L"CubeTexture", BUFFERTYPE_CUBE)))

	{
		ERR_MSG(g_hWnd, L"Buffer Create Failed");
		return E_FAIL;
	}
	//if (FAILED(Insert_Buffer(GetDevice(), L"RectTexture", BUFFERTYPE_RCTEX)))
	//
	//{
	//	ERR_MSG(g_hWnd, L"Buffer Create Failed");
	//	return E_FAIL;
	//}

	if (FAILED(Insert_Buffer(GetDevice(), L"Terrain", BUFFERTYPE_TERRAIN
		, VTXCNTX, VTXCNTZ, 1.f)))

	{
		ERR_MSG(g_hWnd, L"Buffer Create Failed");
		return E_FAIL;
	}
	return S_OK;
}


HRESULT CMainGame::Init()
{
	
	srand(unsigned(time(NULL)));
	//=========== Init Device ===========//
	if (FAILED(InitDevice(g_hWnd, WINMODE_WIN
		, WINSIZEX, WINSIZEY)))
	{
		ERR_MSG(g_hWnd,L"Device Initialize Failed");
		return E_FAIL;
	}
	//=========== Init Input Device ===========//
	if (FAILED(InitInputDevice(g_hInst, g_hWnd)))
	{
		ERR_MSG(g_hWnd,L"Input Device Initialize Failed");
		return E_FAIL;
	}
	if (FAILED(InitResuource()))			return E_FAIL;
	GET_SINGLE(CSceneMgr)->Initalize();

	InitTimeMgr();

	D3DXMatrixIdentity(&matFont);

	return S_OK;
}

void CMainGame::Render()
{
	++m_iCnt;

	m_fTime += GetTime();

	if (m_fTime > 1.f)
	{
		wsprintf(m_szFps, L"FPS : %d", m_iCnt);
		m_iCnt = 0;
		m_fTime = 0.f;
	}
	Begin_Render();
	GET_SINGLE(CSceneMgr)->Render();

	SetTransform(D3DTS_WORLD, &matFont);

	Font_Render(m_szFps, 0, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	End_Render(g_hWnd);

}

void CMainGame::Release()
{

	System_Release();
	GET_SINGLE(CSceneMgr)->Release();
}

void CMainGame::Progress()
{
	SetInputState();
	SetTimeMgr();

	GET_SINGLE(CSceneMgr)->Progress();
}

void CMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(CSceneMgr)->WndProc(hwnd,message,wParam,lParam);
}
