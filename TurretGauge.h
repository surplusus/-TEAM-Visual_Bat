#pragma once
#include "Gauge.h"
class CTurretGauge :
	public CGauge
{
public:
	CTurretGauge();
	~CTurretGauge();
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;


private:

	D3DXMATRIXA16		m_matWorld;
	vector<VTXTEX>											m_vecMultiVertex;
};

