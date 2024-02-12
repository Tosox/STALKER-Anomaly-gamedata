#ifndef        COMMON_H
#define        COMMON_H


#include "shared\common.h"
#include "anomaly_shaders.h"
#include "common_defines.h"
#include "common_iostructs.h"
#include "common_samplers.h"
#include "common_cbuffers.h"
#include "common_functions.h"

//////////////////////////////////////////////////////////////////////////////////////////


#ifdef        USE_R2_STATIC_SUN
#  define xmaterial float(1.0h/4.h)
#else
#  define xmaterial float(L_material.w)
#endif
#define USE_SUNMASK
//////////////////////////////////////////////////////////////////////////////////////////

uniform float4                J_direct        [6];
uniform float4                J_spot                [6];

float2         calc_detail                (float3 w_pos)      {
        float                 dtl        = distance                (w_pos,eye_position)*dt_params.w;
                              dtl        = min              (dtl*dtl, 1);
        float                  dt_mul     = 1  - dtl;        // dt*  [1 ..  0 ]
        float                  dt_add     = .5 * dtl;        // dt+  [0 .. 0.5]
        return                float2      (dt_mul,dt_add);
}

//////////////////////////////////////////////////////////////////////////////////////////
struct                  f_deffer        		{
        float4           position        		: COLOR0;        // px,py,pz, m-id
        float4           Ne                		: COLOR1;        // nx,ny,nz, hemi
        float4       	C                		: COLOR2;        // r, g, b,  gloss
};
//////////////////////////////////////////////////////////////////////////////////////////
struct  				p_screen                {
        float4          hpos               		: POSITION;
        float2          tc0                		: TEXCOORD0;        // Texture coordinates         (for sampling maps)
};

#define FXPS technique _render{pass _code{PixelShader=compile ps_3_0 main();}}
#define FXVS technique _render{pass _code{VertexShader=compile vs_3_0 main();}}

#endif
