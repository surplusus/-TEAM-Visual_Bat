#pragma once
#include "Dynamic.h"
class CPlayer :
	public CDynamic
{
public:
	CPlayer();
	~CPlayer();

private:
	D3DXVECTOR3 m_vMousePos;
	float m_fCamDistance;
public:
	void KeyCheck();
	void MouseCheck();
	void SetCameraPos();
public:
	virtual void SetContantTable();
public:
	virtual HRESULT Initialize();
	virtual void Progress();


	virtual void Render();
	virtual void Release() ;

};

