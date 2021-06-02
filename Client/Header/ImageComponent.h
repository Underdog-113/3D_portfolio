#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

class CImageComponent final : public Engine::CComponent
{
public:
	static const	EComponentID	m_s_componentID = EComponentID::Image;
private:
	

public:
	explicit CImageComponent(); 
	~CImageComponent();

	// CComponent을(를) 통해 상속됨
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