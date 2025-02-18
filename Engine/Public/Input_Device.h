#ifndef InputDev_h__
#define InputDev_h__

#include "Base.h"

BEGIN(Engine)

class CInput_Device : public CBase
{
	

private:
	CInput_Device(void);
	virtual ~CInput_Device(void) = default;
	
public:
	_byte	Get_DIKeyState(_ubyte byKeyID)		
	{ 
		return m_bKeyState[byKeyID]; 
	}

	_byte	Get_DIMouseState(MOUSEKEYSTATE eMouse) 
	{ 	
		return m_tMouseState.rgbButtons[eMouse]; 	
	}

	// 현재 마우스의 특정 축 좌표를 반환
	_long	Get_DIMouseMove(MOUSEMOVESTATE eMouseState)	
	{	
		return *(((_long*)&m_tMouseState) + eMouseState);	
	}

	_bool isKeyPressed(_int _iKey);
	_bool isKeyReleased(_int _iKey);
	_bool isKeyEnter(_int _iKey);	
	_bool isMouseEnter(_uint iKey);	
	_bool isMouseRelease();	 
	
private:
	deque<MOUSEKEYSTATE> mouseBuffer;  // MouseEvent 타입을 저장하는 queue
	
	_bool LeftIsDown  = { false };
	_bool rightIsDown = { false };
	_bool mbuttonDown = { false };


public:
	HRESULT		  Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void		  Update_InputDev(void);
	void		  Push_MouseState(MOUSEKEYSTATE eMouseKeyState); 
	MOUSEKEYSTATE Get_PreMouseState();



private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;

private:
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse	= nullptr;

private:
	_byte					m_bKeyState[256];		// 키보드에 있는 모든 키값을 저장하기 위한 변수
	_byte					m_bPreKeyState[256];    // 키보드의 이전 상태를 저장하는 모든 키 값
	DIMOUSESTATE			m_tMouseState;	
	DIMOUSESTATE			m_tPreMouseState;	
	_bool				    m_bPreMouseState = { false };	

public:
	static CInput_Device* Create(HINSTANCE hInst, HWND hWnd);
	virtual void	Free(void);

};
END
#endif // InputDev_h__
