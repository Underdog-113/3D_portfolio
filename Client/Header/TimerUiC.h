#ifndef TIMERUICOMPONENT_H
#define TIMERUICOMPONENT_H

#include "Component.h"
class CTimerUiC  final : public Engine::CComponent
{
public:
	explicit CTimerUiC();
	~CTimerUiC();

	// CComponent을(를) 통해 상속됨
	SP(Engine::CComponent) MakeClone(Engine::CObject *pObject) override;
	void Awake() override;
	void Start(SP(Engine::CComponent) spThis) override;
	void FixedUpdate(SP(Engine::CComponent) spThis) override;
	void Update(SP(Engine::CComponent) spThis) override;
	void LateUpdate(SP(Engine::CComponent) spThis) override;
	void OnDestroy() override;
	void OnEnable() override;
	void OnDisable() override;

	void Reset() { m_totalTime = 0; }
public:
	static const	EComponentID	m_s_componentID = EComponentID::Text;
private:
	GETTOR(_float, m_totalTime, 0, TotalTime);
};
#endif

// 텍스트 추가
// 내가 원하는 텍스트의 오프셋을변경
// 문자열비교