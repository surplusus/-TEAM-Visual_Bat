#pragma once
class CMousePicker
{
public:
	CMousePicker();
	~CMousePicker();
private:
	RAY*		m_stRay;
	D3DXVECTOR3		m_HittingPoint;
public:
	bool GetHittingPoint(OUT D3DXVECTOR3* hittingpoint);
	RAY	 CalcPickingRay(int x, int y);
	void TransformRay(RAY* ray, D3DXMATRIXA16* matT);
	bool CheckIntersectWithSphere(SPHERE sphere);
	bool CheckIntersectWithTriangle(
		const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2);
	bool CheckIntersectWithTriangleAndGetPosition(
		IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, 
		OUT D3DXVECTOR3 * hitpoint);
};

