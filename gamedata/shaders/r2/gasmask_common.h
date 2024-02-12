#ifndef GASMASK_COMMON_H
#define GASMASK_COMMON_H

/*
	Gasmask overlay shader
	
	Credits: ZHC (visor reflection)

	/////////////////
	Anomaly Team 2020
	/////////////////
*/

//Main gasmask textures
uniform sampler2D s_mask_nm_1;
uniform sampler2D s_mask_nm_2;
uniform sampler2D s_mask_nm_3;
uniform sampler2D s_mask_nm_4;
uniform sampler2D s_mask_nm_5;
uniform sampler2D s_mask_nm_6;
uniform sampler2D s_mask_nm_7;
uniform sampler2D s_mask_nm_8;
uniform sampler2D s_mask_nm_9;
uniform sampler2D s_mask_nm_10;

//Vignette masks
uniform sampler2D s_mask_v_1;
uniform sampler2D s_mask_v_2;
uniform sampler2D s_mask_v_3;

//Condensation droplets texture
uniform sampler2D s_mask_droplets;

//Constants from engine
uniform float4 mask_control; 
uniform float3 drops_control;

//Gasmask settings
#define GM_DIST_INT 0.05 //Refraction intensity
#define GM_DIFF_INT 0.25 //Diffuse cracks intensity
#define GM_VIG_INT 0.5 //Vignette intensity

//Raindrops settings
#define GM_DROPS_TURBSIZE 15.f //Turbulence power
#define GM_DROPS_TURBSHIFT float4(0.35, 1, 0, 1) //Turbulence offset
#define GM_DROPS_TURBTIME sin(0.1/3.f) 
#define GM_DROPS_TURBCOF 0.33 //Turbulence intensity

//Glass reflections settings
#define GM_VIS_NUM 16 //Reflection quality
#define GM_VIS_RADIUS 0.45 //Reflection radius
#define GM_VIS_INTENSITY 0.50 //Reflection intensity

#endif