#include "Input_Device.h"

Engine::CInput_Device::CInput_Device(void)
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));		
	ZeroMemory(m_bPreKeyState, sizeof(m_bPreKeyState));		
}


_bool CInput_Device::isKeyPressed(_int _iKey)
{
	if ((m_bKeyState[_iKey] & 0x80) && (m_bPreKeyState[_iKey] & 0x80)) // 키보드에서 버튼이 풀려난경우?라고 해야하나 ㅋㅋ;;		
		return true;

	else //  처음 작업 키가 입력 되었다면.( * 이전 프레임과 비교해서 )	
		return false;
}

_bool CInput_Device::isKeyReleased(_int _iKey)
{		
	if (!(m_bKeyState[_iKey] & 0x80) && (m_bPreKeyState[_iKey] & 0x80)) // 키보드에서 버튼이 풀려난경우?라고 해야하나 ㅋㅋ;;		
		return true;	

	else //  처음 작업 키가 입력 되었다면.( * 이전 프레임과 비교해서 )	
		return false;	
}

_bool CInput_Device::isKeyEnter(_int _iKey)
{
	if ((m_bKeyState[_iKey] & 0x80) && !(m_bPreKeyState[_iKey] & 0x80)) // 처음 눌렸을 때 		
		return true;

	else //  처음 작업 키가 입력 되었다면.( * 이전 프레임과 비교해서 )	
		return false;		
}

_bool CInput_Device::isMouseEnter(_uint _iKey)		
{
	if ((m_tMouseState.rgbButtons[_iKey] & 0x80) && !(m_tPreMouseState.rgbButtons[_iKey] & 0x80))	
		return true;

	else
		return false; 
	 
	
	//bool bCurMouseState = Get_DIMouseState(DIM_LB) & 0x80;	
	//	
	//if (m_bPreMouseState != bCurMouseState)
	//{
	//	m_bPreMouseState = bCurMouseState;
	//	return true;
	//}

}

_bool CInput_Device::isMouseRelease()
{
	bool isReleasedNow = !(Get_DIMouseState(DIM_LB) & 0x80); // 마우스에서 떼어졌을 때 눌리는	
	
	if (m_bPreMouseState == true && isReleasedNow == true) // true니깐 눌려있다는 상태		
	{
		m_bPreMouseState = false;
		return true;
	}
	
	m_bPreMouseState = !isReleasedNow;
	
		
	return false;
}




HRESULT Engine::CInput_Device::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{

	// DInput 컴객체를 생성하는 함수
	if (FAILED(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK, nullptr)))
		return E_FAIL;
											

	// 키보드 객체 생성
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// 생성된 키보드 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// 장치에 대한 독점권을 설정해주는 함수, (클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pKeyBoard->Acquire();


	// 마우스 객체 생성
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// 생성된 마우스 객체의 대한 정보를 컴 객체에게 전달하는 함수
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// 장치에 대한 독점권을 설정해주는 함수, 클라이언트가 떠있는 상태에서 키 입력을 받을지 말지를 결정하는 함수
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// 장치에 대한 access 버전을 받아오는 함수
	m_pMouse->Acquire();


	return S_OK;
}

void Engine::CInput_Device::Update_InputDev(void)
{
	memcpy(m_bPreKeyState, m_bKeyState, sizeof(_byte) * VK_MAX);
	m_pKeyBoard->GetDeviceState(256, m_bKeyState);	
	
	memcpy(&m_tPreMouseState, &m_tMouseState, sizeof(DIMOUSESTATE));		
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);	
	
}

void CInput_Device::Push_MouseState(MOUSEKEYSTATE eMouseKeyState)
{
	mouseBuffer.push_front(eMouseKeyState);	
}

MOUSEKEYSTATE CInput_Device::Get_PreMouseState()
{
	return mouseBuffer.back();	
}

CInput_Device * CInput_Device::Create(HINSTANCE hInst, HWND hWnd)
{
	CInput_Device*		pInstance = new CInput_Device();

	if (FAILED(pInstance->Ready_InputDev(hInst, hWnd)))
	{
		MSG_BOX("Failed to Created : CInput_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void Engine::CInput_Device::Free(void)
{
	__super::Free();

	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}

