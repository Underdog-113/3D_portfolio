// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#ifndef STDAFX_H
#define STDAFX_H
using namespace std;
#include "targetver.h"

#include <process.h>

//For Grapchis
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

#include<ctime>

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
#include "InventoryManager.h"

#include "ReadyToSortieManager.h"
#include "BattleEndManager.h"
#include "BattleUiManager.h"
#include "MainRoomManager.h"
#include "StageSelectionManager.h"
#include "ValkyriegManager.h"
#include "InventoryManager.h"
#include "BattleEndManager.h"
#include "SupplyManager.h"

#include "DropItemManager.h"

//Client Data
#include "ValkyrieStatusData.h"
#include "CaptainData.h"
#include "InStockValkyrieData.h"
#include "WeaponData.h"
#include "ItemData.h"
#include "SquadData.h"

// ����
//#include <io.h>
//#include "fmod.h"
//#pragma comment (lib, "fmodex64_vc.lib")

#endif