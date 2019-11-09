#pragma once
#include "LoadingFunctorBase.h"

class CLoadingFunctor : public CLoadingFunctorBase
{
public:
	CLoadingFunctor();
	virtual ~CLoadingFunctor();
	bool operator() ();
private:
	int								m_iFuncSize;
	int								m_iFuncIdx;
	queue<function<bool(void)>>		m_queFunc;
	string							m_SelectedChamp;
public:
	bool FuncDefaultMgrSetUp();
	bool FuncLoadMap();
	bool FuncLoadChamp();
	bool FuncLoadMinion();
};