#pragma once
class CMinion;

class CMinionMgr
{
	enum{T_MELEE, T_RANGE, T_CANNON, T_SUPER};
public:
	CMinionMgr();
	~CMinionMgr();
private:
	vector<CMinion*> m_vMinion;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	void CreateMinions();
	void SetFirstPositions(const D3DXVECTOR3* pos);
	void SetHeightMap(CHeightMap** pHeightMap);
};

