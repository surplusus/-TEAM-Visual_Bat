#pragma once
#include "Gauge.h"

class CChampGauge :
	public CGauge
{
public:
	CChampGauge();
	~CChampGauge();
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
};

