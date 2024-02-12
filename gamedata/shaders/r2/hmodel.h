#ifndef        HMODEL_H
#define HMODEL_H

#include "common.h"

uniform samplerCUBE         env_s0                ;
uniform samplerCUBE         env_s1                ;
uniform samplerCUBE         sky_s0                ;
uniform samplerCUBE         sky_s1                ;
uniform float4                         env_color        ;        // color.w  = lerp factor
uniform float4 hmodel_stuff;  //x - hemi vibrance // y - hemi contrast // z - wet surface factor

void        hmodel                 (out float3 hdiffuse, out float3 hspecular, float m, float h, float s, float3 ppoint, float3 normal)
{
		normal = normalize(normal);
        // hscale - something like diffuse reflection
        float3         nw                         = mul                 (m_inv_V,normal);
        float         hscale                 = h;                                //. *        (.5h + .5h*nw.y);
#ifdef         USE_GAMMA_22
                        hscale                = (hscale*hscale);        // make it more linear
#endif

        // reflection vector
        float3        v2pointL        		= normalize        (ppoint);
        float3         v2point               = mul                (m_inv_V,v2pointL);
        float3        vreflect        		= reflect         (v2point,nw);
        float         hspec                 	= .5h+.5h*dot        (vreflect,v2point);

        // material
          float4         light                = tex3D                (s_material, float3(hscale, hspec, m) );                // sample material

        // diffuse color
        float3         e0d               = texCUBE         (env_s0,nw);
        float3         e1d               = texCUBE         (env_s1,nw);
        float3         env_d             = env_color.xyz*lerp(e0d,e1d,env_color.w)        ;
			env_d	*=env_d;
			
        hdiffuse                        = env_d * light.xyz + L_ambient.rgb;

        // specular color
	     float3 vreflectabs    = abs(vreflect);
        float  vreflectmax    = max(vreflectabs.x, max(vreflectabs.y, vreflectabs.z));
            vreflect      /= vreflectmax;
        if (vreflect.y < 0.999)    
            vreflect.y= vreflect.y*2-1;     // fake remapping 
                                                                  // fake remapping
        float3         e0s               = texCUBE         (env_s0,vreflect);
        float3         e1s               = texCUBE         (env_s1,vreflect);
        float3         env_s             = env_color.xyz*lerp(e0s,e1s,env_color.w)        ;
			env_s	*=env_s;
			
	float luminance = 1-dot( light.rgb, float3(LUMINANCE_VECTOR) );

	hspecular	= env_s*light.w*(s+(rain_params.x*0.25))*luminance*15*(rain_params.x*2);

}
#endif
