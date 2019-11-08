#pragma once
class CImage_Loader;
class CGauge
{
public:
	CGauge();
	virtual ~CGauge();
public:
	virtual void Initialize() = 0;
	virtual void Progress()	  = 0;
	virtual void Render()	  = 0;
	virtual void Release()	  = 0;

protected:
	float													m_MAXHP; // �ִ� ü��
	float													m_MAXMP;
	
	LPDIRECT3DTEXTURE9										m_pBlank;
	LPDIRECT3DTEXTURE9										m_pCell;

public:
	void SetInfo(INFO info) { m_stInfo = info; }
	
	void SetParentWorld(D3DXMATRIX World) { m_matParentWorld = World; }

protected:
	INFO	m_stInfo;
	void SetBillBoard();
	void SetLight();
	float														m_fDmg; // ü�� ������ ũ��
	float														m_CurrentHP; // ���� ü��
	float														m_rest; // ���� ü��
	D3DXMATRIX m_matBillBoard;
public:
	void SetMaxHP(float MAXHP) { m_MAXHP = MAXHP; }
	void SufferDmg(float CurrentHP) { m_CurrentHP = CurrentHP; }

protected:
	void RenderBlankGauge(vector<VTXTEX> vecMultiVertex, float y, D3DXVECTOR3 vScale);
	void RenderCellGauge (vector<VTXTEX> vecMultiVertex, float y, D3DXVECTOR3 vScale, float fDmg);

private:
	D3DXMATRIX						m_matParentWorld;
};
