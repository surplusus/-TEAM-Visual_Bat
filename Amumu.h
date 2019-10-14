#pragma once
#include "Champion.h"

class CAmumu : public CChampion
{
public:
	CAmumu();
	virtual ~CAmumu();
private:
	LPD3DXMESH			m_pMesh;
	float				m_fSize;
	bool				m_IsRunning = false;
	bool				m_bIsPicked = false;
public:
	virtual	HRESULT		Initialize()	override;
	virtual void		Progress()		override;
	virtual void		Render()		override;
	virtual void		Release()		override;
private:
	void UpdateWorldMatrix();
	void MouseControl();
	void WASDControl();
public:
	void SetPickingPoint(D3DXVECTOR3* pickpoint);
};

