#pragma once
#include "Champion.h"
class CZealot :	public CChampion
{
public:
	CZealot();
	virtual ~CZealot();
private:
	bool				m_IsRunning = false;
	bool				m_IsTurning = false;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
private:
	//void UpdateWorldMatrix(); Champion Ŭ������ ����
	void MouseControl();
	void QWERControl();
	bool TurnSlowly(const D3DXVECTOR3* destPos);	// �����ؾߵ�

	float lerp(float p1, float p2, float d);
};

