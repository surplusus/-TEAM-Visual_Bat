#pragma once
#include "Gauge.h"

class CChampGauge :
	public CGauge
{
public:
	CChampGauge();
	CChampGauge(D3DXVECTOR3 vPos);
	~CChampGauge();
public:
	virtual void Initialize() override;
	virtual void Progress(D3DXVECTOR3 vPos) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	D3DXMATRIX m_matBill;
	INFO m_Info;

private:
	void SetBlankGauge();
	void SetGaugeCell();

	void RenderBlankGauge();
	void RenderCellGauge();
private:
	
};

