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


//Client Managers
#include "ButtonManager.h"
#include "BattleUiManager.h"

// ����
//#include <io.h>
//#include "fmod.h"
//#pragma comment (lib, "fmodex64_vc.lib")

#endif