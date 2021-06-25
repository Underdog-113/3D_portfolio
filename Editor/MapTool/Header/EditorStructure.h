
typedef struct _Hit_Info
{
	enum Strength { Str_Damage, Str_Low, Str_High, Str_Airborne };
	enum CrowdControl { CC_None, CC_Stun, CC_Airborne };

	GETTOR_SETTOR(_float, damageRate, 1.f, DamageRate)
		GETTOR_SETTOR(Strength, strength, Str_Damage, StrengthType)
		GETTOR_SETTOR(CrowdControl, statEffect, CC_None, CrowdControlType)
}HitInfo;