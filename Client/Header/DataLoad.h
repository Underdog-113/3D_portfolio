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
	void DelegatePush(void(CDataLoad::* function)(Engine::CScene*) , CDataLoad* dataload);
	void DeleGatePop(void(CDataLoad::* function)(Engine::CScene*), CDataLoad* dataload);
	void Load(Engine::CScene* pScene);

public:
	// 이미지 로드
	void ImageLoad(Engine::CScene* pScene);
	
	// 슬라이더 로드
	void SliderLoad(Engine::CScene* pScene);

	// 버튼 로드
	void ButtonLoad(Engine::CScene* pScene);

	// 스크롤뷰 로드
	void ScrollViewLoad(Engine::CScene* pScene);

	// 캔버스 로드
	void CanvasLoad(Engine::CScene* pScene);

	// 캔버스 로드
	void TextLoad(Engine::CScene* pScene);

	// 툴 로드
	void MapLoad(Engine::CScene* pScene);

	// 페이즈 체인저 로드
	void PhaseChangerLoad(Engine::CScene* pScene);
	
	// 포탈 로드
	void PortalLoad(Engine::CScene* pScene);

	// 트랩 로드
	void TrapLoad(Engine::CScene* pScene);

	void EffectLoad(Engine::CScene* pScene);

	void ButtonFunction(SP(CButton) button, std::wstring function);
};
