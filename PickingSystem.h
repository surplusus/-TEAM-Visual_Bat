#pragma once
class CPickingSystem
{
public:
	CPickingSystem();
	~CPickingSystem();
private:
	
public:
	D3DXVECTOR3 GetPosition();// 피킹했던 위치값에 대한 반환
	bool IsPicking();// 피킹여부 검사

};

