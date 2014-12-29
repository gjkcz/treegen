#ifndef __SIMPLEVERTEX_H_INCLUDED__
#define __SIMPLEVERTEX_H_INCLUDED__


#include <xnamath.h>

struct SimpleVertex
{
    XMFLOAT3 Pos;  // Position
    XMFLOAT3 Normal; // Light Normal
    XMFLOAT4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};


#endif // __SIMPLEVERTEX_H_INCLUDED__
