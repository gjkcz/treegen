#ifndef __SIMPLEVERTEX_H_INCLUDED__
#define __SIMPLEVERTEX_H_INCLUDED__


#include <d3dx9math.h>

struct SimpleVertex
{
    D3DXVECTOR3 Pos;  // Position
    D3DXVECTOR3 Normal; // Light Normal
    D3DXVECTOR4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};


#endif // __SIMPLEVERTEX_H_INCLUDED__
