#pragma once

#define NOMINMAX
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "Windows.h"
#include "commdlg.h"
#include <process.h>

namespace Client 
{
	const unsigned int		g_iWinSizeX = 1600;
	const unsigned int		g_iWinSizeY = 900;

	enum LEVELID { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };

	/* 컬링 거리 */
	const float g_fCullingDistance = 30.f; 
	

}

using namespace Client;

extern HINSTANCE g_hInst;
extern HWND g_hWnd;	

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

