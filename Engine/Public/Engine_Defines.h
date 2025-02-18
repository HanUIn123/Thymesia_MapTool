#pragma once

#pragma warning (disable : 4251)

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <d3dcompiler.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <Effects11/d3dx11effect.h>
#include <DirectXTK/DDSTextureLoader.h>
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK\ScreenGrab.h>


#include <DirectXTK\PrimitiveBatch.h>
#include <DirectXTK\VertexTypes.h>
#include <DirectXTK\Effects.h>

#include <DirectXTK\SpriteBatch.h>
#include <DirectXTK\SpriteFont.h>

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>


#include "fmod.h"	
#include "fmod.hpp"	
#include "fmod_codec.h"	
#pragma comment(lib, "fmod_vc.lib")	
#include <io.h>

using namespace DirectX;

#include <vector>
#include <list>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>	

using namespace std;

#include "Engine_Typedef.h"
#include "Engine_Enum.h"
#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"


namespace Engine
{
	static _wstring			g_strTransformTag = TEXT("Com_Transform");

	const unsigned int g_iMaxWidth = 1600;
	const unsigned int g_iMaxHeight = 900;
	

	const unsigned int g_iWinSize_X = 1600;
	const unsigned int g_iWinSize_Y = 900;
	

}

using namespace Engine;


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG