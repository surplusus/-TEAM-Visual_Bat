#pragma once
#include "Tower.h"

class CHeightMap;
class CNexus :
	public CTower
{
public:
	CNexus();
	~CNexus();
public:
private:
	CHeightMap*			m_pHeightMap = nullptr;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

};

