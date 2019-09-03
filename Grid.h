#pragma once
class CPyramid;
class CGrid
{
public:
	CGrid();
	~CGrid();
private:
	vector<CUSTOMVERTEX> m_vecVertex;
	vector<CPyramid*>		m_vecPyramid;
public:
	void SetUp(int nHalfTile = 15, float fInterval = 1.f);
	void Render();
};

