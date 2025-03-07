/*
	Common functions used by lighting 
	Material table
	
	/////////////////
	Anomaly Team 2020
	/////////////////
*/
#include "common.h"

////////////////////////
//Material table
#define MAT_FLORA 6.0

////////////////////////
//Simple subsurface scattering with float-Lambert

//Author: LVutner
float SSS(float3 N, float3 V, float3 L)
{
	const float SSS_DIST = 0.5; //Scattering distortion
	const float SSS_AMB = 0.5; //Scattering ambient
		
    float3 SSS_vector = L + N * SSS_DIST;
    float SSS_light = saturate(dot(V, -SSS_vector)) * 0.5 + 0.5; //float-Lambert approx.	
    return SSS_light + SSS_AMB; //Add some ambient
}
