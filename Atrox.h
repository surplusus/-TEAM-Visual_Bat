#pragma once
#include"Champion.h"
class CAtrox :  public CChampion
{
public:
	CAtrox();
	~CAtrox();
private:
	LPD3DXMESH m_pMesh;
public:
	virtual void	SetContantTable();

private:
	void WorldSetting();
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;

};

