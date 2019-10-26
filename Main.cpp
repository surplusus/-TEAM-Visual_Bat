#include"BaseInclude.h"
#include"include.h"
#include"AppMain.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE Inst, LPSTR _lpstr, INT _in)
{
	AppMain app;
	_CrtSetBreakAlloc(239); // 56은 릭이 발생한 지점
	//_CrtSetBreakAlloc(282); // 56은 릭이 발생한 지점
	app.WinMainInit(hInst,Inst,_lpstr,_in);
	app.WinMainLoop();
	app.Release();
	//_CrtDumpMemoryLeaks(); // 메모리 릭 감지하는 함수
}