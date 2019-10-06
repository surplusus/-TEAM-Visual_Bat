#include "SystemFunc.h"
#include"BaseInclude.h"
#include "Device.h"
#include "TimeMgr.h"
#include "Input.h"

//=============== Device Func 14.05.12 By Burger ===============//
extern  HRESULT InitDevice(HWND hWnd, WINMODE Mode
	, const UINT& iWinCX
	, const UINT& iWinCY)
{
	return (*(CDevice::GetInstance()))->InitDevice(hWnd, Mode, iWinCX, iWinCY);
}

extern  void Begin_Render(void)
{
	(*(CDevice::GetInstance()))->Begin_Render();
}

extern  void End_Render(HWND hWnd)
{
	(*(CDevice::GetInstance()))->End_Render(hWnd);
}

extern  void SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag)
{
	(*(CDevice::GetInstance()))->SetRenderState(Type, dwFlag);
}
//샘플링 처리 설정// 쉐이더에 사용// 필터링처리 등
extern  void SetSamplerState(_D3DSAMPLERSTATETYPE SampOp, _D3DTEXTUREFILTERTYPE FilterType)
{
	(*(CDevice::GetInstance()))->SetSamplerState(SampOp, FilterType);
}

extern  void SetTransform(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* pmatrix)
{
	(*(CDevice::GetInstance()))->SetTransform(Type, pmatrix);
}

extern  void SetTexture(DWORD dwStage, LPDIRECT3DTEXTURE9 pTexture)
{
	(*(CDevice::GetInstance()))->SetTexture(dwStage, pTexture);
}

extern  void SetCubeTexture(DWORD dwStage, LPDIRECT3DCUBETEXTURE9 pTexture)
{
	(*(CDevice::GetInstance()))->SetCubeTexture(dwStage, pTexture);
}

extern  void Font_Render(const TCHAR* szFont, int iX
	, int iY, DWORD dwColor)
{
	(*(CDevice::GetInstance()))->FontRender(szFont, iX, iY, dwColor);
}

extern  void Font_Render(const char* szFont, int iX
	, int iY, DWORD dwColor)
{
	(*(CDevice::GetInstance()))->FontRender(szFont, iX, iY, dwColor);
}

//=============== Device Library : Getter 14.05.12 By Burger ===============//
extern  LPDIRECT3DDEVICE9 GetDevice(void)
{
	return (*(CDevice::GetInstance()))->GetDevice();
}

extern  void GetTransform(_D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix)
{
	(*(CDevice::GetInstance()))->GetTransform(Type, pMatrix);
}


//=============== Time Library 14.05.12 By Burger ===============//
extern  void InitTimeMgr(void)
{
	(*(CTimeMgr::GetInstance()))->InitTimeMgr();
}
extern  void SetTimeMgr(void)
{
	(*(CTimeMgr::GetInstance()))->SetTime();
}

bool UpdateTimeMgr(void)
{
	bool result = (*(CTimeMgr::GetInstance()))->UpdateTimeMgr();
	g_fDeltaTime = (*(CTimeMgr::GetInstance()))->GetSystemDeltaTime();
	return result;
}

//=============== Time Library :: Getter 14.05.12 By Burger ===============//
extern  float GetTime(void)
{
	return (*(CTimeMgr::GetInstance()))->GetTime();
}

void MyDrawFPSByTimeMgr(void)
{
	RECT rt;
	SetRect(&rt, 0, 5, 0, 0);
	string time = "FPS : " + std::to_string(GET_SINGLE(CTimeMgr)->GetFPSTime());
	Font_Render(time.c_str(), 2, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
}

bool CheckPushKeyOneTime(BYTE byKey)
{
	SHORT key = GetAsyncKeyState(byKey);
	static bool isPushed = false;
	if ((key & 0x8000) == 0x8000 && isPushed == false) {
		isPushed = true;
		return true;
	}
	if (isPushed) {
		if ((key & 0x8001) == 0x0000)
			isPushed = false;
	}
	return false;
}

bool CheckUpKeyOneTime(BYTE byKey)
{
	SHORT key = GetAsyncKeyState(byKey);
	static bool isPushed = false;
	if ((key & 0x8000) == 0x8000 && isPushed == false) {
		isPushed = true;
	}
	if (isPushed) {
		if ((key & 0x8001) == 0x0000) {
			isPushed = false;
			return true;
		}
	}
	return false;
}

extern  HRESULT InitInputDevice(HINSTANCE hInst, HWND hWnd)
{
	return (*(CInput::GetInstance()))->InitInputDevice(hInst, hWnd);
}
extern  void SetInputState(void)
{
	(*(CInput::GetInstance()))->SetInputState();
}
extern  bool CheckPushKey(BYTE byKey)
{
	return 	((*(CInput::GetInstance()))->MyGetKeyState(byKey) & 0x80) ? true : false;
}

extern  bool CheckUpKey(BYTE byKey)
{
	return 	((*(CInput::GetInstance()))->MyGetKeyState(byKey) & 0x80) ? false : true;
}

extern  DIMOUSESTATE MyGetMouseState(void)
{
	return 	(*(CInput::GetInstance()))->MyGetMouseState();

}

extern bool CheckPickingOnSphere(SPHERE sphere)
{
	return (*(CInput::GetInstance()))->CheckPickingOnSphere(sphere);
}

extern bool CheckPickingOnTriangle(IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, OUT D3DXVECTOR3 * hitpoint)
{
	return (*(CInput::GetInstance()))->CheckPiningOnTriangleAndGetPosition(p0, p1, p2, hitpoint);
}

//=============== SystemDll Release 14.05.12 By Burger ===============//
extern  void System_Release(void)
{
	(*(CDevice::GetInstance()))->DestroyInstance();
	(*(CTimeMgr::GetInstance()))->DestroyInstance();
	(*(CInput::GetInstance()))->DestroyInstance();
}
