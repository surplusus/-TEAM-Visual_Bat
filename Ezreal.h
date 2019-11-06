#pragma once
#include "Champion.h"

class CParticle;
//����ϴ� Animation �̸� 
//Attack1 -> �⺻��Ÿ
//Attack2 ->�������� ��(e��ų��) ��Ÿ���)
//IDLE1 -> �⺻ ������
//IDLE2,IDLE3 -> ������ ������ ��ȭ�Ǵ� IDLE �ð���ȭ�� ���� ����
class CGauge;
class ColiderComponent;
class CEzreal :
	public CChampion
{
	enum
	{
		SKILL_Q, SKILL_W, SKILL_E, SKILL_R,
	};
public:
	CEzreal();
	CEzreal(string AnimationState,bool bProgress) { 
		m_bProgress = bProgress;
		m_fAngle[ANGLE_X] = 0;
		m_fAngle[ANGLE_Y] = 0;
		m_fAngle[ANGLE_Z] = 0;		
		m_strAnimationState = AnimationState; 

		m_Champ_State.resize(CHAMPION_STATETYPE_END_ANIMSTATE);
		for (int i = 0; i <CHAMPION_STATETYPE_END_ANIMSTATE; i++)
		{
			m_Champ_State[i] = false;
		}


	}
	~CEzreal();
//�����
public:
	string m_ObjName;
private:
	LPD3DXMESH m_pMesh;
	ColiderComponent*  m_pColider;
	bool m_bDirty;
	list<ColiderComponent*> m_ColiderList;
	vector<SKILL_LEVEL> m_SkillLevel;
public:
	virtual void	SetContantTable();
#pragma region Function
private:
	void WorldSetting();
	bool MouseCheck();
	void SetAngleFromPostion();
#pragma endregion

#pragma region StaticValue
private:
	static D3DXVECTOR3			g_MouseHitPoint;
	static std::atomic<bool>	g_bMouseHitPoint;

#pragma endregion
//test
private:
	void AddSkill_Q();
	void AddBaseAttack();
public:
	virtual HRESULT Initialize() override;
	virtual void	Progress()   override;
	virtual void	Render()     override;
	virtual void	Release()    override;
public:
	virtual void		ChangeAniSetByState();
	//test
private:
	vector<bool>				m_Champ_State;
	queue<CHAMPION_STATETYPE>	m_AnimationQueue;
	CHAMPION_STATETYPE m_CurStateType;
	bool m_ChangeMotion;
	float m_fStartTime;
	float m_fEndTime;
	string m_strAnimationState;
	bool m_bProgress = true;

	void SettingFrameAnimation();//���� ������ �ִϸ��̼� ����
	void KeyCheck();
	void SettingAnimationSort();//���¿� ���� �ִϸ��̼� ������ �����ش�.
	void InitAnimationState();

	void InitUpdate();
private://test
	CObj*				m_pTargetObj;
	CGauge*				m_HpBar;
public:
	void PaticleCollisionEvent(COLLISIONEVENT* Evt);
	void OnFindPickingSphere(PICKSPHEREEVENT * evt);
	CHAMPION_STATETYPE SettingSpell1_Motion();
	CHAMPION_STATETYPE SettingAttack_Motion();
	CHAMPION_STATETYPE SettingRun_Motion();
private:
	void StatusInitalize();
};

