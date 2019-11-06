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
	float													m_MAXHP;
	float													m_MAXMP;
	D3DXVECTOR3												m_vPosition;
	
	LPDIRECT3DTEXTURE9										m_pBlank;
	LPDIRECT3DTEXTURE9										m_pCell;

public:
	void SetPosition(D3DXVECTOR3 position) { m_vPosition = position; }

protected:
	void SetBillBoard(D3DXMATRIXA16 * Matrix, float x, float y, float z);

	
	

	void SetLight();
	float m_fDmg;
	float m_fDeal;

public:
	void SetMaxHP(float HP) { m_MAXHP = HP; }
	void SufferDmg(float fDeal) { m_fDeal = fDeal; }

protected:
	void RenderBlankGauge(vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale);
	void RenderCellGauge (vector<VTXTEX> vecMultiVertex, D3DXVECTOR3 vPosition, D3DXVECTOR3 vScale);
};
