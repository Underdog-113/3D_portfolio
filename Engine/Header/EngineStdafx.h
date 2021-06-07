#ifndef ENGINESTDAFX_H
#define ENGINESTDAFX_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4503)
// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN64_LEAN_AND_MEAN

//������Ʈ �ܺ� ��������
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

//������Ʈ ���� ��������
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
#include "SoundManager.h"
#include "TextManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "RenderTargetManager.h"

//ETC
#include "MathHelper.h"
#include "FRC.h"




#endif