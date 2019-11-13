#pragma once
class CMinion;
class CHeightMap;
class CMinionMgr
{
	enum{T_MELEE, T_RANGE, T_CANNON, T_SUPER};
public:
	CMinionMgr();
	~CMinionMgr();
private:
	vector<CMinion*> m_vMinion;
	int m_iDelaySec = 10;
	//int m_iDelaySec = 590;
	int m_iCntSec = 0;
	bool m_bStartRender = false;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	void CreateMinions();
	void SetFirstPositions(CMinion* pMinion, const D3DXVECTOR3* pos);
	void SetHeightMap(CHeightMap** pHeightMap);
	CMinion* GetMinion(int nIndex);
};

