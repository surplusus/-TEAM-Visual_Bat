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
	void SetBillBoard(D3DXMATRIXA16 * Matrix);

	vector<VTXTEX>									m_vecMultiVertex;

	void SetLight();
};
