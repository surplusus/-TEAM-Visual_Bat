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
	virtual void Progress(D3DXVECTOR3 vPos) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void SetBlankGauge();
	void SetGaugeCell();

	void RenderBlankGauge();
	void RenderCell();
};

