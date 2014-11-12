#ifndef __SVERTEX__
#define __SVERTEX__
#include <xnamath.h>

struct SimpleVertex
{
    XMFLOAT3 Pos;  // Position
    XMFLOAT3 Normal; // Light Normal
    XMFLOAT4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};
#endif // __SVERTEX__
