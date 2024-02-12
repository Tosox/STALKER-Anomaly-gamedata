#ifndef	MBLUR_H
#define MBLUR_H

#ifndef 	USE_MBLUR
float3 	mblur	(float2 UV, float3 pos, float3 c_original)	{ return c_original; }
#else

#include "common.h"
////////////////////////////////////////
float4x4 m_current; //Current projection matrix
float4x4 m_previous; //Previous projection matrix
float2 m_blur;	
////////////////////////////////////////

float3 mblur(float2 UV, float3 pos, float3 img)	
{
	//Fix sky ghosting caused by infinite depth value (KD)
	pos.z += (saturate(0.001 - pos.z)*10000.h);
	
	//Sample position buffer
	float4 pos4 = float4(pos, 1.0);
	
	//Get current texture coordinates
	float4 p_current = mul(m_current, pos4);
	float2 current_tc = p_current.xy /= p_current.w;
	
	//Get previous texture coordinates
	float4 p_previous = mul(m_previous, pos4);
	float2 previous_tc = p_previous.xy / p_previous.w;
	
	//Get velocity (multiplied with motion blur intensity)
	float2 p_velocity = (current_tc - previous_tc) * m_blur;
	p_velocity = clamp(p_velocity,-MBLUR_CLAMP,+MBLUR_CLAMP);
	
	//Small hud attenuation
	#ifdef MBLUR_WPN
    if (pos.z < 1.4) // disable for hud
        p_velocity = 0.0;
	#endif
		
	//Accumulate motion blur samples
	float3 accum = (0.0, 0.0, 0.0);
	
	//gimme ze blur
	for (int i = 0; i < MBLUR_SAMPLES; i++)
	{
		accum += s_image.Sample(smp_rtlinear, p_velocity * float(i) + UV).rgb;
	}
	accum /= MBLUR_SAMPLES;
	
	//Add our blur to image. Possibly use some mask in future
	return lerp(img, accum, 1.0);
}
#endif
#endif