#ifndef CLIENTENUM_H
#define CLIENTENUM_H


enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default				= 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Text				= 1 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	NumOfComponentID	= 2 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class ECollisionID
{
	Floor				= 0 + (_uint)Engine::ECollisionID::NumOfColliderID,
	Wall				= 1 + (_uint)Engine::ECollisionID::NumOfColliderID,
	FloorRay			= 2 + (_uint)Engine::ECollisionID::NumOfColliderID,
	WallRay				= 3 + (_uint)Engine::ECollisionID::NumOfColliderID,
	PlayerHitBox		= 4 + (_uint)Engine::ECollisionID::NumOfColliderID,
	PlayerAttack		= 5 + (_uint)Engine::ECollisionID::NumOfColliderID,
	EnemyHitBox			= 6 + (_uint)Engine::ECollisionID::NumOfColliderID,
	EnemyAttack			= 7 + (_uint)Engine::ECollisionID::NumOfColliderID,
	NumOfColliderID		= 8 + (_uint)Engine::ECollisionID::NumOfColliderID
};

enum class EDataID
{
	BasicObject		= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player			= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene			= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy			= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	EFFECT			= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI				= 5 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID		= 6 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy			= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Camera			= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Effect			= 4 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Attack			= 5 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 6 + (_int)Engine::ELayerID::NumOfEngineLayerID
};

enum class EShaderID
{
	WaterShader			= 0 + (_int)Engine::EShaderID::NumOfShaderID,
	EffectShader		= 1 + (_int)Engine::EShaderID::NumOfShaderID,
	DamageFontShader	= 2 + (_int)Engine::EShaderID::NumOfShaderID,
	CatPawShader		= 3 + (_int)Engine::EShaderID::NumOfShaderID,
	CircularGaugeShader	= 4 + (_int)Engine::EShaderID::NumOfShaderID,
	MeshTrailShader		= 5 + (_int)Engine::EShaderID::NumOfShaderID,
	DissolveShader		= 6 + (_int)Engine::EShaderID::NumOfShaderID,
	SpawnEffectShader	= 7 + (_int)Engine::EShaderID::NumOfShaderID,
	SoftEffectShader	= 8 + (_int)Engine::EShaderID::NumOfShaderID,
	AttackRangeShader	= 9 + (_int)Engine::EShaderID::NumOfShaderID,
	NumOfShaderID		= 10 + (_int)Engine::EShaderID::NumOfShaderID
};

enum class ELoadingID
{
	StaticResource,
	BossSceneResource
};
#endif // CLIENTENUM_H