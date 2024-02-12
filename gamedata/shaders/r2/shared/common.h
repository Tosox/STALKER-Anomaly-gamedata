//////////////////////////////////////////////////
//  All comments by Nivenhbro are preceded by !
/////////////////////////////////////////////////


#ifndef SHARED_COMMON_H
#define SHARED_COMMON_H
//
uniform float3x4		m_W;
uniform float3x4		m_V;
uniform float3x4 m_inv_V;
uniform float4x4 	m_P;
uniform float3x4		m_WV;
uniform float4x4 	m_VP;
uniform float4x4 	m_WVP;
uniform float4x4 	m_texgen;
uniform float4x4 	mVPTexgen;
uniform float4		timers;
uniform float4		fog_plane;
uniform float4		fog_params;		// x=near*(1/(far-near)), ?,?, w = -1/(far-near)
uniform float4		fog_color;
uniform float3		L_sun_color;
uniform float3		L_sun_dir_w;
uniform float3		L_sun_dir_e;
uniform float4		L_hemi_color;
uniform float4		L_ambient;		// L_ambient.w = skynbox-lerp-factor
uniform float3 		eye_position;
uniform float3		eye_direction;
uniform float3		eye_normal;
uniform	float4 		dt_params;
uniform float4		hemi_cube_pos_faces;
uniform float4		hemi_cube_neg_faces;
uniform float4 		L_material;                            // 0,0,0,mid
uniform float4		parallax;
uniform float3		rain_params; //x = raindensity, y = wetness 
uniform float4		pp_img_corrections;
uniform float4		pp_img_cg;
uniform float4		actor_data;	
uniform float4 screen_res;	
	
float3 	unpack_normal	(float3 v)	{ return 2*v-1;			}
float3 	unpack_bx2	(float3 v)	{ return 2*v-1; 		}
float3 	unpack_bx4	(float3 v)	{ return 4*v-2; 		} //!reduce the amount of stretching from 4*v-2 and increase precision

float2 	unpack_tc_base	(float2 tc, float du, float dv)		{
		return (tc.xy + float2	(du,dv))*(32.f/32768.f);	//!Increase from 32bit to 64bit floating point
}

float2 	unpack_tc_lmap	(float2 tc)	{ return tc*(1.f/32768.f);	} // [-1  .. +1 ] 

float 	calc_cyclic 	(float x)				{
	float 	phase 	= 1/(2*3.141592653589f);
	float 	sqrt2	= 1.4142136f;
	float 	sqrt2m2	= 2.8284271f;
	float 	f 	= sqrt2m2*frac(x)-sqrt2;	// [-sqrt2 .. +sqrt2] !No changes made, but this controls the grass wave (which is violent if I must say)
	return 	f*f - 1.f;				// [-1     .. +1]
}
float2 	calc_xz_wave 	(float2 dir2D, float frac)		{
	// Beizer
	float2  ctrl_A	= float2(0.f,		0.f	);
	float2 	ctrl_B	= float2(dir2D.x,	dir2D.y	);
	return  lerp	(ctrl_A, ctrl_B, frac);			//!This calculates tree wave. No changes made
}

#endif
