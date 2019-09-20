#pragma once
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


public:
	CInput(void);
	~CInput(void);
};
