#pragma once
#include "DeleGate.h"

class CScene;
class CDataLoad
{
	Delegate<Engine::CScene*> m_loadDeleGate;
public:
	CDataLoad();
	~CDataLoad();

public:
	void Setting();
	//void(CButtonFunction::*)(), CButtonFunction*
	void DelegatePush(void(CDataLoad::* function)(Engine::CScene*) , CDataLoad* dataload);
	void DeleGatePop(void(CDataLoad::* function)(Engine::CScene*), CDataLoad* dataload);
	void Load(Engine::CScene* pScene);

private:
	// 이미지 로드
	void ImageLoad(Engine::CScene* pScene);
	
	// 슬라이더 로드
	void SliderLoad(Engine::CScene* pScene);

	// 버튼 로드
	void ButtonLoad(Engine::CScene* pScene);

	// 스크롤뷰 로드
	void ScrollViewLoad(Engine::CScene* pScene);

	void CanvasLoad(Engine::CScene* pScene);

	// 툴 로드
	void ToolLoad(Engine::CScene* pScene);
	
	void EffectLoad(Engine::CScene* pScene);

	void ButtonFunction(SP(CButton) button, std::wstring function);
};

