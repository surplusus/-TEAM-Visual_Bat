#include "BaseInclude.h"
#include "LoadingFunctor.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "ParticleMgr.h"

#include "Udyr.h"
#include "Ezreal.h"
#include "MinionMgr.h"
#include "Minion.h"
#include "Cursor.h"

CLoadingFunctor::CLoadingFunctor(string sFileName)
	: m_iFuncSize(0)
	, m_iFuncIdx(0)
	, m_sFileName(sFileName)
{
	{
		m_queFunc.push([this]() {return this->SetMeshInfoThruFile(m_sFileName); });
		m_queFunc.push([this]() {return this->FuncDefaultMgrSetUp(); });
		m_queFunc.push([this]() {return this->FuncLoadMap(); });
		m_queFunc.push([this]() {return this->FuncLoadChamp(); });
		m_queFunc.push([this]() {return this->FuncLoadMinion(); });
		m_mapMeshInfo.clear();
	}
	{	// SceneMediator�� functor���� ������ �־��ش�.
		m_SelectedChamp = "";
		m_SelectedChamp = GET_SINGLE(CSceneMgr)->GetSceneMediator()->Get_ST_ChampInfo().m_ChampName;
		if (m_SelectedChamp == "") {
			m_SelectedChamp = "Udyr";
			printf("SceneMeditor�� ChampName�� ���� Udyr�� Functor�� �־����ϴ�.\n");
		}
	}
}

CLoadingFunctor::~CLoadingFunctor()
{
}

bool CLoadingFunctor::operator()()
{
	using FUNC = function<bool(void)>;
	if (m_queFunc.empty())
		return false;
	FUNC fp = m_queFunc.front();
	bool re = fp();
	++m_iFuncIdx;
	m_queFunc.pop();
	return true;
}

bool CLoadingFunctor::FuncDefaultMgrSetUp()
{
	{	// Set up Sounds
		GET_SINGLE(SoundMgr)->SetUp();
		printf("sound set up\n");
	}
	{	// Create ColliderMgr & ParticleMgr
		GET_SINGLE(CParticleMgr)->Initalize();
		GET_SINGLE(CCollisionMgr)->Progress();
	}
	{	// Make Bound
		if (FAILED(AddBounding(GetDevice(), BOUNDTYPE_CUBE)))
		{
			ERR_MSG(g_hWnd, L"BoundingBox Load Failed");
		}
		printf("BoundingBox On!\n");
	}

	{	// Make Cursor
		CCursor* pCursor = new CCursor();
		pCursor->InitCursor();
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetVoidPointerMap("Cursor", reinterpret_cast<void**>(&pCursor));
		pCursor->SetCursor(CCursor::CURSORTYPE::CURSORTYPE_INGAME);
		printf("Make Hand Cursor\n");
	}
	return true;
}

bool CLoadingFunctor::FuncLoadMap()
{
	if (!OperateAddMeshByKey("Map")) {
		printf("�� �Ž� �ε� ����\n");
		return false;
	}
	
	if (!RegisterCloneObjectByKey("Map"))
		ERR_MSG(g_hWnd, L"Champ Register Error");
	return true;
}

bool CLoadingFunctor::FuncLoadChamp()
{
	
	if (!OperateAddMeshByKey(m_SelectedChamp)) {
		printf("è�Ǿ� �Ž� �ε� ����\n");
		return false;
	}

	if (!RegisterCloneObjectByKey(m_SelectedChamp))
		ERR_MSG(g_hWnd, L"Champ Register Error");

	//{	//Ezreal dummy
	//	if (!OperateAddMeshByKey("Ezreal")) {
	//		printf("Ezreal �Ž� �ε� ����\n");
	//		return false;
	//	}
	//	OperateAddObjectByKey("Ezreal");
	//}
	return true;
}

bool CLoadingFunctor::FuncLoadMinion()
{
	{	// �����丵 ���
		string key = "MeleeMinion";
		if (m_mapMeshInfo.find(key) == m_mapMeshInfo.end())
			return false;
		auto info = m_mapMeshInfo[key];

		// �̴Ͼ� �Ŵ��� ����
		CMinionMgr* pMinionMgr = new CMinionMgr;
		// �̴Ͼ� ����&�̸� �־��ְ�
		pMinionMgr->CreateMinions();
		// �Ŵ��� Mediator�� �����ϰ�
		GET_SINGLE(CSceneMgr)->GetSceneMediator()->SetVoidPointerMap("MinionMgr",
			reinterpret_cast<void**>(&pMinionMgr));

		HRESULT re = true;
		bool bSignFalse = false;
		re = AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), pMinionMgr->GetMinion(0)->GetMeshName(), info->m_MeshType);
		if (SUCCEEDED(re))
			printf("1 : %s\n", info->m_ConsoleText.c_str());
		else
			bSignFalse = true;
		if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), pMinionMgr->GetMinion(1)->GetMeshName(), info->m_MeshType)))
			if (SUCCEEDED(re))
				printf("2 : %s\n", info->m_ConsoleText.c_str());
			else
				bSignFalse = true;
		if (SUCCEEDED(AddMesh(GetDevice(), info->m_FolderPath.c_str(), info->m_FileName.c_str(), pMinionMgr->GetMinion(2)->GetMeshName(), info->m_MeshType)))
			if (SUCCEEDED(re))
				printf("3 : %s\n", info->m_ConsoleText.c_str());
			else
				bSignFalse = true;
		if (bSignFalse) {
			basic_string<TCHAR> sTCHAR(info->m_szObjName);
			string name(sTCHAR.begin(), sTCHAR.end());
			cout << name << " �Ž� �ε� ����\n";
			return false;
		}
	}


	printf("Minion Manager register �Ϸ�\n");

	return true;
}