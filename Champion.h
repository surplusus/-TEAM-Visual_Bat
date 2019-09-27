#pragma once
#include "Dynamic.h"
class CChampion :
	public CDynamic
{
public:
	CChampion();
	~CChampion();

protected:
	D3DXVECTOR3		m_vMousePos;
	float			m_fCamDistance;
	TCHAR*			m_strChampionName;

public:
	void			KeyCheck();
	void			MouseCheck();
	void			SetCameraPos();
public:
	virtual void	SetContantTable();
public:
	virtual			HRESULT Initialize() PURE;
	virtual void	Progress() PURE;

	
	virtual void	Render()  PURE;
	virtual void	Release() PURE;
	void			Setup();
};

