#pragma once
#include "Tower.h"
class ColiderComponent;
class CParticle;
class CTurret :
	public CTower
{
public:
	CTurret(D3DXVECTOR3 pos);
	virtual ~CTurret();
public:
	virtual HRESULT	Initialize() override;
	virtual void Progress() override;
	virtual void Render() override;
	virtual void Release() override;
private:
	bool Animation_Break();
private:
	list<ColiderComponent*> m_ColiderList;
	float m_fStart_NewMissleTime;
	const float m_fEnd_NewMissleTime;
	const TCHAR* m_MeshName;
private:
	LPDIRECT3DTEXTURE9				m_pTexture;
	vector<bool>					m_Champ_State;
	float							m_fStartTime;
	float							m_fEndTime;
	bool							m_bProgress;
	bool							m_bDirty;
	bool							m_ChangeMotion;
	string							m_strAnimationState;
	CObj*							m_pTarget;
private:
	virtual void					ChangeAniSetByState() {};
	void							AddAttackLaizer();
	void							PaticleCollisionEvent(COLLISIONEVENT* Evt);
	void							OnFindPickingSphere(PICKSPHEREEVENT * evt);
	void							InitAnimationState();
	void							SettingAnimationSort();//상태에 따른 애니메이션 순서를 정해준다.
	void							SettingFrameAnimation();//현재 실행할 애니메이션 설정
	CHAMPION_STATETYPE				SettingBreak_Motion();
	void							AddLaizer(CObj* pTarget);

public:
	void SetPosition(D3DXVECTOR3 position) { m_Info.vPos = position; }
	void UpdateCollisionList();
	void StatusInit();
	void SetMeshName(const TCHAR* str) { m_MeshName = str; }
};

