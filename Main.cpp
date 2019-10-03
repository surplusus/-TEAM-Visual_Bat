#include"BaseInclude.h"
#include"include.h"
#include"AppMain.h"

INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE Inst, LPSTR _lpstr, INT _in)
{
	AppMain app;

	app.WinMainInit(hInst,Inst,_lpstr,_in);
	app.WinMainLoop();
	app.Release();
}