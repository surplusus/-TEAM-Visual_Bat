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
private:
	//void UpdateWorldMatrix(); Champion 클래스에 있음
public:
	void SetHeightMap(CHeightMap* pHeightMap);
	float lerp(float p1, float p2, float d);
};

