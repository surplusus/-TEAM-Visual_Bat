#pragma once
#include "Champion.h"

class CParticle;
//����ϴ� Animation �̸� 
//Attack1 -> �⺻��Ÿ
//Attack2 ->�������� ��(e��ų��) ��Ÿ���)
//IDLE1 -> �⺻ ������
//IDLE2,IDLE3 -> ������ ������ ��ȭ�Ǵ� IDLE �ð���ȭ�� ���� ����

class ColiderComponent;
class CEzreal :
	public CChampion
{
public:
	CEzreal();
	CEzreal(string AnimationState,bool bProgress) { 
		m_bProgress = bProgress;
		m_fAngle[ANGLE_X] = 0;
		m_fAngle[ANGLE_Y] = 0;
		m_fAngle[ANGLE_Z] = 0;		
		m_strAnimationState = AnimationState; 
	}
	~CEzreal();
private:
	LPD3DXMESH m_pMesh;
	LPD3DXMESH m_pBoxMesh;
	ColiderComponent*  m_pColider;
	bool m_bDirty;
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
	static bool MapChecktThreadLoop(int number, const VTXTEX * vtx);
	static D3DXVECTOR3			g_MouseHitPoint;
	static std::atomic<bool>	g_bMouseHitPoint;

#pragma endregion
//test
private:
	list<CParticle*> m_ListQSkill;
	void AddSkill_Q();
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
	bool m_ChangeMotion;
	float m_fStartTime;
	float m_fEndTime;
	string m_strAnimationState;
	bool m_bProgress = true;

	void SettingFrameAnimation();//���� ������ �ִϸ��̼� ����
	void KeyCheck();
	void SettingAnimationSort();//���¿� ���� �ִϸ��̼� ������ �����ش�.
	void InitAnimationState();
	
};

