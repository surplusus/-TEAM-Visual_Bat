#pragma once
#include "Champion.h"
class CHeightMap;
class CZealot :	public CChampion
{
public:
	CZealot();
	virtual ~CZealot();
private:
	bool				m_IsRunning = false;
	bool				m_IsTurning = false;
	CHeightMap*			m_pHeightMap = nullptr;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
private:
	//void UpdateWorldMatrix(); Champion 클래스에 있음
	void MouseControl();
	void QWERControl();
	bool TurnSlowly(const D3DXVECTOR3* destPos);	// 수정해야됨
public:
	void SetHeightMap(CHeightMap* pHeightMap);
	float lerp(float p1, float p2, float d);
};

