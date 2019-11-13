#pragma once
#include "Champion.h"
#include "BehaviorUdyr.h"

class ColiderComponent;
class CParticle;
class CTurretGauge;
class CUdyr : public CChampion
{
#pragma region 무더기 친구들
	friend struct UdyrBT::UdyrDeath;
	friend struct UdyrBT::UdyrOnTarget;
	friend struct UdyrBT::UdyrHasCoord;
	friend struct UdyrBT::UdyrAttack;
	friend struct UdyrBT::UdyrTargeting;
	friend struct UdyrBT::UdyrSetCoord;
	friend struct UdyrBT::UdyrRun;
	friend struct UdyrBT::UdyrTurn;
	friend class UdyrBT::UdyrBTHandler;
	friend class UdyrBT::UdyrAccessor;
	friend class UdyrBT::WhenEnemyNear;
#pragma endregion
public:
	CUdyr();
	virtual ~CUdyr();
private:
	vector<string>		m_AniSetNameList;
	SPHERE*				m_sphereTarget;
	SPHERE*				m_sphereMe;
	CTurretGauge*		m_pGauge;
	// << : Behavior
	UdyrBT::UdyrBTHandler*	m_pBehavior;
	const UdyrBT::UdyrBTHandler*	GetBehaviorTree();
	int forsync = 0;
	// << : Collision
	ColiderComponent*  m_pCollider;
	list<ColiderComponent*> m_ColliderList;
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
	// Write on BlackBoard
	void			WriteOnBlackBoard(string sKey, bool bValue);
	void			WriteOnBlackBoard(string sKey, int iValue);
	void			WriteOnBlackBoard(string sKey, float fValue);
	void			WriteOnBlackBoard(string sKey, double llValue);
	void			WriteOnBlackBoard(string sKey, string sValue);
public:
	bool			IsEnemyNearInSphere(float fRadius);
	void			UpdatePickPointToEnemySphereCenter();
private:
	void			ChangeAniSetByKey(string key);
	void			SetUpAniSetNameList();
	void			DoOnMouseRButton();
	void			DoOnMouseLButton();
	void			QWERControl();
	void			UpdateColliderList();
	// Event Functions
	void			OperateOnFindPickingSphere(PICKSPHEREEVENT* evt);
	void			OperateOnPaticleCollisionEvent(COLLISIONEVENT* evt);
	void			OperateOnPhysicalAttackEvent(PHYSICALATTACKEVENT* evt);
	void			StopAttackWhenEnemyDie(OBJDIEEVENT* evt);
};

