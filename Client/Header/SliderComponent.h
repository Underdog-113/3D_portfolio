#ifndef SLIDDERCOMPONENT_H
#define SLIDDERCOMPONENT_H

class CSliderComponent final : public Engine::CComponent
{
public:
	static const	EComponentID	m_s_componentID = EComponentID::Image;
private:

public:
	explicit CSliderComponent();
	~CSliderComponent();

	// CComponent��(��) ���� ��ӵ�
	virtual SP(Engine::CComponent) MakeClone(Engine::CObject *pObject);
	virtual void Awake();
	virtual void Start(SP(Engine::CComponent) spThis);
	virtual void FixedUpdate(SP(Engine::CComponent) spThis);
	virtual void Update(SP(Engine::CComponent) spThis);
	virtual void LateUpdate(SP(Engine::CComponent) spThis);
	virtual void OnDestroy();
	virtual void OnEnable();
	virtual void OnDisable();
};

#endif