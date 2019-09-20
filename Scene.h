#pragma once
#include"StateObj.h"
class CScene :public CStateObj
{
public:
	CScene();
	~CScene();

public:	
	virtual HRESULT Initalize() =0;
	virtual void Progress()  =0;
	virtual void Render()    =0;
	virtual void Release()   =0;

    virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
};

