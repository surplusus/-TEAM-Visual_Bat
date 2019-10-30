#pragma once
#include "Champion.h"

class CParticle;
//사용하는 Animation 이름 
//Attack1 -> 기본평타
//Attack2 ->비전쓰고난 후(e스킬후) 평타모션)
//IDLE1 -> 기본 가만히
//IDLE2,IDLE3 -> 가만히 있을때 변화되는 IDLE 시간변화에 따라 실행

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

	void SettingFrameAnimation();//현재 실행할 애니메이션 설정
	void KeyCheck();
	void SettingAnimationSort();//상태에 따른 애니메이션 순서를 정해준다.
	void InitAnimationState();
	
};

