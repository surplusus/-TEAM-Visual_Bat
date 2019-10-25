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
	void CreateMinions();
	void Initialize();
	void Progress();
	void Render();
	void Release();
};

