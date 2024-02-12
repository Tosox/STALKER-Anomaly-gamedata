#ifndef	common_defines_h_included
#define	common_defines_h_included

//////////////////////////////////////////////////////////////////////////////////////////
// Defines                                		//
#define def_gloss       float(2.0 /255.0)
#define def_aref        float(200.0/255.0)
#define def_dbumph      float(0.333)
#define def_virtualh    float(0.05)              // 5cm
#define def_distort     float(0.05)             // we get -0.5 .. 0.5 range, this is -512 .. 512 for 1024, so scale it
#define def_hdr         float(9.0)         		// hight luminance range float(3.h)
#define def_hdr_clip	float(0.75)        		//
#define def_lum_hrange	float(0.7)	// hight luminance range

//////////////////////////////////////////////////////////////////////////////////////////
#ifndef SMAP_size
#define SMAP_size        2048
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//#define SKY_WITH_DEPTH					// sky renders with depth to avoid some problems with reflections
#define SKY_DEPTH float(10000.0)
#define SKY_EPS float(0.001)
#define FARPLANE float(180.0)

//INTERNAL
#define USABLE_BIT_1 uint(0x00002000)
#define USABLE_BIT_2 uint(0x00004000)
#define USABLE_BIT_3 uint(0x00008000)
#define USABLE_BIT_4 uint(0x00010000)
#define USABLE_BIT_5 uint(0x00020000)
#define USABLE_BIT_6 uint(0x00040000)
#define USABLE_BIT_7 uint(0x00080000)
#define USABLE_BIT_8 uint(0x00100000)
#define USABLE_BIT_9 uint(0x00200000)
#define USABLE_BIT_10 uint(0x00400000)
#define USABLE_BIT_11 uint(0x00800000)   // At least two of those four bit flags must be mutually exclusive (i.e. all 4 bits must not be set together)
#define USABLE_BIT_12 uint(0x01000000)   // This is because setting 0x47800000 sets all 5 FP16 exponent bits to 1 which means infinity
#define USABLE_BIT_13 uint(0x02000000)   // This will be translated to a +/-MAX_FLOAT in the FP16 render target (0xFBFF/0x7BFF), overwriting the 
#define USABLE_BIT_14 uint(0x04000000)   // mantissa bits where other bit flags are stored.
#define USABLE_BIT_15 uint(0x80000000)
#define MUST_BE_SET uint(0x40000000)   // This flag *must* be stored in the floating-point representation of the bit flag to store


#endif	//	common_defines_h_included