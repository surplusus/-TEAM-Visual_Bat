#pragma once
#include "Gauge.h"
class CMinionGauge :
	public CGauge
{
public:
	CMinionGauge();
	~CMinionGauge();
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void SetBlankGauge();
	void SetGaugeCell();

	vector<VTXTEX>											m_vecMultiVertex;
};

