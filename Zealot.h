#pragma once
#include "Champion.h"
class CHeightMap;
class CZealot :	public CChampion
{
public:
	CZealot();
	virtual ~CZealot();
private:
	bool				m_bRunning = false;
	bool				m_bTurning = false;
	bool				m_bDirty = false;
	CHeightMap*			m_pHeightMap = nullptr;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
private:
	void MouseControl();
	void QWERControl();
	void ArrowControl();
	bool TurnSlowly(const D3DXVECTOR3* destPos);
	
public:
	void SetHeightMap(CHeightMap* pHeightMap);
	float lerp(float p1, float p2, float d);
};

