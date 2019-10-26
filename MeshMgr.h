#pragma once
struct stLoadProcess
{
	DWORD nSubSetLoaded;
	bool bCompleted ;
	string sConsoleOut ;
};
class CAnimationCtrl;
class CMesh;
class CMeshMgr
{
	DECLARE_SINGLETON(CMeshMgr);
private:
	CMeshMgr();
public:
	~CMeshMgr();
private:
	map<const TCHAR*, CMesh*> m_MapMesh;
	map<string, stLoadProcess> m_mapLoadInfo;
public:
	stLoadProcess& GetLoadInfo(string name) { return m_mapLoadInfo[name]; }

	void GetBoneMatrix(const TCHAR* pMeshKey
		, const CHAR* pBoneName
		, D3DXMATRIX* pOut);
public:
	HRESULT AddMesh(LPDIRECT3DDEVICE9 pDevice
		, const TCHAR* pPath
		, const TCHAR* pFileName
		, const TCHAR* pMeshKey
		, MESHTYPE MeshType);
	void InvalidateMesh(const TCHAR* pMeshKey, D3DXMATRIX* pMatWorld);

	HRESULT CloneMesh(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pMeshKey
		, CAnimationCtrl** ppAniCtrl);

	void Mesh_Render(LPDIRECT3DDEVICE9 pDevice, const TCHAR* pMeshKey);
	CMesh* GetMesh(const TCHAR* pMeshKey);
	void Release();
};
