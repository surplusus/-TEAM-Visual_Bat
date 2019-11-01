#pragma once
#include "Tower.h"
class CTurret :
	public CTower
{
public:
	CTurret();
	virtual ~CTurret();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	bool Animation_Break();
};

