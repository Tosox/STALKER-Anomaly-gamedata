#ifndef	LMODEL_H
#define LMODEL_H

#include "common.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Lighting formulas
float3 specular_phong(float3 pnt, float3 normal, float3 light_direction)
{
	return L_sun_color.rgb * pow( abs( dot(normalize(pnt + light_direction), normal) ), 256.0);
}


#endif