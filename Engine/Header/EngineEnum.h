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
		UI				= 5,
		NumOfRenderID	= 6
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
		SkyBoxShader			= 4,
		/*Shader_Sample	= 0,
		Shader_Terrain	= 1,
		Shader_Mesh		= 2,
		Shader_Shade	= 3,
		Shader_Blend	= 4,
		Shader_Skybox	= 5,*/
		NumOfShaderID	= 5
	};
#pragma endregion

#pragma region PhysicsEnum
	enum class EColliderType
	{
		Point		= 0,
		Ray			= 1,
		Sphere		= 2,
		AABB		= 3,
		OBB			= 4,
		NumOfCT
	};

	enum class ERayType
	{
		LIMITED,
		POSITIVE_INF,
		NEGATIVE_INF,
		ALL_INF
	};

	enum class EColliderID
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
		Mesh					  = 1,
		Texture					= 2,
		Graphics				= 3,
		RigidBody				= 4,
		Collision				= 5,
		Camera					= 6,
		Debug					  = 7,
		RectTex					= 8,
		Bitmap					= 9,
		FadeInOut				= 10,
		Shader					= 11,
    Text					  = 12,
		StateMachine			= 13,
		NumOfEngineComponentID	= 14
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
		BV					= 1,
		DebugArrow			= 2,
		DebugCollision		= 3,
		Grid				= 4,
		UI					= 5,
		NumOfEngineLayerID	
	};


	enum EKey_State
	{
		KEY_STATE_LEFT_MOUSE, KEY_STATE_RIGHT_MOUSE, KEY_STATE_WHEEL_MOUSE,
		KEY_STATE_A, KEY_STATE_B, KEY_STATE_C, KEY_STATE_D, KEY_STATE_E,
		KEY_STATE_F, KEY_STATE_G, KEY_STATE_H, KEY_STATE_I, KEY_STATE_J,
		KEY_STATE_K, KEY_STATE_L, KEY_STATE_M, KEY_STATE_N, KEY_STATE_O,
		KEY_STATE_P, KEY_STATE_Q, KEY_STATE_R, KEY_STATE_S, KEY_STATE_T,
		KEY_STATE_U, KEY_STATE_V, KEY_STATE_W, KEY_STATE_X, KEY_STATE_Y, KEY_STATE_Z,
		KEY_STATE_F1, KEY_STATE_F2, KEY_STATE_F3, KEY_STATE_F4, KEY_STATE_F5, KEY_STATE_F6,
		KEY_STATE_F7, KEY_STATE_F8, KEY_STATE_F9, KEY_STATE_F10, KEY_STATE_F11, KEY_STATE_F12,
		KEY_STATE_1, KEY_STATE_2, KEY_STATE_3, KEY_STATE_4, KEY_STATE_5,
		KEY_STATE_6, KEY_STATE_7, KEY_STATE_8, KEY_STATE_9, KEY_STATE_0,
		KEY_STATE_LEFT_ARROW, KEY_STATE_RIGHT_ARROW, KEY_STATE_DOWN_ARROW, KEY_STATE_UP_ARROW,
		KEY_STATE_CTRL, KEY_STATE_ALT, KEY_STATE_TAB, KEY_STATE_SHIFT,
		KEY_STATE_ENTER, KEY_STATE_SPACE, KEY_STATE_ESC,
		KEY_STATE_MAX
	};
}




#endif // !ENGINEENUM_H
