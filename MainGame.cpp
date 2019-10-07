#include "BaseInclude.h"
#include "MainGame.h"
#include"SceneMgr.h"

float g_fDeltaTime = 0.f;

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
		ERR_MSG(g_hWnd, L"Buffer Create Failed");		return E_FAIL;
	}
	if (FAILED(Insert_Buffer(GetDevice(), L"RectTexture", BUFFERTYPE_RCTEX)))
	
	{
		ERR_MSG(g_hWnd, L"Buffer Create Failed");		return E_FAIL;
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
	GET_SINGLE(CSceneMgr)->Initialize();

	InitTimeMgr();
	D3DXMatrixIdentity(&matFont);

	return S_OK;
}


void CMainGame::Progress()
{
	SetTimeMgr();
	SetInputState();
	if (!UpdateTimeMgr())
		return;
	//cout << "deltatime : " << g_fDeltaTime << " sec_per_frame" << 1.0/61.0 << endl;
	GET_SINGLE(CSceneMgr)->Progress();
}

void CMainGame::Render()
{
	Begin_Render();
	MyDrawFPSByTimeMgr();

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

void CMainGame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(CSceneMgr)->WndProc(hwnd,message,wParam,lParam);
}
