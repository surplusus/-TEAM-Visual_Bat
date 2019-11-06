#pragma once
#include "Tower.h"
class CInhibitor :
	public CTower
{
public:
	CInhibitor() {}
	explicit CInhibitor(D3DXVECTOR3 pos);
	virtual ~CInhibitor();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	bool Animation_Set();
	virtual void		ChangeAniSetByState() {};
public:
	void SetPosition(D3DXVECTOR3 position) { m_Info.vPos = position; }
};

