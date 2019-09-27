#pragma once
class CMousePicker;
class  CInput
{
	DECLARE_SINGLETON(CInput)
private:
	LPDIRECTINPUT8			m_pInput;

private:
	LPDIRECTINPUTDEVICE8	m_pKeyBoard;
	BYTE					m_KeyState[256];

private:
	LPDIRECTINPUTDEVICE8	m_pMouse;
	DIMOUSESTATE			m_MouseState;
	// << : Picker
	CMousePicker*			m_MousePicker;
	D3DXVECTOR3*			m_PickingPoint;
public:
	HRESULT InitInputDevice(HINSTANCE hInst, HWND hWnd);
	void SetInputState(void);
	DIMOUSESTATE MyGetMouseState(void) {
		return m_MouseState;
	}
	BYTE MyGetKeyState(BYTE byKey) {
		return m_KeyState[byKey];
	}

	void Release(void);
	// << : Picker
	bool CheckPickingOnSphere(SPHERE sphere);
	bool CheckPiningOnTriangle(const D3DXVECTOR3* p0, const D3DXVECTOR3* p1, const D3DXVECTOR3* p2);
	bool CheckPiningOnTriangleAndGetPosition(IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, D3DXVECTOR3 * hitpoint);

public:
	CInput(void);
	~CInput(void);
};