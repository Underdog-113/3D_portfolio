#pragma once
#ifndef ENGINESTDAFX_H
#define ENGINESTDAFX_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4503)
#pragma warning(disable : 4717)

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN64_LEAN_AND_MEAN

//프로젝트 외부 참조문서
//For C, window 
#define NOMINMAX
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

//For Containers
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <stack>
#include <queue>
#include <array>

//For FileStream
#include <fstream>

//For strings
#include <sstream>
#include <string>
#include <codecvt>

//For pointers
#include <memory>

//For function pointers
#include <functional>

//For Algorithm
#include <algorithm>

//For Graphics
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

//For Sound
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex64_vc.lib")

#include "PxPhysicsAPI.h"


#ifdef _DEBUG
#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib")
#pragma comment(lib, "PxFoundationDEBUG_x64.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3DEBUG_x64.lib")
#endif

#ifdef NDEBUG
#pragma comment(lib, "PhysX3Common_x64.lib")
#pragma comment(lib, "PxFoundation_x64.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PhysX3_x64.lib")
#endif

using namespace physx;

//프로젝트 내의 참조문서
#include "EngineTypedef.h"
#include "EngineDefine.h"
#include "EngineEnum.h"
#include "EngineFunction.h"
#include "EngineExtern.h"
#include "EngineMacro.h"
#include "EngineStructure.h"
#include "EngineComponents.h"



//Managers
#include "SceneManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "DeviceManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "PSC_Manager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "RenderTargetManager.h"
#include "PhysicsManager.h"

//ETC
#include "MathHelper.h"
#include "FRC.h"




#endif