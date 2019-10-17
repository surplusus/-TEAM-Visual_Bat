#pragma once
#include "Scene.h"

class GuhyunScene :
	public CScene
{
public:
	GuhyunScene();
	virtual ~GuhyunScene();
public:
	class CObjMgr* m_pObjMgr;
	virtual HRESULT Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
private:
	float		m_fSceneTime = 0.f;
private:
	HRESULT Setup();
	void Update();
	void SoundUpdate();
	bool Alarm(float getticktime, float endsec, int idx);
public:
	virtual void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	template<typename T, typename U>
	HRESULT ProcessLButtonPicking(T * obj, U * floor);
};

template<typename T, typename U>
inline HRESULT GuhyunScene::ProcessLButtonPicking(T * obj, U * floor)
{
	if (obj && floor) {
		if (GetMouseState().rgbButtons[1] & 0x80) {

			D3DXVECTOR3 pos = floor->GetPickingPoint();
			if (pos == D3DXVECTOR3(0.f, 0.f, 0.f)) {
				cout << "no face is picked" << endl;
				return S_FALSE;
			}
			obj->SetPickingPoint(&pos);
			return S_OK;
		}
	}
	
	cout << "not exist mouse picking obj or floor" << endl;
	return S_FALSE;
}
