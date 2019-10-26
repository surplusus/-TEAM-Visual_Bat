#pragma once
#include "Champion.h"
class CUdyr : public CChampion
{
public:
	CUdyr();
	virtual ~CUdyr();
private:
	bool				m_bRunning;
	bool				m_bTurning;
	bool				m_bDirty;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

	virtual void	ChangeAniSetByState() override;
private:
	void MouseControl();
	void QWERControl();
	bool TurnSlowly(const D3DXVECTOR3* destPos);
};

