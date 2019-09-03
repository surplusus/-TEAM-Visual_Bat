#pragma once
class CPyramid
{
public:
	CPyramid();
	~CPyramid();
private:
	vector<CUSTOMVERTEX> m_vecVertex;
	D3DXMATRIXA16		 m_matR;
public:
	void SetUp(D3DCOLOR c, D3DXMATRIXA16& mat);
	void Render();
};

