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

void CSceneMediator::SetSceneMember(CScene * member)
{
	m_pSelectScene = dynamic_cast<CSelectScene*>(member);
	m_pLoadingScene = dynamic_cast<CLoadingScene*>(member);
	m_pGameScene = dynamic_cast<CGameScene*>(member);
	m_pGuhyunScene = dynamic_cast<GuhyunScene*>(member);
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
