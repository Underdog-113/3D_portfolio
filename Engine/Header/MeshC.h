#ifndef MESHC_H
#define MESHC_H

#include "RenderComponent.h"

BEGIN(Engine)

class CMeshData;
class CGraphicsC;
class CDynamicMeshData;
class CRootMotion;
class ENGINE_DLL CMeshC final : public CRenderComponent
{
public:
	explicit							CMeshC			(void);
									   ~CMeshC			(void);

public:
			SP(CComponent)				MakeClone		(CObject* pObject) override;
			void						Awake			(void) override;
			void						Start			(SP(CComponent) spThis) override;

			void						FixedUpdate		(SP(CComponent) spThis) override;
			void						Update			(SP(CComponent) spThis) override;
			void						LateUpdate		(SP(CComponent) spThis) override;

			void						PreRender		(SP(CGraphicsC) spGC) override;
			void						PreRender		(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

			void						Render			(SP(CGraphicsC) spGC) override;
			void						Render			(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

			void						PostRender		(SP(CGraphicsC) spGC) override;
			void						PostRender		(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

			void						OnDestroy		(void) override;

			void						OnEnable		(void) override;
			void						OnDisable		(void) override;
public:
			void						AddMeshData		(CMeshData* pMeshData);
			void						AddMeshData		(std::wstring meshKey);
			void						GenMinMaxVtx	(void);
			
			void						OnRootMotion	(void);
			void						OffRootMotion	(void);
			void						ApplyRootMotion (CDynamicMeshData* pDM, _float3* rootMotionMoveAmount);

private:
			void						RenderStatic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex);
			void						RenderStatic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex, LPD3DXEFFECT pEffect);

			void						RenderDynamic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex);
			void						RenderDynamic	(SP(CGraphicsC) spGC, CMeshData* pMeshData, _int meshIndex, LPD3DXEFFECT pEffect);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Mesh;

private:
	typedef std::vector<CMeshData*> _MESHES;
	GETTOR_SETTOR	(_MESHES,			m_vMeshDatas,	{},				MeshDatas)

	GETTOR			(_float3,			m_meshSize,		ZERO_VECTOR,	MeshSize)
	GETTOR			(_float3,			m_minVertex,	MAX_VECTOR,		MinVertex)
	GETTOR			(_float3,			m_maxVertex,	-MAX_VECTOR,	MaxVertex)
	GETTOR_SETTOR	(_bool,				m_initTex,		false,			InitTex)	
	GETTOR			(CRootMotion*,		m_pRootMotion,			nullptr,	RootMotion);
		
	GETTOR			(_float,			m_halfYOffset,	0.f, HalfYOffset)
	};
END
#endif // !MESH_H
