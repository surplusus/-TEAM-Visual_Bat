#include"BaseInclude.h"
#include "AppMain.h"
#include "Device.h"
//EXTERN으로 정의된 윈도우 핸들러
HWND g_hWnd;
HINSTANCE g_hInst;

// 콘솔창 띄우기 (이 프로그램은 _MBCS 로 Main이 실행된다.)
#ifdef _DEBUG
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
//#endif
#endif // _DEBUG include 부분

AppMain::AppMain()
{
}


AppMain::~AppMain()
{
}
//메세지 프로시저
LRESULT WINAPI AppMain::MsgProc(HWND hWnd, UINT msg, WPARAM wParm, LPARAM lParam)
{
	m_MainGame.WndProc(hWnd, msg, wParm, lParam);
	switch (msg)
	{
	case WM_DESTROY:
		System_Release();
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		return 0;
	}
	return DefWindowProc(hWnd,msg,wParm,lParam);
}
//wINDOW 생성 및 초기화 건들지 말것!
void AppMain::WinMainInit(HINSTANCE hInst, HINSTANCE,LPSTR,INT)
{
	m_wc =
	{
		sizeof(WNDCLASSEX),CS_CLASSDC,(WNDPROC)MsgProc,0L,0L,
		GetModuleHandle(NULL),NULL,NULL,NULL,NULL,
		L"League of Legend",NULL
	};

	RegisterClassEx(&m_wc);
	RECT rc = {0,0, WINSIZEX,WINSIZEY};
	m_hWnd = CreateWindow(L"League of Legend", L"League of Legend 1.0", 
		WS_OVERLAPPEDWINDOW,100, 100, rc.right-rc.left, rc.bottom-rc.top,
		GetDesktopWindow(), NULL, m_wc.hInstance, NULL);
	g_hInst = hInst;
	g_hWnd = m_hWnd;
}
//메인 루프 건들지말 것!!
int AppMain::WinMainLoop()
{
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		MSG msg;
		msg.message = NULL;
		m_MainGame.Init();

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				m_MainGame.Progress();
				m_MainGame.Render();
			}
		}
	
	UnregisterClass(L"FrameWork", m_wc.hInstance);
	return 0;
}
//메모리해제
void AppMain::Release()
{

}




