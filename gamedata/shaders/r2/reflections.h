#ifndef REFLECTIONS_H
#define REFLECTIONS_H

uniform samplerCUBE s_env0;
uniform samplerCUBE s_env1;

float3 calc_envmap(float3 vreflect)
{
	vreflect.y = vreflect.y*2-1;
	float3	env0	= texCUBElod (s_env0, float4(vreflect.xyz, 0)).xyz;
	float3	env1	= texCUBElod (s_env1, float4(vreflect.xyz, 0)).xyz;
	return lerp (env0,env1,L_ambient.w);
}
#endif