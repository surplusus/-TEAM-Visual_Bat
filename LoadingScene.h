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
	stMeshInfo(string objName, string folderPath, string fileName)
		: m_ObjName(objName), m_FolderPath(folderPath), m_FileName(fileName) {}
};
using FuncLoading = function<void(void)>;

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
	LPD3DXSPRITE				m_pLoadingSprite;
	LPDIRECT3DTEXTURE9			m_pLoadingTexture;
	D3DXIMAGE_INFO				m_ImageInfo;
	CTextMgr*					m_pTextMgr;
	void Render_Loading();
private:
	CImage_Loader*				m_pBackGround;
	CSelectedPlayer*			m_pChampSelect;
	CSelectedSpells*				m_pSpell_1;
	CSelectedSpells*				m_pSpell_2;


	vector<D3DXVECTOR2>			m_vLinePoint;
	float						m_fLineLength;
	// << :: mediate
	map<string, string>			m_StringInfo;
public:
	map<string, string>* GetStringInfo() { return &m_StringInfo; }
	// >> :: mediate
	// << :: thread
	enum {BOXCOLLIDER = 0,LOADCHAMP = 1,LOADMAP, INROLLCHAMP, INROLLMAP, ENDSTAGE};
	int							m_nStage;
	vector<stMeshInfo*>			m_vpMeshInfo;
	
	vector<FuncLoading>			m_vfuncLoading;
	// 지울 함수들
	static void LoadingFunc1();
	static void LoadingFunc2();
	static void LoadingFunc3();
	static void LoadingFunc4();
	static void LoadingFunc5();

	bool LoadResourceByThread();
	bool RegisterOnObjMgr(stMeshInfo* info);
	static bool LoadStaticMeshByThread(stMeshInfo* info);
	static bool LoadDynamicMeshByThread(stMeshInfo* info);
	// >> :: thread
};

