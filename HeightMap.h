#pragma once
class CHeightMap
{
public:
	CHeightMap();
	~CHeightMap();
public:
	void LoadData(string fileName);
	void Render();
	const VTXTEX* GetVtxInfo() { return m_Vertices; }
	LPD3DXMESH m_pMesh;
	DWORD	m_VtxNum;
	VTXTEX* m_Vertices;
};

