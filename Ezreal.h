#pragma once
#include "Champion.h"
class CSkill;
class CEzreal :
	public CChampion
{
public:
	CEzreal();
	~CEzreal();
private:
	LPD3DXMESH m_pMesh;
public:
	virtual void	SetContantTable();
#pragma region Function
private:
	void WorldSetting();
	bool MouseCheck();
	void SetAngleFromPostion();
	bool Move_Chase(const D3DXVECTOR3 * pDestPoint, const float & fSpeed);
#pragma endregion

#pragma region StaticValue
private:
	static bool MapChecktThreadLoop(int number, const VTXTEX * vtx);
	static D3DXVECTOR3			g_MouseHitPoint;
	static std::atomic<bool>	g_bMouseHitPoint;
#pragma endregion
//test
private:
	list<CSkill*> m_ListQSkill;
	void AddSkill_Q();
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
public:
	// DeleteSkill();
};

