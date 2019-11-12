#pragma once
#include "Tower.h"
class ColiderComponent;
class CParticle;
class CTurret :
	public CTower
{
public:
	CTurret() {}
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
	ColiderComponent * m_pTargetColider;
	CParticle * m_pTurretMissile;
private:
	LPDIRECT3DTEXTURE9				m_pTexture;
	vector<bool>					m_Champ_State;
	float							m_fStartTime;
	float							m_fEndTime;
	bool							m_bProgress;
	bool							m_bDirty;
	bool							m_ChangeMotion;
	string							m_strAnimationState;

private:
	virtual void					ChangeAniSetByState() {};
	void							AddAttackLaizer();
	void							PaticleCollisionEvent(COLLISIONEVENT* Evt);
	void							OnFindPickingSphere(PICKSPHEREEVENT * evt);
	void							InitAnimationState();
	void							SettingAnimationSort();//���¿� ���� �ִϸ��̼� ������ �����ش�.
	void							SettingFrameAnimation();//���� ������ �ִϸ��̼� ����
	CHAMPION_STATETYPE				SettingBreak_Motion();

public:
	void SetPosition(D3DXVECTOR3 position) { m_Info.vPos = position; }
	void UpdateCollisionList();
	void StatusInit();
};

