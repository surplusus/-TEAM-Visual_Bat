#pragma once
#include "Champion.h"
class CZealot :	public CChampion
{
public:
	CZealot();
	virtual ~CZealot();

private:
	float				m_fSize = 0.1f;
	bool				m_IsRunning = false;
	bool				m_bIsPicked = false;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
private:
	void UpdateWorldMatrix();
	void MouseControl();
	void WASDControl();
	bool TurnSlowly(const D3DXVECTOR3* destPos);
};

