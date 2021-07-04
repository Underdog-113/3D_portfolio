#ifndef ATBPATTERN_H
#define ATBPATTERN_H

class Engine::CObject;

class CATBPattern abstract
{
public:
	explicit CATBPattern(void);
	virtual	~CATBPattern(void);

public:
	virtual void Pattern(Engine::CObject* pOwner) PURE;
	virtual void CoolTime(_float& curTime, _float maxTime, _bool& readyType); // 현재 쿨타임, 맥스 쿨타임, 쿨타임 타입
	virtual _float GetCost() { return m_cost; }

	void PatternPlaySound(_TCHAR* fileName, Engine::CObject* pOwner);
	void PatternStopSound(Engine::CObject* pOwner);
	void PatternRepeatSound(_TCHAR* fileName, Engine::CObject* pOwner, _float interval);
	void SetPrequency(Engine::CObject* pOwner, _float* frequency);
	_bool PatternSoundEnd(Engine::CObject* pOwner);

protected:
	_float m_cost = 0;
	_float m_accTime = 0.f;
	_float m_weight = 0.f; // 스킬 가중치
	_bool m_onSound = false;
};
#endif
