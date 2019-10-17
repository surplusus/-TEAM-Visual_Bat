#pragma once
#include "Champion.h"
class CAmumu :
	public CChampion
{
public:
	CAmumu();
	~CAmumu();
private:
	LPD3DXMESH m_pMesh;
public:
	virtual void	SetContantTable();

private:
	void WorldSetting();
	bool MouseCheck();
	void SetAngleFromPostion();
	bool Move_Chase(const D3DXVECTOR3 * pDestPoint, const float & fSpeed);
	static bool MapChecktThreadLoop(int number, const VTXTEX * vtx);
	static bool					bPick;
	static D3DXVECTOR3			g_MouseHitPoint;
	static std::atomic<bool>	g_bHitFloor;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
};

