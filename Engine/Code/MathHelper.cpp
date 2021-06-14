#include "EngineStdafx.h"
#include "MathHelper.h"

USING(CMath)
IMPLEMENT_SINGLETON(CMathHelper)
_float CMathHelper::Max(_float num, _float standard)
{
	return (num = (num > standard) ? num : standard);
}

_float CMathHelper::Min(_float num, _float standard)
{
	return (num = (num < standard) ? num : standard);
}

_float CMathHelper::MinMax(_float num, _float stdMin, _float stdMax)
{
	num = Min(num, stdMax);
	num = Max(num, stdMin);
	return num;
}

_float CMathHelper::UpperRoundOff(_float num, _float stdMax)
{
	if (num > stdMax)
		num -= abs(stdMax);

	return num;
}

_float CMathHelper::LowerRoundOFf(_float num, _float stdMin)
{
	if (num < stdMin)
		num += abs(stdMin);

	return num;
}

_float CMathHelper::RoundOffRange(_float num, _float absRange)
{
	num = UpperRoundOff(num, absRange);
	num = LowerRoundOFf(num, -absRange);

	return num;
}

_float3 CMathHelper::AddX(_float3 & vec, _float num)
{
	return vec + _float3(num, 0, 0);
}

_float3 CMathHelper::AddY(_float3 & vec, _float num)
{
	return vec + _float3(0, num, 0);
}

_float3 CMathHelper::AddZ(_float3 & vec, _float num)
{
	return vec + _float3(0, 0, num);
}

_float3 CMathHelper::QuatToRad(_quat & Q)
{
	double roll, pitch, yaw;

	// roll (x-axis rotation)
	double sinR_cosP = 2 * (Q.w * Q.x + Q.y * Q.z);
	double cosR_cosP = 1 - 2 * (Q.x * Q.x + Q.y * Q.y);
	roll = atan2(sinR_cosP, cosR_cosP);

	// pitch (y-axis rotation)
	double sinP = 2 * (Q.w * Q.y - Q.z * Q.x);
	if (std::abs(sinP) >= 1)
		pitch = copysign(D3DX_PI * 0.5f, sinP);    // use 90 degrees if out of range
	else
		pitch = asin(sinP);

	// yaw (z-axis rotation)
	double sinY_cosP = 2 * (Q.w * Q.z + Q.x * Q.y);
	double cosY_cosP = 1 - 2 * (Q.y * Q.y + Q.z * Q.z);
	yaw = atan2(sinY_cosP, cosY_cosP);

	return _float3((FLOAT)roll, (FLOAT)pitch, (FLOAT)yaw);
}

_float3 CMathHelper::QuatToDegree(_quat & Q)
{
	_float3 result = QuatToRad(Q);
	result.x = D3DXToDegree(result.x);
	result.y = D3DXToDegree(result.y);
	result.z = D3DXToDegree(result.z);

	return result;
}

_bool CMathHelper::SeparateAxisTest(_float3 const& axis, 
									_float const& minA, _float const& maxA,
									_float const& minB, _float const& maxB)
{
	_float axisLengthSquared = D3DXVec3Dot(&axis, &axis);

	//if axis is degenerate to ignore
	if (axisLengthSquared <= EPSILON)
		return true;

	//Calculate two possible overlap ranges
	//left or right
	_float d0 = maxB - minA;//left case
	_float d1 = maxA - minB;//right case

						   //Intervals do not overlap -> no interaction
	if (d0 <= 0.f || d1 <= 0.f)
		return false;

	return true;
}

_float CMathHelper::RandomFloatRange(_float min, _float max)
{
	srand(static_cast <unsigned> (time(0)));
	return min + static_cast<_float>(rand()) / (static_cast<_float>(RAND_MAX / (max - min)));
}

_int CMathHelper::RandomIntRange(_int min, _int max)
{
	srand(static_cast <unsigned> (time(0)));
	return min + static_cast<_int>(rand()) / (static_cast<_int>(INT_MAX / (max - min)));
}

void CMathHelper::OnDestroy(void)
{
}
