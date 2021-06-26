// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#ifndef STDAFX_H
#define STDAFX_H

#include "targetver.h"

#include <process.h>

//For Grapchis
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

//Engine's stdafx.h
#include "EngineStdafx.h"

//Client's includes
#include "ClientTypedef.h"
#include "ClientDefine.h"
#include "ClientEnum.h"
#include "ClientMacro.h"
#include "ClientStructure.h"
#include "ClientFunction.h"
#include "ClientComponents.h"
#include "ClientPatterns.h"

#include "ClientStructure_ValkyrieStatus.h"
#include "ClientStructure_MonsterStatus.h"

#include "StageControlTower.h"

//Client Managers
#include "ButtonManager.h"
#include "BattleUiManager.h"
#include "DataManager.h"
#include "ValkyriegManager.h"

// ����
//#include <io.h>
//#include "fmod.h"
//#pragma comment (lib, "fmodex64_vc.lib")

#endif