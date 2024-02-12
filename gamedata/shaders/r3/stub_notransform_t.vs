#include "common.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Vertex
v2p_TL main ( v_TL_positiont I )
{
	v2p_TL O;
	{
		I.P.xy += 0.5f; //offset

		O.HPos.x = I.P.x * screen_res.z * 2 - 1;
		O.HPos.y = (I.P.y * screen_res.w * 2 - 1)*-1;
		O.HPos.zw = I.P.zw;
	}

	O.Tex0 = I.Tex0;
	O.Color = I.Color.bgra;	//	swizzle vertex colour

 	return O;
}