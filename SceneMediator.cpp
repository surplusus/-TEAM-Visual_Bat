#include "BaseInclude.h"
#include "SceneMediator.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "GuhyunScene.h"
#include <sstream>
#include <typeinfo>

CSceneMediator::CSceneMediator()
{
}


CSceneMediator::~CSceneMediator()
{
	m_mapStringInfo.clear();
	m_mapSceneMember.clear();
}

void CSceneMediator::SetSceneMember(string sceneName, CScene * member)
{
	stringstream ss;
	typeid(member);

}

void CSceneMediator::InsertStringInfo(string key, string info)
{
	m_mapStringInfo.insert(make_pair(key, info));
}

void CSceneMediator::CopyStringInfo(OUT map<string, string>* info)
{
	if (info)
		info->insert(m_mapStringInfo.begin(), m_mapStringInfo.end());
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
				CopyStringInfo(m_pLoadingScene->GetStringInfo());
			}
			else if (member == m_pGameScene) {

			}
			else if (member == m_pGuhyunScene) {

			}
		}	break;
	case PROGRESS:
		{
			if (member == m_pSelectScene) {

			}
			else if (member == m_pLoadingScene) {

			}
			else if (member == m_pGameScene) {

			}
			else if (member == m_pGuhyunScene) {

			}
		}	break;
	case RENDER:
		{
			if (member == m_pSelectScene) {

			}
			else if (member == m_pLoadingScene) {

			}
			else if (member == m_pGameScene) {

			}
			else if (member == m_pGuhyunScene) {

			}
		}	break;
	}

}
