#pragma once
#include"Dynamic.h"
class CHP
	: public CDynamic
{
public:
	CHP();
	CHP(const D3DXMATRIX* pMatrix);
	~CHP();
private:
	const D3DXMATRIX* m_pMatParent;
	D3DXMATRIX m_matBill;

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

};

