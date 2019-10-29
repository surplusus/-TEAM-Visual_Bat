#pragma once
#include "Scene.h"
#include <functional>

struct stMeshInfo
{
	bool m_bComplete = false;
	string m_ObjName;
	string m_FolderPath;
	string m_FileName;
	string m_ConsoleText;
	MESHTYPE m_MeshType;
	stMeshInfo() {}
	stMeshInfo(string objName, string folderPath, string fileName, MESHTYPE type)
		: m_ObjName(objName), m_FolderPath(folderPath), m_FileName(fileName), m_MeshType(type) {}
};
using FuncLoading = function<bool(void)>;

class CImage_Loader;
class CSelectedPlayer;
class CSelectedSpells;
class CUI;
class CTextMgr;
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
	int							m_iMeshInfoSize;
	int							m_iProgressBar;
	void SetUp_ProgressBar();
	void Render_ProgressBar();
	// >> :: Progress Bar
private:
	CTextMgr*					m_pTextMgr;
	CImage_Loader*				m_pBackGround;
	CSelectedPlayer*			m_pChampSelect;
	CSelectedSpells*			m_pSpell_1;
	CSelectedSpells*			m_pSpell_2;


	// << :: mediate
	//map<string, string>			m_StringInfo;
public:
	//map<string, string>*		GetStringInfo() { return &m_StringInfo; }
	// >> :: mediate
	// << :: thread
	map<string, stMeshInfo>		m_mapMeshInfo;
	vector<FuncLoading>			m_vfuncLoading;
	vector<bool>				m_vbLoadingComplete;
	bool OperateFuncAddMeshByKey(string key);
	void OperateFuncAddObjectByKey(string key);
	// 로딩 함수들(vecter에 넣고 하나씩 꺼낸다)
	bool SetMeshInfoThruFile();
	bool FuncDefaultMgrSetUp();
	bool FuncLoadMap();
	bool FuncLoadChamp();
	bool FuncLoadMinion();
	void SetFuncLoading();
	// >> :: thread
};

