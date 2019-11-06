#pragma once
#include "Gauge.h"
class CNexusGauge :
	public CGauge
{
public:
	CNexusGauge();
	~CNexusGauge();
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;


private:

	D3DXMATRIXA16		m_matWorld;
	vector<VTXTEX>											m_vecMultiVertex;
};

