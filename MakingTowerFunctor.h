#pragma once
#include "LoadingFunctorBase.h"

class CMakingTowerFunctor :	public CLoadingFunctorBase
{
public:
	CMakingTowerFunctor();
	virtual ~CMakingTowerFunctor();
	bool operator() ();
private:
	int								m_iFuncSize;
	int								m_iFuncIdx;
	queue<function<bool(void)>>		m_queFunc;
	vector<class CTurret*>			m_vTurret;
	class CInhibitor*				m_pInhibitor;
	class CNexus*					m_pNexus;
public:
	bool FuncLoadTurret();
	bool FuncLoadInhibitor();
	bool FuncLoadNexus();
};

