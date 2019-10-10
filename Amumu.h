#pragma once
#include "Champion.h"

class CAmumu : public CChampion
{
public:
	CAmumu();
	virtual ~CAmumu();
private:
	float						m_fSize;
	bool						m_IsRunning = false;
	bool						m_bIsPicked = false;
private:
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

