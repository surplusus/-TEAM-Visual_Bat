#pragma once
#include "Dynamic.h"
class Minion : public CDynamic
{
public:
	Minion();
	Minion(string name, string filePath);
	virtual ~Minion();

	virtual HRESULT		Initialize();
	virtual void		Progress();
	virtual void		Render();
	virtual void		Release();
private:
	TCHAR* m_sName;
	int num;
};

