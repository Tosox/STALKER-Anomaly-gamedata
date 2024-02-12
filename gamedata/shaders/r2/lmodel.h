#ifndef	LMODEL_H
#define LMODEL_H

#include "common.h"
#include "common_brdf.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Lighting formulas
float4 compute_lighting(float3 N, float3 V, float3 L, float4 alb_gloss, float mat_id)
{
	//float vector
  	float3 H = normalize(L+V);
		
	//Combined light
	float4 light = tex3D(s_material, float3(dot(L,N), dot(H,N), mat_id));
	
	if(mat_id == MAT_FLORA) //Be aware of precision loss/errors
	{
		//Simple subsurface scattering
		float subsurface = SSS(N,V,L);
		light.rgb += subsurface;
	}	

	return light;
}

float4 plight_infinity( float m, float3 pnt, float3 normal, float4 c_tex, float3 light_direction )
{
	//gsc vanilla stuff
	float3 N = normalize(normal);							// normal 
  	float3 V = -normalize(pnt);					// vector2eye
  	float3 L = -normalize(light_direction);						// vector2light

	float4 light = compute_lighting(N,V,L,c_tex,m);
	
	return light; // output (albedo.gloss)
}

float4 plight_local( float m, float3 pnt, float3 normal, float4 c_tex, float3 light_position, float light_range_rsq, out float rsqr )
{
	float3 N		= normalize(normal);							// normal 
	float3 L2P 	= pnt - light_position;                         		// light2point 
	float3 V 		= -normalize	(pnt);					// vector2eye
	float3 L 		= -normalize	((float3)L2P);					// vector2light
	rsqr	= dot		(L2P,L2P);					// distance 2 light (squared)
	float  att 	= saturate	(1 - rsqr*light_range_rsq);			// q-linear attenuate

	float4 light = compute_lighting(N,V,L,c_tex,m);
	
	return att*light; // output (albedo.gloss)
}

float4 	plight_infinity2	(float m, float3 ppoint, float3 normal, float3 light_direction)       				{
  	float3 N		= normal;							// normal 
  	float3 V 	= -normalize		(ppoint);		// vector2eye
  	float3 L 	= -light_direction;					// vector2light
 	float3 H		= normalize			(L+V);			// float-angle-vector 
	float3 R     = reflect         	(-V,N);
	float 	s	= saturate(dot(L,R));
			s	= saturate(dot(H,N));
	float 	f 	= saturate(dot(-V,R));
			s  *= f;
	float4	r	= tex3D 			(s_material,	float3( dot(L,N), s, m ) );	// sample material
			r.w	= pow(saturate(s),4);
  	return	r	;
}

float3 specular_phong(float3 pnt, float3 normal, float3 light_direction)
{
	return L_sun_color.rgb * pow( abs( dot(normalize(pnt + light_direction), normal) ), 256.0);
}

float4	blendp	(float4	value, float4 	tcp)    		{
	#ifndef FP16_BLEND  
		value 	+= (float4)tex2Dproj 	(s_accumulator, tcp); 	// emulate blend
	#endif
	return 	value	;
}
float4	blend	(float4	value, float2 	tc)			{
	#ifndef FP16_BLEND  
		value 	+= (float4)tex2D 	(s_accumulator, tc); 	// emulate blend
	#endif
	return 	value	;
}

#endif
