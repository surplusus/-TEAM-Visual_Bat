#include"BaseInclude.h"
#include "Input.h"
#include "MousePicker.h"

CInput::CInput(void)
	:m_pInput(NULL), m_pKeyBoard(NULL), m_pMouse(NULL), m_MousePicker(NULL)
{
}

CInput::~CInput(void)
{
	Release();
}

HRESULT CInput::InitInputDevice(HINSTANCE hInst, HWND hWnd)
{
	ZeroMemory(m_KeyState, sizeof(BYTE) * 256);
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));

	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8
		, (void**)&m_pInput, NULL)))
		return E_FAIL;

	if (m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, NULL) != DI_OK)
		return E_FAIL;

	if (m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) != DI_OK)
		return E_FAIL;

	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	m_pKeyBoard->Acquire();


	// Mouse
	if (m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL) != DI_OK)
		return E_FAIL;

	if (m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) != DI_OK)
		return E_FAIL;

	m_pMouse->SetDataFormat(&c_dfDIMouse);

	m_pMouse->Acquire();

	// Mouse Picker
	m_MousePicker = new CMousePicker();
	if (FAILED(m_MousePicker->GetHittingPoint(m_PickingPoint)))
		return E_FAIL;

	return S_OK;
}


void CInput::SetInputState(void)
{

	m_pKeyBoard->GetDeviceState(sizeof(m_KeyState), m_KeyState);
	m_pMouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);
}

void CInput::Release(void)
{
	if (m_pKeyBoard)
		m_pKeyBoard->Release();

	if (m_pMouse)
		m_pMouse->Release();

	if (m_pInput)
		m_pInput->Release();
}

bool CInput::CheckPickingOnSphere(SPHERE sphere)
{
	if (!m_MousePicker)
		m_MousePicker = new CMousePicker();
	return m_MousePicker->CheckIntersectWithSphere(sphere);
}

bool CInput::CheckPiningOnTriangle(const D3DXVECTOR3 * p0, const D3DXVECTOR3 * p1, const D3DXVECTOR3 * p2)
{
	if (!m_MousePicker)
		m_MousePicker = new CMousePicker();
	return m_MousePicker->CheckIntersectWithTriangle(p0, p1, p2);
}

bool CInput::CheckPiningOnTriangleAndGetPosition(IN const D3DXVECTOR3 * p0, IN const D3DXVECTOR3 * p1, IN const D3DXVECTOR3 * p2, D3DXVECTOR3 * hitpoint)
{
	if (!m_MousePicker)
		m_MousePicker = new CMousePicker();
	return m_MousePicker->CheckIntersectWithTriangleAndGetPosition(p0, p1, p2, hitpoint);
}
