#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include "Object.h"

BEGIN(Engine)
class ENGINE_DLL CEmptyObject final : public CObject
{
	SMART_DELETER_REGISTER
private:
	explicit	CEmptyObject		(void);
			   ~CEmptyObject		(void);

public:
	static		SP(CEmptyObject)			Create					(_bool isStatic, CScene* pScene);

				SP(Engine::CObject)			MakeClone				(void) override;
		
				void						Awake					(void) override;
				void						Start					(void) override;
		
				void						FixedUpdate				(void) override;
				void						Update					(void) override;
				void						LateUpdate				(void) override;
		
				void						PreRender				(void) override;
				void						Render					(void) override;
				void						PostRender				(void) override;

				void						OnDestroy				(void) override;
		
				void						OnEnable				(void) override;
				void						OnDisable				(void) override;

				void						SetBasicName			(void)  override;

				void						OnCollisionEnter		(Engine::_CollisionInfo ci);
				void						OnCollisionStay			(Engine::_CollisionInfo ci);
				void						OnCollisionExit			(Engine::_CollisionInfo ci);

private:
				void						PickComponentToRender	(void);

private:
	static		_uint						m_s_uniqueID;
	GETTOR		(SP(CRenderComponent),		m_spComponentToRender,		nullptr,		ComponentToRender)
};
END

#endif