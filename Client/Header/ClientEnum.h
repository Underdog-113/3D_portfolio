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
	Pattern				= 2 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	TargetPosition		= 3 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	NumOfComponentID	= 4 + (_uint)Engine::EComponentID::NumOfEngineComponentID
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
	PhaseChanger		= 8 + (_uint)Engine::ECollisionID::NumOfColliderID,
	NumOfColliderID		= 9 + (_uint)Engine::ECollisionID::NumOfColliderID
};

enum class EDataID
{
	BasicObject		= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player			= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene			= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy			= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	EFFECT			= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI				= 5 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Stat			= 6 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Monster			= 7 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID		= 8 + (_uint)Engine::EDataID::NumOfEngineDataID
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
	DamageFontShader	= 1 + (_int)Engine::EShaderID::NumOfShaderID,
	CatPawShader		= 2 + (_int)Engine::EShaderID::NumOfShaderID,
	CircularGaugeShader	= 3 + (_int)Engine::EShaderID::NumOfShaderID,
	MeshTrailShader		= 4 + (_int)Engine::EShaderID::NumOfShaderID,
	DissolveShader		= 5 + (_int)Engine::EShaderID::NumOfShaderID,
	SpawnEffectShader	= 6 + (_int)Engine::EShaderID::NumOfShaderID,
	SoftEffectShader	= 7 + (_int)Engine::EShaderID::NumOfShaderID,
	AttackRangeShader	= 8 + (_int)Engine::EShaderID::NumOfShaderID,
	AlphaMaskShader     = 9 + (_int)Engine::EShaderID::NumOfShaderID,
	FireShader			= 10 + (_int)Engine::EShaderID::NumOfShaderID,
	LaserShader  		= 11 + (_int)Engine::EShaderID::NumOfShaderID,
	NumOfShaderID		= 12 + (_int)Engine::EShaderID::NumOfShaderID
};

enum class EChannelID
{
	MONSTER_0			= 0 + (_int)Engine::EChannelID::NumOfChannelID,
	MONSTER_1			= 1 + (_int)Engine::EChannelID::NumOfChannelID,
	MONSTER_2			= 2 + (_int)Engine::EChannelID::NumOfChannelID,
	MONSTER_3			= 3 + (_int)Engine::EChannelID::NumOfChannelID,
	MONSTER_4			= 4 + (_int)Engine::EChannelID::NumOfChannelID,
	NumOfChannelID		= 5 + (_int)Engine::EChannelID::NumOfChannelID,
};

enum class ELoadingID
{
	StaticResource,
	BossSceneResource
};
#endif // CLIENTENUM_H


// Floor		    : 3
// Wall			    : 4
// FloorRay		    : 5
// WallRay		    : 6
// PlayerHitBox	    : 7
// PlayerAttack	    : 8
// EnemyHitBox	    : 9
// EnemyAttack	    : 10
// NumOfColliderID  : 11