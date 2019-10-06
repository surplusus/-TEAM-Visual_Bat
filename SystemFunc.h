#ifndef _SYSTEMFUNC_H
#define _SYSTEMFUNC_H
#include"BaseInclude.h"
//=============== Device Library 14.05.12 By Burger ===============//
extern  HRESULT InitDevice(HWND hWnd, WINMODE Mode
	, const UINT& iWinCX
	, const UINT& iWinCY);
extern  void Begin_Render(void);
extern  void End_Render(HWND hWnd);
extern  void Font_Render(const TCHAR* szFont, int iX
	, int iY, DWORD dwColor);
extern  void Font_Render(const char* szFont, int iX
	, int iY, DWORD dwColor);

//=============== Device Library : Setter 14.05.12 By Burger ===============//
extern  void SetRenderState(_D3DRENDERSTATETYPE Type, DWORD dwFlag);
extern  void SetTransform(_D3DTRANSFORMSTATETYPE Type, const D3DXMATRIX* matrix);
extern  void SetTexture(DWORD dwStage, LPDIRECT3DTEXTURE9 pTexture);
extern  void SetCubeTexture(DWORD dwStage, LPDIRECT3DCUBETEXTURE9 pTexture);
extern  void SetSamplerState(_D3DSAMPLERSTATETYPE SampOp, _D3DTEXTUREFILTERTYPE FilterType);

//=============== Device Library : Getter 14.05.12 By Burger ===============//
extern  LPDIRECT3DDEVICE9 GetDevice(void);
extern  void GetTransform(_D3DTRANSFORMSTATETYPE Type, D3DXMATRIX* pMatrix);


//=============== Time Library 14.05.12 By Burger ===============//
extern  void InitTimeMgr(void);
extern  void SetTimeMgr(void);

extern  bool UpdateTimeMgr(void);

//=============== Time Library :: Getter 14.05.12 By Burger & 구현 ===============//
extern  float GetTime(void);
extern  void MyDrawFPSByTimeMgr(void);
extern  bool CheckPushKeyOneTime(BYTE byKey);
extern  bool CheckUpKeyOneTime(BYTE byKey);

//=============== Input Library 14.05.12 By Burger ===============//
extern  HRESULT InitInputDevice(HINSTANCE hInst, HWND hWnd);
extern  void SetInputState(void);
extern  bool CheckPushKey(BYTE byKey);
extern  bool CheckUpKey(BYTE byKey);
extern  DIMOUSESTATE MyGetMouseState(void);


//=============== MousePicking Extended By 지환 & 구현 ===============//
extern bool CheckPickingOnSphere(SPHERE sphere);
extern bool CheckPickingOnTriangle(IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, OUT D3DXVECTOR3 * hitpoint);

//=============== System Relase ======================//
extern  void System_Release(void);
#endif