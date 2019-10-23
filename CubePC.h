#pragma once
class cCubePC
{
	DECLARE_SINGLETON(cCubePC)
public:
	cCubePC();
	~cCubePC();

private:
	vector<CUSTOMVERTEX> m_vecVertex;

protected:
	D3DXMATRIXA16 m_matWorld;

	float m_fRotY;

	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3 m_vPosition;

public:
	void Initialize(); // setup
	void Progress(); // update
	void Render();

	D3DXVECTOR3 & GetPosition() { return m_vPosition; }
};

