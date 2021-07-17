// SR_BaseEngine.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"

////////// 콘솔창 띄우기/////////////
#ifdef  _DEBUG
#include <crtdbg.h>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif //  _DEBUG
/////////////////////////////////////

#pragma region SubEngineIncludes
#include "ShaderManager.h"
#include "WndApp.h"
#pragma endregion

#include "MainApp.h"
 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(675667);
	//_CrtSetBreakAlloc(315064);
	
	std::locale::global(std::locale("korean"));

#pragma region SubEnginesAwake
	Engine::CFRC::GetInstance()->Awake();
	Engine::CWndApp::GetInstance()->Awake();
	Engine::CDeviceManager::GetInstance()->Awake();
	Engine::CTextManager::GetInstance()->Awake();
	CMath::CMathHelper::GetInstance();
#pragma endregion

#pragma region SubEnginesStart
	
	Engine::CWndApp::GetInstance()->Start(hInstance, nCmdShow);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
	Engine::CTextManager::GetInstance()->Start();
#pragma endregion

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	SP(CMainApp) pMainApp = CMainApp::Create();
	pMainApp->Awake();
	pMainApp->Start();




	LARGE_INTEGER cpuTick, beginTime, endTime;
	QueryPerformanceFrequency(&cpuTick);
	QueryPerformanceCounter(&beginTime);
	QueryPerformanceCounter(&endTime);

	_float  timeGoesBy	= 0.f;
	_int	frameCount	= 0;
	_float	wheelDir	= 0.f;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_MOUSEWHEEL)
			{
				wheelDir = GET_WHEEL_DELTA_WPARAM(msg.wParam);
				wheelDir = GET_MATH->MinMax(wheelDir, -1, 1);
			}
			Engine::CInputManager::GetInstance()->SetMouseWheelDir(wheelDir);

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		

		if (timeGoesBy >= 1.f)
		{

			timeGoesBy = 0.f;
			frameCount = 0;
			QueryPerformanceFrequency(&cpuTick);
		}

		if (Engine::CFRC::GetInstance()->FrameLock())
		{			
			frameCount++;

			Engine::TIME_MEASURE_START;
			pMainApp->FixedUpdate();
			pMainApp->Update();
			pMainApp->LateUpdate();

			pMainApp->PreRender();
			pMainApp->Render();
			pMainApp->PostRender();
			_float time = Engine::GET_ELAPSED_TIME;
			wheelDir = 0.f;
		}
		
		QueryPerformanceCounter(&endTime);
		timeGoesBy += (float)(endTime.QuadPart - beginTime.QuadPart)/cpuTick.QuadPart;
		beginTime.QuadPart = endTime.QuadPart;
	}
	
	pMainApp->OnDestroy();
	pMainApp.reset();


#pragma region SubengineDestroy
	Engine::CDeviceManager::GetInstance()->DestroyInstance();
	Engine::CWndApp::GetInstance()->DestroyInstance();
	Engine::CFRC::GetInstance()->DestroyInstance();
	CMath::CMathHelper::GetInstance()->DestroyInstance();
	Engine::CTextManager::GetInstance()->DestroyInstance();
#pragma endregion
	return (int)msg.wParam;
}


