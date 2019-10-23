#pragma once
class Minion;

class MinionMgr
{
public:
	MinionMgr();
	~MinionMgr();
private:
	vector<Minion*> m_vMinion;
public:
	void Initialize();
	void Progress();
	void Render();
};

