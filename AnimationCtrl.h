#pragma once
class CAnimationCtrl
{
public:
	CAnimationCtrl();
	CAnimationCtrl(const CAnimationCtrl& Ani);
	~CAnimationCtrl();
private:
	LPD3DXANIMATIONCONTROLLER m_pAniCtrl;
	//���� �����ϰ� �ִ� �ִϸ��̼� Set
	//�ִϸ��̼� Set�̶� ? x���Ͽ��� �������ִ� ����, ���,�ٱ�,�ȱ���� ��ǵ��� �̾߱���
	//�� ��Ǵ� �� Set�̶�� �θ�, ���� ���� �װ��� ����� ������
	//x������ �װ��� �ִϸ��̼� set�� ���� ���̶�� �� �� ����
	
	DWORD m_dwCurrentTrack;	//���� Ʈ��
	DWORD m_dwNewTrack;		//���ο� ��
	DWORD m_dwCurrentAniSet;//���� �ִϸ��̼� set

	//x���� ������ �������ִ� �ִϸ��̼� Set����
	int		m_fDurationTime;
	int		m_numAnimationSets;
	string	m_sAnimationSets;
	bool	m_bIsBlending = false;
	float   m_fTimeDuringBlending = 0.f;
	const float	 m_fAniOverlapTime = 0.25f;
	double  m_dPeriodCurAnimSet = 0.0;
	vector<string> m_vAllAnimationName;
public:
	//�ִϸ��̼� ���� �Լ�
	// �ش� �Լ����� �ִϸ��̼��� �鸮�����ϴ� ��ü�� Progres�Լ����� �ݺ� ȣ��
	// Ư���ִϸ��̼��� �����ϱ� ���� �Լ�
	//���⿡�� �ε����� ��ü �ִϸ��̼��� � �κ��� ������ ������ �Ǵ��ϴ� ����
	void SetAnimationSet(int);
	void SetAnimationSet(string aniName);
	void BlendAnimationSet(string aniName);
	void FrameMove(const TCHAR* pMeshKey, float fTime);
	void DisplayAniSetNameOnConsole();
public:
	LPD3DXANIMATIONCONTROLLER* GetAniCtrl()
	{
		return &m_pAniCtrl;
	}
	CAnimationCtrl* Clone();
public:
	void Release();

};

