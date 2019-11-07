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
	float													m_MAXHP; // 최대 체력
	float													m_MAXMP;
	D3DXVECTOR3												m_vPosition;
	
	LPDIRECT3DTEXTURE9										m_pBlank;
	LPDIRECT3DTEXTURE9										m_pCell;

public:
	void SetPosition(D3DXVECTOR3 position) { m_vPosition = position; }
	void SetWorld(D3DXMATRIX World) { m_matWorld = World; }

protected:
	void SetBillBoard();
	void SetLight();
	float														m_fDmg; // 체력 게이지 크기
	float														m_CurrentHP; // 현재 체력
	float														m_rest; // 남은 체력
	D3DXMATRIX m_matBillBoard;
public:
	void SetMaxHP(float MAXHP) { m_MAXHP = MAXHP; }
	void SufferDmg(float CurrentHP) { m_CurrentHP = CurrentHP; }

protected:
	void RenderBlankGauge(vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale);
	void RenderCellGauge (vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale);

private:
	D3DXMATRIX						m_matWorld;
};
