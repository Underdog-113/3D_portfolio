#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Engine
{
#pragma region GraphicsEnum
	enum class EDisplayMdoe
	{
		FullMode,
		WinMode
	};

	//GraphicsComponent RenderID
	enum class ERenderID
	{
		Base			= 0,
		NonAlpha		= 1,
		WireFrame		= 2,
		AlphaTest		= 3,
		AlphaBlend		= 4,
		Particle		= 5,
		UI				= 6,
		NumOfRenderID	= 7
	};

	//Camera Mdoe
	enum class ECameraMode
	{
		Fixed			= 0,
		Free			= 1,
		Edit			= 2,
		FPS				= 3,
		TPS				= 4,
		NumOfCameraMode	= 5
	};

	//MeshType
	enum class EMeshType
	{
		Static			= 0,
		Dynamic			= 1,
		NumOfMeshType	= 2
	};

	enum class EDebugBV
	{
		Sphere			= 0,
		AABB			= 1,
		NumOfDebugBV	= 2
	};

	enum class EDebugMT
	{
		BV				= 0,
		ArrowR			= 1,
		ArrowU			= 2,
		ArrowF			= 3,
		Mesh			= 4,
		NumOfDebugMT	= 5
	};

	enum class EShaderID
	{
		MeshShader				= 0,
		RectTexShader			= 1,
		DeferredBlendShader		= 2,
		DeferredLightShader		= 3,
		SliderShader			= 4,
		WaterShader				= 5,
		EffectShader			= 6,
		DamageFont				= 7,
		CatPawShader			= 8,
		CircularGauge			= 9,
		CelShader				= 10,
		SkyBoxShader			= 11,
		MeshTrailShader			= 12,
		NumOfShaderID			= 13

	};
#pragma endregion

#pragma region PhysicsEnum
	enum class EPhysicsBodyType
	{
		Static					= 0,
		Dynamic					= 1,
		Kinematic				= 2,
		NumOfPhysicsBodyType	= 3
	};

	enum class EColliderType
	{
		Point		= 0,
		Ray			= 1,
		Sphere		= 2,
		AABB		= 3,
		OBB			= 4,
		NumOfCT
	};

	enum class EActorType
	{
		Static		= 0,
		Dynamic		= 1
	};

	enum class ERayType
	{
		LIMITED,
		POSITIVE_INF,
		NEGATIVE_INF,
		ALL_INF
	};

	enum class ECollisionID
	{
		CameraRay			= 0,
		Button				= 1,
		Mouse				= 2,
		NumOfColliderID		= 3
	};

	enum class EConstraint
	{
		None				= 1 << 0,
		FreezePositionX		= 1 << 1,
		FreezePositionY		= 1 << 2,
		FreezePositionZ		= 1 << 3,
		FreezeRotationX		= 1 << 4,
		FreezeRotationY		= 1 << 5,
		FreezeRotationZ		= 1 << 6,
		FreezePosition		= 1 << 7,
		FreezeRotation		= 1 << 8,
		FreezeAll			= 1 << 9
	};
#pragma endregion

	enum class EComponentID
	{
		Transform				= 0,
		Mesh					= 1,
		Texture					= 2,
		Graphics				= 3,
		RigidBody				= 4,
		Collision				= 5,
		Camera					= 6,
		Debug					= 7,
		RectTex					= 8,
		Physics					= 9,
		CubeTex					= 10,
		Shader					= 11,
        Text					= 12,
		StateMachine			= 13,
		ParticleSystem			= 14,
		NumOfEngineComponentID	= 15
	};

	enum class EChannelID
	{
		BGM,
		AMBIENT,
		PLAYER,
		PLAYEREFFECT,
		EFFECT,
		UI,
		NumOfChannelID
	};

	enum class EDataID
	{
		Engine				= 0,
		Object				= 1,
		Component			= 2,
		NumOfEngineDataID	= 3
	};

	enum class ELayerID
	{
		Camera				= 0,
		Debug				= 1,
		Decoration			= 2,
		Effect				= 3,
		UI					= 4,
		NumOfEngineLayerID  = 5
	};
}




#endif // !ENGINEENUM_H
