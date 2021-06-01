#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Engine.h"

BEGIN(Engine)
class CObject;
class CScene;
class ENGINE_DLL CObjectFactory final : public CEngine
{
private:
							CObjectFactory				(void);
						   ~CObjectFactory				(void);
public:
	static	CObjectFactory*		Create					(CScene* pOwnerScene);
			void				Free					(void);

			void				Awake					(void) override;
			void				Start					(void);

			void				OnDestroy				(void);

			void				OnEnable				(void);
			void				OnDisable				(void);

			HRESULT				AddPrototype			(SP(CObject) pPrototype);
			SP(CObject)			AddClone				(const std::wstring& protoObjectKey,
														 _bool isStatic = false,
														 _int layerTag = UNDEFINED,
														 const std::wstring& name = L"");

			void				ClearCurPrototype		(void);

public:
	typedef std::unordered_map<std::wstring, SP(CObject)> _PROTOTYPES;
			_PROTOTYPES&		GetCurPrototype			(void);
	static	_PROTOTYPES&		GetStaticPrototypes		(void);

private:
			_PROTOTYPES			m_mCurPrototypes;
	static	_PROTOTYPES			m_s_mStaticPrototypes;

	static	_uint				m_s_usage;

	GETTOR	(CScene*,			m_pOwnerScene,			nullptr,		OwnerScene)
};
END
#endif