#ifndef MESHC_H
#define MESHC_H

#include "RenderComponent.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"
BEGIN(Engine)


class CGraphicsC;
class CRootMotion;
class ENGINE_DLL CMeshC final : public CRenderComponent
{
public:
	explicit							CMeshC						(void);
									   ~CMeshC						(void);

public:
			SP(CComponent)				MakeClone					(CObject* pObject) override;
			void						Awake						(void) override;
			void						Start						(SP(CComponent) spThis) override;

			void						FixedUpdate					(SP(CComponent) spThis) override;
			void						Update						(SP(CComponent) spThis) override;
			void						LateUpdate					(SP(CComponent) spThis) override;


			void						PreRender					(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;
			void						Render						(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;
			void						PostRender					(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect) override;

			void						RenderPerShader				(SP(CGraphicsC) spGC) override;

			void						OnDestroy					(void) override;

			void						OnEnable					(void) override;
			void						OnDisable					(void) override;
public:
			void						SetMeshData					(CMeshData* pMeshData);
			void						SetMeshData					(std::wstring meshKey);
			void						GenMinMaxVtx				(void);

			void						OnRootMotion				(void);
			void						OffRootMotion				(void);
			void						ApplyRootMotion				(CDynamicMeshData* pDM);

			CStaticMeshData*			GetFirstMeshData_Static		(void);
			CDynamicMeshData*			GetFirstMeshData_Dynamic	(void);

private:
			void						RenderStatic				(SP(CGraphicsC) spGC, CMeshData* pMeshData, LPD3DXEFFECT pEffect);
			void						RenderStaticPerSubset		(SP(CGraphicsC) spGC);
			void						RenderDynamic				(SP(CGraphicsC) spGC, CMeshData* pMeshData, LPD3DXEFFECT pEffect);
			void						RenderDynamicPerSubset		(SP(CGraphicsC) spGC);

public:
	static const	EComponentID		m_s_componentID = EComponentID::Mesh;

private:
	GETTOR			(CMeshData*,		m_pMeshData,				nullptr,		MeshData)

	GETTOR			(_float3,			m_meshSize,					ZERO_VECTOR,	MeshSize)
	GETTOR			(_float3,			m_minVertex,				MAX_VECTOR,		MinVertex)
	GETTOR			(_float3,			m_maxVertex,				-MAX_VECTOR,	MaxVertex)
	GETTOR_SETTOR	(_bool,				m_initTex,					false,			InitTex)
	GETTOR			(CRootMotion*,		m_pRootMotion,				nullptr,		RootMotion);

	GETTOR			(_float3,			m_rootMotionPos,			ZERO_VECTOR,	RootMotionPos)
	GETTOR			(_float,			m_halfYOffset,				0.f,			HalfYOffset)
	GETTOR_SETTOR	(_bool,				m_isEffectMesh,				false,			IsEffectMesh)


	GETTOR			(_bool,				m_haveDrawn,				false,			HaveDrawn)

};
END
#endif // !MESH_H
