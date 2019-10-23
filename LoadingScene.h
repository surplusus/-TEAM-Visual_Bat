#pragma once
#include "Scene.h"
#include "Text.h"
struct stMeshInfo
{
	bool m_bComplete = false;
	string m_ObjName;
	string m_FolderPath;
	string m_FileName;
	string m_ConsoleText;
	MESHTYPE m_MeshType;
	stMeshInfo(string objName, string folderPath, string fileName, MESHTYPE type)
		: m_ObjName(objName), m_FolderPath(folderPath), m_FileName(fileName), m_MeshType(type) {}
};

class CImage_Loader;
class CSelectedChampion;
class CUI;
class CLoadingScene :
	public CScene
{
public:
	CLoadingScene();
	~CLoadingScene();
	CLoadingScene(CUI * Champ) {}
public:
	HRESULT Initialize();
	void Progress() ;
	void Render() ;
	void Release() ;
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {}
private:
	// << :: Progress Bar
	LPD3DXSPRITE				m_pLoadingSprite;
	LPDIRECT3DTEXTURE9			m_pLoadingTexture;
	D3DXIMAGE_INFO				m_ImageInfo;
	void Render_Loading();
	// << :: Progress Bar
private:
	CImage_Loader*				m_pBackGround;
	CSelectedChampion*			m_pChampSelect;
	// << :: mediate
	map<string, string>			m_StringInfo;
public:
	map<string, string>* GetStringInfo() { return &m_StringInfo; }
	// >> :: mediate
	// << :: thread
	enum {BOXCOLLIDER = 0,LOADCHAMP = 1,LOADMAP, INROLLCHAMP, INROLLMAP, ENDSTAGE};
	int							m_nStage;
	vector<stMeshInfo*>			m_vpMeshInfo;
	map<string, stMeshInfo*>	m_mapMeshInfo;
	bool LoadResourceByThread();
	bool RegisterOnObjMgr(stMeshInfo* info);
	static bool LoadMeshByThread(stMeshInfo* info);

	//static bool LoadDynamicMeshByThread(stMeshInfo* info);
	// >> :: thread
};

