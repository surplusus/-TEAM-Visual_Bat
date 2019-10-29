#pragma once
#include "Gauge.h"
class CChampGague :
	public CGauge
{
public:
	CChampGague();
	~CChampGague();
public:
	virtual void Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
};

