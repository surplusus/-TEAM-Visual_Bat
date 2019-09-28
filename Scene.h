#pragma once
#include"StateObj.h"
class CScene   :public CStateObj
{
public:
	CScene();
	virtual ~CScene();

public:	
	virtual HRESULT Initialize() =0;
	virtual void Progress()  =0;
	virtual void Render()    =0;
	virtual void Release()   =0;

    virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
};

