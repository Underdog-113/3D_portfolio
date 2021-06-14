#ifndef SLIDER_H
#define SLIDER_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CSlider final : public CObject
{
public:
	enum ESliderDirection { LeftToRight, RightToLeft, BottomToTop, TopToBottom };
	SMART_DELETER_REGISTER
private:
	CSlider();
	~CSlider();

public:
	// CObject을(를) 통해 상속됨
	static	SP(CSlider) Create(_bool isStatic, CScene* pScene);
	SP(CObject) MakeClone(void) override;

	void Awake(void) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void PreRender(void) override;
	void Render(void) override;
	void PostRender(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

	void AddSliderData(_float value, _float maxValue, SP(CObject) spBackGround, SP(CObject) spFill);
private:
	void SetBasicName(void) override;
private:
	static _uint m_s_uniqueID;

	GETTOR_SETTOR(_float, m_value, 1, Value)
	GETTOR_SETTOR(_float, m_MaxValue, 1, MaxValue)
		GETTOR_SETTOR(_float, m_MinValue, 1, MinValue)
	GETTOR_SETTOR(SP(CObject), m_spBackGround, nullptr, BackGround)
	GETTOR_SETTOR(SP(CObject), m_spFill, nullptr, Fill)
	GETTOR_SETTOR(ESliderDirection, m_direction, ESliderDirection::LeftToRight, Direction)
};
END
#endif