#include "BaseInclude.h"
#include "SceneMediator.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "GuhyunScene.h"
#include "InGameScene.h"
#include <sstream>
#include <typeinfo>

CSceneMediator::CSceneMediator()
{
}


CSceneMediator::~CSceneMediator()
{
	m_mapSceneMember.clear();
	m_mapVoidPointer.clear();
}

void CSceneMediator::SetSceneMember(CScene * member)
{
	if (dynamic_cast<CSelectScene*>(member) != nullptr) {
		m_pSelectScene = dynamic_cast<CSelectScene*>(member);
		return;
	}
	else if (dynamic_cast<CLoadingScene*>(member) != nullptr) {
		m_pLoadingScene = dynamic_cast<CLoadingScene*>(member);
		return;
	}
	else if (dynamic_cast<CGameScene*>(member) != nullptr) {
		m_pGameScene = dynamic_cast<CGameScene*>(member);
		return;
	}
	else if (dynamic_cast<GuhyunScene*>(member) != nullptr) {
		m_pGuhyunScene = dynamic_cast<GuhyunScene*>(member);
		return;
	}
	else if (dynamic_cast<CInGameScene*>(member) != nullptr) {
		m_pInGameScene = dynamic_cast<CInGameScene*>(member);
		return;
	}
}

void CSceneMediator::MediateInfo(MEDIATETYPE type, CScene * member)
{
	switch (type)
	{
	case INIT:
	{
		if (member == m_pSelectScene) {

		}
		else if (member == m_pLoadingScene) {
			SetSelectedChampInfo(m_stInFo);
		}
		else if (member == m_pGameScene) {

		}
		else if (member == m_pGuhyunScene) {

		}
		else if (member == m_pInGameScene) {

		}
	}	break;
	case SETTER:
	{
		if (member == m_pSelectScene) {

		}
		else if (member == m_pLoadingScene) {
			SetSelectedChampInfo(m_stInFo);
		}
		else if (member == m_pGameScene) {

		}
		else if (member == m_pGuhyunScene) {

		}
		else if (member == m_pInGameScene) {

		}
	}	break;
	case GETTER:
	{
		if (member == m_pSelectScene) {

		}
		else if (member == m_pLoadingScene) {

		}
		else if (member == m_pGameScene) {

		}
		else if (member == m_pGuhyunScene) {
			m_pGuhyunScene->GetMinionMgr(m_mapVoidPointer["MinionMgr"]);
		}
		else if (member == m_pInGameScene) {

		}
	}	break;
	default:
		break;
	}
}

void CSceneMediator::SetVoidPointerMap(string key, IN void ** pVoid)
{
	m_mapVoidPointer.insert(make_pair(key, pVoid));
}
